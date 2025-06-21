using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Windows.Forms;

using Newtonsoft.Json;

using IVSDKDotNet;
using IVSDKDotNet.Native;
using IVSDKDotNet.Attributes;

using Manager.Classes.Json.Script;
using Manager.Managers;

namespace Manager.Classes.Scripts
{
    public class FoundScript
    {

        #region Variables and Properties
        // Script stuff
        public ScriptFileInfo TheFileInfo;
        public ScriptConfig Config;

        // Assembly stuff
        private Assembly theAssembly;
        public Type EntryPoint;
        private object theScriptObject;
        private bool wasConstructed;

        // Public Fields
        public FieldInfo[] EntryPointPublicFields;
        public List<FieldInfo[]> OtherPublicFields;

        // Lists
        public Dictionary<string, Action<string[]>> ConsoleCommands;
        public Dictionary<string, BoundPhoneNumber> BoundPhoneNumbers;

        // Manager
        public bool PublicFieldsWindowOpen;
        public long LastTimePublicFieldsWindowWasOpened;
        private bool wasLastTimePublicFieldsWindowOpenedTimeSet;

        // Thread
        public int ThreadID = -1;

        // Other
        public bool IsAborting;
        public bool Running;
        public bool WasPausedForVideoEditor;
        public bool WasCreatedWhenInVideoEditor;
        private bool initEventCalled;
        private bool hasOnFirstD3D9FrameEventBeenRaised;
        private DateTime nextTick;

        // Properties
        public Guid ID
        {
            get
            {
                if (theScriptObject == null)
                    return Guid.Empty;

                if (IsScriptHookDotNetScript)
                    return GetScriptAs<GTA.Script>().GUID;
                else
                    return GetScriptAs<Script>().ID;
            }
        }
        public bool IsScriptHookDotNetScript
        {
            get
            {
                if (theScriptObject == null)
                    return TheFileInfo.IsScriptHookDotNetScript;

                return theScriptObject.GetType().BaseType == typeof(GTA.Script);
            }
        }
        public bool IsIVSDKDotNetScript
        {
            get
            {
                if (theScriptObject == null)
                    return TheFileInfo.IsIVSDKDotNetScript;

                return theScriptObject.GetType().BaseType == typeof(Script);
            }
        }
        public ScriptType ScriptType
        {
            get
            {
                if (theScriptObject == null)
                {
                    if (TheFileInfo.IsIVSDKDotNetScript)
                        return ScriptType.IVSDKDotNet;
                    else if (TheFileInfo.IsScriptHookDotNetScript)
                        return ScriptType.ScriptHookDotNet;
                    else
                        return ScriptType.Unknown;
                }

                if (IsScriptHookDotNetScript)
                    return ScriptType.ScriptHookDotNet;

                return ScriptType.IVSDKDotNet;
            }
        }
        #endregion

        #region Constructor
        public FoundScript(ScriptFileInfo fileInfo, Assembly assembly, Type entryPoint)
        {
            TheFileInfo = fileInfo;
            theAssembly = assembly;
            EntryPoint = entryPoint;

            // Lists
            // Initializing all lists with a Capacity of 8 so they don't need to resize for every new item that is added to them (Aslong as they don't reach the set Capacity).
            ConsoleCommands = new Dictionary<string, Action<string[]>>(8);
            BoundPhoneNumbers = new Dictionary<string, BoundPhoneNumber>(8);
        }
        #endregion

        #region Raisers
        // IV-SDK .NET only
        public void RaiseInitialized()
        {
            if (IsScriptHookDotNetScript)
                return;

            if (!initEventCalled)
            {
                GetScriptAs<Script>().RaiseInitialized();
                initEventCalled = true;
            }
        }
        public void RaiseUninitialize()
        {
            if (IsScriptHookDotNetScript)
                return;

            // Raise uninitialized event
            GetScriptAs<Script>().RaiseUninitialize();
        }

        public void RaiseBoundPhoneNumberAction(string number)
        {
            if (BoundPhoneNumbers.TryGetValue(number, out BoundPhoneNumber num))
                num.DialedAction?.Invoke();
        }

