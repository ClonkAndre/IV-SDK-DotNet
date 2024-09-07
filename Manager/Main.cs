using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Net;
using System.Reflection;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Numerics;

using Newtonsoft.Json;

using IVSDKDotNet;
using IVSDKDotNet.Attributes;
using IVSDKDotNet.Enums;
using IVSDKDotNet.Manager;

using Manager.Classes;
using Manager.Classes.Json;
using Manager.Managers;
using Manager.UI;

namespace Manager
{
    public class Main : ManagerScript
    {
        #region Variables
        internal static Main Instance;

        // Lists
        public Queue<Action> ActionQueue;

        public List<FoundScript> ActiveScripts;
        public List<AdvancedTask> ActiveTasks;
        public List<DelayedAction> DelayedActions;
        
        public List<string> TierOneSupporters;
        public List<string> TierTwoSupporters;
        public List<string> TierThreeSupporters;

        public List<IntPtr> GlobalRegisteredTextures; // For any texture that couldn't be assigned to any script

        // Managers
        public PluginManager ThePluginManager;
        public RemoteConnectionManager ConnectionManager;

        // UI
        public ConsoleUI Console;
        public NotificationUI Notification;

        // Hooks
        private KeyWatchDog[] keyWatchDogs;

        // Debug
        public bool DisableKeyEvents;
        public bool ThrowOnError;
        public bool DoNotResetImGuiStyle;

        // Other
        public Version CurrentWrapperVersion;
        public UpdateChecker UpdateChecker;
        public WebClient downloadClient;
        public Process GTAIVProcess;
        public DateTime TimeSinceLastScriptReload;
        private Guid processCheckerTimerID;

        public bool FirstFrame = true;
        public bool IsGTAIVWindowInFocus;
        public bool OnWindowFocusChangedEventCalled;
        public bool WasBoundPhoneNumbersProcessed;
        private int lastLogLineCount;

        public int MainThreadID;

        private readonly object activeScriptsLockObj = new object();

#if PREVIEW
        private SettingsFile previewDatFile;
        private bool showPreviewDialog = true;
#endif

        #endregion

        #region Events

        // Assembly
        private Assembly CurrentDomain_AssemblyResolve(object sender, ResolveEventArgs args)
        {
            string assemblyName = args.Name.Split(',')[0];
            string assemblyPath = string.Format("{0}\\{1}.dll", CLR.CLRBridge.IVSDKDotNetBinaryPath, assemblyName);

            if (assemblyName.EndsWith(".resources"))
            {
                Logger.LogDebug(string.Format("Was searching for a resources file with the name {0}. Skipping.", assemblyName));
                return null;
            }

            Logger.LogDebug(string.Format("Trying to resolve assembly {0}...", assemblyName));

            if (File.Exists(assemblyPath))
                return Assembly.UnsafeLoadFrom(assemblyPath);
            else
                Logger.LogError(string.Format("Could not find required assembly {0} which should be in the IVSDKDotNet > bin folder! Game might crash!", assemblyName));

            return null;
        }

        // UpdateChecker
        private void UpdateChecker_VersionCheckFailed(Exception e)
        {
            Notification.ShowNotification(NotificationType.Error, DateTime.UtcNow.AddSeconds(5), "An error occured while checking for IV-SDK .NET updates", "Check the IV-SDK .NET console for more details.", "UPDATE_CHECK_FAILED");
            Logger.LogError(string.Format("Error while checking for updates. Details: {0}", e.ToString()));
        }
        private void UpdateChecker_VersionCheckCompleted(UpdateChecker.VersionCheckInfo result)
        {
            if (result.NewVersionAvailable)
            {
                Notification.ShowNotification(NotificationType.Default, DateTime.UtcNow.AddSeconds(7), "New IV-SDK .NET update available!", string.Format("Version {0} of IV-SDK .NET is available to download.", result.NewVersion), "NEW_UPDATE_AVAILABLE");
                Logger.Log(string.Format("Version {0} of IV-SDK .NET is available!", result.NewVersion));
            }
            else
            {
                Logger.Log("There is currently no new IV-SDK .NET update available.");

                if (!result.IsSilentCheck)
                    Notification.ShowNotification(NotificationType.Default, DateTime.UtcNow.AddSeconds(7), "No new IV-SDK .NET update available", "There is currently no new IV-SDK .NET update available.", "NO_NEW_UPDATE_AVAILABLE");
            }
        }

        // DownloadClient
        private void DownloadClient_DownloadStringCompleted(object sender, DownloadStringCompletedEventArgs e)
        {
            if (e.Error != null)
            {
                Logger.LogError(string.Format("An error occured while trying to gather some basic information!{0}" +
                    "The thing that failed: {1}{0}" +
                    "Details: {2}", Environment.NewLine, e.UserState == null ? "UNKNOWN" : e.UserState, e.Error));
                return;
            }

            try
            {
                switch (e.UserState.ToString())
                {
                    case "GET_TIER_ONE_SUPPORTERS":
                        {
                            string data = e.Result;

                            if (!string.IsNullOrWhiteSpace(data))
                                TierOneSupporters = JsonConvert.DeserializeObject<List<string>>(data);

                            downloadClient.DownloadStringAsync(new Uri("https://www.dropbox.com/scl/fi/lvt1vd1uvkn7noalsw483/TierTwoSupporter.json?rlkey=7kdoynmiep0nilnyqqbib4s1e&dl=1"), "GET_TIER_TWO_SUPPORTERS");
                        }
                        break;
                    case "GET_TIER_TWO_SUPPORTERS":
                        {
                            string data = e.Result;

                            if (!string.IsNullOrWhiteSpace(data))
                                TierTwoSupporters = JsonConvert.DeserializeObject<List<string>>(data);

                            downloadClient.DownloadStringAsync(new Uri("https://www.dropbox.com/scl/fi/6ey0rb7uib8bxd8t0suy3/TierThreeSupporter.json?rlkey=33svhsggspdvbwdnpcnx684j4&dl=1"), "GET_TIER_THREE_SUPPORTERS");
                        }
                        break;
                    case "GET_TIER_THREE_SUPPORTERS":
                        {
                            string data = e.Result;

                            if (!string.IsNullOrWhiteSpace(data))
                                TierThreeSupporters = JsonConvert.DeserializeObject<List<string>>(data);

                            Logger.LogDebug("Got all supporters!");
                        }
                        break;
                }
            }
            catch (Exception ex)
            {
                Logger.LogError(string.Format("An error occured while trying to process basic information!{0}" +
                    "Details: {1}", Environment.NewLine, ex));
            }
        }

        #endregion

        #region Constructor
        public Main()
        {
            // Set instance
            Instance = this;

            // Get current IVSDKDotNet Version
            CurrentWrapperVersion = typeof(IVSDKDotNet.IVAchievements).Assembly.GetName().Version;

            // Subscribe to AppDomain events
            AppDomain.CurrentDomain.AssemblyResolve += CurrentDomain_AssemblyResolve;

            // Lists
            ActionQueue =                   new Queue<Action>();

            ActiveScripts =                 new List<FoundScript>();
            ActiveTasks =                   new List<AdvancedTask>();
            DelayedActions =                new List<DelayedAction>();

            TierOneSupporters =             new List<string>();
            TierTwoSupporters =             new List<string>();
            TierThreeSupporters =           new List<string>();

            GlobalRegisteredTextures =      new List<IntPtr>();

            // Managers
            ThePluginManager =  new PluginManager();
            ConnectionManager = new RemoteConnectionManager();

            // UI
            Console = new ConsoleUI();
            Console.OnConsoleCommand += Console_OnConsoleCommand;
            Notification = new NotificationUI();

            SetUpKeyWatchDogs();

            // Other
            UpdateChecker = new UpdateChecker(CLR.CLRBridge.Version, "https://www.dropbox.com/s/smaz6ij8dkzd7nh/version.txt?dl=1");
            UpdateChecker.VersionCheckFailed +=     UpdateChecker_VersionCheckFailed;
            UpdateChecker.VersionCheckCompleted +=  UpdateChecker_VersionCheckCompleted;

            downloadClient = new WebClient();
            downloadClient.DownloadStringCompleted += DownloadClient_DownloadStringCompleted;

            GTAIVProcess = Process.GetCurrentProcess();

            // ScriptHookDotNet stuff
            SHDNStuff.LoadIncludedScriptHookDotNetAssembly();
            SHDNStuff.Init();

            // Init Reflection
            if (Reflection.Initialize())
                Logger.LogDebug("Initialized Reflection class.");
            else
                Logger.LogDebug("Failed to initialize Reflection class!");

            // Start process in focus checker timer
            processCheckerTimerID = StartNewTimerInternal(1000, () =>
            {

                if (!Reflection.IsCallOnWindowFocusChangedAvailable())
                {
                    AbortTaskOrTimer(processCheckerTimerID);
                    return;
                }

                IsGTAIVWindowInFocus = Helper.ProcessHelper.IsProcessInFocus(GTAIVProcess);

                // Invoke focus changed event
                if (IsGTAIVWindowInFocus)
                {
                    if (!OnWindowFocusChangedEventCalled)
                    {
                        Reflection.CallOnWindowFocusChanged(true);
                        OnWindowFocusChangedEventCalled = true;
                    }
                }
                else
                {
                    if (OnWindowFocusChangedEventCalled)
                    {
                        Reflection.CallOnWindowFocusChanged(false);
                        OnWindowFocusChangedEventCalled = false;
                    }
                }

            });

#if PREVIEW
            // Preview build stuff
            string previewDatFilePath = CLR.CLRBridge.IVSDKDotNetDataPath + "\\preview.dat";
            previewDatFile = new SettingsFile(previewDatFilePath);

            if (File.Exists(previewDatFilePath))
            {
                previewDatFile.Load();

                // Check if loaded file is valid
                if (!previewDatFile.DoesSectionExists("Preview"))
                {
                    previewDatFile.Clear();
                    previewDatFile.AddSection("Preview");
                    previewDatFile.AddKeyToSection("Preview", "Version");
                    return;
                }

                // Check if dialog was already shown for current preview version
                if (previewDatFile.GetValue("Preview", "Version", "0") == CLR.CLRBridge.Version)
                    showPreviewDialog = false;
            }
            else
            {
                try
                {
                    File.Create(previewDatFilePath).Dispose();
                    previewDatFile.AddSection("Preview");
                    previewDatFile.AddKeyToSection("Preview", "Version");
                }
                catch (Exception){}
            }
#endif
        }
        #endregion

