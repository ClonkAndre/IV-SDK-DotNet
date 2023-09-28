using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using System.Windows.Forms;

using IVSDKDotNet;
using IVSDKDotNet.Direct3D9;

namespace Manager.Classes
{
    public class FoundScript
    {
        #region Variables
        // Script info
        public Guid ID;
        public string Name;
        public string FullPath;
        public bool RaiseOnD3D9InitEvent = true;

        public Type EntryPoint;
        public FieldInfo[] PublicFields;
        public Script Script;
        public List<AdvancedTask> ScriptTasks;
        public List<string> ConsoleCommands;

        // Graphics
        public D3DGraphics GFX;
        public Dictionary<Guid, D3DResource> D3D9Objects;

        // Other
        private bool running;
        private bool initEventCalled;
        private Task cleanUpTask;
        public Exception AbortError;
        #endregion

        #region Constructor
        public FoundScript(Guid id, Type entryPoint, Script script)
        {
            ID = id;
            EntryPoint = entryPoint;
            PublicFields = EntryPoint.GetFields();
            Script = script;
            ScriptTasks = new List<AdvancedTask>();
            ConsoleCommands = new List<string>();
            D3D9Objects = new Dictionary<Guid, D3DResource>();
            running = true;
        }
        #endregion

        #region Raisers
        public void RaiseInitialized()
        {
            if (!initEventCalled)
            {
                Script.RaiseInitialized();
                initEventCalled = true;
            }
        }
        public void RaiseTick()
        {
            DateTime time = DateTime.UtcNow;
            Script.RaiseTick();
            Script.TickEventExecutionTime = DateTime.UtcNow - time;
        }
        public void RaiseGameLoad()
        {
            DateTime time = DateTime.UtcNow;
            Script.RaiseGameLoad();
            Script.GameLoadEventExecutionTime = DateTime.UtcNow - time;
        }
        public void RaiseGameLoadPriority()
        {
            DateTime time = DateTime.UtcNow;
            Script.RaiseGameLoadPriority();
            Script.GameLoadPriorityEventExecutionTime = DateTime.UtcNow - time;
        }
        public void RaiseMountDevice()
        {
            DateTime time = DateTime.UtcNow;
            Script.RaiseMountDevice();
            Script.MountDeviceEventExecutionTime = DateTime.UtcNow - time;
        }
        public void RaiseDrawing()
        {
            DateTime time = DateTime.UtcNow;
            Script.RaiseDrawing();
            Script.DrawingEventExecutionTime = DateTime.UtcNow - time;
        }
        public void RaiseProcessCamera()
        {
            DateTime time = DateTime.UtcNow;
            Script.RaiseProcessCamera();
            Script.ProcessCameraEventExecutionTime = DateTime.UtcNow - time;
        }
        public void RaiseProcessAutomobile(UIntPtr vehPtr)
        {
            DateTime time = DateTime.UtcNow;
            Script.RaiseProcessAutomobile(vehPtr);
            Script.ProcessAutomobileEventExecutionTime = DateTime.UtcNow - time;
        }
        public void RaiseProcessPad()
        {
            DateTime time = DateTime.UtcNow;
            Script.RaiseProcessPad();
            Script.ProcessPadEventExecutionTime = DateTime.UtcNow - time;
        }

        public void RaiseOnEndScene(IntPtr device)
        {
            if (GFX != null)
            {
                DateTime time = DateTime.UtcNow;

                // Raise OnInit event once
                if (RaiseOnD3D9InitEvent)
                {
                    GFX.Device = device;
                    GFX.RaiseOnInit(device);
                    GFX.OnInitEventExecutionTime = DateTime.UtcNow - time;
                    RaiseOnD3D9InitEvent = false;
                }

                // Raise OnDeviceEndScene event
                GFX.Device = device;
                GFX.RaiseOnDeviceEndScene(device);
                GFX.OnDeviceEndSceneEventExecutionTime = DateTime.UtcNow - time;
            }
        }
        public void RaiseOnBeforeReset(IntPtr device, IntPtr presentParameters)
        {
            if (GFX != null)
            {
                // Reset D3DResources
                D3DResource[] res = D3D9Objects.Values.ToArray();
                for (int i = 0; i < res.Length; i++)
                {
                    D3DResource obj = res[i];
                    switch (obj.DXType)
                    {
                        case eD3D9ResourceType.Font:
                            ((SharpDX.Direct3D9.Font)obj.Handle).OnLostDevice();
                            break;
                    }
                }

                DateTime time = DateTime.UtcNow;
                GFX.Device = device;
                GFX.RaiseOnBeforeDeviceReset(device, Marshal.PtrToStructure<SharpDX.Direct3D9.PresentParameters>(presentParameters).ToD3DPresentParameters());
                GFX.OnBeforeDeviceResetEventExecutionTime = DateTime.UtcNow - time;
            }
        }
        public void RaiseOnAfterReset(IntPtr device)
        {
            if (GFX != null)
            {
                // Refresh D3DResources
                D3DResource[] res = D3D9Objects.Values.ToArray();
                for (int i = 0; i < res.Length; i++)
                {
                    D3DResource obj = res[i];
                    switch (obj.DXType)
                    {
                        case eD3D9ResourceType.Font:
                            ((SharpDX.Direct3D9.Font)obj.Handle).OnResetDevice();
                            break;
                    }
                }

                DateTime time = DateTime.UtcNow;
                GFX.Device = device;
                GFX.RaiseOnAfterDeviceReset(device);
                GFX.OnAfterDeviceResetEventExecutionTime = DateTime.UtcNow - time;
            }
        }

