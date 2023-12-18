using System;
using System.Collections.Generic;
using System.Reflection;
using System.Threading.Tasks;
using System.Windows.Forms;

using IVSDKDotNet;

namespace Manager.Classes
{
    public class FoundScript
    {
        #region Variables
        // Script info
        public Guid ID;
        public string Name;
        public string FullPath;
        public bool HasOnFirstD3D9FrameEventBeenRaised;

        public Type EntryPoint;
        public FieldInfo[] PublicFields;
        public Script TheScript;
        public List<AdvancedTask> ScriptTasks;
        public List<string> ConsoleCommands;

        // Dear ImGui
        public List<IntPtr> Textures;

        // Other
        public bool Running;
        public bool InitEventCalled;
        private Task cleanUpTask;
        public Exception AbortError;
        #endregion

        #region Constructor
        public FoundScript(string name, string fullPath, Script script, Type entryPoint)
        {
            Name = name;
            FullPath = fullPath;
            TheScript = script;
            ID = TheScript.ID;

            EntryPoint = entryPoint;
            PublicFields = EntryPoint.GetFields(BindingFlags.Instance | BindingFlags.Public);
            
            // Lists
            // Initializing all lists with a Capacity of 8 so they don't need to resize for every new item that is added to them (Aslong as they don't reach the set Capacity).
            ScriptTasks = new List<AdvancedTask>(8);
            ConsoleCommands = new List<string>(8);
            Textures = new List<IntPtr>(8);

            Running = true;
        }
        #endregion

        #region Raisers
        public void RaiseInitialized()
        {
            if (!InitEventCalled)
            {
                TheScript.RaiseInitialized();
                InitEventCalled = true;
            }
        }
        public void RaiseUninitialize()
        {
            TheScript.RaiseUninitialize();
        }

        public void RaiseTick()
        {
            if (!IsScriptReady())
                return;

            DateTime time = DateTime.UtcNow;
            TheScript.RaiseTick();
            TheScript.TickEventExecutionTime = DateTime.UtcNow - time;
        }
        public void RaiseGameLoad()
        {
            if (!IsScriptReady())
                return;

            DateTime time = DateTime.UtcNow;
            TheScript.RaiseGameLoad();
            TheScript.GameLoadEventExecutionTime = DateTime.UtcNow - time;
        }
        public void RaiseGameLoadPriority()
        {
            if (!IsScriptReady())
                return;

            DateTime time = DateTime.UtcNow;
            TheScript.RaiseGameLoadPriority();
            TheScript.GameLoadPriorityEventExecutionTime = DateTime.UtcNow - time;
        }
        public void RaiseMountDevice()
        {
            if (!IsScriptReady())
                return;

            DateTime time = DateTime.UtcNow;
            TheScript.RaiseMountDevice();
            TheScript.MountDeviceEventExecutionTime = DateTime.UtcNow - time;
        }
        public void RaiseDrawing()
        {
            if (!IsScriptReady())
                return;

            DateTime time = DateTime.UtcNow;
            TheScript.RaiseDrawing();
            TheScript.DrawingEventExecutionTime = DateTime.UtcNow - time;
        }
        public void RaiseProcessCamera()
        {
            if (!IsScriptReady())
                return;

            DateTime time = DateTime.UtcNow;
            TheScript.RaiseProcessCamera();
            TheScript.ProcessCameraEventExecutionTime = DateTime.UtcNow - time;
        }
        public void RaiseProcessAutomobile(UIntPtr vehPtr)
        {
            if (!IsScriptReady())
                return;

            DateTime time = DateTime.UtcNow;
            TheScript.RaiseProcessAutomobile(vehPtr);
            TheScript.ProcessAutomobileEventExecutionTime = DateTime.UtcNow - time;
        }
        public void RaiseProcessPad(UIntPtr padPtr)
        {
            if (!IsScriptReady())
                return;

            DateTime time = DateTime.UtcNow;
            TheScript.RaiseProcessPad(padPtr);
            TheScript.ProcessPadEventExecutionTime = DateTime.UtcNow - time;
        }
        public void RaiseOnFirstD3D9Frame()
        {
            if (!IsScriptReady())
                return;

            if (!HasOnFirstD3D9FrameEventBeenRaised)
            {
                DateTime time = DateTime.UtcNow;
                TheScript.RaiseOnFirstD3D9Frame();
                TheScript.OnFirstD3D9FrameEventExecutionTime = DateTime.UtcNow - time;

                HasOnFirstD3D9FrameEventBeenRaised = true;
            }
        }

        public void RaiseKeyDown(KeyEventArgs e)
        {
            if (!IsScriptReady())
                return;

            DateTime time = DateTime.UtcNow;
            TheScript.RaiseKeyDown(e);
            TheScript.KeyDownEventExecutionTime = DateTime.UtcNow - time;
        }
        public void RaiseKeyUp(KeyEventArgs e)
        {
            if (!IsScriptReady())
                return;

            DateTime time = DateTime.UtcNow;
            TheScript.RaiseKeyUp(e);
            TheScript.KeyUpEventExecutionTime = DateTime.UtcNow - time;
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
            TheScript.Dispose();
            TheScript = null;
            ID = Guid.Empty;
            Name = null;
            FullPath = null;
            EntryPoint = null;
        }
        public void Stop()
        {
            Running = false;
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

                if (!ImGuiIV.ReleaseTexture(TheScript, ref txtPtr))
                    Logger.LogWarning(string.Format("Could not release texture {0} of script {1}.", txtPtr, scriptName));
            }

            // Clear list
            Textures.Clear();

            // Log
            Logger.LogDebug(string.Format("Destroyed {0} Direct3D9 Textures of script {1}", texturesCount, scriptName));
        }
        #endregion

        #region Functions
        /// <summary>
        /// Gets if the <see cref="Script"/> is ready so their events can be executed.
        /// </summary>
        /// <returns>True if the <see cref="Script"/> is ready. Otherwise false.</returns>
        public bool IsScriptReady()
        {
            return Running && InitEventCalled;
        }
        #endregion
    }
}