        // IV-SDK .NET and ScriptHookDotNet
        public void RaiseTick()
        {
            // Raise tick
            if (IsScriptHookDotNetScript)
            {
                if (Natives.IS_PAUSE_MENU_ACTIVE())
                    return;

                // Always allow the thread to tick
                // TODO: Once both IV-SDK .NET and SHDN fully use their thread, we can probably reduce the code of this function
                // to just this.
                if (ThreadManager.TryGetThread(ThreadID, out Threading.NetThread thread))
                {
                    thread.TickNow();
                }
            }
            else
            {
                if (!IsScriptReady())
                    return;

                Script script = GetScriptAs<Script>();

                script.RaiseTick();

                // Raise WaitTick if can tick
                DateTime utcNow = DateTime.UtcNow;

                if (nextTick == DateTime.MinValue)
                    nextTick = utcNow.AddMilliseconds(script.WaitTickInterval);

                if (!(utcNow > nextTick))
                    // Tick is not allowed yet
                    return;
                else
                    // Set next tick
                    nextTick = DateTime.UtcNow.AddMilliseconds(script.WaitTickInterval);

                script.RaiseWaitTick();
            }
        }
        public void RaiseThreadedTick()
        {
            if (!IsScriptReady())
                return;

            // Raise tick
            // NOTE: Only raise the tick events of SHDN scripts for now, IV-SDK .NET scripts will follow in a future update
            if (IsScriptHookDotNetScript)
            {
                GTA.Script script = GetScriptAs<GTA.Script>();

                SHDNManager.SetCurrentScript(1, script);

                // Invoke Tick event
                try
                {
                    script.DoTick();
                }
                catch (Exception ex)
                {
                    ScriptManager.HandleScriptException(this, "Tick", ex);
                }

                SHDNManager.SetCurrentScript(1, null);
            }
        }
        public void RaiseGameLoad()
        {
            if (IsScriptHookDotNetScript)
                return;
            if (!IsScriptReady())
                return;

            Script script = GetScriptAs<Script>();
            script.RaiseGameLoad();
        }
        public void RaiseGameLoadPriority()
        {
            if (IsScriptHookDotNetScript)
                return;
            if (!IsScriptReady())
                return;

            Script script = GetScriptAs<Script>();
            script.RaiseGameLoadPriority();
        }
        public void RaiseMountDevice()
        {
            if (IsScriptHookDotNetScript)
                return;
            if (!IsScriptReady())
                return;

            Script script = GetScriptAs<Script>();
            script.RaiseMountDevice();
        }
        public void RaiseDrawing()
        {
            if (IsScriptHookDotNetScript)
                return;
            if (!IsScriptReady())
                return;

            Script script = GetScriptAs<Script>();
            script.RaiseDrawing();
        }
        public void RaiseProcessCamera()
        {
            if (IsScriptHookDotNetScript)
                return;
            if (!IsScriptReady())
                return;

            Script script = GetScriptAs<Script>();
            script.RaiseProcessCamera();
        }
        public void RaiseProcessAutomobile(UIntPtr vehPtr)
        {
            if (IsScriptHookDotNetScript)
                return;
            if (!IsScriptReady())
                return;

            Script script = GetScriptAs<Script>();
            script.RaiseProcessAutomobile(vehPtr);
        }
        public void RaiseProcessPad(UIntPtr padPtr)
        {
            if (IsScriptHookDotNetScript)
                return;
            if (!IsScriptReady())
                return;

            Script script = GetScriptAs<Script>();
            script.RaiseProcessPad(padPtr);
        }
        public void RaiseIngameStartup()
        {
            if (IsScriptHookDotNetScript)
                return;
            if (!IsScriptReady())
                return;

            Script script = GetScriptAs<Script>();
            script.RaiseIngameStartup();
        }