        #region Raisers
        public override void RaiseTick()
        {
            if (Config.PauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

            // Get ID of this thread
            MainThreadID = System.Threading.Thread.CurrentThread.ManagedThreadId;

            // Cleanup ScriptHookDotNet cache
            SHDNStuff.ProcessCache();

            // Load ScriptHookDotNet scripts on first frame
            if (!SHDNStuff.WereScriptHookDotNetScriptsLoadedThisSession)
            {
                LoadSHDNScripts();
                SHDNStuff.WereScriptHookDotNetScriptsLoadedThisSession = true;
            }

            // Check for key presses for ScriptHookDotNet scripts
            if (keyWatchDogs != null)
                keyWatchDogs[1].Process();

            // Process stuff from queue
            if (ActionQueue.Count != 0)
                ActionQueue.Dequeue()?.Invoke();

            // Raise all IV-SDK .NET script Tick events
            ActiveScripts.ForEach(fs =>
            {
                try
                {
                    fs.RaiseTick();
                }
                catch (Exception ex)
                {
                    HandleScriptException(fs, 8d, "Tick", ex);
                }
            });

            // Process bound phone numbers of scripts
            IVPhoneInfo phoneInfo = IVPhoneInfo.ThePhoneInfo;

            if (phoneInfo != null)
            {
                switch ((ePhoneState)phoneInfo.State)
                {
                    case ePhoneState.Hidden:

                        // Reset state
                        WasBoundPhoneNumbersProcessed = false;

                        break;

                    case ePhoneState.CalledNumberBusy:

                        if (!WasBoundPhoneNumbersProcessed)
                        {

                            // Process dialed number
                            ActiveScripts.ForEach(fs =>
                            {
                                try
                                {
                                    fs.RaiseBoundPhoneNumberAction(phoneInfo.CurrentNumberInput);
                                }
                                catch (Exception ex)
                                {
                                    HandleScriptException(fs, 8d, "RaiseBoundPhoneNumberAction", ex, true);
                                }
                            });

                            WasBoundPhoneNumbersProcessed = true;
                        }

                        break;
                }
            }
        }
        public override void RaiseGameLoad()
        {
            ActiveScripts.ForEach(fs =>
            {
                try
                {
                    fs.RaiseGameLoad();
                }
                catch (Exception ex)
                {
                    HandleScriptException(fs, 8d, "GameLoad", ex);
                }
            });
        }
        public override void RaiseGameLoadPriority()
        {
            ActiveScripts.ForEach(fs =>
            {
                try
                {
                    fs.RaiseGameLoadPriority();
                }
                catch (Exception ex)
                {
                    HandleScriptException(fs, 8d, "GameLoadPriority", ex);
                }
            });
        }
        public override void RaiseMountDevice()
        {
            ActiveScripts.ForEach(fs =>
            {
                try
                {
                    fs.RaiseMountDevice();
                }
                catch (Exception ex)
                {
                    HandleScriptException(fs, 8d, "MountDevice", ex);
                }
            });
        }
        public override void RaiseDrawing()
        {
            // Save log file if content changed
            int currentLogLinesCount = Logger.GetLogItems().Count;
            if (lastLogLineCount != currentLogLinesCount)
            {
                lastLogLineCount = currentLogLinesCount;

                // Something changed, save log file
                SaveLogFile();
            }

            if (Config.PauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

            // Raise all script Drawing events
            ActiveScripts.ForEach(fs =>
            {
                try
                {
                    fs.RaiseDrawing();
                }
                catch (Exception ex)
                {
                    HandleScriptException(fs, 8d, "Drawing", ex);
                }
            });
        }
        public override void RaiseProcessCamera()
        {
            if (Config.PauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

            ActiveScripts.ForEach(fs =>
            {
                try
                {
                    fs.RaiseProcessCamera();
                }
                catch (Exception ex)
                {
                    HandleScriptException(fs, 8d, "ProcessCamera", ex);
                }
            });
        }
        public override void RaiseProcessAutomobile(UIntPtr vehPtr)
        {
            if (Config.PauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

            ActiveScripts.ForEach(fs =>
            {
                try
                {
                    fs.RaiseProcessAutomobile(vehPtr);
                }
                catch (Exception ex)
                {
                    HandleScriptException(fs, 8d, "ProcessAutomobile", ex);
                }
            });
        }
        public override void RaiseProcessPad(UIntPtr padPtr)
        {
            // Update the remote server
            ConnectionManager.Update();

            if (Config.PauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

            // Do stuff on first frame
            if (FirstFrame)
            {
                UpdateChecker.CheckForUpdates(true);
                GetSupporters();
                FirstFrame = false;
            }

            // Check for key presses for IV-SDK .NET scripts
            if (keyWatchDogs != null)
                keyWatchDogs[0].Process();

            // Raise all script ProcessPad events
            ActiveScripts.ForEach(fs =>
            {
                try
                {
                    fs.RaiseProcessPad(padPtr);
                }
                catch (Exception ex)
                {
                    HandleScriptException(fs, 8d, "ProcessPad", ex);
                }
            });
        }
        public override void RaiseOnD3D9Frame(IntPtr devicePtr, ImGuiIV_DrawingContext ctx)
        {
            DateTime dtNow = DateTime.UtcNow;

            // Execute Delayed Actions if there are any
            for (int i = 0; i < DelayedActions.Count; i++)
            {
                DelayedAction dA = DelayedActions[i];

                // When reloading the scripts, this could return NULL.
                // I think it could be because a script was starting a Task/Timer which when the script unloads,
                // will also get destroyed and at the end it starts a delayed action to fully get rid of it.
                // For now we just check if that's the case and then we just remove that delayed action entry from the list and continue :cowboy:

                if (dA == null)
                {
                    DelayedActions.RemoveAt(i);
                    continue;
                }

                if (dtNow >= dA.ExecuteIn)
                {
                    try
                    {
                        if (dA.ActionToExecute != null)
                        {
                            if (!string.IsNullOrEmpty(dA.Purpose))
                                Logger.LogDebug(string.Format("Delayed Action triggered. Purpose: {0}", dA.Purpose));
                            dA.ActionToExecute.Invoke(dA, dA.Parameter);
                        }
                        DelayedActions.RemoveAt(i);
                    }
                    catch (Exception ex)
                    {
                        Logger.LogError(string.Format("An error occured while executing delayed action. DA Purpose: {0}, Details: {1}", dA.Purpose, ex.ToString()));
                        DelayedActions.RemoveAt(i);
                    }
                }
            }

            // Reset ImGui style to default for script windows
            ResetImGuiStyle();

            // Raise all script OnImGuiRendering events
            ActiveScripts.ForEach(fs =>
            {
                try
                {
                    fs.RaiseOnImGuiRendering(devicePtr, ctx);
                }
                catch (Exception ex)
                {
                    HandleScriptException(fs, 8d, "OnImGuiRendering", ex);
                }

                // The script itself might've changed the style of ImGui so we need to reset it for the next script
                ResetImGuiStyle();
            });

            // Set internal custom style
            if (Config.UseCustomThemeForManagerAndConsole)
                SetImGuiPurpleStyle();

#if PREVIEW
            if (showPreviewDialog)
            {
                ImGuiIV.OpenPopup("IV-SDK .NET Preview Version");
                ImGuiIV.CreateSimplePopupDialog("IV-SDK .NET Preview Version",
                    string.Format("This is a preview version of IV-SDK .NET v{1}, which means it's only meant to be a preview of what to expect in the final update.{0}" +
                    "You usually only get this preview when you got an active Patreon/Ko-fi subscription. So if that's the case, thank you!{0}" +
                    "If you got this preview build from somewhere else, maybe consider supporting my work and get access to more preview stuff!{0}{0}" +
                    "If you encounter any bugs or got any suggestions, be sure to share them on my discord server or on the gtaforums IV-SDK .NET thread!", Environment.NewLine, CLR.CLRBridge.Version),
                    true,
                    true,
                    false,
                    "Understood",
                    null,
                    () =>
                    {
                        // Save that dialog was shown for current preview version
                        previewDatFile.SetValue("Preview", "Version", CLR.CLRBridge.Version);
                        previewDatFile.Save();

                        previewDatFile.Clear();
                        previewDatFile = null;
                        showPreviewDialog = false;
                    },
                    null);
            }
#endif

            // Draw internal stuff
            Console.DoUI();
            Notification.DoUI();
            ManagerUI.DoUI(devicePtr, ctx);
        }
        public override void RaiseOnBeforeNewImGuiFrame(IntPtr devicePtr)
        {
            // Create fonts that wait to be created and added
            if (SHDNStuff.FontsToBeCreated.Count != 0)
            {
                while (SHDNStuff.FontsToBeCreated.Count != 0)
                    SHDNStuff.FontsToBeCreated.Dequeue().Reload();
            }
        }
        public override void RaiseIngameStartup()
        {
            if (Config.ReloadScriptsOnReload)
            {
                LoadScripts();
                return;
            }

            // Raise all script IngameStartup events
            ActiveScripts.ForEach(fs =>
            {
                try
                {
                    fs.RaiseIngameStartup();
                }
                catch (Exception ex)
                {
                    HandleScriptException(fs, 8d, "IngameStartup", ex);
                }
            });
        }

        private void KeyWatchDog_KeyDown(object sender, KeyEventArgs e)
        {
            if (Config.PauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

            // Only do stuff here if event comes from IV-SDK .NET KeyWatchDog
            if (sender == keyWatchDogs[0])
            {
                // Raise local things
                if (Console != null)
                    Console.KeyDown(e);

                // Check stuff
                Checker.CheckSwitchCursorKeyPressed(e);
                Checker.CheckOpenManagerWindowKeyPressed(e);
            }

            if (DisableKeyEvents)
                return;

            // Raise all script KeyDown events
            ActiveScripts.ForEach(fs =>
            {
                try
                {
                    if (fs.IsScriptHookDotNetScript)
                    {
                        fs.RaiseKeyDown(sender, e);
                    }
                    else
                    {
                        if (fs.GetScriptAs<Script>().OnlyRaiseKeyEventsWhenInGame)
                        {
                            if (IVPlayerInfo.FindThePlayerPed() != UIntPtr.Zero)
                                fs.RaiseKeyDown(sender, e);
                        }
                        else
                        {
                            fs.RaiseKeyDown(sender, e);
                        }
                    }
                }
                catch (Exception ex)
                {
                    HandleScriptException(fs, 8d, "KeyDown", ex);
                }
            });
        }
        private void KeyWatchDog_KeyUp(object sender, KeyEventArgs e)
        {
            if (Config.PauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

            if (DisableKeyEvents)
                return;

            // Raise all script KeyUp events
            ActiveScripts.ForEach(fs =>
            {
                try
                {
                    if (fs.IsScriptHookDotNetScript)
                    {
                        fs.RaiseKeyUp(sender, e);
                    }
                    else
                    {
                        if (fs.GetScriptAs<Script>().OnlyRaiseKeyEventsWhenInGame)
                        {
                            if (IVPlayerInfo.FindThePlayerPed() != UIntPtr.Zero)
                                fs.RaiseKeyUp(sender, e);
                        }
                        else
                        {
                            fs.RaiseKeyUp(sender, e);
                        }
                    }
                }
                catch (Exception ex)
                {
                    HandleScriptException(fs, 8d, "KeyUp", ex);
                }
            });
        }

        private void Console_OnConsoleCommand(string command, string[] args)
        {
            ActiveScripts.ForEach(fs =>
            {
                fs.RaiseOnConsoleCommand(command, args);
            });
        }
        #endregion

        #region Methods

        // Load stuff
        public void LoadScriptsInternal()
        {
            LoadIVSDKDotNetScripts();

            // Load ScriptHookDotNet scripts
            if (SHDNStuff.WereScriptHookDotNetScriptsLoadedThisSession)
                LoadSHDNScripts();

            TimeSinceLastScriptReload = DateTime.Now;
        }
        public void LoadIVSDKDotNetScripts()
        {
            if (!Directory.Exists(CLR.CLRBridge.IVSDKDotNetScriptsPath))
            {
                Directory.CreateDirectory(CLR.CLRBridge.IVSDKDotNetScriptsPath);
                return;
            }

            // Abort currently loaded IV-SDK .NET scripts
            AbortScripts(ScriptType.IVSDKDotNet, AbortReason.Manager, false);

            // Load IV-SDK .NET scripts
            string[] scriptFiles = Directory.GetFiles(CLR.CLRBridge.IVSDKDotNetScriptsPath, "*.ivsdk.dll", SearchOption.TopDirectoryOnly);

            for (int i = 0; i < scriptFiles.Length; i++)
                LoadAssembly(scriptFiles[i]);

            // Log
            Logger.Log(string.Format("Finished loading {0} IV-SDK .NET scripts.", ActiveScripts.Count(x => x.IsIVSDKDotNetScript)));
        }
        public void LoadSHDNScripts()
        {
            if (CLR.CLRBridge.DisableScriptHookDotNetLoading)
            {
                Notification.ShowNotification(NotificationType.Warning, DateTime.UtcNow.AddSeconds(7d), "Could not load ScriptHookDotNet mods", "The IV-SDK .NET ScriptHookDotNet mod loader got disabled because the old ScriptHookDotNet is currently installed.", "SHDN_MOD_LOADING_IS_DISABLED");
                return;
            }
            if (!Config.LoadScriptHookDotNetScripts)
                return;

            string shdnScriptsPath = string.Format("{0}\\scripts", IVGame.GameStartupPath);

            if (!Directory.Exists(shdnScriptsPath))
                return;

            // Abort currently loaded ScriptHookDotNet scripts
            AbortScripts(ScriptType.ScriptHookDotNet, AbortReason.Manager, false);

            // Load ScriptHookDotNet scripts
            string[] scriptFiles = Directory.GetFiles(shdnScriptsPath, "*.net.dll", SearchOption.TopDirectoryOnly);

            for (int i = 0; i < scriptFiles.Length; i++)
                LoadAssembly(scriptFiles[i]);

            // Log
            Logger.Log(string.Format("Finished loading {0} ScriptHookDotNet scripts.", ActiveScripts.Count(x => x.IsScriptHookDotNetScript)));
        }

        public void LoadScript(string name)
        {
            if (!Directory.Exists(CLR.CLRBridge.IVSDKDotNetScriptsPath))
            {
                Directory.CreateDirectory(CLR.CLRBridge.IVSDKDotNetScriptsPath);
                return;
            }

            // Check if script with this name is already loaded
            FoundScript fs = GetFoundScript(name);

            if (fs == null)
            {

                // Get path to script file
                string scriptPath = string.Format("{0}\\{1}", CLR.CLRBridge.IVSDKDotNetScriptsPath, name);

                // Check if file exists
                if (!File.Exists(scriptPath))
                {
                    Logger.LogWarning(string.Format("File {0} does not exists in the scripts folder!", name));
                    return;
                }

                // Try to load script
                if (LoadAssembly(scriptPath))
                    Logger.Log(string.Format("Script {0} got loaded!", name));

            }
            else
            {
                Logger.LogWarning(string.Format("Script {0} is already loaded.", name));
            }
        }
        public bool LoadAssembly(string path)
        {
            if (string.IsNullOrWhiteSpace(path))
                return false;

            // Get file name with and without extension from given path
            string rawFileName =    Path.GetFileName(path);
            string fileName =       Path.GetFileNameWithoutExtension(path);

            // Check if fileName contains the .ivsdk AND .net part
            if (fileName.Contains(".ivsdk") && fileName.Contains(".net"))
            {
                Logger.LogWarning(string.Format("Couldn't determine for what kind of SDK the file {0} is supposed to be " +
                    "because it contains both the extensions for a IV-SDK .NET (.ivsdk) and for a ScriptHookDotNet (.net) script.", rawFileName));
                return false;
            }

            // Check for which SDK this script is supposed to be
            bool isIVSDKDotNetScript =      fileName.Contains(".ivsdk");
            bool isScriptHookDotNetScript = fileName.Contains(".net");

            // Check result
            if (!isIVSDKDotNetScript && !isScriptHookDotNetScript)
            {
                Logger.LogWarning(string.Format("The file '{0}' could not be recognized as a IV-SDK .NET Script because it's missing the '.ivsdk' extension.", rawFileName));
                return false;
            }

            // Remove extensions from file because we figured out for which SDK this script is
            fileName = fileName.Replace(".ivsdk", "").Replace(".net", "");

            // Check if script is already loaded
            FoundScript foundScript = GetFoundScript(fileName);

            if (foundScript != null)
            {
                Logger.LogWarning(string.Format("Not loading script '{0}' because it is already loaded.", fileName));
                return false;
            }

            // Try loading the Script
            try
            {
                using (FileStream fs = new FileStream(path, FileMode.Open, FileAccess.Read))
                {
                    Type scriptType = null;

                    // Get byte array from file stream
                    byte[] fileByteArray = Helper.GetByteArray(fs);

                    // Load the assembly into the domain
                    Assembly assembly = Assembly.Load(fileByteArray);

                    // If script is a ScriptHookDotNet script then handle it differently
                    if (isScriptHookDotNetScript)
                    {
                        Type[] shdnScriptTypes = assembly.GetTypes().Where(x => x.IsSubclassOf(typeof(GTA.Script))).ToArray();

                        if (shdnScriptTypes.Length == 0)
                        {
                            Logger.LogWarning(string.Format("Could not load ScriptHookDotNet script '{0}' because no entry-point could be found.", fileName));
                            return false;
                        }

                        for (int i = 0; i < shdnScriptTypes.Length; i++)
                        {
                            scriptType = shdnScriptTypes[i];

                            if (scriptType != null)
                            {
                                // Log
                                Logger.Log(string.Format("Found ScriptHookDotNet script: {0}", scriptType.FullName));

                                // Create new FoundScript object
                                // The FoundScript object does not actually get initialized fully.
                                // When the constructor of the GTA.Script gets called, it will handle the initialization of the FoundScript object (SHDN_LateInitializeScript function will get called).
                                foundScript = new FoundScript(fileName, path, assembly, scriptType);

                                // We need to put it in the list early for ScriptHookDotNet so the SHDN_LateInitializeScript function can find the script in the ActiveScripts list.
                                ActiveScripts.Add(foundScript);

                                // Create the script
                                GTA.Script shdnScript = (GTA.Script)assembly.CreateInstance(scriptType.FullName);

                                if (shdnScript == null)
                                {
                                    Logger.LogWarning(string.Format("Failed to create new instance of ScriptHookDotNet script '{0}'.", fileName));
                                    ActiveScripts.Remove(foundScript);
                                    foundScript = null;
                                    return false;
                                }

                                // Reset current constructing shdn script
                                SHDNStuff.SetCurrentScript(GTA.ScriptEvent.ctor, null);
                            }
                        }

                        return true;
                    }

                    // Get the first class that inherites from the IVSDKDotNet.Script class
                    scriptType = assembly.GetTypes().Where(x => x.IsSubclassOf(typeof(Script))).FirstOrDefault();

                    // Could not find any classes that inherit the IVSDKDotNet.Script class
                    if (scriptType == null)
                    {
                        Logger.LogWarning(string.Format("Could not load script '{0}' because the entry-point for IV-SDK .NET could not be found.", fileName));
                        return false;
                    }

                    // Log
                    Logger.Log(string.Format("Found script: {0}", scriptType.FullName));

                    // Check if script was made with an older IVSDKDotNetWrapper version and user wants to prevent older scripts from loading
                    if (Config.DoNotLoadLegacyScripts)
                    {
                        AssemblyName referencedWrapperAssembly = assembly.GetReferencedAssemblies().Where(x => x.Name == "IVSDKDotNetWrapper").FirstOrDefault();

                        if (referencedWrapperAssembly.Version < CurrentWrapperVersion)
                        {

                            Logger.LogWarning(string.Format("Script '{0}' did not get loaded because it was created with an older version of the IVSDKDotNetWrapper.dll ({1}) and the setting 'DoNotLoadLegacyScripts' is set to true." +
                                " The current version of the IVSDKDotNetWrapper.dll is: {2}", fileName, referencedWrapperAssembly.Version, CurrentWrapperVersion));

                            Notification.ShowNotification(NotificationType.Error, DateTime.UtcNow.AddSeconds(6d),
                                string.Format("Script {0} did not get loaded.", fileName),
                                "Check console for details.",
                                "COULD_NOT_LOAD_SCRIPT");

                            return false;
                        }
                    }

                    // Create new instance of type for assembly
                    Script script = (Script)assembly.CreateInstance(scriptType.FullName);

                    if (script == null)
                    {
                        Logger.LogWarning(string.Format("An unknown error occured while trying to create new instance of IV-SDK .NET script '{0}'.", fileName));
                        return false;
                    }

                    // Register AssemblyResolve event
                    script.ScriptDomain.AssemblyResolve += ScriptDomain_AssemblyResolve;

                    // Check for script settings file
                    string settingsFilePath = string.Format("{0}\\{1}.ini", CLR.CLRBridge.IVSDKDotNetScriptsPath, fileName);
                    if (File.Exists(settingsFilePath))
                    {
                        script.Settings = new SettingsFile(settingsFilePath);
                        script.Settings.Load();
                    }

                    // Check for script resource folder
                    string resourceFolderPath = string.Format("{0}\\{1}", CLR.CLRBridge.IVSDKDotNetScriptsPath, fileName);
                    if (Directory.Exists(resourceFolderPath))
                        script.ScriptResourceFolder = resourceFolderPath;

                    // Create new FoundScript object
                    foundScript = new FoundScript(fileName, path, assembly, script, scriptType);

                    // Get the script config of the script if it has one
                    foundScript.GetScriptConfig();

                    // TODO
                    //foundScript.CheckForExistenceOfReferencedAssemblies();

                    // Add script to ActiveScripts list.
                    ActiveScripts.Add(foundScript);

                    // Raise Initialize
                    try
                    {
                        foundScript.RaiseInitialized();
                    }
                    catch (Exception ex)
                    {
                        HandleScriptException(foundScript, 8d, "Initialized", ex);
                    }

                    return true;
                }
            }
            catch (ReflectionTypeLoadException ex)
            {
                Exception[] exs = ex.LoaderExceptions;
                for (int i = 0; i < exs.Length; i++)
                {
                    Exception e = exs[i];
                    Logger.LogError(string.Format("A ReflectionTypeLoadException occured while trying to load script '{0}'. Details: {1}", fileName, e));
                }

#if DEBUG
                // Throw on exception when manager is a debug build and a debugger is attached
                if (Debugger.IsAttached)
                    throw;
#endif
            }
            catch (Exception ex)
            {
                Logger.LogError(string.Format("An exception occured while trying to load script '{0}'. Details: {1}", fileName, ex));

#if DEBUG
                // Throw on exception when manager is a debug build and a debugger is attached
                if (Debugger.IsAttached)
                    throw;
#endif
            }

            return false;
        }

        private Assembly ScriptDomain_AssemblyResolve(object sender, ResolveEventArgs args)
        {
            FoundScript foundScript = null;

            try
            {
                if (args.RequestingAssembly == null)
                    return null;
                if (Path.GetExtension(args.Name.Split(new string[] { "," }, StringSplitOptions.None)[0]) == ".resources")
                    return null;

                // Get the name of the script that requests the target assembly and remove the .ivsdk suffix from name
                string requestingAssemblyName = args.RequestingAssembly.GetName().Name;

                if (requestingAssemblyName.ToLower().EndsWith(".ivsdk"))
                    requestingAssemblyName = requestingAssemblyName.Remove(requestingAssemblyName.Length - 6, 6);

                // Find the script that is requesting the assembly
                foundScript = GetFoundScript(requestingAssemblyName);

                if (foundScript.IsScriptHookDotNetScript)
                    return null;

                if (foundScript != null)
                {
                    Script script = foundScript.GetScriptAs<Script>();

                    string assemblyName = args.Name.Split(',')[0];
                    string scriptsDir = Path.GetDirectoryName(foundScript.FullPath);
                    string customDir = string.Format("{0}\\{1}", IVGame.GameStartupPath, script.CustomAssembliesPath);

                    string fileFullPath = string.Empty;

                    eAssembliesLocation scriptAssembliesLocation = script.AssembliesLocation;

                    // Debug
                    switch (scriptAssembliesLocation)
                    {
                        case eAssembliesLocation.Custom:
                            Logger.LogDebug(string.Format("Script {0} is requesting assembly {1} which should be in {2}", foundScript.EntryPoint.FullName, args.Name, customDir));
                            break;
                        default:
                            Logger.LogDebug(string.Format("Script {0} is requesting assembly {1} which should be in {2}", foundScript.EntryPoint.FullName, args.Name, scriptAssembliesLocation.ToString()));
                            break;
                    }

                    // Load Assembly by AssemblyLocation set by script
                    switch (scriptAssembliesLocation)
                    {

                        case eAssembliesLocation.GameRootDirectory:
                            Logger.LogWarning(string.Format("Script {0} was requesting assembly {1} but it was not found in the root directory of GTA IV! Aborting.", foundScript.EntryPoint.FullName, assemblyName));
                            break;

                        case eAssembliesLocation.ScriptsDirectory:

                            fileFullPath = string.Format("{0}\\{1}.dll", scriptsDir, assemblyName);
                            if (File.Exists(fileFullPath))
                                return Assembly.UnsafeLoadFrom(fileFullPath);

                            Logger.LogWarning(string.Format("Script {0} was requesting assembly {1} but it was not found in the scripts directory! Aborting.", foundScript.EntryPoint.FullName, assemblyName));
                            break;

                        case eAssembliesLocation.DecideManuallyForEachAssembly:

                            fileFullPath = script.RaiseAssemblyResolve(assemblyName);
                            if (File.Exists(fileFullPath))
                                return Assembly.UnsafeLoadFrom(fileFullPath);

                            Logger.LogWarning(string.Format("Script {0} was requesting assembly {1} but it was not found in directory ({2})! Aborting.", foundScript.EntryPoint.FullName, assemblyName, Path.GetDirectoryName(fileFullPath)));
                            break;

                        case eAssembliesLocation.Custom:

                            fileFullPath = string.Format("{0}\\{1}.dll", customDir, assemblyName);
                            if (File.Exists(fileFullPath))
                                return Assembly.UnsafeLoadFrom(fileFullPath);

                            Logger.LogWarning(string.Format("Script {0} was requesting assembly {1} but it was not found in the custom directory ({2})! Aborting.", foundScript.EntryPoint.FullName, assemblyName, script.CustomAssembliesPath));
                            break;
                    }

                }
                else
                {
                    Logger.LogWarning(string.Format("Could not find requesting script {0}! Assemblies couldn't get loaded for this script.", requestingAssemblyName));
                }
            }
            catch (Exception ex)
            {
                Logger.LogError(string.Format("An error occured while loading assembly {0} for Script {1}. Aborting. Details: {2}", args.Name, foundScript != null ? foundScript.EntryPoint.FullName : "UNKNOWN", ex.ToString()));
            }

            return null;
        }

        // Abort script stuff
        public void AbortScripts(ScriptType scriptsToAbort, AbortReason reason, bool showMessage)
        {
            if (ActiveScripts.Count == 0)
            {
                if (showMessage)
                    Logger.Log("There are no scripts to abort.");

                return;
            }

            switch (scriptsToAbort)
            {
                case ScriptType.All:

                    // IV-SDK .NET scripts
                    ActiveScripts.ForEach(x =>
                    {
                        if (x.IsIVSDKDotNetScript)
                            x.Abort(reason, showMessage);
                    });
                    ActiveScripts.RemoveAll(x => x.IsIVSDKDotNetScript);

                    // ScriptHookDotNet scripts
                    ActiveScripts.ForEach(x =>
                    {
                        if (x.IsScriptHookDotNetScript)
                            x.Abort(reason, showMessage);
                    });
                    ActiveScripts.RemoveAll(x => x.IsScriptHookDotNetScript);

                    // Get rid of registered textures that couldn't be assigned to any script
                    DestroyGlobalRegisteredTextures();

                    // Clear ScriptHookDotNet Cache
                    GTA.ContentCache.RemoveAll(true);

                    break;
                case ScriptType.IVSDKDotNet:

                    // IV-SDK .NET scripts
                    ActiveScripts.ForEach(x =>
                    {
                        if (x.IsIVSDKDotNetScript)
                            x.Abort(reason, showMessage);
                    });
                    ActiveScripts.RemoveAll(x => x.IsIVSDKDotNetScript);

                    break;
                case ScriptType.ScriptHookDotNet:

                    // ScriptHookDotNet scripts
                    ActiveScripts.ForEach(x =>
                    {
                        if (x.IsScriptHookDotNetScript)
                            x.Abort(reason, showMessage);
                    });
                    ActiveScripts.RemoveAll(x => x.IsScriptHookDotNetScript);

                    // Clear ScriptHookDotNet Cache
                    GTA.ContentCache.RemoveAll(true);

                    break;
            }

            // Force garbage collection
            GC.Collect();
            GC.WaitForPendingFinalizers();
            GC.Collect();
        }
        public void AbortScriptTasks(Guid scriptId)
        {
            AdvancedTask[] tasks = ActiveTasks.Where(x => x.OwnerID == scriptId).ToArray();

            if (tasks.Length == 0)
                return;

            for (int i = 0; i < tasks.Length; i++)
            {
                AdvancedTask advancedTask = tasks[i];

                advancedTask.PauseTimer = true;
                advancedTask.RequestCancellation();
            }
        }

        // DelayedAction
        public void StartDelayedAction(Guid id, string purpose, DateTime executeIn, Action<DelayedAction, object> actionToExecute, object parameter)
        {
            DelayedActions.Insert(DelayedActions.Count, new DelayedAction(id, purpose, executeIn, actionToExecute, parameter));
        }

        // ImGui
        private void ResetImGuiStyle()
        {
            if (DoNotResetImGuiStyle)
                return;

            string selectedImGuiStyle = Config.ImGuiStyle.ToLower();

            if (selectedImGuiStyle == "dark")
                ImGuiIV.StyleColorsDark();
            else if (selectedImGuiStyle == "classic")
                ImGuiIV.StyleColorsClassic();
            else if (selectedImGuiStyle == "light")
                ImGuiIV.StyleColorsLight();
            else
                ImGuiIV.StyleColorsDark();

            ImGuiIV.StyleLayoutDefault();
        }
        private void SetImGuiPurpleStyle()
        {
            // Purple Comfy style by RegularLunar from ImThemes
            // Slighty modified
            ImGuiIV_Style style = ImGuiIV.GetStyle();

            style.Alpha = 1.0f;
            style.DisabledAlpha = 0.5f;
            style.WindowPadding = new Vector2(8.0f, 8.0f);
            style.WindowRounding = 10.0f;
            style.WindowBorderSize = 1.0f;
            style.WindowMinSize = new Vector2(30.0f, 30.0f);
            style.WindowTitleAlign = new Vector2(0.5f, 0.5f);
            style.WindowMenuButtonPosition = eImGuiDir.Right;
            style.ChildRounding = 5.0f;
            style.ChildBorderSize = 1.0f;
            style.PopupRounding = 10.0f;
            style.PopupBorderSize = 0.0f;
            style.FramePadding = new Vector2(5.0f, 3.5f);
            style.FrameRounding = 5.0f;
            style.FrameBorderSize = 0.0f;
            style.ItemSpacing = new Vector2(5.0f, 4.0f);
            style.ItemInnerSpacing = new Vector2(5.0f, 5.0f);
            style.CellPadding = new Vector2(4.0f, 2.0f);
            style.IndentSpacing = 5.0f;
            style.ColumnsMinSpacing = 5.0f;
            style.ScrollbarSize = 15.0f;
            style.ScrollbarRounding = 9.0f;
            style.GrabMinSize = 15.0f;
            style.GrabRounding = 5.0f;
            style.TabRounding = 5.0f;
            style.TabBorderSize = 0.0f;
            style.TabMinWidthForCloseButton = 0.0f;
            style.ColorButtonPosition = eImGuiDir.Right;
            style.ButtonTextAlign = new Vector2(0.5f, 0.5f);
            style.SelectableTextAlign = new Vector2(0.0f, 0.0f);

            Vector4[] colors = style.Colors;
            colors[(int)eImGuiCol.Text] = new Vector4(1.0f, 1.0f, 1.0f, 1.0f);
            colors[(int)eImGuiCol.TextDisabled] = new Vector4(1.0f, 1.0f, 1.0f, 0.3605149984359741f);
            colors[(int)eImGuiCol.WindowBg] = new Vector4(0.09803921729326248f, 0.09803921729326248f, 0.09803921729326248f, 1.0f);
            colors[(int)eImGuiCol.ChildBg] = new Vector4(1.0f, 0.0f, 0.0f, 0.0f);
            colors[(int)eImGuiCol.PopupBg] = new Vector4(0.09803921729326248f, 0.09803921729326248f, 0.09803921729326248f, 1.0f);
            colors[(int)eImGuiCol.Border] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.BorderShadow] = new Vector4(0.0f, 0.0f, 0.0f, 0.0f);
            colors[(int)eImGuiCol.FrameBg] = new Vector4(0.1568627506494522f, 0.1568627506494522f, 0.1568627506494522f, 1.0f);
            colors[(int)eImGuiCol.FrameBgHovered] = new Vector4(0.3803921639919281f, 0.4235294163227081f, 0.572549045085907f, 0.5490196347236633f);
            colors[(int)eImGuiCol.FrameBgActive] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.TitleBg] = new Vector4(0.09803921729326248f, 0.09803921729326248f, 0.09803921729326248f, 1.0f);
            colors[(int)eImGuiCol.TitleBgActive] = new Vector4(0.09803921729326248f, 0.09803921729326248f, 0.09803921729326248f, 1.0f);
            colors[(int)eImGuiCol.TitleBgCollapsed] = new Vector4(0.2588235437870026f, 0.2588235437870026f, 0.2588235437870026f, 0.55f);
            colors[(int)eImGuiCol.MenuBarBg] = new Vector4(0.0f, 0.0f, 0.0f, 0.0f);
            colors[(int)eImGuiCol.ScrollbarBg] = new Vector4(0.1568627506494522f, 0.1568627506494522f, 0.1568627506494522f, 0.0f);
            colors[(int)eImGuiCol.ScrollbarGrab] = new Vector4(0.2f, 0.2f, 0.2f, 1.0f);
            colors[(int)eImGuiCol.ScrollbarGrabHovered] = new Vector4(0.2352941185235977f, 0.2352941185235977f, 0.2352941185235977f, 1.0f);
            colors[(int)eImGuiCol.ScrollbarGrabActive] = new Vector4(0.294117659330368f, 0.294117659330368f, 0.294117659330368f, 1.0f);
            colors[(int)eImGuiCol.CheckMark] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.SliderGrab] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.SliderGrabActive] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.Button] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.ButtonHovered] = new Vector4(0.56f, 0.38f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.ButtonActive] = new Vector4(0.44f, 0.22f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.Header] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.HeaderHovered] = new Vector4(0.56f, 0.38f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.HeaderActive] = new Vector4(0.44f, 0.22f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.Separator] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.SeparatorHovered] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.SeparatorActive] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.ResizeGrip] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.ResizeGripHovered] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.ResizeGripActive] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.Tab] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.TabHovered] = new Vector4(0.56f, 0.38f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.TabActive] = new Vector4(0.44f, 0.22f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.TabUnfocused] = new Vector4(0.0f, 0.4509803950786591f, 1.0f, 0.0f);
            colors[(int)eImGuiCol.TabUnfocusedActive] = new Vector4(0.1333333402872086f, 0.2588235437870026f, 0.4235294163227081f, 0.0f);
            colors[(int)eImGuiCol.PlotLines] = new Vector4(0.294117659330368f, 0.294117659330368f, 0.294117659330368f, 1.0f);
            colors[(int)eImGuiCol.PlotLinesHovered] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.PlotHistogram] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.PlotHistogramHovered] = new Vector4(0.7372549176216125f, 0.6941176652908325f, 0.886274516582489f, 0.5490196347236633f);
            colors[(int)eImGuiCol.TableHeaderBg] = new Vector4(0.1882352977991104f, 0.1882352977991104f, 0.2000000029802322f, 1.0f);
            colors[(int)eImGuiCol.TableBorderStrong] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.TableBorderLight] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.2901960909366608f);
            colors[(int)eImGuiCol.TableRowBg] = new Vector4(0.0f, 0.0f, 0.0f, 0.0f);
            colors[(int)eImGuiCol.TableRowBgAlt] = new Vector4(1.0f, 1.0f, 1.0f, 0.03433477878570557f);
            colors[(int)eImGuiCol.TextSelectedBg] = new Vector4(0.501960813999176f, 0.3019607961177826f, 1.0f, 0.5490196347236633f);
            colors[(int)eImGuiCol.DragDropTarget] = new Vector4(1.0f, 1.0f, 0.0f, 0.8999999761581421f);
            colors[(int)eImGuiCol.NavHighlight] = new Vector4(0.0f, 0.0f, 0.0f, 1.0f);
            colors[(int)eImGuiCol.NavWindowingHighlight] = new Vector4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
            colors[(int)eImGuiCol.NavWindowingDimBg] = new Vector4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
            colors[(int)eImGuiCol.ModalWindowDimBg] = new Vector4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.3499999940395355f);
            style.Colors = colors;
        }

        // Other
        public void HandleScriptException(FoundScript target, double notifySecondsVisible, string eventErrorOccuredIn, Exception ex, bool isInternalEvent = false)
        {
            // Stop script so it doesn't raise any events anymore
            target.Stop();

            string scriptName = target.EntryPoint.FullName;

            // Show and Log the error
            if (target.IsScriptHookDotNetScript)
            {
                Notification.ShowNotification(
                    NotificationType.Error,
                    DateTime.UtcNow.AddSeconds(notifySecondsVisible),
                    string.Format("[ScriptHookDotNet] An error occured in {0} {2} {1}.", scriptName, eventErrorOccuredIn, isInternalEvent ? "internal event" : ""),
                    ex.Message,
                    string.Format("ERROR_IN_SCRIPT_{0}", scriptName));

                Logger.LogError(string.Format("An error occured while processing {0} event for ScriptHookDotNet script {1}. Aborting script. Details: {2}", eventErrorOccuredIn, scriptName, ex));
            }
            else
            {
                Notification.ShowNotification(
                    NotificationType.Error,
                    DateTime.UtcNow.AddSeconds(notifySecondsVisible),
                    string.Format("An error occured in {0} {1}.", scriptName, eventErrorOccuredIn),
                    ex.Message,
                    string.Format("ERROR_IN_SCRIPT_{0}", scriptName));

                Logger.LogError(string.Format("An error occured while processing '{0}' event for script '{1}'. Aborting script. Details: {2}", eventErrorOccuredIn, scriptName, ex));
            }

            // Abort script
            AbortScriptInternal(AbortReason.Manager, target, true);
        }
        private void SetUpKeyWatchDogs()
        {
            keyWatchDogs = new KeyWatchDog[2];

            // IV-SDK .NET
            keyWatchDogs[0] = new KeyWatchDog("IVSDKDotNet");
            keyWatchDogs[0].KeyDown += KeyWatchDog_KeyDown;
            keyWatchDogs[0].KeyUp   += KeyWatchDog_KeyUp;

            // ScriptHookDotNet
            keyWatchDogs[1] = new KeyWatchDog("ScriptHookDotNet");
            keyWatchDogs[1].KeyDown += KeyWatchDog_KeyDown;
            keyWatchDogs[1].KeyUp   += KeyWatchDog_KeyUp;
        }
        private void SaveLogFile()
        {
            try
            {
                string[] logItems = Logger.GetLogItemsAsString();

                // Save file at target location
                if (Config.CreateLogFilesInMainDirectory)
                {
                    File.WriteAllLines("IVSDKDotNet.log", logItems);
                }
                else
                {
                    if (!Directory.Exists(CLR.CLRBridge.IVSDKDotNetLogsPath))
                    {
                        Directory.CreateDirectory(CLR.CLRBridge.IVSDKDotNetLogsPath);
                        File.WriteAllLines(string.Format("{0}\\{1}", CLR.CLRBridge.IVSDKDotNetLogsPath, CLR.CLRBridge.CurrentLogFileName), logItems);
                        return;
                    }

                    // Get all log files in the logs folder
                    string[] logFiles = Directory.GetFiles(CLR.CLRBridge.IVSDKDotNetLogsPath, "*.log");

                    // If there are more log files then allowed
                    if (logFiles.Length > Config.MaxLogsFiles)
                    {
                        // Delete the first file that is present in the array which SHOULD be the oldest one (Even tho the order of the array returned by the Directory.GetFiles function in not guaranteed)
                        File.Delete(logFiles[0]);
                    }

                    // Save file
                    File.WriteAllLines(string.Format("{0}\\{1}", CLR.CLRBridge.IVSDKDotNetLogsPath, CLR.CLRBridge.CurrentLogFileName), logItems);
                }
            }
            catch (Exception ex)
            {
#if DEBUG
                throw ex;
#endif
            }
        }
        private void GetSupporters()
        {
            try
            {
                downloadClient.DownloadStringAsync(new Uri("https://www.dropbox.com/scl/fi/ml4gx8sgzmznru5llcqpm/TierOneSupporter.json?rlkey=wldl4y6swfb2oy96h763grft3&dl=1"), "GET_TIER_ONE_SUPPORTERS");
            }
            catch (Exception ex)
            {
                Logger.LogError(string.Format("An error occured while trying to get all current Patreon / Ko-fi supporters. Sorry about that :({0}" +
                    "Details: {1}", Environment.NewLine, ex));
            }
        }

        private void DestroyGlobalRegisteredTextures()
        {
            if (GlobalRegisteredTextures.Count == 0)
                return;

            Logger.LogDebug(string.Format("Trying to get rid of {0} textures registered in the global textures list.", GlobalRegisteredTextures.Count));

            for (int i = 0; i < GlobalRegisteredTextures.Count; i++)
            {
                IntPtr texturePtr = GlobalRegisteredTextures[i];

                if (ImGuiIV.IsTextureValid(texturePtr))
                {
                    if (!ImGuiIV.ReleaseTexture(ref texturePtr))
                        Logger.LogWarning(string.Format("Could not release texture {0} registered in the global textures list.", texturePtr));
                }
                else
                {
                    Logger.LogDebug(string.Format("Not destroying texture {0} registered in the global textures list because it's not valid anymore.", texturePtr));
                }

                GlobalRegisteredTextures.RemoveAt(i);
                i--;
            }
        }

        #endregion

        #region Functions

        // Script stuff
        public Script GetIVSDKDotNetScript(Guid id)
        {
            return GetIVSDKDotNetScripts().Where(x => x.ID == id).FirstOrDefault();
        }
        public Script[] GetIVSDKDotNetScripts()
        {
            return ActiveScripts.Where(x => x.IsIVSDKDotNetScript).Select(x => x.GetScriptAs<Script>()).ToArray();
        }
        public GTA.Script GetScriptHookDotNetScript(Guid id)
        {
            return GetScriptHookDotNetScripts().Where(x => x.GUID == id).FirstOrDefault();
        }
        public GTA.Script[] GetScriptHookDotNetScripts()
        {
            return ActiveScripts.Where(x => x.IsScriptHookDotNetScript).Select(x => x.GetScriptAs<GTA.Script>()).ToArray();
        }

        public FoundScript GetFoundScript(Guid id)
        {
            FoundScript fs = null;

            lock (activeScriptsLockObj)
            {
                fs = ActiveScripts.Where(x => x.ID == id).FirstOrDefault();
            }

            return fs;
        }
        public FoundScript GetFoundScript(string name)
        {
            if (string.IsNullOrWhiteSpace(name))
                return null;

            FoundScript fs = null;

            lock (activeScriptsLockObj)
            {
                fs = ActiveScripts.Where(x => x.FileName.ToLower() == name.ToLower()
                    || x.EntryPoint.FullName.ToLower() == name.ToLower()).FirstOrDefault();
            }

            return fs;
        }

        public bool AbortScriptInternal(AbortReason reason, Guid id)
        {
            // Try find and abort script
            FoundScript script = GetFoundScript(id);

            if (script != null)
            {
                Logger.Log(string.Format("Aborting script {0}...", script.EntryPoint.FullName));
                script.Abort(reason, true);
                GC.Collect();
                return ActiveScripts.Remove(script);
            }

            return false;
        }
        public bool AbortScriptInternal(AbortReason reason, FoundScript script, bool showMessage)
        {
            if (script != null)
            {
                if (showMessage)
                    Logger.Log(string.Format("Aborting script {0}...", script.EntryPoint.FullName));

                script.Abort(reason, showMessage);

                bool result = ActiveScripts.Remove(script);
                GC.Collect();
                return result;
            }

            return false;
        }

        public Guid StartNewTimerInternal(int interval, Action actionToExecute)
        {
            // Create task
            AdvancedTask task = new AdvancedTask(Guid.NewGuid(), Guid.Empty, TaskUseCase.Timer, interval);

            // Start task
            bool r = task.Start(TaskCreationOptions.LongRunning, () => AdvancedTask.TimerStatic(task, actionToExecute), (TaskData args) =>
            {
                // If the task ends, a delayed action will start which gets rid of the task in 5 seconds
                StartDelayedAction(
                    args.Source.ID,
                    string.Format("Getting rid of task {0} from Manager. (CFSM: TaskDisposer in AdvancedTask class)", args.Source.ID),
                    DateTime.UtcNow.AddSeconds(5),
                    AdvancedTask.TaskDisposer,
                    args.Source);
            });

            if (r)
            {
                ActiveTasks.Add(task);
                return task.ID;
            }

            task = null;
            return Guid.Empty;
        }

        #endregion

        #region Overrides

        #region Manager Stuff
        public override void Cleanup()
        {
            try
            {
                // Log
                Logger.LogDebug("Manager is starting its cleanup process...");

                if (Console != null)
                    Console.Close();
                Notification.Cleanup();

                // Stop remote server
                ConnectionManager.Dispose();

                // Abort all currently running scripts
                AbortScripts(ScriptType.All, AbortReason.Manager, false);

                // Stop all active task
                if (ActiveTasks.Count != 0)
                {
                    double waitAllTimeout = 3.5d;
                    DateTime taskCleanUpStartTime = DateTime.UtcNow;
                    int activeTasksCount = ActiveTasks.Count;

                    try
                    {
                        Task[] tasksToCancel = new Task[activeTasksCount];

                        // Put all active tasks in task array and cancel them
                        for (int i = 0; i < activeTasksCount; i++)
                        {
                            AdvancedTask advancedTask = ActiveTasks[i];

                            // Put actual task in task array
                            tasksToCancel[i] = advancedTask.ActualTask.Task;

                            // Request task to cancel
                            advancedTask.RequestCancellation();
                        }

                        // Wait until all tasks are completed
                        if (Task.WaitAll(tasksToCancel, TimeSpan.FromSeconds(waitAllTimeout)))
                        {
                            // Dispose all tasks
                            ActiveTasks.ForEach(x => x.Dispose());

                            // Log how long this process took
                            TimeSpan timeResult = (DateTime.UtcNow - taskCleanUpStartTime);
                            Logger.LogDebug(string.Format("{0} active tasks stopped. This process took {1}.{2} seconds.", activeTasksCount, timeResult.Seconds, timeResult.Milliseconds));
                        }
                        else
                        {
                            Logger.LogWarning(string.Format("Could not get rid of {0} active tasks after waiting for {1} seconds.", activeTasksCount, waitAllTimeout));
                        }
                    }
                    catch (Exception ex)
                    {
                        Logger.LogError(string.Format("Stopping {0} active tasks failed. Details: {1}", activeTasksCount, ex));
                    }
                }

                // Cleanup SHDN stuff
                SHDNStuff.Cleanup();

                // Cleanup lists
                ActiveScripts.Clear();
                ActiveTasks.Clear();
                DelayedActions.Clear();

                TierOneSupporters.Clear();
                TierTwoSupporters.Clear();
                TierThreeSupporters.Clear();

                // Destroy keyWatchDogs
                if (keyWatchDogs != null)
                {
                    for (int i = 0; i < keyWatchDogs.Length; i++)
                    {
                        KeyWatchDog keyWatchDog = keyWatchDogs[i];
                        keyWatchDog.KeyDown -= KeyWatchDog_KeyDown;
                        keyWatchDog.KeyUp -= KeyWatchDog_KeyUp;
                        keyWatchDog.Dispose();
                        keyWatchDogs[i] = null;
                    }
                    keyWatchDogs = null;
                }

                Logger.LogDebug("Cleanup process for manager script finished!");
            }
            catch (Exception ex)
            {
                Logger.LogError(string.Format("Error while cleaning up in manager script! Details: {0}", ex));
            }
        }
        public override void ApplySettings(SettingsFile settings)
        {
            // Apply settings
            Config.ApplySettings(settings);

            // Start the server if allowed
            if (Config.AllowRemoteConnections)
                ConnectionManager.Start(false);
        }
        #endregion

        #region Script Stuff
        public override void LoadScripts()
        {
            LoadScriptsInternal();
        }

        public override bool AbortScript(Guid id)
        {
            return AbortScriptInternal(AbortReason.Script, id);
        }

        public override Script GetScript(Guid id)
        {
            return ActiveScripts.Where(x => x.ID == id && x.IsIVSDKDotNetScript).Select(s => s.GetScriptAs<Script>()).FirstOrDefault();
        }
        public override Script GetScript(string name)
        {
            return ActiveScripts.Where(x => x.FileName == name || x.EntryPoint.FullName == name && x.IsIVSDKDotNetScript).Select(s => s.GetScriptAs<Script>()).FirstOrDefault();
        }
        public override bool IsScriptRunning(Guid id)
        {
            FoundScript foundScript = GetFoundScript(id);

            if (foundScript != null)
                return foundScript.IsScriptReady();

            return false;
        }
        public override bool IsScriptRunning(string name)
        {
            FoundScript foundScript = GetFoundScript(name);

            if (foundScript != null)
                return foundScript.IsScriptReady();

            return false;
        }
        public override string GetScriptName(Guid id)
        {
            FoundScript foundScript = GetFoundScript(id);

            if (foundScript != null)
                return foundScript.EntryPoint.FullName;

            return string.Empty;
        }
        public override string GetScriptFullPath(Guid id)
        {
            FoundScript foundScript = GetFoundScript(id);

            if (foundScript != null)
                return foundScript.FullPath;

            return string.Empty;
        }
        public override int GetActiveScriptsCount()
        {
            return ActiveScripts.Count;
        }

        public override bool SendScriptCommand(Guid sender, Guid toScript, string command, object[] parameters, out object result)
        {
            // Find target script that should receive the script command
            FoundScript foundScript = GetFoundScript(toScript);

            if (foundScript != null)
            {
                try
                {
                    // Try send script command to target script
                    if (foundScript.RaiseScriptCommandReceived(sender, command, parameters, out object res))
                    {
                        result = res;
                        return true;
                    }
                }
                catch (Exception ex)
                {
                    HandleScriptException(foundScript, 8d, "ScriptCommandReceived", ex);
                }
            }

            result = null;
            return false;
        }
        public override bool SendScriptCommand(Guid sender, string toScript, string command, object[] parameters, out object result)
        {
            // Find target script that should receive the script command
            FoundScript foundScript = GetFoundScript(toScript);

            if (foundScript != null)
            {
                try
                {
                    // Try send script command to target script
                    if (foundScript.RaiseScriptCommandReceived(sender, command, parameters, out object res))
                    {
                        result = res;
                        return true;
                    }
                }
                catch (Exception ex)
                {
                    HandleScriptException(foundScript, 8d, "ScriptCommandReceived", ex);
                }
            }

            result = null;
            return false;
        }

        public override Guid StartNewTask(Guid forScript, Func<object> funcToExecute, Action<object> continueWithAction)
        {
            FoundScript s = GetFoundScript(forScript);

            if (s != null)
            {
                // Create task
                AdvancedTask task = new AdvancedTask(Guid.NewGuid(), s.ID, TaskUseCase.Custom);

                // Start task
                bool r = task.Start(TaskCreationOptions.None, funcToExecute, (TaskData args) =>
                {
                    // Invoke custom continue with action
                    continueWithAction?.Invoke(args.CustomData);

                    // If the task ends, a delayed action will start which gets rid of the task in 5 seconds
                    StartDelayedAction(
                        args.Source.ID,
                        string.Format("Getting rid of task {0} from Script {1}. (CFSM: TaskDisposer in AdvancedTask class)", args.Source.ID, args.Source.OwnerID),
                        DateTime.UtcNow.AddSeconds(5),
                        AdvancedTask.TaskDisposer,
                        args.Source);
                });

                if (r)
                {
                    //s.ScriptTasks.Add(task);
                    ActiveTasks.Add(task);
                    return task.ID;
                }

                task = null;
                return Guid.Empty;
            }

            return Guid.Empty;
        }
        public override Guid StartNewTimer(Guid forScript, int interval, Action actionToExecute)
        {
            FoundScript s = GetFoundScript(forScript);

            if (s != null)
            {
                // Create task
                AdvancedTask task = new AdvancedTask(Guid.NewGuid(), s.ID, TaskUseCase.Timer, interval);

                // Start task
                bool r = task.Start(TaskCreationOptions.LongRunning, () => AdvancedTask.TimerStatic(task, actionToExecute), (TaskData args) =>
                {
                    // If the task ends, a delayed action will start which gets rid of the task in 5 seconds
                    StartDelayedAction(
                        args.Source.ID,
                        string.Format("Getting rid of task {0} from Script {1}. (CFSM: TaskDisposer in AdvancedTask class)", args.Source.ID, args.Source.OwnerID),
                        DateTime.UtcNow.AddSeconds(5),
                        AdvancedTask.TaskDisposer,
                        args.Source);
                });

                if (r)
                {
                    //s.ScriptTasks.Add(task);
                    ActiveTasks.Add(task);
                    return task.ID;
                }

                task = null;
                return Guid.Empty;
            }

            return Guid.Empty;
        }
        #endregion

        #region Direct3D9 Stuff

        // Texture stuff
        public override void Direct3D9_RegisterScriptTexture(string forScript, IntPtr ptr)
        {
            // Get script from ID
            FoundScript fs = GetFoundScript(forScript);

            if (fs != null)
            {
                if (!fs.Textures.Contains(ptr))
                {
                    fs.Textures.Add(ptr);
                    Logger.LogDebug(string.Format("Registered texture {0} for script {1}.", ptr, fs.EntryPoint.FullName));
                }
                else
                {
                    Logger.LogDebug(string.Format("Texture {0} is already registered for script {1}.", ptr, fs.EntryPoint.FullName));
                }
            }
            else
            {
                Logger.LogDebug("Could not find script to assign texture to! Adding to global texture list.");
                GlobalRegisteredTextures.Add(ptr);
            }
        }

        #endregion

        #region Console
        public override void OpenConsole()
        {
            Console.Open();
        }
        public override void CloseConsole()
        {
            Console.Close();
        }
        public override void ClearConsole()
        {
            Console.Clear();
        }

        public override bool IsConsoleOpen()
        {
            return Console.IsConsoleOpen;
        }

        public override bool RegisterConsoleCommand(Guid fromScript, string name, Action<string[]> actionToExecute)
        {
            // Get script by id
            FoundScript fs = GetFoundScript(fromScript);

            if (fs != null)
            {
                string nameToLower = name.ToLower();

                if (fs.ConsoleCommands.ContainsKey(nameToLower))
                    return false;

                // Add command to commands list
                fs.ConsoleCommands.Add(nameToLower, actionToExecute);

                return true;
            }

            return false;
        }
        public override bool ExecuteConsoleCommand(string name)
        {
            return Console.ExecuteCommand(name);
        }
        #endregion

        #region Phone
        public override bool RegisterPhoneNumber(Guid forScript, string number, Action dialedAction)
        {
            if (string.IsNullOrWhiteSpace(number))
                return false;
            if (dialedAction == null)
                return false;

            FoundScript fs = GetFoundScript(forScript);

            if (fs != null)
                return fs.AddPhoneNumber(number, dialedAction);

            return false;
        }
        public override bool UnregisterPhoneNumber(Guid fromScript, string number)
        {
            if (string.IsNullOrWhiteSpace(number))
                return false;

            FoundScript fs = GetFoundScript(fromScript);

            if (fs != null)
                return fs.RemovePhoneNumber(number);

            return false;
        }
        #endregion

        #region Game
        public override bool IsGameInFocus()
        {
            return IsGTAIVWindowInFocus;
        }
        #endregion

        #region Tasks
        public override void WaitInTask(Guid id, int waitTimeInMilliseconds)
        {
            ActiveTasks.ForEach(x =>
            {
                if (x.ID == id)
                    x.Wait(waitTimeInMilliseconds);
            });
        }
        public override void AbortTaskOrTimer(Guid id)
        {
            ActiveTasks.ForEach(x =>
            {
                if (x.ID == id)
                    x.RequestCancellation();
            });
        }
        public override void ChangeTimerState(Guid id, bool pause)
        {
            ActiveTasks.ForEach(x =>
            {
                if (x.ID == id)
                    x.PauseTimer = pause;
            });
        }
        public override void ChangeTimerInterval(Guid id, int interval)
        {
            ActiveTasks.ForEach(x =>
            {
                if (x.ID == id)
                    x.TimerInterval = interval;
            });
        }
        #endregion

        #region Helper
        public override string Helper_ConvertObjectToJsonString(object obj, bool useFormatting)
        {
            if (obj == null)
                return string.Empty;

            // Find all fields which got the json exclude attribute
            IEnumerable<string> fieldsToIgnore = obj.GetType().GetFields(BindingFlags.Instance | BindingFlags.Public)
                .Where(x => x.GetCustomAttribute<ExcludeFromJsonSerializationAttribute>() != null)
                .Select(x => x.Name);

            return JsonConvert.SerializeObject(
                obj,
                useFormatting ? Formatting.Indented : Formatting.None,
                new JsonSerializerSettings() { ContractResolver = new JsonHelper.IgnorePropertiesResolver(fieldsToIgnore) });
        }
        public override object Helper_ConvertJsonStringToObject(string str, Type targetType)
        {
            if (string.IsNullOrWhiteSpace(str))
                return null;

            try
            {
                return JsonConvert.DeserializeObject(str, targetType);
            }
            catch (Exception)
            {
                return null;
            }
        }
        #endregion

        #region ScriptHookDotNet
        public override int SHDN_LateInitializeScript(string name, object script, out string assemblyFullPath)
        {
            if (script == null)
            {
                assemblyFullPath = null;
                return 1;
            }

            FoundScript fs = GetFoundScript(name);

            if (fs != null)
            {
                Helper.WriteToDebugOutput(Priority.Default, "Found FoundScript object for late initialization of ScriptHookDotNet script {0}!", name);
                assemblyFullPath = fs.FullPath;
                fs.LateInitialize(script);
                return 0;
            }
            else
            {
                Helper.WriteToDebugOutput(Priority.High, "Unable to find FoundScript object for late initialization of ScriptHookDotNet script {0}!", name);
            }

            assemblyFullPath = null;
            return 2;
        }

        public override object SHDN_GetScriptByName(string name)
        {
            FoundScript fs = GetFoundScript(name);

            if (fs != null)
                return fs.TheScriptObject;

            return null;
        }
        public override object SHDN_GetScriptByGUID(Guid id)
        {
            FoundScript fs = GetFoundScript(id);

            if (fs != null)
                return fs.TheScriptObject;

            return null;
        }

        public override object SHDN_GetCurrentScript(int iEvent)
        {
            return SHDNStuff.GetCurrentScript((GTA.ScriptEvent)iEvent);
        }
        public override void SHDN_SetCurrentScript(int iEvent, object script)
        {
            SHDNStuff.SetCurrentScript((GTA.ScriptEvent)iEvent, script);
        }

        public override void SHDN_AddFont(object obj)
        {
            if (obj == null)
            {
                Logger.LogDebug(string.Format("Given font object was null! Will not add to queue."));
                return;
            }

            SHDNStuff.FontsToBeCreated.Enqueue((GTA.Font)obj);
            Logger.LogDebug("Successfully added new shdn font to queue!");
        }

        public override bool SHDN_VerboseLoggingEnabled()
        {
            return SHDNStuff.EnableVerboseLogging;
        }
        public override bool SHDN_NativeCallLoggingEnabled()
        {
            return SHDNStuff.NativeCallLoggingEnabled;
        }
        public override bool SHDN_IsScriptRunning(Guid id)
        {
            FoundScript fs = GetFoundScript(id);

            if (fs != null)
                return fs.IsScriptReady();

            return false;
        }
        #endregion

        #region Other
        public override int GetMainThreadID()
        {
            return MainThreadID;
        }
        #endregion

        #endregion
    }
}