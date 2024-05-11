using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Reflection;
using System.Threading.Tasks;
using System.Windows.Forms;

using Newtonsoft.Json;

using IVSDKDotNet;
using IVSDKDotNet.Enums;
using IVSDKDotNet.Native;

using Manager.Classes.Json.Script;

namespace Manager.Classes
{
    public class FoundScript
    {
        #region Variables and Properties
        // Script stuff
        public string Name;
        public string FullPath;
        public bool HasOnFirstD3D9FrameEventBeenRaised;

        public Assembly TheAssembly;
        public Type EntryPoint;
        public FieldInfo[] PublicFields;
        public object TheScriptObject;

        public ScriptConfig Config;

        // Lists
        public List<AdvancedTask> ScriptTasks;
        public List<string> ConsoleCommands;
        public Dictionary<string, BoundPhoneNumber> BoundPhoneNumbers;

        // Dear ImGui
        public List<IntPtr> Textures;

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
        #endregion

        #region Constructor
        public FoundScript(string name, string fullPath, Assembly theAssembly, object scriptObject, Type entryPoint)
        {
            Name = name;
            FullPath = fullPath;
            TheAssembly = theAssembly;
            TheScriptObject = scriptObject;
            EntryPoint = entryPoint;
            PublicFields = EntryPoint.GetFields(BindingFlags.Instance | BindingFlags.Public);
            
            // Lists
            // Initializing all lists with a Capacity of 8 so they don't need to resize for every new item that is added to them (Aslong as they don't reach the set Capacity).
            ScriptTasks = new List<AdvancedTask>(8);
            ConsoleCommands = new List<string>(8);
            BoundPhoneNumbers = new Dictionary<string, BoundPhoneNumber>(8);
            Textures = new List<IntPtr>(8);

            Running = true;
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

                        // Do some stuff for certain actions
                        switch (a.ID)
                        {
                            case GTA.ScriptActionID.KeyDown:
                                script.KeyDownActionQueued = false;
                                break;
                            case GTA.ScriptActionID.KeyUp:
                                script.KeyUpActionQueued = false;
                                break;
                        }
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
                DateTime time = DateTime.UtcNow;

                Script script = GetScriptAs<Script>();

                script.RaiseTick();
                script.TickEventExecutionTime = DateTime.UtcNow - time;

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

            DateTime time = DateTime.UtcNow;
            script.RaiseGameLoad();
            script.GameLoadEventExecutionTime = DateTime.UtcNow - time;
        }
        public void RaiseGameLoadPriority()
        {
            if (IsScriptHookDotNetScript)
                return;
            if (!IsScriptReady())
                return;

            Script script = GetScriptAs<Script>();

            DateTime time = DateTime.UtcNow;
            script.RaiseGameLoadPriority();
            script.GameLoadPriorityEventExecutionTime = DateTime.UtcNow - time;
        }
        public void RaiseMountDevice()
        {
            if (IsScriptHookDotNetScript)
                return;
            if (!IsScriptReady())
                return;

            Script script = GetScriptAs<Script>();

            DateTime time = DateTime.UtcNow;
            script.RaiseMountDevice();
            script.MountDeviceEventExecutionTime = DateTime.UtcNow - time;
        }
        public void RaiseDrawing()
        {
            if (IsScriptHookDotNetScript)
                return;
            if (!IsScriptReady())
                return;

            Script script = GetScriptAs<Script>();

            DateTime time = DateTime.UtcNow;
            script.RaiseDrawing();
            script.DrawingEventExecutionTime = DateTime.UtcNow - time;
        }
        public void RaiseProcessCamera()
        {
            if (IsScriptHookDotNetScript)
                return;
            if (!IsScriptReady())
                return;

            Script script = GetScriptAs<Script>();

            DateTime time = DateTime.UtcNow;
            script.RaiseProcessCamera();
            script.ProcessCameraEventExecutionTime = DateTime.UtcNow - time;
        }
        public void RaiseProcessAutomobile(UIntPtr vehPtr)
        {
            if (IsScriptHookDotNetScript)
                return;
            if (!IsScriptReady())
                return;

            Script script = GetScriptAs<Script>();

            DateTime time = DateTime.UtcNow;
            script.RaiseProcessAutomobile(vehPtr);
            script.ProcessAutomobileEventExecutionTime = DateTime.UtcNow - time;
        }
        public void RaiseProcessPad(UIntPtr padPtr)
        {
            if (IsScriptHookDotNetScript)
                return;
            if (!IsScriptReady())
                return;

            Script script = GetScriptAs<Script>();

            DateTime time = DateTime.UtcNow;
            script.RaiseProcessPad(padPtr);
            script.ProcessPadEventExecutionTime = DateTime.UtcNow - time;
        }
        public void RaiseIngameStartup()
        {
            if (IsScriptHookDotNetScript)
                return;
            if (!IsScriptReady())
                return;

            Script script = GetScriptAs<Script>();

            DateTime time = DateTime.UtcNow;
            script.RaiseIngameStartup();
            script.IngameStartupEventExecutionTime = DateTime.UtcNow - time;
        }

