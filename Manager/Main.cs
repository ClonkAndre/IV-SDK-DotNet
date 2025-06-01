using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Net;
using System.Reflection;
using System.Threading.Tasks;
using System.Windows.Forms;

using Newtonsoft.Json;

using IVSDKDotNet;
using IVSDKDotNet.Attributes;
using IVSDKDotNet.Enums;
using IVSDKDotNet.Internal;
using IVSDKDotNet.Manager;
using IVSDKDotNet.Native;

using Manager.Classes;
using Manager.Classes.Json;
using Manager.Classes.Scripts;
using Manager.Classes.Threading;
using Manager.Managers;
using Manager.UI;

namespace Manager
{
    public class Main : ManagerScript
    {

        #region Variables
        internal static Main Instance;

        // Lists
        public List<AdvancedTask> ActiveTasks;
        private Queue<ImPopup> pendingPopups;

        public List<string> TierOneSupporters;
        public List<string> TierTwoSupporters;
        public List<string> TierThreeSupporters;

        public List<IntPtr> GlobalRegisteredTextures; // For any texture that couldn't be assigned to any script

        // Managers
        public RemoteConnectionManager ConnectionManager;

        // Hooks
        private KeyWatchDog keyWatchDog;

        // Debug
        public bool DisableKeyEvents;
        public bool ThrowOnError;
        public bool AllowWriteToDebugOutput = true;
        
        // Threading
        private GenericThread drawThread;

        // Rendering
        private ImPopup currentPopup;

        // Other
        public UpdateChecker UpdateChecker;
        private WebClient downloadClient;
        public Process GTAIVProcess;
        private Guid processCheckerTimerID;
        public ImGuiIV_DrawingContext GlobalDrawCtx;

        private bool isShuttingDown;
        private bool wasLoadingMessageShown;
        private bool allowDrawing;
        public bool FirstFrame = true;
        public bool IsGTAIVWindowInFocus;
        public bool OnWindowFocusChangedEventCalled;
        private bool wasBoundPhoneNumbersProcessed;
        private int lastLogLineCount;

        public int PlayerPedHandle;
        public int PlayerVehicleHandle;

#if PREVIEW
        private SettingsFile previewDatFile;
#endif

        #endregion

        #region Events

        // Assembly
        private Assembly CurrentDomain_AssemblyResolve(object sender, ResolveEventArgs args)
        {
            AssemblyName assemblyName = new AssemblyName(args.Name);

            if (assemblyName.Name.EndsWith(".resources"))
            {
                Helper.WriteToDebugOutput(Priority.Default, "Was searching for a resources file with the name {0}. Skipping.", assemblyName.Name);
                return null;
            }

            string assemblyFileName = string.Concat(assemblyName.Name, ".dll");

            Helper.WriteToDebugOutput(Priority.Default, "Trying to resolve dependency {0} ({1}) for assembly {2}", assemblyName.Name, assemblyFileName, args.RequestingAssembly == null ? "UNKNOWN" : args.RequestingAssembly.FullName);

            // Try get file full path from within cache
            string assemblyFullPath = FileCacheManager.GetFullPathOfCachedFile(assemblyFileName);

            // Try load file if it exists
            if (File.Exists(assemblyFullPath))
            {
                Helper.WriteToDebugOutput(Priority.Default, "Found dependency {0} in the file cache! FullPath: {1}", assemblyFileName, assemblyFullPath);
                return Assembly.UnsafeLoadFrom(assemblyFullPath);
            }
            else
            {
                Helper.WriteToDebugOutput(Priority.Default, "Could not find required dependency {0}! Game might crash!", assemblyFileName, assemblyFullPath);
                Logger.LogErrorEx("Could not find required dependency {0}! Game might crash!", assemblyFileName);
            }

            return null;
        }