        public void RaiseKeyDown(object sender, KeyEventArgs e)
        {
            if (!IsScriptReady())
                return;

            //KeyWatchDog keyWatchDog = (KeyWatchDog)sender;

            if (IsScriptHookDotNetScript)
            {
                //if (keyWatchDog.Tag == "ScriptHookDotNet")
                //{
                //    GTA.Script script = GetScriptAs<GTA.Script>();

                //    script.DoKeyDown(new GTA.KeyEventArgs(e.KeyData));
                //    script.ProcessBoundKeys(e.KeyData);
                //}

                GTA.Script script = GetScriptAs<GTA.Script>();

                script.DoKeyDown(new GTA.KeyEventArgs(e.KeyData));
                script.ProcessBoundKeys(e.KeyData);
            }
            else
            {
                //if (keyWatchDog.Tag == "IVSDKDotNet")
                //{
                //    Script script = GetScriptAs<Script>();
                //    script.RaiseKeyDown(e);
                //}

                Script script = GetScriptAs<Script>();

                if (script.OnlyRaiseKeyEventsWhenInGame && IVPlayerInfo.FindThePlayerPed() == UIntPtr.Zero)
                    return;

                script.RaiseKeyDown(e);
            }
        }
        public void RaiseKeyUp(object sender, KeyEventArgs e)
        {
            if (!IsScriptReady())
                return;

            //KeyWatchDog keyWatchDog = (KeyWatchDog)sender;

            if (IsScriptHookDotNetScript)
            {
                //if (keyWatchDog.Tag == "ScriptHookDotNet")
                //{
                //    GTA.Script script = GetScriptAs<GTA.Script>();
                //    script.DoKeyUp(new GTA.KeyEventArgs(e.KeyData));
                //}

                GTA.Script script = GetScriptAs<GTA.Script>();

                script.DoKeyUp(new GTA.KeyEventArgs(e.KeyData));
            }
            else
            {
                //if (keyWatchDog.Tag == "IVSDKDotNet")
                //{
                //    Script script = GetScriptAs<Script>();
                //    script.RaiseKeyUp(e);
                //}

                Script script = GetScriptAs<Script>();

                if (script.OnlyRaiseKeyEventsWhenInGame && IVPlayerInfo.FindThePlayerPed() == UIntPtr.Zero)
                    return;

                script.RaiseKeyUp(e);
            }
        }

        public bool RaiseScriptCommandReceived(Guid sender, string command, object[] args, out object result)
        {
            if (!IsScriptReady())
            {
                result = null;
                return false;
            }

            if (IsScriptHookDotNetScript)
            {
                // Get the command sender
                GTA.Script senderScript = ScriptManager.GetScriptHookDotNetScript(sender);

                // Send script command to ScriptHookDotNet script
                GetScriptAs<GTA.Script>().ScriptCommandReceived(new GTA.ScriptCommandEventArgs(senderScript, command, args));

                result = null;
                return true;
            }
            else
            {
                // Get the command sender
                Script senderScript = ScriptManager.GetIVSDKDotNetScript(sender);

                // Send script command to IVSDKDotNet script
                result = GetScriptAs<Script>().RaiseScriptCommandReceived(senderScript, args, command);
                return true;
            }
        }
        public void RaiseOnConsoleCommand(string command, string[] args)
        {
            if (IsIVSDKDotNetScript)
                return;
            if (!IsScriptReady())
                return;

            GTA.Script script = GetScriptAs<GTA.Script>();

            script.ConsoleCommandReceived(command, args);
        }

        // Direct3D9 (IV-SDK .NET and ScriptHookDotNet)
        public void RaiseOnImGuiRendering(IntPtr devicePtr, ImGuiIV_DrawingContext ctx)
        {
            if (!IsScriptReady())
                return;

            if (IsScriptHookDotNetScript)
            {
                if (Natives.IS_PAUSE_MENU_ACTIVE() || Natives.IS_SCREEN_FADING_OUT() || Natives.IS_SCREEN_FADED_OUT())
                    return;

                GTA.Script script = GetScriptAs<GTA.Script>();

                SHDNManager.SetCurrentScript(5, script);

                try
                {
                    script.DoPerFrameDrawing(ctx);
                    script.DoPerFrameScriptDrawing();
                }
                catch (Exception ex)
                {
                    ScriptManager.HandleScriptException(this, "PerFrameDrawing", ex);
                }

                SHDNManager.SetCurrentScript(5, null);
            }
            else
            {
                Script script = GetScriptAs<Script>();

                // Raise on first D3D9 frame event
                if (!hasOnFirstD3D9FrameEventBeenRaised)
                {
                    script.RaiseOnFirstD3D9Frame(devicePtr);

                    hasOnFirstD3D9FrameEventBeenRaised = true;
                }

                script.RaiseOnImGuiRendering(devicePtr, ctx);
            }
        }
        #endregion