        public void RaiseKeyDown(KeyEventArgs e)
        {
            if (!IsScriptReady())
                return;

            if (IsScriptHookDotNetScript)
            {
                GTA.Script script = GetScriptAs<GTA.Script>();

                if (script.KeyDownActionQueued)
                    return;

                script.ActionQueue.Enqueue(new GTA.ScriptAction(GTA.ScriptActionID.KeyDown, () =>
                {
                    script.DoKeyDown(new GTA.KeyEventArgs(e.KeyData));
                    script.ProcessBoundKeys(e.KeyData);
                }));

                script.KeyDownActionQueued = true;
            }
            else
            {
                Script script = GetScriptAs<Script>();

                DateTime time = DateTime.UtcNow;
                script.RaiseKeyDown(e);
                script.KeyDownEventExecutionTime = DateTime.UtcNow - time;
            }
        }
        public void RaiseKeyUp(KeyEventArgs e)
        {
            if (!IsScriptReady())
                return;

            if (IsScriptHookDotNetScript)
            {
                GTA.Script script = GetScriptAs<GTA.Script>();

                if (script.KeyUpActionQueued)
                    return;

                script.ActionQueue.Enqueue(new GTA.ScriptAction(GTA.ScriptActionID.KeyUp, () => script.DoKeyUp(new GTA.KeyEventArgs(e.KeyData))));

                script.KeyUpActionQueued = true;
            }
            else
            {
                Script script = GetScriptAs<Script>();

                DateTime time = DateTime.UtcNow;
                script.RaiseKeyUp(e);
                script.KeyUpEventExecutionTime = DateTime.UtcNow - time;
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
        public void RaiseOnFirstD3D9Frame(IntPtr devicePtr)
        {
            if (IsScriptHookDotNetScript)
                return;
            if (!IsScriptReady())
                return;

            if (!HasOnFirstD3D9FrameEventBeenRaised)
            {
                Script script = GetScriptAs<Script>();

                DateTime time = DateTime.UtcNow;
                script.RaiseOnFirstD3D9Frame(devicePtr);
                script.OnFirstD3D9FrameEventExecutionTime = DateTime.UtcNow - time;

                HasOnFirstD3D9FrameEventBeenRaised = true;
            }
        }
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

                // TODO: Add event execution time
                script.RaiseOnImGuiRendering(devicePtr, ctx);
            }
        }
        #endregion

        #region Methods
        public void Abort(AbortReason reason, bool showMessage)
        {
            if (cleanUpTask != null)
                return;

            // Stop active script tasks
            StopActiveScriptTasks();

            // Disable the functionality to raise any script events (Except for the Uninitialize event)
            Stop();

            // Raise Uninitialize event
            RaiseUninitialize();

            // Clear ImGui Draw Calls List for this Script
            ClearImGuiDrawCalls();

            // Delete all console commands registered by this script
            for (int i = 0; i < ConsoleCommands.Count; i++)
            {
                string command = ConsoleCommands[i];

                if (Main.Instance.Console.Commands.ContainsKey(command))
                    Main.Instance.Console.Commands.Remove(command);
            }
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
                        Logger.Log(string.Format("An API Client has successfully aborted the script {0}.", Name));
                        break;
                    case AbortReason.Manual:
                        Logger.Log(string.Format("Script {0} was successfully aborted by user.", Name));
                        break;
                    case AbortReason.Script:
                        Logger.Log(string.Format("Script {0} was successfully aborted by another script (Or by {0} itself).", Name));
                        break;
                    case AbortReason.Manager:
                        Logger.Log(string.Format("Manager successfully aborted script {0}.", Name));
                        break;
                }
            }

            // Cleanup other script things
            if (IsScriptHookDotNetScript)
                GetScriptAs<GTA.Script>().Dispose();
            else
                GetScriptAs<Script>().Dispose();