        // UpdateChecker
        private void UpdateChecker_VersionCheckFailed(Exception e)
        {
            NotificationUI.ShowNotification(NotificationType.Error, DateTime.UtcNow.AddSeconds(5), "An error occured while checking for IV-SDK .NET updates", "Check the IV-SDK .NET console for more details.", "UPDATE_CHECK_FAILED");
            Logger.LogError(string.Format("Error while checking for updates. Details: {0}", e.ToString()));
        }
        private void UpdateChecker_VersionCheckCompleted(UpdateChecker.VersionCheckInfo result)
        {
            if (result.NewVersionAvailable)
            {
                NotificationUI.ShowNotification(NotificationType.Default, DateTime.UtcNow.AddSeconds(7), "New IV-SDK .NET update available!", string.Format("Version {0} of IV-SDK .NET is available to download.", result.NewVersion), "NEW_UPDATE_AVAILABLE");
                Logger.Log(string.Format("Version {0} of IV-SDK .NET is available!", result.NewVersion));
            }
            else
            {
                Logger.Log("There is currently no new IV-SDK .NET update available.");

                if (!result.IsSilentCheck)
                    NotificationUI.ShowNotification(NotificationType.Default, DateTime.UtcNow.AddSeconds(7), "No new IV-SDK .NET update available", "There is currently no new IV-SDK .NET update available.", "NO_NEW_UPDATE_AVAILABLE");
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

            // Subscribe to AppDomain events
            AppDomain.CurrentDomain.AssemblyResolve += CurrentDomain_AssemblyResolve;

            // Lists
            ActiveTasks =                   new List<AdvancedTask>();
            pendingPopups =                 new Queue<ImPopup>();
            GlobalRegisteredTextures =      new List<IntPtr>();
            TierOneSupporters =             new List<string>();
            TierTwoSupporters =             new List<string>();
            TierThreeSupporters =           new List<string>();

            // UI
            NotificationUI.Init();

            ConsoleUI.Init();
            ConsoleUI.OnConsoleCommand += Console_OnConsoleCommand;

            // Managers
            DelayedActionManager.Init();
            FileCacheManager.Init();
            MinHookManager.Init();
            PluginManager.Init();
            ConnectionManager = new RemoteConnectionManager();
            ScriptManager.Init();
            TaskManager.Init();
            ThreadManager.Init();

            ManagedNativeCaller.Init();

            // Hooks
            keyWatchDog = new KeyWatchDog();
            keyWatchDog.KeyDown += KeyWatchDog_KeyDown;
            keyWatchDog.KeyUp += KeyWatchDog_KeyUp;

            // Threading
            drawThread = ThreadManager.CreateGenericThread(() =>
            {
                ThreadManager.StoreCurrentThreadTlsContext();
                ThreadManager.ChangeTlsContextOfCurrentThreadToContextOfTargetThread(GameThread.RenderThread);

                // Raise all script OnImGuiRendering events
                ScriptManager.RaiseOnD3D9Frame(RAGE.GetDirect3DDevice9(), Main.Instance.GlobalDrawCtx);

                ThreadManager.RestoreTlsContextForCurrentThread();

            }, threadName: "IV-SDK .NET Draw Thread");
            drawThread.BlockWait = true;
            drawThread.Launch();

            // Other
            UpdateChecker = new UpdateChecker(CLR.CLRBridge.Version.ToString(), "https://www.dropbox.com/s/smaz6ij8dkzd7nh/version.txt?dl=1");
            UpdateChecker.VersionCheckFailed +=     UpdateChecker_VersionCheckFailed;
            UpdateChecker.VersionCheckCompleted +=  UpdateChecker_VersionCheckCompleted;

            downloadClient = new WebClient();
            downloadClient.DownloadStringCompleted += DownloadClient_DownloadStringCompleted;

            GTAIVProcess = Process.GetCurrentProcess();

            // Init Reflection
            if (Reflection.Init())
                Logger.LogDebug("Initialized Reflection class.");
            else
                Logger.LogDebug("Failed to initialize Reflection class!");

            // Start process in focus checker timer
            processCheckerTimerID = StartNewTimerInternal(1000, () =>
            {

                if (!Reflection.LocalRAGE.IsRaiseOnWindowFocusChangedAvailable())
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
                        Reflection.LocalRAGE.RaiseOnWindowFocusChanged(true);
                        OnWindowFocusChangedEventCalled = true;
                    }
                }
                else
                {
                    if (OnWindowFocusChangedEventCalled)
                    {
                        Reflection.LocalRAGE.RaiseOnWindowFocusChanged(false);
                        OnWindowFocusChangedEventCalled = false;
                    }
                }

            });

            Secrittzzz.Init();

            // First Start stuff
            CheckFirstStart();

#if PREVIEW
            // Preview build stuff
            CheckPreviewBuild();
#endif
        }
        #endregion