        #region Methods
        // - - - Only for ScriptHookDotNet scripts - - -
        public void LateInitialize(object scriptObject)
        {
            theScriptObject = scriptObject;
            GetPublicFields();
        }

        public void Abort(AbortReason reason, bool showMessage, bool forceAbort = false)
        {
            if (!WasConstructed())
                return;

            // Check if script can be aborted
            if (!CanScriptBeAborted(reason, forceAbort))
            {
                Logger.LogDebug(string.Format("Script {0} will not be aborted as it is set to force no abort.", EntryPoint.FullName));
                return;
            }

            IsAborting = true;

            // Reset some stuff
            PublicFieldsWindowOpen = false;

            // Stop thread
            if (ThreadID != -1)
                ThreadManager.TryShutdownThread(ThreadID);

            // Stop active script tasks
            ScriptManager.AbortScriptTasks(ID);

            // Disable the functionality to raise any script events (Except for the Uninitialize event)
            Stop();

            // Raise Uninitialize event
            RaiseUninitialize();

            // Get rid of all registered script textures
            DXManager.DestroyAllTexturesOfThisScript(ID);

            // Save script settings file
            SaveSettingsFile();

            // Delete all console commands registered by this script
            ConsoleCommands.Clear();

            // Delete all phone numbers registered by this script
            BoundPhoneNumbers.Clear();

            // Log
            if (showMessage)
            {
                switch (reason)
                {
                    case AbortReason.API:
                        Logger.Log(string.Format("An API Client has successfully aborted the script {0}.", EntryPoint.FullName));
                        break;
                    case AbortReason.Manual:
                    case AbortReason.Console:
                        Logger.Log(string.Format("Script {0} was successfully aborted by user.", EntryPoint.FullName));
                        break;
                    case AbortReason.Script:
                        Logger.Log(string.Format("Script {0} was successfully aborted by another script (Or by {0} itself).", EntryPoint.FullName));
                        break;
                    case AbortReason.Manager:
                        Logger.Log(string.Format("Manager successfully aborted script {0}.", EntryPoint.FullName));
                        break;
                }
            }

            // Let plugins know
            PluginManager.RaiseOnScriptAbort(ID);

            // Cleanup other script things
            if (IsScriptHookDotNetScript)
                GetScriptAs<GTA.Script>().Dispose();
            else
                GetScriptAs<Script>().Dispose();

            EntryPoint = null;
        }
        public void Stop()
        {
            Running = false;
        }

        public void PauseForVideoEditor()
        {
            WasPausedForVideoEditor = true;
            Running = false;
        }
        public void ResumeFromPauseForVideoEditor()
        {
            if (WasPausedForVideoEditor)
            {
                WasPausedForVideoEditor = false;
                Running = true;
            }
        }

        public void CreateAndLaunchThread()
        {
            if (ThreadID != -1)
                return;
            //if (IsIVSDKDotNetScript) // Add this feature for IV-SDK .NET scripts too in a future update
            //    return;

            // Launch thread which will then also construct the script
            ThreadID = ThreadManager.CreateScriptThread(this, true);
        }

        public void Wait(int milliseconds)
        {
            if (!IsScriptReady())
                return;

            ThreadManager.WaitInThread(ThreadID, milliseconds);
        }

        /// <summary>
        /// Queues a <see cref="Action"/> to be run on the script's thread.
        /// </summary>
        /// <param name="a">The action to be run on the thread.</param>
        public void QueueOnThreadDispatcher(Action a)
        {
            if (!IsScriptReady())
                return;

            if (ThreadManager.TryGetThread(ThreadID, out Threading.NetThread thread))
            {
                thread.GetDispatcher().DispatchAndForget(a);
            }
            else
            {
                Helper.WriteToDebugOutput(Priority.Medium, "Could not queue action to the thread of script {0}! The thread was not found.", TheFileInfo.FileName);
            }
        }

