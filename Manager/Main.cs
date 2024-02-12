using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using IVSDKDotNet;
using IVSDKDotNet.Enums;
using IVSDKDotNet.Manager;

using Manager.Classes;
using Manager.Managers;
using Manager.UI;

//using ScriptHookDotNet = GTA;

namespace Manager
{
    public class Main : ManagerScript
    {
        #region Variables
        internal static Main Instance;

        // Lists
        public List<FoundScript> ActiveScripts;
        public List<AdvancedTask> LocalTasks;
        public List<DelayedAction> DelayedActions;

        // public List<ScriptHookDotNet.Script> ScriptHookDotNetScripts = new List<ScriptHookDotNet.Script>();

        // Managers
        public RemoteConnectionManager ConnectionManager;

        // UI
        public ConsoleUI Console;
        public NotificationUI Notification;

        // Hooks
        private KeyWatchDog keyWatchDog;

        // Other
        public Version CurrentWrapperVersion;
        public UpdateChecker UpdateChecker;
        public Process GTAIVProcess;
        private Guid processCheckerTimerID;
        internal Script DummyScript;

        public bool FirstFrame = true;
        public bool IsGTAIVWindowInFocus;
        public bool OnWindowFocusChangedEventCalled;
        private int lastLogLineCount;
        #endregion

        #region Events

        // Assembly
        private Assembly CurrentDomain_AssemblyResolve(object sender, ResolveEventArgs args)
        {
            string assemblyName = args.Name.Split(',')[0];
            string assemblyPath = string.Format("{0}\\{1}.dll", CLR.CLRBridge.IVSDKDotNetBinaryPath, assemblyName);

            if (File.Exists(assemblyPath))
                return Assembly.UnsafeLoadFrom(assemblyPath);

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

            // Lists
            ActiveScripts =     new List<FoundScript>();
            LocalTasks =        new List<AdvancedTask>();
            DelayedActions =    new List<DelayedAction>();

            // Managers
            ConnectionManager = new RemoteConnectionManager();

            // UI
            Console = new ConsoleUI();
            Notification = new NotificationUI();

            // Subscribe to AppDomain events
            AppDomain.CurrentDomain.AssemblyResolve += CurrentDomain_AssemblyResolve;

            // TODO: Might remove KeyWatchDog and replace with ImGui key events
            keyWatchDog =   new KeyWatchDog();
            keyWatchDog.KeyDown +=  KeyWatchDog_KeyDown;
            keyWatchDog.KeyUp +=    KeyWatchDog_KeyUp;

            // Other
            UpdateChecker = new UpdateChecker(CLR.CLRBridge.Version, "https://www.dropbox.com/s/smaz6ij8dkzd7nh/version.txt?dl=1");
            UpdateChecker.VersionCheckFailed +=     UpdateChecker_VersionCheckFailed;
            UpdateChecker.VersionCheckCompleted +=  UpdateChecker_VersionCheckCompleted;

            GTAIVProcess = Process.GetCurrentProcess();

            // Start process in focus checker timer
            processCheckerTimerID = StartNewTimerInternal(1000, () =>
            {

                IsGTAIVWindowInFocus = Helper.ProcessHelper.IsProcessInFocus(GTAIVProcess);

                // Invoke focus changed event
                if (IsGTAIVWindowInFocus)
                {
                    if (!OnWindowFocusChangedEventCalled)
                    {
                        RaiseWindowFocusChanged(true);
                        OnWindowFocusChangedEventCalled = true;
                    }
                }
                else
                {
                    if (OnWindowFocusChangedEventCalled)
                    {
                        RaiseWindowFocusChanged(false);
                        OnWindowFocusChangedEventCalled = false;
                    }
                }

            });
        }
        #endregion

