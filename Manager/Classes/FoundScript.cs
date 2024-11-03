using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Threading.Tasks;
using System.Windows.Forms;

using Newtonsoft.Json;

using IVSDKDotNet;
using IVSDKDotNet.Native;
using IVSDKDotNet.Attributes;

using Manager.Classes.Json.Script;

namespace Manager.Classes
{
    public class FoundScript
    {
        #region Variables and Properties
        // Script stuff
        public string FileName;
        public string FullPath;
        public bool HasOnFirstD3D9FrameEventBeenRaised;

        public Assembly TheAssembly;
        public object TheScriptObject;

        public ScriptConfig Config;

        // Public Fields
        public FieldInfo[] EntryPointPublicFields;
        public List<FieldInfo[]> OtherPublicFields;

        // Types
        public Type EntryPoint;

        // Lists
        public Dictionary<string, Action<string[]>> ConsoleCommands;
        public Dictionary<string, BoundPhoneNumber> BoundPhoneNumbers;
        public List<RegisteredEvent> RegisteredEvents;

        // Dear ImGui
        public List<IntPtr> Textures;

        // Manager
        public bool PublicFieldsWindowOpen;

        // Other
        public bool Running;
        public bool InitEventCalled;
        private Task cleanUpTask;
        public Exception AbortError;
        private DateTime nextTick;

        // Properties
        public Guid ID
        {
            get
            {
                if (TheScriptObject == null)
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
                if (TheScriptObject == null)
                    return false;

                return TheScriptObject.GetType().BaseType == typeof(GTA.Script);
            }
        }
        public bool IsIVSDKDotNetScript
        {
            get
            {
                if (TheScriptObject == null)
                    return false;

                return TheScriptObject.GetType().BaseType == typeof(Script);
            }
        }
        public ScriptType ScriptType
        {
            get
            {
                if (TheScriptObject == null)
                    return ScriptType.Unknown;

                if (IsScriptHookDotNetScript)
                    return ScriptType.ScriptHookDotNet;

                return ScriptType.IVSDKDotNet;
            }
        }
        #endregion

        #region Constructor
        // IV-SDK .NET Constructor
        public FoundScript(string fileName, string fullPath, Assembly theAssembly, object scriptObject, Type entryPoint)
        {
            FileName = fileName;
            FullPath = fullPath;
            TheAssembly = theAssembly;
            TheScriptObject = scriptObject;
            EntryPoint = entryPoint;

            GetPublicFields();

            // Lists
            // Initializing all lists with a Capacity of 8 so they don't need to resize for every new item that is added to them (Aslong as they don't reach the set Capacity).
            ConsoleCommands = new Dictionary<string, Action<string[]>>(8);
            BoundPhoneNumbers = new Dictionary<string, BoundPhoneNumber>(8);
            //RegisteredEvents = new List<RegisteredEvent>(8);
            Textures = new List<IntPtr>(8);

            Running = true;
        }
        
        // ScriptHookDotNet Constructor
        public FoundScript(string fileName, string fullPath, Assembly theAssembly, Type entryPoint)
        {
            FileName = fileName;
            FullPath = fullPath;
            TheAssembly = theAssembly;
            EntryPoint = entryPoint;
        }
        #endregion