        public void SetLastTimePublicFieldsWindowWasOpened()
        {
            if (PublicFieldsWindowOpen && !wasLastTimePublicFieldsWindowOpenedTimeSet)
            {
                LastTimePublicFieldsWindowWasOpened = DateTime.UtcNow.Ticks;
                wasLastTimePublicFieldsWindowOpenedTimeSet = true;
            }
            else
            {
                wasLastTimePublicFieldsWindowOpenedTimeSet = false;
            }
        }

        private void GetPublicFields()
        {
            // Get public fields of entry point
            EntryPointPublicFields = EntryPoint.GetFields(BindingFlags.Instance | BindingFlags.Static | BindingFlags.Public);

            // Get public fields of types which got the "ShowStaticFieldsInInspector" attribute
            if (IsIVSDKDotNetScript)
            {
                Type[] scriptTypesWithStaticFieldsAttribute = theAssembly.GetTypes().Where(x => x.GetCustomAttribute<ShowStaticFieldsInInspector>() != null).ToArray();

                if (scriptTypesWithStaticFieldsAttribute.Length != 0)
                    OtherPublicFields = new List<FieldInfo[]>();

                // Find fields of types
                for (int i = 0; i < scriptTypesWithStaticFieldsAttribute.Length; i++)
                {
                    Type t = scriptTypesWithStaticFieldsAttribute[i];

                    FieldInfo[] fields = t.GetFields(BindingFlags.Public | BindingFlags.Static);

                    if (fields == null || fields.Length == 0)
                        continue;

                    OtherPublicFields.Add(fields);
                }
            }
        }

        private void SaveSettingsFile()
        {
            if (IsIVSDKDotNetScript)
            {
                Script s = GetScriptAs<Script>();

                if (s.SaveSettingsOnUnload)
                {
                    SettingsFile settings = s.Settings;

                    if (settings != null)
                        settings.Save();
                }

                return;
            }

            if (IsScriptHookDotNetScript)
            {
                GTA.SettingsFile settings = GetScriptAs<GTA.Script>().pSettings;

                if (settings != null)
                    settings.Save();
            }
        }
        #endregion

        #region Functions

        // Script stuff
        public T GetScriptAs<T>()
        {
            return (T)theScriptObject;
        }
        public object GetTheScriptObject()
        {
            return theScriptObject;
        }
        public string GetEntryPointName()
        {
            if (EntryPoint == null)
                return null;

            return EntryPoint.FullName;
        }

        /// <summary>
        /// Gets if this script was already constructed using the <see cref="ConstructScript"/> function.
        /// </summary>
        /// <returns><see langword="true"/> if the script was constructed. Otherwise, <see langword="false"/>.</returns>
        public bool WasConstructed()
        {
            //return theScriptObject != null;
            return wasConstructed;
        }

        /// <summary>
        /// Gets if this script can construct instantly the moment it was loaded by <see cref="ScriptManager.LoadAssembly(string)"/>.
        /// <para>ScriptHookDotNet script will always return <see langword="false"/>, so they only construct once in-game.</para>
        /// </summary>
        /// <returns><see langword="true"/> if this script can construct instantly. Otherwise, <see langword="false"/>.</returns>
        public bool CanScriptConstructInstantly()
        {
            if (IsScriptHookDotNetScript)
                return false;

            // Dont allow instant construction when in video editor and scripts are set to pause when in video editor
            // The script will construct once the video editor will exit
            if (WasCreatedWhenInVideoEditor && Classes.Config.PauseScriptExecutionWhenInVideoEditor)
                return false;

            // Check if dev wants to make the script not construct instantly
            // TODO: Test if all works as expected
            return Config == null ? false : Config.CanScriptConstructInstantly;
        }

        /// <summary>
        /// Tries to construct the script aslong as <see cref="CanScriptConstructInstantly"/> allows it.
        /// </summary>
        /// <returns><see langword="true"/> if the script was successfully constructed. <see langword="false"/> when the script could not construct yet, it was already constructed, the construction failed or the script type couldn't be determined.</returns>
        public bool TryConstructScript()
        {
            if (CanScriptConstructInstantly())
                return ConstructScript();

            return false;
        }