        #region Raisers
        public override void RaiseTick()
        {
            if (Config.PauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

            // Raise all script Tick events
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
        }
        public override void RaiseGameLoad()
        {
            if (Config.PauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

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
            if (Config.PauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

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
            if (Config.PauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

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

            DateTime dtNow = DateTime.UtcNow;

            // Execute Delayed Actions if there are any
            for (int i = 0; i < DelayedActions.Count; i++)
            {
                DelayedAction dA = DelayedActions[i];
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
                    }
                }
            }

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
                FirstFrame = false;
            }

            // Check for key presses
            if (keyWatchDog != null)
                keyWatchDog.ProcessCheck();

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
        public override void RaiseUIRendering()
        {
            // Raise all script OnFirstD3D9Frame events
            ActiveScripts.ForEach(fs =>
            {
                try
                {
                    fs.RaiseOnFirstD3D9Frame();
                }
                catch (Exception ex)
                {
                    HandleScriptException(fs, 8d, "OnFirstD3D9Frame", ex);
                }
            });

            // Draw internal stuff
            Console.DoUI();
            Notification.DoUI();
            ManagerUI.DoUI();
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

            // Raise local things
            if (Console != null)
                Console.KeyDown(e);

            // Check stuff
            Checker.CheckSwitchCursorKeyPressed(e);
            Checker.CheckOpenManagerWindowKeyPressed(e);

            // Raise all script KeyDown events
            ActiveScripts.ForEach(fs =>
            {
                try
                {
                    if (fs.TheScript.OnlyRaiseKeyEventsWhenInGame)
                    {
                        if (IVPlayerInfo.FindThePlayerPed() != UIntPtr.Zero)
                            fs.RaiseKeyDown(e);
                    }
                    else
                    {
                        fs.RaiseKeyDown(e);
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

            // Raise all script KeyUp events
            ActiveScripts.ForEach(fs =>
            {
                try
                {
                    if (fs.TheScript.OnlyRaiseKeyEventsWhenInGame)
                    {
                        if (IVPlayerInfo.FindThePlayerPed() != UIntPtr.Zero)
                            fs.RaiseKeyUp(e);
                    }
                    else
                    {
                        fs.RaiseKeyUp(e);
                    }
                }
                catch (Exception ex)
                {
                    HandleScriptException(fs, 8d, "KeyUp", ex);
                }
            });
        }
        #endregion

        #region Methods

        // Load stuff
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

        private bool HandleShdnAssembly(string rawFileName, string fileName, Assembly assembly)
        {
#if !DEBUG
            Logger.LogWarning(string.Format("The file {0} was recognized as a ScriptHookDotNet script, which are currently not supported by IV-SDK .NET.", rawFileName));
            Notification.ShowNotification(NotificationType.Default, DateTime.UtcNow.AddSeconds(5d), "Unsupported Script", string.Format("The file {0} was recognized as a ScriptHookDotNet script, which are currently not supported by IV-SDK .NET.", rawFileName), "UNSUPPORTED_SCRIPT");
            return false;
#else
            Type[] types = assembly.GetTypes();

            for (int i = 0; i < types.Length; i++)
            {
                Type t = types[i];

                if (t != null)
                    Logger.LogDebug(string.Format("Types of {0}: FullName: {1}, Base: {2}", fileName, t.FullName, t.BaseType.FullName));
            }

            //Type scriptType = assembly.GetTypes().Where(x => x.IsSubclassOf(typeof(ScriptHookDotNet.Script))).FirstOrDefault();
            Type scriptType = null;

            if (scriptType != null)
            {
                //ScriptHookDotNet.Script script = (ScriptHookDotNet.Script)assembly.CreateInstance(scriptType.FullName);
                //ScriptHookDotNetScripts.Add(script);

                Logger.LogDebug("Created new instance of shdn script!");
            }
            else
            {
                Logger.LogDebug("Could not find shdn script entry-point!");
            }

            return true;
#endif
        }
        public bool LoadAssembly(string path)
        {
            if (string.IsNullOrWhiteSpace(path))
                return false;

            // Get file name with and without extension from given path
            string rawFileName = Path.GetFileName(path);
            string fileName = Path.GetFileNameWithoutExtension(path);

            bool isIVSDKDotNetScript = false;
            bool isScriptHookDotNetScript = false;

            // Check if fileName contains the .ivsdk AND .net part
            if (fileName.Contains(".ivsdk") && fileName.Contains(".net"))
            {
                Logger.LogWarning(string.Format("Couldn't determine for what kind of SDK the file {0} is supposed to be " +
                    "because it contains both the extensions for a IV-SDK .NET (.ivsdk) and for a ScriptHookDotNet (.net) script.", rawFileName));
                return false;
            }

            // Check for which SDK this script is supposed to be
            isIVSDKDotNetScript = fileName.Contains(".ivsdk");
            isScriptHookDotNetScript = fileName.Contains(".net");

            // Remove extensions
            fileName = fileName.Replace(".ivsdk", "").Replace(".net", "");

            // Check result
            if (!isIVSDKDotNetScript && !isScriptHookDotNetScript)
            {
                Logger.LogWarning(string.Format("The file {0} could not be recognized as a IV-SDK .NET Script because it's missing the '.ivsdk' extension.", rawFileName));
                return false;
            }

            // Check if script is already loaded
            FoundScript foundScript = GetFoundScript(fileName);

            if (foundScript != null)
            {
                Logger.LogWarning(string.Format("Script {0} is already loaded.", fileName));
                return false;
            }

            // Try loading the Script
            try
            {
                using (FileStream fs = new FileStream(path, FileMode.Open, FileAccess.Read))
                {
                    // Get byte array from file stream
                    byte[] fileByteArray = Helper.GetByteArray(fs);

                    // Load the assembly into the domain
                    Assembly assembly = Assembly.Load(fileByteArray);
                    
                    // If script is a ScriptHookDotNet script then handle it differently
                    if (isScriptHookDotNetScript)
                        return HandleShdnAssembly(rawFileName, fileName, assembly);

                    // Get the first class that inherites from the IVSDKDotNet.Script class
                    Type scriptType = assembly.GetTypes().Where(x => x.IsSubclassOf(typeof(Script))).FirstOrDefault();

                    // Could not find any classes that inherit the IVSDKDotNet.Script class
                    if (scriptType == null)
                    {
                        Logger.LogWarning(string.Format("Could not load script {0} because the entry-point for IV-SDK .NET could not be found.", fileName));
                        return false;
                    }

                    // Log
                    Logger.Log(string.Format("Found script: {0}", scriptType.FullName));

                    // Check if script was made with an older IVSDKDotNetWrapper version
                    if (Config.DoNotLoadLegacyScripts)
                    {
                        AssemblyName referencedWrapperAssembly = assembly.GetReferencedAssemblies().Where(x => x.Name == "IVSDKDotNetWrapper").FirstOrDefault();

                        if (referencedWrapperAssembly.Version < CurrentWrapperVersion)
                        {

                            Logger.LogWarning(string.Format("Script {0} did not get loaded because it was created with an older version of the IVSDKDotNetWrapper.dll ({1}) and the setting 'DoNotLoadLegacyScripts' is set to true." +
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
                        Logger.LogWarning(string.Format("An unknown error occured while trying to create new instance of the script {0}.", fileName));
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
                    foundScript = new FoundScript(fileName, path, script, scriptType);

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

                        //Notification.ShowNotification(NotificationType.Error, DateTime.UtcNow.AddSeconds(8), string.Format("An error occured in {0} Initialized.", foundScript.Name), ex.Message, string.Format("ERROR_IN_SCRIPT_{0}", foundScript.Name));
                        //Logger.LogError(string.Format("An error occured while processing initialized event for script {0}. Aborting script. Details: {1}", foundScript.Name, ex.ToString()));
                        //AbortScript(foundScript.ID);
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
                // Throw on exception when manager is a debug build
                throw;
#endif
            }
            catch (Exception ex)
            {
                Logger.LogError(string.Format("An exception occured while trying to load script '{0}'. Details: {1}", fileName, ex));

#if DEBUG
                // Throw on exception when manager is a debug build
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

                if (foundScript != null)
                {

                    string assemblyName = args.Name.Split(',')[0];
                    string scriptsDir = Path.GetDirectoryName(foundScript.FullPath);
                    string customDir = string.Format("{0}\\{1}", IVGame.GameStartupPath, foundScript.TheScript.CustomAssembliesPath);

                    string fileFullPath = string.Empty;

                    eAssembliesLocation scriptAssembliesLocation = foundScript.TheScript.AssembliesLocation;

                    // Debug
                    switch (scriptAssembliesLocation)
                    {
                        case eAssembliesLocation.Custom:
                            Logger.LogDebug(string.Format("Script {0} is requesting assembly {1} which should be in {2}", foundScript.Name, args.Name, customDir));
                            break;
                        default:
                            Logger.LogDebug(string.Format("Script {0} is requesting assembly {1} which should be in {2}", foundScript.Name, args.Name, scriptAssembliesLocation.ToString()));
                            break;
                    }

                    // Load Assembly by AssemblyLocation set by script
                    switch (scriptAssembliesLocation)
                    {

                        case eAssembliesLocation.GameRootDirectory:
                            Logger.LogWarning(string.Format("Script {0} was requesting assembly {1} but it was not found in the root directory of GTA IV! Aborting.", foundScript.Name, assemblyName));
                            break;

                        case eAssembliesLocation.ScriptsDirectory:

                            fileFullPath = string.Format("{0}\\{1}.dll", scriptsDir, assemblyName);
                            if (File.Exists(fileFullPath))
                                return Assembly.UnsafeLoadFrom(fileFullPath);

                            Logger.LogWarning(string.Format("Script {0} was requesting assembly {1} but it was not found in the scripts directory! Aborting.", foundScript.Name, assemblyName));
                            break;

                        case eAssembliesLocation.DecideManuallyForEachAssembly:

                            fileFullPath = foundScript.TheScript.RaiseAssemblyResolve(assemblyName);
                            if (File.Exists(fileFullPath))
                                return Assembly.UnsafeLoadFrom(fileFullPath);

                            Logger.LogWarning(string.Format("Script {0} was requesting assembly {1} but it was not found in directory ({2})! Aborting.", foundScript.Name, assemblyName, Path.GetDirectoryName(fileFullPath)));
                            break;

                        case eAssembliesLocation.Custom:

                            fileFullPath = string.Format("{0}\\{1}.dll", customDir, assemblyName);
                            if (File.Exists(fileFullPath))
                                return Assembly.UnsafeLoadFrom(fileFullPath);

                            Logger.LogWarning(string.Format("Script {0} was requesting assembly {1} but it was not found in the custom directory ({2})! Aborting.", foundScript.Name, assemblyName, foundScript.TheScript.CustomAssembliesPath));
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
                Logger.LogError(string.Format("An error occured while loading assembly {0} for Script {1}. Aborting. Details: {2}", args.Name, foundScript != null ? foundScript.Name : "UNKNOWN", ex.ToString()));
            }

            return null;
        }

        // Console stuff
        public void AddConsoleCommandToScript(Guid id, string command)
        {
            FoundScript s = GetFoundScript(id);
            if (s != null)
            {
                if (!s.ConsoleCommands.Contains(command))
                    s.ConsoleCommands.Add(command);
            }
        }

        // Abort script stuff
        public void AbortScripts(AbortReason reason, bool showMessage)
        {
            if (ActiveScripts.Count != 0)
            {
                ActiveScripts.ForEach(x => x.Abort(reason, showMessage));
                ActiveScripts.Clear();
                GC.Collect();
            }
            else
            {
                if (showMessage)
                    Logger.Log("There are no scripts to abort.");
            }
        }

        // DelayedAction
        public void StartDelayedAction(Guid id, string purpose, DateTime executeIn, Action<DelayedAction, object> actionToExecute, object parameter)
        {
            DelayedActions.Insert(DelayedActions.Count, new DelayedAction(id, purpose, executeIn, actionToExecute, parameter));
        }

        // Other
        private void HandleScriptException(FoundScript target, double notifySecondsVisible, string eventErrorOccuredIn, Exception ex)
        {
            // Stop script
            target.Stop();

            // Show and Log the error
            Notification.ShowNotification(
                NotificationType.Error,
                DateTime.UtcNow.AddSeconds(notifySecondsVisible),
                string.Format("An error occured in {0} {1}.", target.Name, eventErrorOccuredIn),
                ex.Message,
                string.Format("ERROR_IN_SCRIPT_{0}", target.Name));

            Logger.LogError(string.Format("An error occured while processing {0} event for script {1}. Aborting script. Details: {2}", eventErrorOccuredIn, target.Name, ex));

            // Abort script
            AbortScriptInternal(AbortReason.Manager, target, true);
        }
        private void SaveLogFile()
        {
            try
            {
                StringBuilder strBuilder = new StringBuilder();

                // Build file content
                List<Logger.tLogItem> logItems = Logger.GetLogItems();
                for (int i = 0; i < logItems.Count; i++)
                    strBuilder.AppendLine(logItems[i].ToString());

                // Save file at target location
                if (Config.CreateLogFilesInMainDirectory)
                {
                    File.WriteAllText("IVSDKDotNet.log", strBuilder.ToString());
                }
                else
                {
                    if (!Directory.Exists(CLR.CLRBridge.IVSDKDotNetLogsPath))
                    {
                        Directory.CreateDirectory(CLR.CLRBridge.IVSDKDotNetLogsPath);
                        File.WriteAllText(string.Format("{0}\\{1}", CLR.CLRBridge.IVSDKDotNetLogsPath, CLR.CLRBridge.CurrentLogFileName), strBuilder.ToString());
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
                    File.WriteAllText(string.Format("{0}\\{1}", CLR.CLRBridge.IVSDKDotNetLogsPath, CLR.CLRBridge.CurrentLogFileName), strBuilder.ToString());
                }
            }
            catch (Exception)
            {
#if DEBUG
                throw;
#endif
            }
        }

        #endregion

        #region Functions

        // Script stuff
        public FoundScript GetFoundScript(Guid id)
        {
            return ActiveScripts.Where(x => x.ID == id).FirstOrDefault();
        }
        public FoundScript GetFoundScript(string name)
        {
            return ActiveScripts.Where(x => x.Name == name).FirstOrDefault();
        }

        public bool AbortScriptInternal(AbortReason reason, Guid id)
        {
            FoundScript script = ActiveScripts.Where(x => x.ID == id).FirstOrDefault();

            if (script != null)
            {
                Logger.Log(string.Format("Aborting script {0}...", script.Name));
                script.Abort(reason, true);
                return ActiveScripts.Remove(script);
            }

            return false;
        }
        public bool AbortScriptInternal(AbortReason reason, FoundScript script, bool showMessage)
        {
            if (script != null)
            {
                if (showMessage)
                    Logger.Log(string.Format("Aborting script {0}...", script.Name));

                script.Abort(reason, showMessage);

                bool result = ActiveScripts.Remove(script);
                GC.Collect();
                return result;
            }

            return false;
        }

        public Guid StartNewTimerInternal(int interval, Action actionToExecute)
        {
            AdvancedTask task = new AdvancedTask(Guid.NewGuid(), null, TaskUseCase.Timer, interval);

            bool r = task.Start(TaskCreationOptions.LongRunning, () => AdvancedTask.TimerStatic(task, actionToExecute), (AdvancedTask.InvokeData args) =>
            {
                StartDelayedAction(args.STask.ID, string.Format("Disposing and deleting task {0} of Manager. CFSM: LocalTaskDisposer in AdvancedTask class", args.STask.ID.ToString()), DateTime.UtcNow.AddSeconds(5), AdvancedTask.LocalTaskDisposer, args.STask);
            });

            if (r)
            {
                LocalTasks.Add(task);
                return task.ID;
            }

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
                Logger.Log("Starting to clean up in the manager script...");

                // Stop remote server
                ConnectionManager.Dispose();

                // Abort all currently running scripts
                AbortScripts(AbortReason.Manager, false);

                // Stop task
                AbortTaskOrTimer(processCheckerTimerID);

                // Cleanup lists
                ActiveScripts.Clear();
                LocalTasks.Clear();
                DelayedActions.Clear();

                // Uninit keyWatchDog
                keyWatchDog.KeyDown -= KeyWatchDog_KeyDown;
                keyWatchDog.KeyUp -= KeyWatchDog_KeyUp;
                keyWatchDog.Dispose();
                keyWatchDog = null;

                Logger.LogDebug("Cleanup in manager script finished!");
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
        public override void SetDummyScript(Script script)
        {
            DummyScript = script;
        }
        #endregion

        #region Script Stuff
        public override void LoadScripts()
        {
            if (!Directory.Exists(CLR.CLRBridge.IVSDKDotNetScriptsPath))
            {
                Directory.CreateDirectory(CLR.CLRBridge.IVSDKDotNetScriptsPath);
                return;
            }

            // Abort currently loaded scripts
            AbortScripts(AbortReason.Manager, false);

            string[] scriptFiles = Directory.GetFiles(CLR.CLRBridge.IVSDKDotNetScriptsPath, "*.ivsdk.dll", SearchOption.TopDirectoryOnly);
            for (int i = 0; i < scriptFiles.Length; i++)
                LoadAssembly(scriptFiles[i]);

            // Log
            Logger.Log(string.Format("Loaded {0} of {1} scripts!", ActiveScripts.Count.ToString(), scriptFiles.Length.ToString()));
        }
        public override bool AbortScript(Guid id)
        {
            return AbortScriptInternal(AbortReason.Script, id);
        }

        public override Script GetScript(Guid id)
        {
            return ActiveScripts.Where(x => x.ID == id).Select(s => s.TheScript).FirstOrDefault();
        }
        public override Script GetScript(string name)
        {
            return ActiveScripts.Where(x => x.Name == name).Select(s => s.TheScript).FirstOrDefault();
        }
        public override bool IsScriptRunning(Guid id)
        {
            FoundScript foundScript = ActiveScripts.Where(x => x.ID == id).FirstOrDefault();

            if (foundScript != null)
                return foundScript.IsScriptReady();

            return false;
        }
        public override bool IsScriptRunning(string name)
        {
            FoundScript foundScript = ActiveScripts.Where(x => x.Name == name).FirstOrDefault();

            if (foundScript != null)
                return foundScript.IsScriptReady();

            return false;
        }
        public override Script[] GetAllScripts()
        {
            return ActiveScripts.Select(x => x.TheScript).ToArray();
        }
        public override string GetScriptName(Guid id)
        {
            FoundScript foundScript = ActiveScripts.Where(x => x.ID == id).FirstOrDefault();

            if (foundScript != null)
                return foundScript.Name;

            return string.Empty;
        }
        public override string GetScriptFullPath(Guid id)
        {
            FoundScript foundScript = ActiveScripts.Where(x => x.ID == id).FirstOrDefault();

            if (foundScript != null)
                return foundScript.FullPath;

            return string.Empty;
        }
        public override int GetActiveScriptsCount()
        {
            return ActiveScripts.Count;
        }

        public override bool SendScriptCommand(Script toScript, string command, out object result)
        {
            FoundScript foundScript = ActiveScripts.Where(x => x.ID == toScript.ID).FirstOrDefault();

            if (foundScript != null)
            {
                try
                {
                    if (foundScript.IsScriptReady())
                    {
                        result = foundScript.TheScript.RaiseScriptCommandReceived(toScript, command);
                        return true;
                    }
                }
                catch (Exception ex)
                {
                    Notification.ShowNotification(NotificationType.Error, DateTime.UtcNow.AddSeconds(8), string.Format("An error occured in {0} ScriptCommandReceived.", foundScript.Name), ex.Message, string.Format("ERROR_IN_SCRIPT_{0}", foundScript.Name));
                    Logger.LogError(string.Format("An error occured while processing ScriptCommandReceived event for script {0}. Aborting script. Details: {1}", foundScript.Name, ex.ToString()));
                    AbortScript(foundScript.ID);
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
                AdvancedTask task = new AdvancedTask(Guid.NewGuid(), s, TaskUseCase.Custom);

                bool r = task.Start(TaskCreationOptions.None, funcToExecute, (AdvancedTask.InvokeData args) =>
                {
                    continueWithAction?.Invoke(args.CustomData);
                    StartDelayedAction(args.STask.ID, string.Format("Disposing and deleting task {0} of script {1}. CFSM: TaskDisposer in AdvancedTask class", args.STask.ID.ToString(), args.STask.Owner.Name), DateTime.UtcNow.AddSeconds(5), AdvancedTask.TaskDisposer, args.STask);
                });

                if (r)
                {
                    s.ScriptTasks.Add(task);
                    return task.ID;
                }

                return Guid.Empty;
            }

            return Guid.Empty;
        }
        public override Guid StartNewTimer(Guid forScript, int interval, Action actionToExecute)
        {
            FoundScript s = GetFoundScript(forScript);

            if (s != null)
            {
                AdvancedTask task = new AdvancedTask(Guid.NewGuid(), s, TaskUseCase.Timer, interval);

                bool r = task.Start(TaskCreationOptions.LongRunning, () => AdvancedTask.TimerStatic(task, actionToExecute), (AdvancedTask.InvokeData args) =>
                {
                    StartDelayedAction(args.STask.ID, string.Format("Disposing and deleting timer task {0} of script {1}. CFSM: TaskDisposer in AdvancedTask class", args.STask.ID.ToString(), args.STask.Owner.Name), DateTime.UtcNow.AddSeconds(5), AdvancedTask.TaskDisposer, args.STask);
                });

                if (r)
                {
                    s.ScriptTasks.Add(task);
                    return task.ID;
                }

                return Guid.Empty;
            }

            return Guid.Empty;
        }
        #endregion

        #region Direct3D9 Stuff

        // Texture stuff
        public override void Direct3D9_RegisterScriptTexture(Script forScript, IntPtr ptr)
        {
            // Get script from ID
            FoundScript fs = GetFoundScript(forScript.ID);

            if (fs != null)
            {
                if (!fs.Textures.Contains(ptr))
                {
                    fs.Textures.Add(ptr);
                    Logger.LogDebug(string.Format("Registered texture {0} for script {1}.", ptr, fs.Name));
                }
                else
                {
                    Logger.LogDebug(string.Format("Texture {0} is already registered for script {1}.", ptr, fs.Name));
                }
            }
        }
        public override void Direct3D9_UnregisterScriptTexture(Script forScript, IntPtr ptr)
        {
            // Get script from ID
            FoundScript fs = GetFoundScript(forScript.ID);

            if (fs != null)
            {
                if (fs.Textures.Contains(ptr))
                {
                    fs.Textures.Remove(ptr);
                    Logger.LogDebug(string.Format("Unregistered texture {0} from script {1}.", ptr, fs.Name));
                }
                else
                {
                    Logger.LogDebug(string.Format("Texture {0} is already unregistered from script {1}.", ptr, fs.Name));
                }
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
            return Console.RegisterCommand(fromScript, name, actionToExecute);
        }
        public override bool ExecuteConsoleCommand(string name)
        {
            return Console.ExecuteCommand(name);
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
            // ActiveScripts
            for (int i = 0; i < ActiveScripts.Count; i++)
            {
                for (int s = 0; s < ActiveScripts[i].ScriptTasks.Count; s++)
                {
                    AdvancedTask at = ActiveScripts[i].ScriptTasks[s];

                    if (at.ID == id)
                        at.Wait(waitTimeInMilliseconds);
                }
            }

            // local tasks
            for (int i = 0; i < LocalTasks.Count; i++)
            {
                AdvancedTask at = LocalTasks[i];

                if (at.ID == id)
                    at.Wait(waitTimeInMilliseconds);
            }
        }
        public override void AbortTaskOrTimer(Guid id)
        {
            // ActiveScripts
            for (int i = 0; i < ActiveScripts.Count; i++)
            {
                for (int s = 0; s < ActiveScripts[i].ScriptTasks.Count; s++)
                {
                    AdvancedTask at = ActiveScripts[i].ScriptTasks[s];

                    if (at.ID == id)
                        at.Abort();
                }
            }

            // local tasks
            for (int i = 0; i < LocalTasks.Count; i++)
            {
                AdvancedTask at = LocalTasks[i];

                if (at.ID == id)
                    at.Abort();
            }
        }
        public override void ChangeTimerState(Guid id, bool pause)
        {
            // ActiveScripts
            for (int i = 0; i < ActiveScripts.Count; i++)
            {
                for (int s = 0; s < ActiveScripts[i].ScriptTasks.Count; s++)
                {
                    AdvancedTask at = ActiveScripts[i].ScriptTasks[s];

                    if (at.ID == id)
                        at.ShouldPause = pause;
                }
            }

            // local tasks
            for (int i = 0; i < LocalTasks.Count; i++)
            {
                AdvancedTask at = LocalTasks[i];

                if (at.ID == id)
                    at.ShouldPause = pause;
            }
        }
        public override void ChangeTimerInterval(Guid id, int interval)
        {
            // ActiveScripts
            for (int i = 0; i < ActiveScripts.Count; i++)
            {
                for (int s = 0; s < ActiveScripts[i].ScriptTasks.Count; s++)
                {
                    AdvancedTask at = ActiveScripts[i].ScriptTasks[s];

                    if (at.ID == id)
                        at.SleepTime = interval;
                }
            }

            // local tasks
            for (int i = 0; i < LocalTasks.Count; i++)
            {
                AdvancedTask at = LocalTasks[i];

                if (at.ID == id)
                    at.SleepTime = interval;
            }
        }
        #endregion

        #endregion
    }
}