        #region Raisers
        // IV-SDK .NET only
        public void RaiseInitialized()
        {
            if (IsScriptHookDotNetScript)
                return;

            if (!InitEventCalled)
            {
                GetScriptAs<Script>().RaiseInitialized();
                InitEventCalled = true;
            }
        }
        public void RaiseUninitialize()
        {
            if (IsScriptHookDotNetScript)
                return;

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
            if (!IsScriptReady())
                return;

            // Raise tick
            if (IsScriptHookDotNetScript)
            {
                if (Natives.IS_PAUSE_MENU_ACTIVE())
                    return;

                GTA.Script script = GetScriptAs<GTA.Script>();

                SHDNStuff.SetCurrentScript(GTA.ScriptEvent.Tick, script);

                // Invoke Tick event
                try
                {
                    script.DoTick();
                }
                catch (Exception ex)
                {
                    Main.Instance.HandleScriptException(this, 8d, "Tick", ex);
                }

                // Process action queue
                try
                {
                    if (script.ActionQueue.Count != 0)
                    {
                        GTA.ScriptAction a = script.ActionQueue.Dequeue();
                        a.Act?.Invoke();
                    }
                }
                catch (Exception ex)
                {
                    Main.Instance.HandleScriptException(this, 8d, "ActionQueueProcessor", ex);
                }

                SHDNStuff.SetCurrentScript(GTA.ScriptEvent.Tick, null);
            }
            else
            {
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

            KeyWatchDog keyWatchDog = (KeyWatchDog)sender;

            if (IsScriptHookDotNetScript)
            {
                if (keyWatchDog.Tag == "ScriptHookDotNet")
                {
                    GTA.Script script = GetScriptAs<GTA.Script>();

                    script.DoKeyDown(new GTA.KeyEventArgs(e.KeyData));
                    script.ProcessBoundKeys(e.KeyData);
                }
            }
            else
            {
                if (keyWatchDog.Tag == "IVSDKDotNet")
                {
                    Script script = GetScriptAs<Script>();
                    script.RaiseKeyDown(e);
                }
            }
        }
        public void RaiseKeyUp(object sender, KeyEventArgs e)
        {
            if (!IsScriptReady())
                return;

            KeyWatchDog keyWatchDog = (KeyWatchDog)sender;

            if (IsScriptHookDotNetScript)
            {
                if (keyWatchDog.Tag == "ScriptHookDotNet")
                {
                    GTA.Script script = GetScriptAs<GTA.Script>();
                    script.DoKeyUp(new GTA.KeyEventArgs(e.KeyData));
                }
            }
            else
            {
                if (keyWatchDog.Tag == "IVSDKDotNet")
                {
                    Script script = GetScriptAs<Script>();
                    script.RaiseKeyUp(e);
                }
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
                GTA.Script senderScript = Main.Instance.GetScriptHookDotNetScript(sender);

                // Send script command to ScriptHookDotNet script
                GetScriptAs<GTA.Script>().ScriptCommandReceived(new GTA.ScriptCommandEventArgs(senderScript, command, args));

                result = null;
                return true;
            }
            else
            {
                // Get the command sender
                Script senderScript = Main.Instance.GetIVSDKDotNetScript(sender);

                // Send script command to IVSDKDotNet script
                result = GetScriptAs<Script>().RaiseScriptCommandReceived(senderScript, args, command);
                return true;
            }
        }
        public void RaiseOnConsoleCommand(string command, string[] args)
        {
            if (IsIVSDKDotNetScript)
                return;

            GTA.Script script = GetScriptAs<GTA.Script>();

            script.ActionQueue.Enqueue(new GTA.ScriptAction(GTA.ScriptActionID.ConsoleCommand, () =>
            {
                script.ConsoleCommandReceived(command, args);
            }));
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

                SHDNStuff.SetCurrentScript(GTA.ScriptEvent.PerFrameDrawing, script);

                try
                {
                    script.DoPerFrameDrawing(ctx);
                    script.DoPerFrameScriptDrawing();
                }
                catch (Exception ex)
                {
                    Main.Instance.HandleScriptException(this, 8d, "PerFrameDrawing", ex);
                }

                SHDNStuff.SetCurrentScript(GTA.ScriptEvent.PerFrameDrawing, null);
            }
            else
            {
                Script script = GetScriptAs<Script>();

                // Raise on first D3D9 frame event
                if (!HasOnFirstD3D9FrameEventBeenRaised)
                {
                    script.RaiseOnFirstD3D9Frame(devicePtr);

                    HasOnFirstD3D9FrameEventBeenRaised = true;
                }

                script.RaiseOnImGuiRendering(devicePtr, ctx);
            }
        }
        #endregion

        #region Methods
        // - - - Only for ScriptHookDotNet scripts - - -
        public void LateInitialize(object scriptObject)
        {
            TheScriptObject = scriptObject;

            GetPublicFields();

            // Lists
            // Initializing all lists with a Capacity of 8 so they don't need to resize for every new item that is added to them (Aslong as they don't reach the set Capacity).
            ConsoleCommands = new Dictionary<string, Action<string[]>>(8);
            BoundPhoneNumbers = new Dictionary<string, BoundPhoneNumber>(8);
            Textures = new List<IntPtr>(8);

            Running = true;
        }

        public void Abort(AbortReason reason, bool showMessage, bool forceAbort = false)
        {
            // Check if script can be aborted
            if (!CanScriptBeAborted(reason, forceAbort))
            {
                Logger.LogDebug(string.Format("Script {0} will not be aborted as it is set to force no abort.", EntryPoint.FullName));
                return;
            }

            if (cleanUpTask != null)
                return;

            // Reset some stuff
            PublicFieldsWindowOpen = false;

            // Stop active script tasks
            Main.Instance.AbortScriptTasks(ID);

            // Disable the functionality to raise any script events (Except for the Uninitialize event)
            Stop();

            // Raise Uninitialize event
            RaiseUninitialize();

            // Remove all registered event subscriptions
            RemoveEventSubscriptions();

            // Delete all console commands registered by this script
            ConsoleCommands.Clear();

            // Delete all phone numbers registered by this script
            BoundPhoneNumbers.Clear();

            // Destroy textures created by script
            DestroyScriptTextures();

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

            // Cleanup other script things
            if (IsScriptHookDotNetScript)
                GetScriptAs<GTA.Script>().Dispose();
            else
                GetScriptAs<Script>().Dispose();

            FileName = null;
            FullPath = null;
            EntryPoint = null;
        }
        public void Stop()
        {
            Running = false;
        }