        /// <summary>
        /// Starts constructing the script using the <see cref="Assembly.CreateInstance(string)"/> function.
        /// </summary>
        /// <returns><see langword="true"/> if the script was successfully constructed. <see langword="false"/> when the script was already constructed, the construction failed or the script type couldn't be determined.</returns>
        public bool ConstructScript()
        {
            if (WasConstructed())
                return false; // Script was already constructed

            Helper.WriteToDebugOutput(Priority.Default, "About to construct script {0} (Type: {1}, ScriptThreadID: {2}).", TheFileInfo.FileName, ScriptType, ThreadID);

            switch (ScriptType)
            {
                case ScriptType.IVSDKDotNet:
                    {
                        // Log
                        Logger.LogEx("Constructing IV-SDK .NET script: {0} ({1})...", EntryPoint.FullName, TheFileInfo.FileName);

                        try
                        {
                            // Create new instance
                            Script script = (Script)theAssembly.CreateInstance(EntryPoint.FullName);

                            if (script == null)
                            {
                                Logger.LogErrorEx("An unknown error occured while trying to create new instance of IV-SDK .NET script '{0}'.", TheFileInfo.FileName);
                                return false;
                            }

                            // Assign newly created instance to the script object
                            theScriptObject = script;

                            // Check if script ID is already assigned to another script
                            FoundScript possibleConflictingScript = ScriptManager.GetFoundScript(script.ID);
                            if (possibleConflictingScript != null && possibleConflictingScript.TheFileInfo.FileName != TheFileInfo.FileName)
                            {
                                Helper.WriteToDebugOutput(Priority.High, "ID of script '{0}' conflicts with script '{1}'!", TheFileInfo.FileName, possibleConflictingScript.TheFileInfo.FileName);
                                ScriptManager.HandleScriptIdConflict(ScriptType.IVSDKDotNet, script, EntryPoint.FullName);
                                return false;
                            }

                            // Check for script settings file
                            string settingsFilePath = string.Format("{0}\\{1}.ini", CLR.CLRBridge.IVSDKDotNetScriptsPath, TheFileInfo.FileNameWithoutExtension);
                            if (File.Exists(settingsFilePath))
                            {
                                script.Settings = new SettingsFile(settingsFilePath);
                                script.Settings.Load();
                            }

                            // Check for script resource folder
                            string resourceFolderPath = string.Format("{0}\\{1}", CLR.CLRBridge.IVSDKDotNetScriptsPath, TheFileInfo.FileNameWithoutExtension);
                            if (Directory.Exists(resourceFolderPath))
                            {
                                script.ScriptResourceFolder = resourceFolderPath;
                            }
                        }
                        catch (Exception ex)
                        {
                            Logger.LogError("=======================================================================================");
                            Logger.LogErrorEx("An exception occured while trying to construct IV-SDK .NET script '{0}'!", TheFileInfo.FileName);
                            Logger.LogErrorEx("Details: {0}", ex);
                            Logger.LogError("=======================================================================================");

                            ScriptManager.HandleScriptException(this, string.Empty, ex, true);

                            return false;
                        }

                        // Get the public fields of the script
                        GetPublicFields();

                        // Let plugins know a new script was loaded
                        PluginManager.RaiseOnScriptLoad(ID);

                        // Raise Initialize
                        try
                        {
                            RaiseInitialized();
                        }
                        catch (Exception ex)
                        {
                            ScriptManager.HandleScriptException(this, "Initialized", ex);
                        }
                    }
                    break;
                case ScriptType.ScriptHookDotNet:
                    {
                        // Log
                        Logger.LogEx("Constructing ScriptHookDotNet script: {0} ({1})...", EntryPoint.FullName, TheFileInfo.FileName);

                        try
                        {
                            // Create the script
                            theAssembly.CreateInstance(EntryPoint.FullName);
                        }
                        catch (Exception ex)
                        {
                            Logger.LogError("=======================================================================================");
                            Logger.LogErrorEx("An exception occured while trying to construct ScriptHookDotNet script '{0}'!", TheFileInfo.FileName);
                            Logger.LogErrorEx("Details: {0}", ex);
                            Logger.LogError("=======================================================================================");

                            ScriptManager.HandleScriptException(this, string.Empty, ex, true);

                            return false;
                        }

                        // Reset current constructing shdn script
                        SHDNManager.SetCurrentScript(0, null);
                    }
                    break;
                case ScriptType.Unknown:
                    Logger.LogWarningEx("Could not construct script '{0}' because the type couldn't be determined!");
                    return false;
            }

            // If this gets here we can safely say the script got constructed
            wasConstructed = true;

            // Set running flag
            // TODO: When in video editor, and the user reloads all scripts, the setting "PauseExecutionWhenInVideoEditor" will be ignored
            // meaning that the constructor and the initialized event will run... This should not be the case when in the video editor!
            // Figure out a solution which queues these calls when exiting the video editor.
            Running = true;

            Helper.WriteToDebugOutput(Priority.Default, "Script {0} was constructed!", EntryPoint.FullName);

            return true;
        }