        #region Raisers
        public override void RaiseTick()
        {
            if (isShuttingDown)
                return;
            
            // Process the thread manager
            ThreadManager.ProcessMainThread();

            if (Config.PauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

            // Process MinHookManager
            MinHookManager.Process();

            // Store the handle of the player ped and vehicle
            Natives.GET_PLAYER_CHAR(Natives.CONVERT_INT_TO_PLAYERINDEX(Natives.GET_PLAYER_ID()), out PlayerPedHandle);
            Natives.GET_CAR_CHAR_IS_USING(PlayerPedHandle, out PlayerVehicleHandle);

            // Process ScriptHookDotNet stuff
            SHDNManager.Process();

            Secrittzzz.Process();

            // - - - - Native Calling Test - - - -
            //uint playerId = ManagedNativeCaller.Call<uint>(IVSDKDotNet.Native.eNativeHash.NATIVE_GET_PLAYER_ID);
            //int playerIndex = ManagedNativeCaller.Call<int>(IVSDKDotNet.Native.eNativeHash.NATIVE_CONVERT_INT_TO_PLAYERINDEX, (NativeArg)playerId);

            //NativeArg playerChar = new NativeArg(true, typeof(int));
            //ManagedNativeCaller.Call(IVSDKDotNet.Native.eNativeHash.NATIVE_GET_PLAYER_CHAR, (NativeArg)playerIndex, playerChar);

            //NativeArg playerCoordX = new NativeArg(true, typeof(float));
            //NativeArg playerCoordY = new NativeArg(true, typeof(float));
            //NativeArg playerCoordZ = new NativeArg(true, typeof(float));
            //ManagedNativeCaller.Call(IVSDKDotNet.Native.eNativeHash.NATIVE_GET_CHAR_COORDINATES, playerChar.Reuse(), playerCoordX, playerCoordY, playerCoordZ);

            //System.Numerics.Vector3 vec = new System.Numerics.Vector3(playerCoordX, playerCoordY, playerCoordZ);
            //ManagedNativeCaller.Call(IVSDKDotNet.Native.eNativeHash.NATIVE_DRAW_CHECKPOINT, (NativeArg)vec, (NativeArg)1f, (NativeArg)255, (NativeArg)255, (NativeArg)255);


            //NativeArgument arg1 = new NativeArgument(true, typeof(int));
            //NativeCaller.Call((uint)IVSDKDotNet.Native.eNativeHash.NATIVE_GET_MOUSE_WHEEL, arg1);
            //SHDN_ShowMessage(arg1.GetValue<int>().ToString(), 4000);

            // ManagedNativeCaller.Call<uint>((uint)eNativeHash.NATIVE_PRINT_STRING_WITH_LITERAL_STRING_NOW, (NativeArg)"STRING", (NativeArg)"Test!", (NativeArg)(uint)1000, (NativeArg)true);
            
            // Start constructing all scripts
            if (!wasLoadingMessageShown && !Natives.IS_SCREEN_FADED_OUT() && !ScriptManager.AreAllScriptsConstructed())
            {
                wasLoadingMessageShown = true;

                Natives.PAUSE_GAME();
                Natives.TRIGGER_LOADING_MUSIC_ON_NEXT_FADE();
                Natives.FORCE_LOADING_SCREEN(true);

                // Store and replace text of text label
                string originalText = IVText.TheIVText.Get(0x5B52D1DE, string.Empty);
                IVText.TheIVText.ReplaceTextOfTextLabel(0x5B52D1DE, "Waiting for scripts to finish constructing...");

                // Unnecessary, but i do like the user to atleast see the text once so they know the scripts are currently constructing
                // Also they get to hear the loading music which is nice (even tho it kicks in relatively late, but i deffo dont want to wait just for the music to begin)
                ThreadManager.ForceWaitWhileProcessingWindowMessages(TimeSpan.FromSeconds(3d));

                // Launching the script threads will start to construct all scripts that have not been constructed yet
                ScriptManager.CreateAndLaunchAllScriptThreads();

                // Wait for all scripts to finish constructing so that this method is not leaving the stack and
                // potentionally corrupt certain things because the gtathread is switching from the dummy thread
                // back to its original thread.
                while (!ScriptManager.AreAllScriptsConstructed())
                {
                    IVGrcWindow.ProcessWindowMessage(); // Keep processing window messages so the OS doesnt think the game froze

                    // Show progress to user
                    ScriptManager.GetConstructedScriptsCount(out int constructedScripts, out int scriptsToConstruct);
                    IVText.TheIVText.ReplaceTextOfTextLabel(0x5B52D1DE, string.Format("Constructing script {0} out of {1}...", constructedScripts, scriptsToConstruct));

                    ThreadManager.ForceAllScriptThreadsToTick(); // Keep them threads tickin'
                    System.Threading.Thread.Sleep(1);
                }

                // Restore text of text label back to original
                IVText.TheIVText.ReplaceTextOfTextLabel(0x5B52D1DE, originalText);

                Natives.UNPAUSE_GAME();
                Natives.PLAY_SOUND_FRONTEND(-1, "GENERAL_FRONTEND_GAME_INFO_BEEP_LEFT");
                Natives.PLAY_SOUND_FRONTEND(-1, "GENERAL_FRONTEND_GAME_INFO_BEEP_RIGHT");
                Natives.FORCE_LOADING_SCREEN(false);
            }

            // Raise all plugin Tick events
            PluginManager.RaiseTick();

            // Raise all script Tick events
            ScriptManager.RaiseTick();

            // Process bound phone numbers of scripts
            IVPhoneInfo phoneInfo = IVPhoneInfo.ThePhoneInfo;

            if (phoneInfo != null)
            {
                switch ((ePhoneState)phoneInfo.State)
                {
                    case ePhoneState.Hidden:

                        // Reset state
                        wasBoundPhoneNumbersProcessed = false;

                        break;

                    case ePhoneState.CalledNumberBusy:

                        if (!wasBoundPhoneNumbersProcessed)
                        {

                            // Process dialed number
                            ScriptManager.RaiseBoundPhoneNumberAction(phoneInfo.CurrentNumberInput);

                            wasBoundPhoneNumbersProcessed = true;
                        }

                        break;
                }
            }
        }
        public override void RaiseGameLoad()
        {
            // Raise all plugin GameLoad events
            PluginManager.RaiseGameLoad();

            // Raise all script GameLoad events
            ScriptManager.RaiseGameLoad();
        }
        public override void RaiseGameLoadPriority()
        {
            // Raise all plugin GameLoadPriority events
            PluginManager.RaiseGameLoadPriority();

            // Raise all script GameLoadPriority events
            ScriptManager.RaiseGameLoadPriority();
        }
        public override void RaiseMountDevice()
        {
            // Raise all plugin MountDevice events
            PluginManager.RaiseMountDevice();

            // Raise all script MountDevice events
            ScriptManager.RaiseMountDevice();
        }
        public override void RaiseDrawing()
        {
            if (Config.PauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

            // Raise all script Drawing events
            ScriptManager.RaiseDrawing();
        }
        public override void RaiseProcessCamera()
        {
            if (Config.PauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

            // Raise all script ProcessCamera events
            ScriptManager.RaiseProcessCamera();
        }
        public override void RaiseProcessAutomobile(UIntPtr vehPtr)
        {
            if (Config.PauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

            // Raise all script ProcessAutomobile events
            ScriptManager.RaiseProcessAutomobile(vehPtr);
        }
        public override void RaiseProcessPad(UIntPtr padPtr)
        {
            // Store data of this thread
            ThreadManager.StoreGameThreadData(GameThread.MainThread);

            // Update the remote server
            ConnectionManager.Update();

            if (Config.PauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

            // Do stuff on first frame
            if (FirstFrame)
            {
                if (Config.EnableAutomaticUpdateCheck)
                    UpdateChecker.CheckForUpdates(true);

                GetSupporters();
                FirstFrame = false;
            }

            // Check for key presses
            if (keyWatchDog != null)
                keyWatchDog.Process();

            // Raise all script ProcessPad events
            ScriptManager.RaiseProcessPad(padPtr);
        }
        public override void RaiseOnD3D9Frame(IntPtr devicePtr, ImGuiIV_DrawingContext ctx)
        {
            if (!ImGuiIV.WasImGuiInitialized || !allowDrawing || isShuttingDown)
                return;

            // Adjust global font scale dynamically
            ImGuiIV_IO imguiIO = ImGuiIV.GetIO();
            imguiIO.FontGlobalScale = Config.GlobalFontScale;

            // Process the thread manager
            ThreadManager.ProcessRenderThread();

            GlobalDrawCtx = ctx;

            // Store data of this thread
            ThreadManager.StoreGameThreadData(GameThread.RenderThread);

            DelayedActionManager.Process();

            // Reset ImGui style to default for script/plugin windows
            UIStyles.ResetImGuiStyle();

            // Raise all plugin OnImGuiGlobalRendering events
            PluginManager.RaiseOnImGuiGlobalRenderingEvent(devicePtr, ctx);

            // Allow the draw thread to tick which then allows every script do be able to draw stuff
            drawThread.TickNow();

            // Set internal custom style
            if (Config.UseCustomThemeForManagerAndConsole)
                UIStyles.SetImGuiPurpleStyle();

            // Show pending popups
            if (currentPopup == null)
            {
                // Get a new pending popup
                if (pendingPopups.Count != 0)
                {
                    currentPopup = pendingPopups.Dequeue();
                    currentPopup.Open();
                }
            }
            else
            {
                if (!currentPopup.Show())
                    currentPopup = null;
            }

            // Draw internal stuff
            ConsoleUI.DoUI();
            NotificationUI.DoUI();
            ManagerUI.DoUI(devicePtr, ctx);
        }
        public override void RaiseOnBeforeNewImGuiFrame(IntPtr devicePtr)
        {
            if (!ImGuiIV.WasImGuiInitialized || !allowDrawing)
                return;

            SHDNManager.OnBeforeNewImGuiFrame();
        }
        public override void RaiseIngameStartup()
        {
            wasLoadingMessageShown = false;

            if (Config.ReloadScriptsOnReload)
                ScriptManager.LoadIVSDKDotNetScripts();

            // ScriptHookDotNet scripts need to be reloaded
            ScriptManager.LoadSHDNScripts();

            // Raise all script IngameStartup events
            ScriptManager.RaiseIngameStartup();
        }

        private void KeyWatchDog_KeyDown(object sender, KeyEventArgs e)
        {
            if (Config.PauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

            // Check for key stuff
            KeyChecker.CheckAll(e);

            if (DisableKeyEvents)
                return;

            // Raise all script KeyDown events
            ScriptManager.RaiseKeyDown(sender, e);
        }
        private void KeyWatchDog_KeyUp(object sender, KeyEventArgs e)
        {
            if (Config.PauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

            if (DisableKeyEvents)
                return;

            // Raise all script KeyUp events
            ScriptManager.RaiseKeyUp(sender, e);
        }

        private void Console_OnConsoleCommand(string command, string[] args)
        {
            ScriptManager.RaiseOnConsoleCommand(command, args);
        }
        #endregion

#region Methods

#if PREVIEW
        private void CheckPreviewBuild()
        {
            string previewDatFilePath = Path.Combine(CLR.CLRBridge.IVSDKDotNetDataPath, "preview.dat");
            previewDatFile = new SettingsFile(previewDatFilePath);

            bool canShowDialog = false;

            // Try loading the file
            if (previewDatFile.Load())
            {
                // Check if loaded file is valid
                if (!previewDatFile.DoesSectionExists("Preview"))
                {
                    previewDatFile.Clear();
                    previewDatFile.AddSection("Preview");
                    previewDatFile.AddKeyToSection("Preview", "Version");
                    return;
                }

                // Check if dialog was already shown for current preview version
                canShowDialog = previewDatFile.GetValue("Preview", "Version", "0") != CLR.CLRBridge.Version;
            }
            else // File does not exists
            {
                try
                {
                    File.Create(previewDatFilePath).Dispose();
                    previewDatFile.AddSection("Preview");
                    previewDatFile.AddKeyToSection("Preview", "Version");
                    canShowDialog = true;
                }
                catch (Exception) { }
            }

            if (canShowDialog)
            {
                // Show popup
                AddPendingPopup(new ImPopup(
                    "IV-SDK .NET Preview Version",
                    string.Format("This is a preview version of IV-SDK .NET v{1}, which means it's only meant to be a preview of what to expect in the final update.{0}" +
                    "You usually only get this preview when you got an active Patreon/Ko-fi subscription. So if that's the case, thank you!{0}" +
                    "If you got this preview build from somewhere else, maybe consider supporting my work and get access to more preview stuff!{0}{0}" +
                    "If you encounter any bugs or got any suggestions, be sure to share them on my discord server or on the gtaforums IV-SDK .NET thread!", Environment.NewLine, CLR.CLRBridge.Version),
                    true,
                    "Understood",
                    null,
                    () =>
                    {
                        // Save that dialog was shown for current preview version
                        previewDatFile.SetValue("Preview", "Version", CLR.CLRBridge.Version);
                        previewDatFile.Save();

                        previewDatFile.Clear();
                        previewDatFile = null;
                    },
                    null));
            }
        }
#endif
        private void CheckFirstStart()
        {
            string path = Path.Combine(CLR.CLRBridge.IVSDKDotNetDataPath, "noFirstStart.dat");
            
            // Check if this is the first start or not
            if (!File.Exists(path))
            {
                // This is the first start
                try
                {
                    File.Create(path).Dispose();
                }
                catch (Exception){}

                // Show popup
                AddPendingPopup(new ImPopup(
                    "Welcome to IV-SDK .NET!",
                    "It looks like this is your first time using IV-SDK .NET. " +
                    "To get started, check out the official documentation to learn everything about IV-SDK .NET.",
                    true,
                    "Understood",
                    "View Documentation",
                    null,
                    () =>
                    {
                        Process.Start(""); // TODO: Give it the link!
                    }));
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

        public void DestroyGlobalRegisteredTextures()
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

        public void AddPendingPopup(ImPopup popup)
        {
            pendingPopups.Enqueue(popup);
        }

#endregion

        #region Functions

        public Guid StartNewTimerInternal(int interval, Action actionToExecute)
        {
            // Create task
            AdvancedTask task = new AdvancedTask(Guid.NewGuid(), Guid.Empty, TaskUseCase.Timer, interval);

            // Start task
            bool r = task.Start(TaskCreationOptions.LongRunning, () => AdvancedTask.TimerStatic(task, actionToExecute), (TaskData args) =>
            {
                // If the task ends, a delayed action will start which gets rid of the task in 5 seconds
                DelayedActionManager.StartDelayedAction(
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
        public override void InitializationFinished(SettingsFile settings)
        {
            // Apply settings
            Config.ApplySettings(settings);

            // Late initialize SHDN stuff
            SHDNManager.LoadIncludedScriptHookDotNetAssembly();
            if (Config.LoadScriptHookDotNetScripts && !CLR.CLRBridge.DisableScriptHookDotNetLoading)
            {
                SHDNManager.Init();
                SHDNContentCacheManager.Init();
            }

            // Start the server if allowed
            if (Config.AllowRemoteConnections)
                ConnectionManager.Start(false);

            // Automatically load scripts
            if (!Config.DisableScriptLoadOnStartup)
            {
                ScriptManager.LoadScriptsInternal();
            }

            allowDrawing = true;
        }
        public override void Shutdown()
        {
            try
            {
                // Tell all plugins that the manager is shutting down
                PluginManager.RaiseOnShutdown();

                // Log
                Logger.LogDebug("Manager is starting to shut down...");

                isShuttingDown = true;

                ConsoleUI.Shutdown();
                NotificationUI.Shutdown();

                // Stop remote server
                ConnectionManager.Dispose();

                // Abort all currently running scripts
                ScriptManager.AbortScripts(ScriptType.All, AbortReason.Manager);

                // Abort all currently running plugins
                PluginManager.UnloadPlugins(AbortReason.Manager, false);

                // Destroy keyWatchDog
                if (keyWatchDog != null)
                {
                    keyWatchDog.Dispose();
                    keyWatchDog = null;
                }

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

                    ActiveTasks.Clear();
                }

                // Clear lists
                pendingPopups.Clear();
                TierOneSupporters.Clear();
                TierTwoSupporters.Clear();
                TierThreeSupporters.Clear();

                // Cleanup managers
                DelayedActionManager.Shutdown();
                FileCacheManager.Shutdown();
                MinHookManager.Shutdown();
                ScriptManager.Shutdown();
                PluginManager.Shutdown();
                SHDNContentCacheManager.Shutdown();
                SHDNManager.Shutdown();
                TaskManager.Shutdown();
                ThreadManager.Shutdown();

                Logger.LogDebug("Manager finished its shutting down process!");
            }
            catch (Exception ex)
            {
                Logger.LogErrorEx("Error while shutting down the manager script! Details: {0}", ex);
            }
        }
        #endregion

        #region Script Stuff
        public override void LoadScripts()
        {
            ScriptManager.LoadScriptsInternal();
        }

        public override bool AbortScript(Guid id)
        {
            return ScriptManager.AbortScriptInternal(AbortReason.Script, id, true);
        }

        public override Script GetScript(Guid id)
        {
            return ScriptManager.GetIVSDKDotNetScript(id);
        }
        public override Script GetScript(string name)
        {
            return ScriptManager.GetIVSDKDotNetScript(name);
        }
        public override bool IsScriptRunning(Guid id)
        {
            FoundScript foundScript = ScriptManager.GetFoundScript(id);

            if (foundScript != null)
                return foundScript.IsScriptReady();

            return false;
        }
        public override bool IsScriptRunning(string name)
        {
            FoundScript foundScript = ScriptManager.GetFoundScript(name);

            if (foundScript != null)
                return foundScript.IsScriptReady();

            return false;
        }

        public override bool IsIVSDKDotNetScript(Guid id)
        {
            FoundScript script = ScriptManager.GetFoundScript(id);

            if (script != null)
                return script.IsIVSDKDotNetScript;

            return false;
        }
	    public override bool IsIVSDKDotNetScript(string name)
        {
            FoundScript script = ScriptManager.GetFoundScript(name);

            if (script != null)
                return script.IsIVSDKDotNetScript;

            return false;
        }

        public override string GetScriptName(Guid id)
        {
            FoundScript foundScript = ScriptManager.GetFoundScript(id);

            if (foundScript != null)
                return foundScript.EntryPoint.FullName;

            return string.Empty;
        }
        public override string GetScriptFullPath(Guid id)
        {
            FoundScript foundScript = ScriptManager.GetFoundScript(id);

            if (foundScript != null)
                return foundScript.TheFileInfo.FullPath;

            return string.Empty;
        }
        public override int GetActiveScriptsCount()
        {
            return ScriptManager.GetActiveScriptsCount();
        }

        public override bool SendScriptCommand(Guid sender, Guid toScript, string command, object[] parameters, out object result)
        {
            return ScriptManager.SendScriptCommand(sender, toScript, command, parameters, out result);
        }
        public override bool SendScriptCommand(Guid sender, string toScript, string command, object[] parameters, out object result)
        {
            return ScriptManager.SendScriptCommand(sender, toScript, command, parameters, out result);
        }

        // TODO: Get rid of these probably
        public override Guid StartNewTask(Guid forScript, Func<object> funcToExecute, Action<object> continueWithAction)
        {
            FoundScript s = ScriptManager.GetFoundScript(forScript);

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
                    DelayedActionManager.StartDelayedAction(
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
            FoundScript s = ScriptManager.GetFoundScript(forScript);

            if (s != null)
            {
                // Create task
                AdvancedTask task = new AdvancedTask(Guid.NewGuid(), s.ID, TaskUseCase.Timer, interval);

                // Start task
                bool r = task.Start(TaskCreationOptions.LongRunning, () => AdvancedTask.TimerStatic(task, actionToExecute), (TaskData args) =>
                {
                    // If the task ends, a delayed action will start which gets rid of the task in 5 seconds
                    DelayedActionManager.StartDelayedAction(
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

        #region Plugin
        public override void LoadPlugins()
        {
            // Load plugins if allowed
            if (Config.AllowPluginLoading)
                PluginManager.LoadPlugins();
        }
        #endregion

        #region Direct3D9 Stuff

        // Texture stuff
        public override void Direct3D9_RegisterScriptTexture(string forScript, IntPtr ptr)
        {
            // Get script from ID
            FoundScript fs = ScriptManager.GetFoundScript(forScript);

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

        #region Hooking Stuff
        public override bool MinHook_RegisterHook(string ofScript, uint address)
        {
            return MinHookManager.RegisterHook(address, ofScript);
        }
        #endregion

        #region Console
        public override void OpenConsole()
        {
            ConsoleUI.Open();
        }
        public override void CloseConsole()
        {
            ConsoleUI.Close();
        }
        public override void ClearConsole()
        {
            ConsoleUI.Clear();
        }

        public override bool IsConsoleOpen()
        {
            return ConsoleUI.IsConsoleOpen;
        }

        public override bool RegisterConsoleCommand(Guid fromScript, string name, Action<string[]> actionToExecute)
        {
            // Get script by id
            FoundScript fs = ScriptManager.GetFoundScript(fromScript);

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
            return ConsoleUI.ExecuteCommand(name);
        }

        public override string GetLastConsoleCommand()
        {
            return ConsoleUI.GetLastConsoleCommand();
        }
        public override void ResetLastConsoleCommand()
        {
            ConsoleUI.ResetLastConsoleCommand();
        }
        #endregion

        #region Phone
        public override bool RegisterPhoneNumber(Guid forScript, string number, Action dialedAction)
        {
            if (string.IsNullOrWhiteSpace(number))
                return false;
            if (dialedAction == null)
                return false;

            FoundScript fs = ScriptManager.GetFoundScript(forScript);

            if (fs != null)
                return fs.AddPhoneNumber(number, dialedAction);

            return false;
        }
        public override bool UnregisterPhoneNumber(Guid fromScript, string number)
        {
            if (string.IsNullOrWhiteSpace(number))
                return false;

            FoundScript fs = ScriptManager.GetFoundScript(fromScript);

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
        public override void GetPlayerAndCurrentVehicleHandle(out int playerHandle, out int vehicleHandle)
        {
            playerHandle = PlayerPedHandle;
            vehicleHandle = PlayerVehicleHandle;
        }
        #endregion

        #region Thread

        public override void WaitInScript(Guid id, int milliseconds)
        {
            if (id != Guid.Empty)
            {
                // Try to wait in the target script
                FoundScript fs = ScriptManager.GetFoundScript(id);

                if (fs != null)
                {
                    Helper.WriteToDebugOutput(Priority.Default, "Script '{0}' wants to wait for {1}ms.", fs.EntryPoint.FullName, milliseconds);
                    fs.Wait(milliseconds);
                }
            }
            else
            {
                // Try to wait in the current thread if no target script id was provided
                ThreadManager.WaitInThread(GetCurrentThreadID(), milliseconds);
            }
        }
        public override object GetScriptThisThreadIsOwnedBy()
        {
            if (ThreadManager.TryGetThread(GetCurrentThreadID(), out NetThread thread))
            {
                if (thread.Type == ThreadType.ScriptThread)
                {
                    FoundScript fs = (thread as ScriptThread).OwnerScript;

                    if (!fs.IsScriptReady())
                        return null;

                    return fs.GetTheScriptObject();
                }
            }

            return null;
        }

        // Dispatches the native call to the main thread to be invoked there
        // If the current thread is already the main thread, the native will get invoked directly
        public override void DispatchNativeCall(uint hash, UIntPtr contextPointer)
        {
            if (!ThreadManager.IsGameThreadDataAvailable(GameThread.MainThread))
            {
#if DEBUG
                Helper.BreakInDebugger();
#else
                return;
#endif
            }

            // Check if native call can be invoked directly or if we need to do some trickery
            if (ThreadManager.IsCurrentThreadTheMainThread())
            {
                // Called from main thread, can be invoked directly
                IVNativeInvoke.Invoke(hash, contextPointer, ThreadManager.GetCurrentThreadID());
            }
            else
            {
                // Store the thread id this native function was called from before we change tls context
                int callerThreadId = ThreadManager.GetCurrentThreadID();

                // Invoke the native with tls context of main thread
                ThreadManager.SetCurrentThreadTlsContextToMainThreadContextAndExecute(() =>
                {
                    IVNativeInvoke.Invoke(hash, contextPointer, callerThreadId);
                });
            }
        }

        public override int GetMainThreadID()
        {
            return ThreadManager.GetGameThreadData(GameThread.MainThread).ThreadID;
        }
        public override int GetCurrentThreadID()
        {
            return ThreadManager.GetCurrentThreadID();
        }
        public override bool IsThisThreadTheScriptRenderThread(int threadId)
        {
            return threadId == drawThread.ThreadId;
        }  

        public override void ThreadManager_StoreCurrentThreadTlsContext()
        {
            ThreadManager.StoreCurrentThreadTlsContext();
        }
        public override void ThreadManager_ChangeTlsContextOfCurrentThreadToContextOfTargetThread(int gameThreadId)
        {
            ThreadManager.ChangeTlsContextOfCurrentThreadToContextOfTargetThread((GameThread)gameThreadId);
        }
        public override void ThreadManager_RestoreTlsContextForCurrentThread()
        {
            ThreadManager.RestoreTlsContextForCurrentThread();
        }

        #endregion

        #region Native

        public override T CallNativeUsingManagedNativeCaller<T>(uint hash, NativeArg[] args)
        {
            //NativeArg[] nativeArgs = new NativeArg[args.Length];

            //// Convert args to native args
            //for (int i = 0; i < nativeArgs.Length; i++)
            //{
            //    object arg = args[i];

            //    // Check if object is null, which means it should be an out-parameter
            //    if (arg == null)
            //    {
            //        nativeArgs[i] = new NativeArg(true, arg.GetType());
            //        continue;
            //    }

            //    nativeArgs[i] = NativeArg.FromObject(arg);
            //}
            
            // Call native
            return ManagedNativeCaller.Call<T>(hash, args);

            //// Set out-parameters
            //for (int i = 0; i < nativeArgs.Length; i++)
            //{
            //    object arg = args[i];

            //    // Check if object is null, which means it is an out-parameter
            //    if (arg == null)
            //    {
            //        // Set out-parameter value
            //        args[i] = nativeArgs[i].Value;
            //    }
            //}
        }

        public override uint TryGetNativeHashByName(string name)
        {
            if (ManagedNativeCaller.TryGetNativeHashFromString(name, out uint hash))
                return hash;

            return 0U;
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

            FoundScript fs = ScriptManager.GetFoundScript(name);

            if (fs != null)
            {
                Helper.WriteToDebugOutput(Priority.Default, "Found FoundScript object for late initialization of ScriptHookDotNet script {0}!", name);
                assemblyFullPath = fs.TheFileInfo.FullPath;
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
            FoundScript fs = ScriptManager.GetFoundScript(name);

            if (fs != null)
                return fs.GetTheScriptObject();

            return null;
        }
        public override object SHDN_GetScriptByGUID(Guid id)
        {
            FoundScript fs = ScriptManager.GetFoundScript(id);

            if (fs != null)
                return fs.GetTheScriptObject();

            return null;
        }

        public override Guid SHDN_GetIdOfCurrentExecutingScript()
        {
            if (ThreadManager.TryGetThread(ThreadManager.GetCurrentThreadID(), out NetThread thread))
            {
                // This was called from within a script so it should be a script thread
                if (thread.Type != ThreadType.ScriptThread)
                    return Guid.Empty;

                return (thread as ScriptThread).OwnerScript.ID;
            }

            return Guid.Empty;
        }
        public override object SHDN_GetCurrentScript(int iEvent)
        {
            return SHDNManager.GetCurrentScript(iEvent);
        }
        public override void SHDN_SetCurrentScript(int iEvent, object script)
        {
            SHDNManager.SetCurrentScript(iEvent, script);
        }

        public override void SHDN_AddFont(object obj)
        {
            if (obj == null)
            {
                Logger.LogDebug(string.Format("Given font object was null! Will not add to queue."));
                return;
            }

            SHDNManager.AddFont(obj);
            Logger.LogDebug("Successfully added new shdn font to queue!");
        }

        public override bool SHDN_VerboseLoggingEnabled()
        {
            return SHDNManager.EnableVerboseLogging;
        }
        public override bool SHDN_NativeCallLoggingEnabled()
        {
            return SHDNManager.NativeCallLoggingEnabled;
        }
        public override bool SHDN_IsScriptRunning(Guid id)
        {
            FoundScript fs = ScriptManager.GetFoundScript(id);

            if (fs != null)
                return fs.IsScriptReady();

            return false;
        }

        public override void SHDN_ShowMessage(string str, int time)
        {
            SHDNManager.SetMessageToShow(str);
            SHDNManager.SetMessageTime(time);
        }

        public override void SHDNCache_AddEntity(Guid ownerScript, object entity)
        {
            SHDNContentCacheManager.AddEntity(ownerScript, entity);
        }
        public override void SHDNCache_RemoveEntity(object entity)
        {
            SHDNContentCacheManager.RemoveEntity(entity);
        }
        public override void SHDNCache_RemoveEntity(int handle)
        {
            SHDNContentCacheManager.RemoveEntity(handle);
        }
        public override object SHDNCache_GetEntity(int handle, int requestedType, Guid ownerScript)
        {
            return SHDNContentCacheManager.GetEntity(handle, requestedType, ownerScript);
        }

        public override void SHDNCache_AddPlayer(object player)
        {
            SHDNContentCacheManager.AddPlayer(player);
        }
        public override void SHDNCache_RemovePlayer(object player)
        {
            SHDNContentCacheManager.RemovePlayer(player);
        }
        public override object SHDNCache_GetPlayer(int id)
        {
            return SHDNContentCacheManager.GetPlayer(id);
        }
        #endregion

        #endregion

    }
}