        private void GetPublicFields()
        {
            // Get public fields of entry point
            EntryPointPublicFields = EntryPoint.GetFields(BindingFlags.Instance | BindingFlags.Static | BindingFlags.Public);

            // Get public fields of types which got the "ShowStaticFieldsInInspector" attribute
            if (IsIVSDKDotNetScript)
            {
                Type[] scriptTypesWithStaticFieldsAttribute = TheAssembly.GetTypes().Where(x => x.GetCustomAttribute<ShowStaticFieldsInInspector>() != null).ToArray();

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

        public void GetScriptConfig()
        {
            try
            {
                if (IsIVSDKDotNetScript)
                {
                    string rawConfig = Helper.GetContentOfEmbeddedResource(TheAssembly, "config.ivsdkdotnet");

                    if (string.IsNullOrEmpty(rawConfig))
                        return;

                    Config = JsonConvert.DeserializeObject<ScriptConfig>(rawConfig);   
                }
            }
            catch (Exception ex)
            {
                Logger.LogError(string.Format("Failed to get script config of Script {0}! Details: {1}", EntryPoint.FullName, ex));
            }
        }
        //public void CheckForExistenceOfReferencedAssemblies()
        //{
        //    if (IsScriptHookDotNetScript)
        //        return;
        //    if (Config == null)
        //        return;

        //    // TODO

        //    Script script = GetScriptAs<Script>();

        //    // Check if referenced assemblies of script exists
        //    AssemblyName[] referencedAssemblies = TheAssembly.GetReferencedAssemblies();

        //    for (int i = 0; i < referencedAssemblies.Length; i++)
        //    {
        //        string assemblyName = string.Format("{0}.dll", referencedAssemblies[i].Name);
        //        Logger.LogDebug("Looking for: " + assemblyName);

        //        // Try finding the assembly location
        //        string assemblyFileName = string.Empty;

        //        switch (script.AssembliesLocation)
        //        {
        //            case eAssembliesLocation.GameRootDirectory:
        //                assemblyFileName = Directory.GetFiles(IVGame.GameStartupPath, "*.dll").Where(x => x.ToLower().EndsWith(assemblyName.ToLower())).FirstOrDefault();
        //                break;
        //            case eAssembliesLocation.ScriptsDirectory:
        //                assemblyFileName = Directory.GetFiles(CLR.CLRBridge.IVSDKDotNetScriptsPath, "*.dll").Where(x => x.ToLower().EndsWith(assemblyName.ToLower())).FirstOrDefault();
        //                break;

        //            default:
        //                continue;
        //        }

        //        if (string.IsNullOrWhiteSpace(assemblyFileName))
        //            continue;

        //        // If file does not exists
        //        if (!File.Exists(assemblyFileName))
        //        {
        //            Logger.LogWarning("- does not exists!");
        //        }
        //    }
        //}

        private void RemoveEventSubscriptions()
        {
            if (RegisteredEvents != null)
            {
                RegisteredEvents.ForEach(x => x.RemoveSubscription());
                RegisteredEvents.Clear();
            }
        }
        private void DestroyScriptTextures()
        {
            string scriptName = EntryPoint == null ? "UNKNOWN" : EntryPoint.FullName;
            
            if (Textures.Count == 0)
            {
                Logger.LogDebug(string.Format("There are no textures to destroy for script {0}.", scriptName));
                return;
            }

            int texturesCount = Textures.Count;

            // Get rid of each Texture this Script created
            for (int i = 0; i < Textures.Count; i++)
            {
                IntPtr txtPtr = Textures[i];

                if (ImGuiIV.IsTextureValid(txtPtr))
                {
                    if (!ImGuiIV.ReleaseTexture(ref txtPtr))
                        Logger.LogWarning(string.Format("Could not release texture {0} of script {1}.", txtPtr, scriptName));
                }
                else
                {
                    Logger.LogDebug(string.Format("Not destroying texture {0} of script {1} because it's not valid anymore.", txtPtr, scriptName));
                }
            }

            // Clear list
            Textures.Clear();

            // Log
            Logger.LogDebug(string.Format("Destroyed {0} Direct3D9 Textures of script {1}", texturesCount, scriptName));
        }
        #endregion

        #region Functions
        public T GetScriptAs<T>()
        {
            return (T)TheScriptObject;
        }

        /// <summary>
        /// Gets if the <see cref="Script"/> is ready so their events can be executed.
        /// </summary>
        /// <returns>True if the <see cref="Script"/> is ready. Otherwise false.</returns>
        public bool IsScriptReady()
        {
            if (IsScriptHookDotNetScript)
                return Running;

            return Running && InitEventCalled;
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