        /// <summary>
        /// Gets if the script is ready.
        /// </summary>
        /// <returns><see langword="true"/> if the script is ready. Otherwise, <see langword="false"/>.</returns>
        public bool IsScriptReady()
        {
            if (!WasConstructed())
                return false;

            if (IsScriptHookDotNetScript)
                return Running;

            return Running && initEventCalled;
        }

        public bool CanScriptBeAborted(AbortReason reason, bool forceAbort)
        {
            if (IsIVSDKDotNetScript && !forceAbort)
            {
                if (!GetScriptAs<Script>().ForceNoAbort)
                    return true;

                return reason == AbortReason.Manual;
            }

            return true;
        }

        // ScriptConfig stuff
        public bool GetScriptConfig()
        {
            if (IsScriptHookDotNetScript)
                return false;

            try
            {
                string rawConfig = Helper.GetContentOfEmbeddedResource(theAssembly, "scriptConfig.json");

                if (string.IsNullOrEmpty(rawConfig))
                    return false;

                // Remove all the comments from the json string
                rawConfig = string.Join(Environment.NewLine,
                    rawConfig.Split(new[] { "\r\n", "\r", "\n" }, StringSplitOptions.None)
                    .Where(line => !line.TrimStart().StartsWith("//")));

                // Deserialize the string to a object
                Config = JsonConvert.DeserializeObject<ScriptConfig>(rawConfig);

                Logger.LogDebugEx("Loaded script config of script {0}!", TheFileInfo.FileName);
                return true;
            }
            catch (Exception ex)
            {
                Logger.LogErrorEx("Failed to read script config of script {0}! Details: {1}", TheFileInfo.FileName, ex);
            }

            return false;
        }
        public bool AreScriptConfigDependenciesPresent()
        {
            if (IsScriptHookDotNetScript)
                return true;
            if (Config == null)
                return true;
            if (!Config.HasDependencyInfo())
                return true;

            int count = 0;

            // Check dependencies
            for (int i = 0; i < Config.Dependencies.Count; i++)
            {
                ScriptDependencyInfo dependencyInfo = Config.Dependencies[i];

                if (FileCacheManager.IsFilePresentWithVersionCheck(Folder.Any, dependencyInfo.FileName, dependencyInfo.SpecificVersion))
                    count++;
            }

            return count == Config.Dependencies.Count;
        }
        public bool AreScriptConfigIncompatibleModsPresent()
        {
            if (IsScriptHookDotNetScript)
                return false;
            if (Config == null)
                return false;
            if (!Config.HasIncompatibleMods())
                return false;

            // Check incompatible mods
            for (int i = 0; i < Config.IncompatibleMods.Count; i++)
            {
                string incompatibleMod = Config.IncompatibleMods[i];

                if (FileCacheManager.IsFilePresent(Folder.Any, incompatibleMod))
                    return true;
            }

            return false;
        }

        // Phone stuff
        public bool AddPhoneNumber(string number, Action a)
        {
            string cleanedNumber = IVSDKDotNet.Helper.CleanPhoneNumber(number);
            
            if (BoundPhoneNumbers.ContainsKey(cleanedNumber))
                return false;

            BoundPhoneNumbers.Add(cleanedNumber, new BoundPhoneNumber(cleanedNumber, a));
            return true;
        }
        public bool RemovePhoneNumber(string number)
        {
            string cleanedNumber = IVSDKDotNet.Helper.CleanPhoneNumber(number);

            if (!BoundPhoneNumbers.ContainsKey(cleanedNumber))
                return false;

            return BoundPhoneNumbers.Remove(cleanedNumber);
        }

        #endregion
    }
}