        public void RaiseKeyDown(KeyEventArgs e)
        {
            Script.RaiseKeyDown(e);
        }
        public void RaiseKeyUp(KeyEventArgs e)
        {
            Script.RaiseKeyUp(e);
        }
        #endregion

        #region Methods
        public void Abort(bool showMessage, bool wasApiCall = false)
        {
            if (cleanUpTask != null)
                return;

            // Disable the functionality to raise any script events (except for the Uninitialize event)
            Stop();

            // Raise Uninitialize event
            Script.RaiseUninitialize();

            // Start cleanup process
            cleanUpTask = Task.Run(() =>
            {
                try
                {
                    // Delete all console commands registered by this script
                    for (int i = 0; i < ConsoleCommands.Count; i++)
                    {
                        string command = ConsoleCommands[i];
                        if (Main.Instance.Console.Commands.ContainsKey(command))
                            Main.Instance.Console.Commands.Remove(command);
                    }
                    ConsoleCommands.Clear();

                    // Stop all active script tasks
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
                        Main.Instance.Console.PrintDebug(string.Format("{0} active tasks stopped for script {1}. This process took {2}.{3} seconds.", scriptTasks.Length.ToString(), Name, timeResult.Seconds, timeResult.Milliseconds));

                    }
                    ScriptTasks.Clear();

                    // Dispose script
                    Script.Dispose();
                    Script = null;

                    // Destroy script resources
                    DestroyD3D9Objects();

                    return null;
                }
                catch (Exception ex)
                {
                    return ex;
                }
            }).ContinueWith(r =>
            {
                if (r.Result != null)
                {
                    AbortError = r.Result;
                    Main.Instance.Console.PrintError(string.Format("An error occured while aborting script {0}. Details: {1}", Name, r.Result.ToString()));
                }
                else
                {
                    if (showMessage)
                    {
                        if (wasApiCall)
                            Main.Instance.Console.Print(string.Format("An API Client has successfully aborted the script {0}.", Name));
                        else
                            Main.Instance.Console.Print(string.Format("Successfully aborted script {0}.", Name));
                    }
                }

                // Clean everything else
                ID = Guid.Empty;
                Name = null;
                FullPath = null;
                EntryPoint = null;
            });
        }
        public void Stop()
        {
            running = false;
        }

        public void DestroyD3D9Objects()
        {
            GFX = null;

            if (D3D9Objects != null)
            {
                D3D9Objects.Values.ToList().ForEach(x => {
                    if (x == null)
                        return;

                    SharpDX.ComObject obj = (SharpDX.ComObject)x.Handle;

                    if (obj != null)
                    {
                        if (!obj.IsDisposed) obj.Dispose();
                    }
                });
                D3D9Objects.Clear();

                // Log
                Main.Instance.Console.PrintDebug(string.Format("Destroyed D3D9 objects of script {0}", string.IsNullOrEmpty(Name) ? "UNKNOWN" : Name));
            }
        }
        #endregion

        #region Functions
        /// <summary>
        /// Gets if the <see cref="IVSDKDotNet.Script"/> is ready so their events can be executed.
        /// </summary>
        /// <returns>True if the <see cref="IVSDKDotNet.Script"/> is ready. Otherwise false.</returns>
        public bool IsScriptReady()
        {
            return running && initEventCalled;
        }
        #endregion
    }
}