            Name = null;
            FullPath = null;
            EntryPoint = null;
        }
        public void Stop()
        {
            Running = false;
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
                Logger.LogError(string.Format("Failed to get script config of Script {0}! Details: {1}", Name, ex));
            }
        }
        public void CheckForExistenceOfReferencedAssemblies()
        {
            if (IsScriptHookDotNetScript)
                return;
            if (Config == null)
                return;

            // TODO

            Script script = GetScriptAs<Script>();

            // Check if referenced assemblies of script exists
            AssemblyName[] referencedAssemblies = TheAssembly.GetReferencedAssemblies();

            for (int i = 0; i < referencedAssemblies.Length; i++)
            {
                string assemblyName = string.Format("{0}.dll", referencedAssemblies[i].Name);
                Logger.LogDebug("Looking for: " + assemblyName);

                // Try finding the assembly location
                string assemblyFileName = string.Empty;

                switch (script.AssembliesLocation)
                {
                    case eAssembliesLocation.GameRootDirectory:
                        assemblyFileName = Directory.GetFiles(IVGame.GameStartupPath, "*.dll").Where(x => x.ToLower().EndsWith(assemblyName.ToLower())).FirstOrDefault();
                        break;
                    case eAssembliesLocation.ScriptsDirectory:
                        assemblyFileName = Directory.GetFiles(CLR.CLRBridge.IVSDKDotNetScriptsPath, "*.dll").Where(x => x.ToLower().EndsWith(assemblyName.ToLower())).FirstOrDefault();
                        break;

                    default:
                        continue;
                }

                if (string.IsNullOrWhiteSpace(assemblyFileName))
                    continue;

                // If file does not exists
                if (!File.Exists(assemblyFileName))
                {
                    Logger.LogWarning("- does not exists!");
                }
            }
        }

        private void StopActiveScriptTasks()
        {
            cleanUpTask = Task.Run(() =>
            {
                try
                {
                    if (ScriptTasks.Count != 0)
                    {
                        DateTime taskCleanUpStartTime = DateTime.UtcNow;
                        Task[] scriptTasks = new Task[ScriptTasks.Count];

                        // Put all active tasks in task array and cancel them
                        for (int i = 0; i < ScriptTasks.Count; i++)
                        {
                            AdvancedTask sTask = ScriptTasks[i];
                            scriptTasks[i] = sTask.task;
                            sTask.taskController.Cancel();
                        }

                        // Wait until all tasks are completed
                        Task.WaitAll(scriptTasks);

                        // Dispose and remove all tasks from user
                        for (int i = 0; i < ScriptTasks.Count; i++)
                        {
                            AdvancedTask sTask = ScriptTasks[i];
                            sTask.Dispose();
                            ScriptTasks.RemoveAt(i);
                        }

                        // Log how long this process took
                        TimeSpan timeResult = (taskCleanUpStartTime - DateTime.UtcNow);
                        Logger.LogDebug(string.Format("{0} active tasks stopped for script {1}. This process took {2}.{3} seconds.", scriptTasks.Length.ToString(), Name, timeResult.Seconds, timeResult.Milliseconds));

                    }

                    ScriptTasks.Clear();

                    return null;
                }
                catch (Exception ex)
                {
                    return ex;
                }
            }).ContinueWith(x =>
            {
                if (x.Result != null)
                {
                    AbortError = x.Result;
                    Logger.LogError(string.Format("An error occured while stopping active scripts tasks for {0}. Details: {1}", Name, x.Result));
                }
            });
        }
        private void ClearImGuiDrawCalls()
        {
            List<ImGuiIV_DrawCommandData> list = ImGuiIV.DrawCommandsList;

            for (int i = 0; i < list.Count; i++)
            {
                ImGuiIV_DrawCommandData drawData = list[i];

                if (drawData.CallerScriptID == ID)
                    ImGuiIV.DrawCommandsList.RemoveAt(i);
            }
        }
        private void DestroyScriptTextures()
        {
            string scriptName = string.IsNullOrEmpty(Name) ? "UNKNOWN" : Name;
            int texturesCount = Textures.Count;

            if (Textures.Count == 0)
            {
                Logger.LogDebug(string.Format("There are no Direct3D9 Textures to destroy for script {0}.", scriptName));
                return;
            }

            // Get rid of each Texture this Script created
            for (int i = 0; i < Textures.Count; i++)
            {
                IntPtr txtPtr = Textures[i];

                if (IsScriptHookDotNetScript)
                {
                    // TODO
                }
                else
                {
                    if (!ImGuiIV.ReleaseTexture(GetScriptAs<Script>(), ref txtPtr))
                        Logger.LogWarning(string.Format("Could not release texture {0} of script {1}.", txtPtr, scriptName));
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
