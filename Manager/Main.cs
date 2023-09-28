using System;
using System.Collections.Generic;
using System.Drawing;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Reflection;
using System.Threading.Tasks;
using System.Windows.Forms;

using Newtonsoft.Json;

using IVSDKDotNet;
using IVSDKDotNet.Enums;
using IVSDKDotNet.Manager;
using IVSDKDotNet.Direct3D9;

using Manager.Classes;
using Manager.Direct3D9;
using Manager.Managers;

namespace Manager
{
    public class Main : ManagerScript
    {

        public const string ManagerVersion = "1.0";

        #region Variables
        internal static Main Instance;

        // Lists
        public List<FoundScript> ActiveScripts;
        public List<AdvancedTask> LocalTasks;
        private List<DelayedAction> delayedActions;

        // Managers
        public ConsoleManager Console;
        public NotificationManager Notification;
        public RemoteConnectionManager ConnectionManager;

        // Hooks
        private DXHook direct3D9Hook;
        private KeyWatchDog keyWatchDog;

        // Local Direct3D9 Resources
        public SharpDX.Direct3D9.Font LocalD3D9Font;

        // Other
        public UpdateChecker UpdateChecker;
        public Process GTAIVProcess;
        private SettingsFile settings;
        private Mouse mouse;
        private Guid processCheckerTimerID;
        public string IVSDKDotNetPath, IVSDKDotNetBinaryPath, ScriptsPath;
        private bool firstFrame = true;

        public bool IsGTAIVWindowInFocus;
        private bool onWindowFocusChangedEventCalled;
        private bool pauseScriptExecutionWhenNotInFocus;
        private bool allowRemoteConnections;
        #endregion

        #region Events

        // Assembly
        private Assembly CurrentDomain_AssemblyResolve(object sender, ResolveEventArgs args)
        {
            string assemblyName = args.Name.Split(',')[0];
            string assemblyPath = string.Format("{0}\\{1}.dll", IVSDKDotNetBinaryPath, assemblyName);

            if (File.Exists(assemblyPath))
                return Assembly.UnsafeLoadFrom(assemblyPath);

            return null;
        }

        // WndProc
        private bool WndProcHook_OnWndMessage(IntPtr hWnd, uint msg, UIntPtr wParam, IntPtr lParam)
        {
            switch (msg)
            {
                case 2: // WM_DESTROY - Window starts to being destroyed.
                    Cleanup();
                    break;
            }
            return false;
        }

        // Direct3D9Hook
        private void Direct3D9Hook_InternalOnInit(IntPtr device)
        {
            SharpDX.Direct3D9.Device d = (SharpDX.Direct3D9.Device)device;

            // Create local D3D9 resources
            LocalD3D9Font = new SharpDX.Direct3D9.Font(d, D3DFontDescription.Default().ToSharpDXFontDescription());
            mouse = new Mouse(device);
        }

        // UpdateChecker
        private void UpdateChecker_VersionCheckFailed(Exception e)
        {
            Notification.ShowNotification(NotificationType.Error, DateTime.UtcNow.AddSeconds(5), "An error occured while checking for IV-SDK .NET updates", "Check the IV-SDK .NET console for more details.", "UPDATE_CHECK_FAILED");
            Console.PrintError(string.Format("Error while checking for updates. Details: {0}", e.ToString()));
        }
        private void UpdateChecker_VersionCheckCompleted(UpdateChecker.VersionCheckInfo result)
        {
            if (result.NewVersionAvailable)
            {
                Notification.ShowNotification(NotificationType.Default, DateTime.UtcNow.AddSeconds(7), "New IV-SDK .NET update available!", string.Format("Version {0} of IV-SDK .NET is available to download.", result.NewVersion), "NEW_UPDATE_AVAILABLE");
                Console.Print(string.Format("Version {0} of IV-SDK .NET is available!", result.NewVersion));
            }
            else
            {
                Console.Print("There is currently no new IV-SDK .NET update available.");
            }
        }

        #endregion

        #region Constructor
        public Main()
        {
            // Set instance
            Instance = this;

            // Set paths
            IVSDKDotNetPath =       Application.StartupPath + "\\IVSDKDotNet";
            IVSDKDotNetBinaryPath = IVSDKDotNetPath + "\\bin";
            ScriptsPath =           IVSDKDotNetPath + "\\scripts";

            // Lists
            ActiveScripts =     new List<FoundScript>();
            LocalTasks =        new List<AdvancedTask>();
            delayedActions =    new List<DelayedAction>();

            // Managers
            Console =           new ConsoleManager();
            Notification =      new NotificationManager();
            ConnectionManager = new RemoteConnectionManager();

            // Subscribe to AppDomain events
            AppDomain.CurrentDomain.AssemblyResolve += CurrentDomain_AssemblyResolve;

            // Hooks
            direct3D9Hook = new DXHook();
            direct3D9Hook.OnInit +=         Direct3D9Hook_InternalOnInit;
            direct3D9Hook.OnEndScene +=     Direct3D9Hook_OnEndScene;
            direct3D9Hook.OnBeforeReset +=  Direct3D9Hook_OnBeforeReset;
            direct3D9Hook.OnAfterReset +=   Direct3D9Hook_OnAfterReset;

            RAGE.OnWndProcMessageReceived += WndProcHook_OnWndMessage;

            keyWatchDog =   new KeyWatchDog();
            keyWatchDog.KeyDown +=  KeyWatchDog_KeyDown;
            keyWatchDog.KeyUp +=    KeyWatchDog_KeyUp;

            // Init WndProc Hook
            StartDelayedAction(Guid.NewGuid(), "Initialize WndProc Hook", DateTime.UtcNow.AddSeconds(1), (DelayedAction dA, object param) => {
                try
                {
                    bool result = RAGE.InitWndProcHook();
                    if (result)
                        Console.PrintDebug("[WndProcHook] Hooked!");
                    else
                        Console.PrintError("An unknown error occured while trying to initialize the WndProc hook! Scripts that rely on it may not work correctly.");
                }
                catch (Exception ex)
                {
                    Console.PrintError(string.Format("An error occured while trying to initialize the WndProc Hook. Details: {0}", ex.ToString()));
                }
            }, null);

            // Init D3D9 Hook
            StartDelayedAction(Guid.NewGuid(), "Initialize D3D9 Hook", DateTime.UtcNow.AddSeconds(1), (DelayedAction dA, object param) => {
                try
                {
                    direct3D9Hook.Init(RAGE.GetHWND());
                }
                catch (Exception ex)
                {
                    Console.UseOldDrawingSystem = true;
                    Notification.UseOldDrawingSystem = true;

                    Console.PrintError("An error occured while trying to initialize the D3D9 Hook. D3D9 drawing will not be available. Using legacy console and notification drawing method.");
                    Console.PrintError("If you happen to have dxvk or an ENB installed, please note that IV-SDK .NET does not currently work in combination with dxvk or an ENB.");
                    Console.PrintError("Details: " + ex.ToString());
                }
            }, null);

            // Other
            UpdateChecker = new UpdateChecker(ManagerVersion, "https://www.dropbox.com/s/smaz6ij8dkzd7nh/version.txt?dl=1");
            UpdateChecker.VersionCheckFailed +=     UpdateChecker_VersionCheckFailed;
            UpdateChecker.VersionCheckCompleted +=  UpdateChecker_VersionCheckCompleted;

            GTAIVProcess = Process.GetCurrentProcess();

            // Start process in focus checker timer
            processCheckerTimerID = StartNewTimerInternel(1000, () =>
            {

                IsGTAIVWindowInFocus = Helper.ProcessHelper.IsProcessInFocus(GTAIVProcess);

                // Invoke focus changed event
                if (IsGTAIVWindowInFocus)
                {
                    if (!onWindowFocusChangedEventCalled)
                    {
                        CGame.RaiseOnWindowFocusChanged(true);
                        onWindowFocusChangedEventCalled = true;
                    }
                }
                else
                {
                    if (onWindowFocusChangedEventCalled)
                    {
                        CGame.RaiseOnWindowFocusChanged(false);
                        onWindowFocusChangedEventCalled = false;
                    }
                }

            });

            // Print about text to console
#if DEBUG
            Console.Print(string.Format("IV-SDK .NET DEBUG version {0} by ItsClonkAndre", ManagerVersion));
#else
            Console.Print(string.Format("IV-SDK .NET Release version {0} by ItsClonkAndre", ManagerVersion));
#endif

            // Load IV-SDK .NET settings from file
            LoadConfig();

            // Start the server
            if (allowRemoteConnections)
                ConnectionManager.Start();
        }
        #endregion

        #region Raisers
        public override void RaiseTick()
        {
            if (pauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

            // Raise all script Tick events
            ActiveScripts.ForEach(fs =>
            {
                try
                {
                    if (fs.IsScriptReady())
                        fs.RaiseTick();
                }
                catch (Exception ex)
                {
                    Notification.ShowNotification(NotificationType.Error, DateTime.UtcNow.AddSeconds(8), string.Format("An error occured in {0} Tick.", fs.Name), ex.Message, string.Format("ERROR_IN_SCRIPT_{0}", fs.Name));
                    Console.PrintError(string.Format("An error occured while processing Tick event for script {0}. Aborting script. Details: {1}", fs.Name, ex.ToString()));
                    AbortScript(fs.ID);
                }
            });

            // Draw console and notifications
            if (Console.UseOldDrawingSystem)        Console.Draw(IntPtr.Zero);
            if (Notification.UseOldDrawingSystem)   Notification.Draw(IntPtr.Zero);
        }
        public override void RaiseGameLoad()
        {
            if (pauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

            ActiveScripts.ForEach(fs =>
            {
                try
                {
                    if (fs.IsScriptReady())
                        fs.RaiseGameLoad();
                }
                catch (Exception ex)
                {
                    Notification.ShowNotification(NotificationType.Error, DateTime.UtcNow.AddSeconds(8), string.Format("An error occured in {0} GameLoad.", fs.Name), ex.Message, string.Format("ERROR_IN_SCRIPT_{0}", fs.Name));
                    Console.PrintError(string.Format("An error occured while processing GameLoad event for script {0}. Aborting script. Details: {1}", fs.Name, ex.ToString()));
                    AbortScript(fs.ID);
                }
            });
        }
        public override void RaiseGameLoadPriority()
        {
            if (pauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

            ActiveScripts.ForEach(fs =>
            {
                try
                {
                    if (fs.IsScriptReady())
                        fs.RaiseGameLoadPriority();
                }
                catch (Exception ex)
                {
                    Notification.ShowNotification(NotificationType.Error, DateTime.UtcNow.AddSeconds(8), string.Format("An error occured in {0} GameLoadPriority.", fs.Name), ex.Message, string.Format("ERROR_IN_SCRIPT_{0}", fs.Name));
                    Console.PrintError(string.Format("An error occured while processing GameLoadPriority event for script {0}. Aborting script. Details: {1}", fs.Name, ex.ToString()));
                    AbortScript(fs.ID);
                }
            });
        }
        public override void RaiseMountDevice()
        {
            if (pauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

            ActiveScripts.ForEach(fs =>
            {
                try
                {
                    if (fs.IsScriptReady())
                        fs.RaiseMountDevice();
                }
                catch (Exception ex)
                {
                    Notification.ShowNotification(NotificationType.Error, DateTime.UtcNow.AddSeconds(8), string.Format("An error occured in {0} MountDevice.", fs.Name), ex.Message, string.Format("ERROR_IN_SCRIPT_{0}", fs.Name));
                    Console.PrintError(string.Format("An error occured while processing MountDevice event for script {0}. Aborting script. Details: {1}", fs.Name, ex.ToString()));
                    AbortScript(fs.ID);
                }
            });
        }
        public override void RaiseDrawing()
        {
            // Update the remote server
            ConnectionManager.Update();

            if (pauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

            DateTime dtNow = DateTime.UtcNow;

            // Execute Delayed Actions if there are any
            for (int i = 0; i < delayedActions.Count; i++)
            {
                DelayedAction dA = delayedActions[i];
                if (dtNow >= dA.ExecuteIn)
                {
                    try
                    {
                        if (dA.ActionToExecute != null)
                        {
                            if (!string.IsNullOrEmpty(dA.Purpose))
                                Console.PrintDebug(string.Format("Delayed Action triggered. Purpose: {0}", dA.Purpose));
                            dA.ActionToExecute.Invoke(dA, dA.Parameter);
                        }
                        delayedActions.RemoveAt(i);
                    }
                    catch (Exception ex)
                    {
                        Console.PrintError(string.Format("An error occured while executing delayed action. DA Purpose: {0}, Details: {1}", dA.Purpose, ex.ToString()));
                    }
                }
            }

            // Raise all script Drawing events
            ActiveScripts.ForEach(fs =>
            {
                try
                {
                    if (fs.IsScriptReady())
                        fs.RaiseDrawing();
                }
                catch (Exception ex)
                {
                    Notification.ShowNotification(NotificationType.Error, DateTime.UtcNow.AddSeconds(8), string.Format("An error occured in {0} Drawing.", fs.Name), ex.Message, string.Format("ERROR_IN_SCRIPT_{0}", fs.Name));
                    Console.PrintError(string.Format("An error occured while processing Drawing event for script {0}. Aborting script. Details: {1}", fs.Name, ex.ToString()));
                    AbortScript(fs.ID);
                }
            });
        }
        public override void RaiseProcessCamera()
        {
            if (pauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

            ActiveScripts.ForEach(fs =>
            {
                try
                {
                    if (fs.IsScriptReady())
                        fs.RaiseProcessCamera();
                }
                catch (Exception ex)
                {
                    Notification.ShowNotification(NotificationType.Error, DateTime.UtcNow.AddSeconds(8), string.Format("An error occured in {0} ProcessCamera.", fs.Name), ex.Message, string.Format("ERROR_IN_SCRIPT_{0}", fs.Name));
                    Console.PrintError(string.Format("An error occured while processing ProcessCamera event for script {0}. Aborting script. Details: {1}", fs.Name, ex.ToString()));
                    AbortScript(fs.ID);
                }
            });
        }
        public override void RaiseProcessAutomobile(UIntPtr vehPtr)
        {
            if (pauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

            ActiveScripts.ForEach(fs =>
            {
                try
                {
                    if (fs.IsScriptReady())
                        fs.RaiseProcessAutomobile(vehPtr);
                }
                catch (Exception ex)
                {
                    Notification.ShowNotification(NotificationType.Error, DateTime.UtcNow.AddSeconds(8), string.Format("An error occured in {0} ProcessAutomobile.", fs.Name), ex.Message, string.Format("ERROR_IN_SCRIPT_{0}", fs.Name));
                    Console.PrintError(string.Format("An error occured while processing ProcessAutomobile event for script {0}. Aborting script. Details: {1}", fs.Name, ex.ToString()));
                    AbortScript(fs.ID);
                }
            });
        }
        public override void RaiseProcessPad()
        {
            if (pauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

            // Do stuff on first frame
            if (firstFrame)
            {
                UpdateChecker.CheckForUpdates(true);
                firstFrame = false;
            }

            // Check for key presses
            if (keyWatchDog != null)
                keyWatchDog.ProcessCheck();

            // Raise all script ProcessPad events
            ActiveScripts.ForEach(fs =>
            {
                try
                {
                    if (fs.IsScriptReady())
                        fs.RaiseProcessPad();
                }
                catch (Exception ex)
                {
                    Notification.ShowNotification(NotificationType.Error, DateTime.UtcNow.AddSeconds(8), string.Format("An error occured in {0} ProcessPad.", fs.Name), ex.Message, string.Format("ERROR_IN_SCRIPT_{0}", fs.Name));
                    Console.PrintError(string.Format("An error occured while processing ProcessPad event for script {0}. Aborting script. Details: {1}", fs.Name, ex.ToString()));
                    AbortScript(fs.ID);
                }
            });
        }

        private void Direct3D9Hook_OnEndScene(IntPtr device)
        {
            if (pauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

            SharpDX.Direct3D9.Device d = (SharpDX.Direct3D9.Device)device;

            // Enable scissor test render state
            d.SetRenderState(SharpDX.Direct3D9.RenderState.ScissorTestEnable, true);

            // Draw script things
            ActiveScripts.ForEach(fs =>
            {
                try
                {
                    if (fs.IsScriptReady())
                        fs.RaiseOnEndScene(device);
                }
                catch (Exception ex)
                {
                    Notification.ShowNotification(NotificationType.Error, DateTime.UtcNow.AddSeconds(8), string.Format("An error occured in {0} Direct3D9Hook_OnEndScene.", fs.Name), ex.Message, string.Format("ERROR_IN_SCRIPT_{0}", fs.Name));
                    Console.PrintError(string.Format("An error occured while processing Direct3D9Hook_OnEndScene event for script {0}. Aborting script. Details: {1}", fs.Name, ex.ToString()));
                    AbortScript(fs.ID);
                }
            });

            // Draw local things over script things
            if (Console != null)        Console.Draw(device);
            if (Notification != null)   Notification.Draw(device);
            if (mouse != null)          mouse.Draw(device);
        }
        private void Direct3D9Hook_OnBeforeReset(IntPtr device, IntPtr presentParameters)
        {
            if (pauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

            ActiveScripts.ForEach(fs =>
            {
                try
                {
                    if (fs.IsScriptReady())
                        fs.RaiseOnBeforeReset(device, presentParameters);
                }
                catch (Exception ex)
                {
                    Notification.ShowNotification(NotificationType.Error, DateTime.UtcNow.AddSeconds(8), string.Format("An error occured in {0} Direct3D9Hook_OnBeforeReset.", fs.Name), ex.Message, string.Format("ERROR_IN_SCRIPT_{0}", fs.Name));
                    Console.PrintError(string.Format("An error occured while processing Direct3D9Hook_OnBeforeReset event for script {0}. Aborting script. Details: {1}", fs.Name, ex.ToString()));
                    AbortScript(fs.ID);
                }
            });
        }
        private void Direct3D9Hook_OnAfterReset(IntPtr device)
        {
            if (pauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

            ActiveScripts.ForEach(fs =>
            {
                try
                {
                    if (fs.IsScriptReady())
                        fs.RaiseOnAfterReset(device);
                }
                catch (Exception ex)
                {
                    Notification.ShowNotification(NotificationType.Error, DateTime.UtcNow.AddSeconds(8), string.Format("An error occured in {0} Direct3D9Hook_OnAfterReset.", fs.Name), ex.Message, string.Format("ERROR_IN_SCRIPT_{0}", fs.Name));
                    Console.PrintError(string.Format("An error occured while processing Direct3D9Hook_OnAfterReset event for script {0}. Aborting script. Details: {1}", fs.Name, ex.ToString()));
                    AbortScript(fs.ID);
                }
            });
        }

        private void KeyWatchDog_KeyDown(object sender, KeyEventArgs e)
        {
            if (pauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

            // Raise local things
            if (Console != null)
                Console.KeyDown(e);

            // Raise all script KeyDown events
            ActiveScripts.ForEach(fs =>
            {
                try
                {
                    if (fs.IsScriptReady())
                    {
                        if (fs.Script.OnlyRaiseKeyEventsWhenInGame)
                        {
                            if (CPlayerInfo.FindPlayerPed() != UIntPtr.Zero)
                                fs.RaiseKeyDown(e);
                        }
                        else
                        {
                            fs.RaiseKeyDown(e);
                        }
                    }
                }
                catch (Exception ex)
                {
                    Notification.ShowNotification(NotificationType.Error, DateTime.UtcNow.AddSeconds(8), string.Format("An error occured in {0} KeyDown.", fs.Name), ex.Message, string.Format("ERROR_IN_SCRIPT_{0}", fs.Name));
                    Console.PrintError(string.Format("An error occured while processing KeyDown event for script {0}. Aborting script. Details: {1}", fs.Name, ex.ToString()));
                    AbortScript(fs.ID);
                }
            });

#if DEBUG
            // Debug key
            if (e.KeyCode == Keys.Pause)
            {

            }
#endif
        }
        private void KeyWatchDog_KeyUp(object sender, KeyEventArgs e)
        {
            if (pauseScriptExecutionWhenNotInFocus && !IsGTAIVWindowInFocus)
                return;

            // Raise all script KeyUp events
            ActiveScripts.ForEach(fs =>
            {
                try
                {
                    if (fs.IsScriptReady())
                    {
                        if (fs.Script.OnlyRaiseKeyEventsWhenInGame)
                        {
                            if (CPlayerInfo.FindPlayerPed() != UIntPtr.Zero)
                                fs.RaiseKeyUp(e);
                        }
                        else
                        {
                            fs.RaiseKeyUp(e);
                        }
                    }
                }
                catch (Exception ex)
                {
                    Notification.ShowNotification(NotificationType.Error, DateTime.UtcNow.AddSeconds(8), string.Format("An error occured in {0} KeyUp.", fs.Name), ex.Message, string.Format("ERROR_IN_SCRIPT_{0}", fs.Name));
                    Console.PrintError(string.Format("An error occured while processing KeyUp event for script {0}. Aborting script. Details: {1}", fs.Name, ex.ToString()));
                    AbortScript(fs.ID);
                }
            });
        }
        #endregion

        #region Helper Overrides
        public override string Helper_JSON_ConvertObjectToJsonString(object obj)
        {
            return JsonConvert.SerializeObject(obj);
        }
        public override object Helper_JSON_ConvertJsonStringToObject(string str)
        {
            return JsonConvert.DeserializeObject(str);
        }
        #endregion

        #region Console Overrides
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

        public override void PrintToConsole(string str)
        {
            Console.Print(str);
        }
        public override void PrintDebugToConsole(string str)
        {
            Console.PrintDebug(str);
        }
        public override void PrintWarnToConsole(string str)
        {
            Console.PrintWarning(str);
        }
        public override void PrintErrorToConsole(string str)
        {
            Console.PrintError(str);
        }

        public override bool IsConsoleOpen()
        {
            return Console.IsConsoleVisible;
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

        #region Mouse Overrides
        public override void SetMouseVisibility(bool visible)
        {
            if (mouse != null)
                mouse.IsVisible = visible;
        }
        public override bool GetMouseVisibility()
        {
            if (mouse != null)
                return mouse.IsVisible;

            return false;
        }

        public override bool GetMouseLeftButtonDown()
        {
            if (mouse != null)
                return mouse.LeftButtonDown;

            return false;
        }
        public override bool GetMouseRightButtonDown()
        {
            if (mouse != null)
                return mouse.RightButtonDown;

            return false;
        }
        public override bool GetMouseXButton1Down()
        {
            if (mouse != null)
                return mouse.XButton1Down;

            return false;
        }
        public override bool GetMouseXButton2Down()
        {
            if (mouse != null)
                return mouse.XButton2Down;

            return false;
        }
        public override int GetMouseWheelValue()
        {
            if (mouse != null)
                return mouse.MouseWheel;

            return 0;
        }

        public override Size GetMouseCursorSize()
        {
            if (mouse != null)
                return mouse.CursorSize;

            return Size.Empty;
        }
        public override void SetMouseCursorSize(Size size)
        {
            if (mouse != null)
                mouse.CursorSize = size;
        }

        public override void SetMousePosition(Point pos)
        {
            if (mouse != null)
                mouse.Position = pos;
        }
        public override Point GetMousePosition()
        {
            if (mouse != null)
                return mouse.Position;

            return Point.Empty;
        }

        public override bool GetMouseIntersectsWith(Rectangle rect)
        {
            if (mouse != null)
                return mouse.IntersectsWith(rect);

            return false;
        }
        #endregion

        #region Game Overrides
        public override bool IsGameInFocus()
        {
            return IsGTAIVWindowInFocus;
        }
        #endregion

        #region Direct3D9 Overrides

        public override void Direct3D9_Graphics_CreateNewInstance(ref object instance, Script forScript)
        {
            if (instance == null)
                return;
            if (forScript == null)
                return;

            FoundScript s = GetFoundScript(forScript.ID);
            if (s != null)
            {
                if (s.GFX == null)
                {
                    s.GFX = (D3DGraphics)instance;
                    s.GFX.Device = direct3D9Hook.DevicePtr;
                    Console.PrintDebug(string.Format("Set graphics instance for script {0}.", s.Name));
                }
            }
        }
        public override void Direct3D9_Graphics_DisposeInstance(Script ofScript)
        {
            if (ofScript == null)
                return;

            FoundScript s = GetFoundScript(ofScript.ID);

            if (s != null)
                s.GFX = null;
        }

        // Texture stuff
        public override long Direct3D9_Graphics_GetAvailableTextureMemory()
        {
            if (direct3D9Hook == null)
                return 0;
            if (direct3D9Hook.DevicePtr == IntPtr.Zero)
                return 0;

            return ((SharpDX.Direct3D9.Device)direct3D9Hook.DevicePtr).AvailableTextureMemory;
        }
        public override D3DResult Direct3D9_Graphics_CreateD3D9Texture(Script forScript, IntPtr device, string filePath, Size size)
        {
            if (forScript == null)
                return new D3DResult(new NullReferenceException("forScript is null!"));
            if (device == IntPtr.Zero)
                return new D3DResult(new Exception("device is not valid!"));
            if (!File.Exists(filePath))
                return new D3DResult(new FileNotFoundException(string.Format("File {0} was not found.", filePath)));

            try
            {
                Size textureSize = size;
                if (textureSize == Size.Empty) // Try to gatter size of texture manually if size is not specified
                {
                    using (Image img = Bitmap.FromFile(filePath))
                    {
                        textureSize = img.Size;
                    }
                }

                SharpDX.Direct3D9.Texture t = SharpDX.Direct3D9.Texture.FromFile((SharpDX.Direct3D9.Device)device, filePath, -2, -2, 1, SharpDX.Direct3D9.Usage.None, SharpDX.Direct3D9.Format.A8R8G8B8, SharpDX.Direct3D9.Pool.Managed, SharpDX.Direct3D9.Filter.Default, SharpDX.Direct3D9.Filter.Default, 0);
                D3DResource resource = new D3DResource(Guid.NewGuid(), eD3D9ResourceType.Texture, JsonConvert.SerializeObject(textureSize), t.NativePointer);
                GetFoundScript(forScript.ID)?.D3D9Objects.Add(resource.ID, resource);

                // Log
                Console.PrintDebug(string.Format("Created new {0} D3D9Resource {1} (ID: {2}) for script {3}.", resource.DXType.ToString(), resource.Handle.ToString(), resource.ID.ToString(), forScript.GetName()));

                return new D3DResult(null, resource.ID, resource);
            }
            catch (Exception ex)
            {
                return new D3DResult(ex);
            }
        }
        public override D3DResult Direct3D9_Graphics_CreateD3D9Texture(Script forScript, IntPtr device, byte[] data, Size size)
        {
            if (forScript == null)
                return new D3DResult(new NullReferenceException("forScript is null!"));
            if (device == IntPtr.Zero)
                return new D3DResult(new Exception("device is not valid!"));

            try
            {
                Size textureSize = size;
                if (textureSize == Size.Empty) // Try to gatter size of texture manually if size is not specified
                {
                    using (MemoryStream ms = new MemoryStream(data))
                    {
                        using (Image img = Bitmap.FromStream(ms))
                        {
                            textureSize = img.Size;
                        }
                    }
                }

                SharpDX.Direct3D9.Texture t = SharpDX.Direct3D9.Texture.FromMemory((SharpDX.Direct3D9.Device)device, data, -2, -2, 1, SharpDX.Direct3D9.Usage.None, SharpDX.Direct3D9.Format.A8R8G8B8, SharpDX.Direct3D9.Pool.Managed, SharpDX.Direct3D9.Filter.Default, SharpDX.Direct3D9.Filter.Default, 0);
                D3DResource resource = new D3DResource(Guid.NewGuid(), eD3D9ResourceType.Texture, JsonConvert.SerializeObject(textureSize), t.NativePointer);
                GetFoundScript(forScript.ID)?.D3D9Objects.Add(resource.ID, resource);

                // Log
                Console.PrintDebug(string.Format("Created new {0} D3D9Resource {1} (ID: {2}) for script {3}.", resource.DXType.ToString(), resource.Handle.ToString(), resource.ID.ToString(), forScript.GetName()));

                return new D3DResult(null, resource.ID, resource);
            }
            catch (Exception ex)
            {
                return new D3DResult(ex);
            }
        }
        public override Exception Direct3D9_Graphics_ReleaseD3D9Texture(Script ofScript, D3DResource resource)
        {
            if (ofScript == null)
                return new NullReferenceException("ofScript is null!");
            if (resource == null)
                return new NullReferenceException("resource is null!");

            try
            {

                FoundScript s = GetFoundScript(ofScript.ID);
                if (s != null)
                {
                    if (s.D3D9Objects.TryGetValue(resource.ID, out D3DResource res))
                    {

                        SharpDX.ComObject obj = (SharpDX.ComObject)res.Handle;
                        obj.Dispose();
                        s.D3D9Objects.Remove(resource.ID);

                        // Log
                        if (obj.IsDisposed)
                            Console.PrintDebug(string.Format("Disposed {0} D3D9Resource {1} ({2}) of script {3}.", res.DXType.ToString(), res.Handle.ToString(), res.ID.ToString(), ofScript.GetName()));

                        return null;

                    }
                    else
                    {
                        return new Exception(string.Format("Could not find resource with ID {0}", resource.ID.ToString()));
                    }
                }

                return new Exception(string.Format("Could not find script with name {0} (ID {1})", ofScript.GetName(), ofScript.ID.ToString()));
            }
            catch (Exception ex)
            {
                return ex;
            }
        }

        // Font stuff
        public override D3DResult Direct3D9_Graphics_CreateD3D9Font(Script forScript, IntPtr device, D3DFontDescription fontDescription)
        {
            if (forScript == null)
                return new D3DResult(new NullReferenceException("forScript is null!"));
            if (device == IntPtr.Zero)
                return new D3DResult(new Exception("device is not valid!"));

            try
            {
                D3DResource resource = new D3DResource(Guid.NewGuid(), eD3D9ResourceType.Font, string.Empty, new SharpDX.Direct3D9.Font((SharpDX.Direct3D9.Device)device, fontDescription.ToSharpDXFontDescription()).NativePointer);
                GetFoundScript(forScript.ID)?.D3D9Objects.Add(resource.ID, resource);

                // Log
                Console.PrintDebug(string.Format("Created new {0} D3D9Resource {1} (ID: {2}) for script {3}.", resource.DXType.ToString(), resource.Handle.ToString(), resource.ID.ToString(), forScript.GetName()));

                return new D3DResult(null, resource.ID, resource);
            }
            catch (Exception ex)
            {
                return new D3DResult(ex);
            }
        }
        public override Exception Direct3D9_Graphics_ReleaseD3D9Font(Script ofScript, D3DResource resource)
        {
            if (ofScript == null)
                return new NullReferenceException("ofScript is null!");
            if (resource == null)
                return new NullReferenceException("resource is null!");

            try
            {

                FoundScript s = GetFoundScript(ofScript.ID);
                if (s != null)
                {
                    if (s.D3D9Objects.TryGetValue(resource.ID, out D3DResource res))
                    {

                        SharpDX.ComObject obj = (SharpDX.ComObject)res.Handle;
                        obj.Dispose();
                        s.D3D9Objects.Remove(resource.ID);

                        // Log
                        if (obj.IsDisposed)
                            Console.PrintDebug(string.Format("Disposed {0} D3D9Resource {1} ({2}) of script {3}.", res.DXType.ToString(), res.Handle.ToString(), res.ID.ToString(), ofScript.GetName()));

                        return null;

                    }
                    else
                    {
                        return new Exception(string.Format("Could not find resource with ID {0}", resource.ID.ToString()));
                    }
                }

                return new Exception(string.Format("Could not find script with name {0} (ID {1})", ofScript.GetName(), ofScript.ID.ToString()));
            }
            catch (Exception ex)
            {
                return ex;
            }
        }
        public override Rectangle Direct3D9_Graphics_MeasureText(D3DResource fontResource, string text, Rectangle rect, eD3DFontDrawFlags drawFlags)
        {
            if (fontResource != null)
            {
                if (fontResource.DXType != eD3D9ResourceType.Font)
                {
                    return Rectangle.Empty;
                }
            }

            SharpDX.Direct3D9.Font f = (SharpDX.Direct3D9.Font)(fontResource != null ? fontResource.Handle : LocalD3D9Font.NativePointer);
            if (f != null)
            {
                SharpDX.Mathematics.Interop.RawRectangle rawRect = f.MeasureText(null, text, rect.ToRawRectangle(), (SharpDX.Direct3D9.FontDrawFlags)drawFlags);
                return new Rectangle(rawRect.Left, rawRect.Top, rawRect.Right, rawRect.Bottom);
            }

            return Rectangle.Empty;
        }

        // DrawLine
        public override bool Direct3D9_Graphics_DrawLines(object instance, IntPtr device, Vector2[] vertices, Color color, bool antialias, int pattern, float patternScale, float thickness)
        {
            if (instance == null)
                return false;

            SharpDX.Mathematics.Interop.RawVector2[] rawVectorArray = new SharpDX.Mathematics.Interop.RawVector2[vertices.Length];

            // Convert System.Drawing.Vector2's to SharpDX.Mathematics.Interop.RawVector2's
            for (int i = 0; i < vertices.Length; i++)
            {
                rawVectorArray[i] = vertices[i].ToRawVector2();
            }

            return Drawing.DrawLines((D3DGraphics)instance, device, rawVectorArray, color, antialias, pattern, patternScale, thickness);
        }
        public override bool Direct3D9_Graphics_DrawLine(object instance, IntPtr device, Vector2 point1, Vector2 point2, Color color, bool antialias, int pattern, float patternScale, float thickness)
        {
            if (instance == null)
                return false;

            return Drawing.DrawLine((D3DGraphics)instance, device, point1, point2, color, antialias, pattern, patternScale, thickness);
        }

        // DrawCircle
        public override bool Direct3D9_Graphics_DrawCircle(object instance, IntPtr device, Vector2 pos, float radius, float rotation, eD3DCircleType type, bool smoothing, int resolution, Color color)
        {
            if (instance == null)
                return false;

            return Drawing.DrawCircle((D3DGraphics)instance, device, pos, radius, rotation, type, smoothing, resolution, color);
        }
        public override bool Direct3D9_Graphics_DrawCircleFilled(object instance, IntPtr device, Vector2 pos, float radius, float rotation, eD3DCircleType type, bool smoothing, int resolution, Color color)
        {
            if (instance == null)
                return false;

            return Drawing.DrawCircleFilled((D3DGraphics)instance, device, pos, radius, rotation, type, smoothing, resolution, color);
        }

        // DrawBox
        public override bool Direct3D9_Graphics_DrawBoxFilled(object instance, IntPtr device, Vector2 pos, SizeF size, Color color)
        {
            if (instance == null)
                return false;

            return Drawing.DrawBoxFilled((D3DGraphics)instance, device, pos, size, color);
        }
        public override bool Direct3D9_Graphics_DrawBox(object instance, IntPtr device, Vector2 pos, SizeF size, float lineWidth, Color color)
        {
            if (instance == null)
                return false;

            return Drawing.DrawBox((D3DGraphics)instance, device, pos, size, lineWidth, color);
        }
        public override bool Direct3D9_Graphics_DrawBoxBordered(object instance, IntPtr device, Vector2 pos, SizeF size, float borderWidth, Color color, Color borderColor)
        {
            if (instance == null)
                return false;

            return Drawing.DrawBoxBordered((D3DGraphics)instance, device, pos, size, borderWidth, color, borderColor);
        }
        public override bool Direct3D9_Graphics_DrawBoxRounded(object instance, IntPtr device, Vector2 pos, SizeF size, float radius, bool smoothing, Color color, Color borderColor)
        {
            if (instance == null)
                return false;

            return Drawing.DrawBoxRounded((D3DGraphics)instance, device, pos, size, radius, smoothing, color, borderColor);
        }

        // DrawTexture
        public override bool Direct3D9_Graphics_DrawTexture(object instance, IntPtr device, D3DResource txt, RectangleF rect, float rotation, Color tint)
        {
            if (instance == null)
                return false;

            RectangleF targetRect = rect;

            // Set size of texture automatically
            if (targetRect.Size == SizeF.Empty)
            {
                Size textureSize = JsonConvert.DeserializeObject<Size>(txt.ResourceProperties);
                targetRect = new RectangleF(targetRect.X, targetRect.Y, textureSize.Width, textureSize.Height);
            }

            return Drawing.DrawTexture((D3DGraphics)instance, device, txt.Handle, targetRect, rotation, tint);
        }

        // DrawString
        public override bool Direct3D9_Graphics_DrawString(object instance, IntPtr device, D3DResource fontResource, string text, Rectangle rect, eD3DFontDrawFlags drawFlags, Color color)
        {
            if (instance == null)
                return false;

            return Drawing.DrawString((D3DGraphics)instance, fontResource != null ? fontResource.Handle : LocalD3D9Font.NativePointer, text, rect.ToRawRectangle(), drawFlags, color);
        }
        public override bool Direct3D9_Graphics_DrawString(object instance, IntPtr device, D3DResource fontResource, string text, Point pos, Color color)
        {
            if (instance == null)
                return false;

            return Drawing.DrawString((D3DGraphics)instance, fontResource != null ? fontResource.Handle : LocalD3D9Font.NativePointer, text, pos, color);
        }

        // Other
        public override void Direct3D9_Graphics_SetScissorRect(IntPtr device, Rectangle rect)
        {
            if (device == IntPtr.Zero)
                return;

            ((SharpDX.Direct3D9.Device)device).ScissorRect = rect.ToRawRectangle();
        }
        public override Rectangle Direct3D9_Graphics_GetScissorRect(IntPtr device)
        {
            if (device == IntPtr.Zero)
                return Rectangle.Empty;

            return ((SharpDX.Direct3D9.Device)device).ScissorRect.ToRectangle();
        }

        public override bool Direct3D9_Graphics_IsDrawingAvailable()
        {
            return !(Console.UseOldDrawingSystem && Notification.UseOldDrawingSystem);
        }

        #endregion

        #region Methods

        // Cleaning
        public void Cleanup()
        {
            try
            {
                // Log
                Console.Print("Cleaning up...");

                // Stop remote server
                ConnectionManager.Dispose();

                // Abort all currently running scripts
                AbortScripts(false);

                // Stop task
                AbortTaskOrTimer(processCheckerTimerID);

                // Cleanup lists
                ActiveScripts.Clear();
                LocalTasks.Clear();
                delayedActions.Clear();

                // Uninit keyWatchDog
                keyWatchDog.KeyDown -=  KeyWatchDog_KeyDown;
                keyWatchDog.KeyUp -=    KeyWatchDog_KeyUp;
                keyWatchDog.Dispose();
                keyWatchDog = null;

                // Uninit direct3D9Hook and destroy local resources
                direct3D9Hook.OnInit -=         Direct3D9Hook_InternalOnInit;
                direct3D9Hook.OnEndScene -=     Direct3D9Hook_OnEndScene;
                direct3D9Hook.OnBeforeReset -=  Direct3D9Hook_OnBeforeReset;
                direct3D9Hook.OnAfterReset -=   Direct3D9Hook_OnAfterReset;

                if (LocalD3D9Font != null)
                {
                    LocalD3D9Font.Dispose();
                    LocalD3D9Font = null;
                }

                direct3D9Hook.Dispose();
                direct3D9Hook = null;

                if (mouse != null)
                {
                    mouse.Dispose();
                    mouse = null;
                }

                // Unregister from WndProc received event
                RAGE.OnWndProcMessageReceived -= WndProcHook_OnWndMessage;
            }
            catch (Exception ex)
            {
                Console.PrintError(string.Format("Error while cleaning up. Details: {0}", ex.ToString()));
            }
        }

        // Load script stuff
        public override void LoadScripts()
        {
            if (!Directory.Exists(ScriptsPath))
            {
                Directory.CreateDirectory(ScriptsPath);
                return;
            }

            // Abort currently loaded scripts
            AbortScripts(false);
            
            string[] scriptFiles = Directory.GetFiles(ScriptsPath, "*.ivsdk.dll");
            for (int i = 0; i < scriptFiles.Length; i++)
                LoadAssembly(scriptFiles[i]);

            // Log
            Console.Print(string.Format("Loaded {0} of {1} scripts!", ActiveScripts.Count.ToString(), scriptFiles.Length.ToString()));
        }
        public override void LoadScript(string name)
        {
            if (!Directory.Exists(ScriptsPath))
            {
                Directory.CreateDirectory(ScriptsPath);
                return;
            }

            // Check if script with this name is already loaded
            FoundScript fs = GetFoundScript(name);
            if (fs == null)
            {

                // Get path to script file
                string scriptPath = string.Format("{0}\\{1}", ScriptsPath, name);

                // Check if file exists
                if (!File.Exists(scriptPath))
                {
                    Console.PrintWarning(string.Format("File {0} does not exists in the scripts folder!", name));
                    return;
                }

                // Try to load script
                if (LoadAssembly(scriptPath))
                    Console.Print(string.Format("Script {0} got loaded!", name));

            }
            else
            {
                Console.PrintWarning(string.Format("Script {0} is already loaded.", name));
            }
        }
        public bool LoadAssembly(string path, bool throwOnError = false)
        {
            try
            {
                using (FileStream fs = new FileStream(path, FileMode.Open, FileAccess.Read))
                {

                    byte[] fileByteArray = Helper.GetByteArray(fs);

                    Assembly assembly = Assembly.Load(fileByteArray);
                    string assemblyName = assembly.GetName().Name.Split('.')[0];

                    // Get types from assembly
                    Type[] containedTypes = assembly.GetTypes();
                    for (int i = 0; i < containedTypes.Length; i++)
                    {
                        Type containedType = containedTypes[i];

                        if (containedType.IsSubclassOf(typeof(Script)))
                        {

                            // Log
                            Console.Print(string.Format("Found script: {0}", containedType.FullName));

                            // Create new instance of type for assembly
                            Script script = (Script)assembly.CreateInstance(containedType.FullName);

                            if (script != null)
                            {

                                // Register AssemblyResolve event
                                script.ScriptDomain.AssemblyResolve += ScriptDomain_AssemblyResolve;

                                // Check for script settings file
                                string settingsFilePath = string.Format("{0}\\{1}.ini", ScriptsPath, assemblyName);
                                if (File.Exists(settingsFilePath))
                                {
                                    script.Settings = new SettingsFile(settingsFilePath);
                                    script.Settings.Load();
                                }

                                // Check for script resource folder
                                string resourceFolderPath = string.Format("{0}\\{1}", ScriptsPath, assemblyName);
                                if (Directory.Exists(resourceFolderPath)) script.ScriptResourceFolder = resourceFolderPath;

                                // Check if FoundScript with this assembly name already exists in ActiveScripts list
                                FoundScript foundScript = GetFoundScript(assemblyName);
                                if (foundScript != null)
                                { // FoundScript object with this assembly name already exists in ActiveScripts list. Create new instance for this class which inherits from Script
                                  // Todo
                                }
                                else
                                { // No FoundScript object found with this assembly name in ActiveScripts list. Create new FoundScript object and add to ActiveScripts list
                                    foundScript = new FoundScript(script.ID, containedType, script);
                                    foundScript.Name = assemblyName;
                                    foundScript.FullPath = path;

                                    ActiveScripts.Add(foundScript); // Add script to ActiveScripts list.

                                    if (firstFrame) // The player was not actually in-game yet. Raise Initialized event of the Script later.
                                    {
                                        StartDelayedAction(Guid.NewGuid(), "Raise script init event", DateTime.UtcNow.AddSeconds(3), (DelayedAction dA, object param) => {
                                            FoundScript fs2 = (FoundScript)param;
                                            try
                                            {
                                                foundScript.RaiseInitialized();
                                            }
                                            catch (Exception ex)
                                            {
                                                Notification.ShowNotification(NotificationType.Error, DateTime.UtcNow.AddSeconds(8), string.Format("An error occured in {0} Initialized.", fs2.Name), ex.Message, string.Format("ERROR_IN_SCRIPT_{0}", fs2.Name));
                                                Console.PrintError(string.Format("An error occured while processing initialized event for script {0}. Aborting script. Details: {1}", fs2.Name, ex.ToString()));
                                                AbortScript(fs2.ID);
                                            }
                                        }, foundScript);
                                    }
                                    else // The player was in-game and so we want to initialize the Script instantly
                                    {
                                        try
                                        {
                                            foundScript.RaiseInitialized();
                                        }
                                        catch (Exception ex)
                                        {
                                            Notification.ShowNotification(NotificationType.Error, DateTime.UtcNow.AddSeconds(8), string.Format("An error occured in {0} Initialized.", foundScript.Name), ex.Message, string.Format("ERROR_IN_SCRIPT_{0}", foundScript.Name));
                                            Console.PrintError(string.Format("An error occured while processing initialized event for script {0}. Aborting script. Details: {1}", foundScript.Name, ex.ToString()));
                                            AbortScript(foundScript.ID);
                                        }
                                    }
                                }

                                return true;
                            }

                        }
                    }

                }
            }
            catch (ReflectionTypeLoadException ex)
            {

                if (throwOnError)
                    throw ex;

                Exception[] exs = ex.LoaderExceptions;
                for (int i = 0; i < exs.Length; i++)
                {
                    Exception e = exs[i];
                    Console.PrintError(string.Format("A ReflectionTypeLoadException occured while trying to load script '{0}'. Details: {1}", Path.GetFileName(path), e.ToString()));
                }

            }
            catch (Exception ex)
            {
                if (throwOnError)
                    throw ex;

                Console.PrintError(string.Format("An exception occured while trying to load script '{0}'. Details: {1}", Path.GetFileName(path), ex.ToString()));
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

                string requestingAssemblyName = args.RequestingAssembly.GetName().Name;

                if (requestingAssemblyName.ToLower().EndsWith(".ivsdk"))
                    requestingAssemblyName = requestingAssemblyName.Remove(requestingAssemblyName.Length - 6, 6);

                foundScript = GetFoundScript(requestingAssemblyName);

                // Debug
                Console.PrintDebug(string.Format("Script {0} is searching for their required assembly {1}.", requestingAssemblyName, args.Name));

                if (foundScript != null)
                {

                    string assemblyName = args.Name.Split(',')[0];
                    string scriptsDir = Path.GetDirectoryName(foundScript.FullPath);
                    string customDir = string.Format("{0}\\{1}", CGame.GameStartupPath, foundScript.Script.CustomAssembliesPath);

                    string fileFullPath = string.Empty;

                    eAssembliesLocation scriptAssembliesLocation = foundScript.Script.AssembliesLocation;

                    // Debug
                    switch (scriptAssembliesLocation)
                    {
                        case eAssembliesLocation.Custom:
                            Console.PrintDebug(string.Format("Script {0} is requesting assembly {1} which should be in {2}", foundScript.Name, args.Name, customDir));
                            break;
                        default:
                            Console.PrintDebug(string.Format("Script {0} is requesting assembly {1} which should be in {2}", foundScript.Name, args.Name, scriptAssembliesLocation.ToString()));
                            break;
                    }

                    // Load Assembly by AssemblyLocation set by script
                    switch (scriptAssembliesLocation)
                    {

                        case eAssembliesLocation.GameRootDirectory:
                            Console.PrintWarning(string.Format("Script {0} was requesting assembly {1} but it was not found in the root directory of GTA IV! Aborting.", foundScript.Name, assemblyName));
                            break;

                        case eAssembliesLocation.ScriptsDirectory:

                            fileFullPath = string.Format("{0}\\{1}.dll", scriptsDir, assemblyName);
                            if (File.Exists(fileFullPath))
                                return Assembly.UnsafeLoadFrom(fileFullPath);

                            Console.PrintWarning(string.Format("Script {0} was requesting assembly {1} but it was not found in the scripts directory! Aborting.", foundScript.Name, assemblyName));
                            break;

                        case eAssembliesLocation.DecideManuallyForEachAssembly:

                            fileFullPath = foundScript.Script.RaiseAssemblyResolve(assemblyName);
                            if (File.Exists(fileFullPath))
                                return Assembly.UnsafeLoadFrom(fileFullPath);

                            Console.PrintWarning(string.Format("Script {0} was requesting assembly {1} but it was not found in directory ({2})! Aborting.", foundScript.Name, assemblyName, Path.GetDirectoryName(fileFullPath)));
                            break;

                        case eAssembliesLocation.Custom:

                            fileFullPath = string.Format("{0}\\{1}.dll", customDir, assemblyName);
                            if (File.Exists(fileFullPath))
                                return Assembly.UnsafeLoadFrom(fileFullPath);

                            Console.PrintWarning(string.Format("Script {0} was requesting assembly {1} but it was not found in the custom directory ({2})! Aborting.", foundScript.Name, assemblyName, foundScript.Script.CustomAssembliesPath));
                            break;
                    }

                }
                else
                {
                    Console.PrintWarning(string.Format("Could not find requesting script {0}! Assemblies couldn't get loaded for this script.", requestingAssemblyName));
                }
            }
            catch (Exception ex)
            {
                Console.PrintError(string.Format("An error occured while loading assembly {0} for Script {1}. Aborting. Details: {2}", args.Name, foundScript != null ? foundScript.Name : "UNKNOWN", ex.ToString()));
            }

            // Abort script
            if (foundScript != null)
                AbortScriptInternal(AbortReason.Manager, foundScript.ID);

            return null;
        }

        // Config stuff
        public void LoadConfig(bool suppressMessage = true)
        {
            // Settings file is already loaded, dispose.
            if (settings != null)
            {
                settings.Dispose();
                settings = null;
            }

            // Create new instance of the SettingsFile class
            settings = new SettingsFile(string.Format("{0}\\config.ini", IVSDKDotNetPath));

            // Try to load settings from given ctor path
            if (settings.Load())
            {
                if (!suppressMessage)
                    Console.Print("Loaded IV-SDK .NET config.ini!");
            }
            else
            {
                Console.PrintWarning("Could not load IV-SDK .NET config.ini! Using default settings.");
            }

            // Set stuff from settings file
            // Scripts
            pauseScriptExecutionWhenNotInFocus = settings.GetBoolean("Scripts", "PauseExecutionWhenNotInFocus", true);

            // Console
            Console.OpenCloseKey = settings.GetKey("Console", "OpenCloseKey", Keys.F4);
            Console.CanDisablePlayerMovement = settings.GetBoolean("Console", "DisablePlayerControlWhenOpen", true);

            // API
            allowRemoteConnections = settings.GetBoolean("API", "AllowConnections", true);
            ConnectionManager.ShowNotificationOnConnection = settings.GetBoolean("API", "ShowNotificationOnConnection", true);
            ConnectionManager.ServerPort = (ushort)settings.GetInteger("API", "PortOverride", 57315);
            ConnectionManager.MaxServerClients = (ushort)settings.GetInteger("API", "MaxClientsOverride", 1);
            ConnectionManager.AllowRemoteReloadScripts = settings.GetBoolean("API", "AllowRemoteReloadScripts", true);
            ConnectionManager.AllowRemoteLoadScripts = settings.GetBoolean("API", "AllowRemoteLoadScripts", true);
            ConnectionManager.AllowRemoteAbortScripts = settings.GetBoolean("API", "AllowRemoteAbortScripts", true);

            ConnectionManager.AllowRemoteNativeFunctionCalls = settings.GetBoolean("API", "AllowRemoteNativeFunctionCalls", true);
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
        public override void AbortScripts(bool showMessage)
        {
            AbortScriptsInternal(AbortReason.Script, showMessage);
        }
        public void AbortScriptsInternal(AbortReason reason, bool showMessage)
        {
            if (ActiveScripts.Count != 0)
            {
                ActiveScripts.ForEach(x => x.Abort(showMessage));
                ActiveScripts.Clear();
                GC.Collect();
            }
            else
            {
                if (showMessage)
                    Console.Print("There are no scripts to abort.");
            }
        }

        // DelayedAction
        public void StartDelayedAction(Guid id, string purpose, DateTime executeIn, Action<DelayedAction, object> actionToExecute, object parameter)
        {
            delayedActions.Insert(delayedActions.Count, new DelayedAction(id, purpose, executeIn, actionToExecute, parameter));
        }
        
        // Tasks
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

        // Overrides
        public override bool AbortScript(Guid id)
        {
            return AbortScriptInternal(AbortReason.Script, id);
        }
        public bool AbortScriptInternal(AbortReason reason, Guid id)
        {
            FoundScript script = ActiveScripts.Where(x => x.ID == id).FirstOrDefault();

            if (script != null)
            {
                Console.Print(string.Format("Aborting script {0}...", script.Name));
                script.Abort(true);
                return ActiveScripts.Remove(script);
            }

            return false;
        }

        public override Script GetScript(Guid id)
        {
            return ActiveScripts.Where(x => x.ID == id).Select(s => s.Script).FirstOrDefault();
        }
        public override Script GetScript(string name)
        {
            return ActiveScripts.Where(x => x.Name == name).Select(s => s.Script).FirstOrDefault();
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
            return ActiveScripts.Select(x => x.Script).ToArray();
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

        public override bool SendScriptCommand(Script toScript, string command)
        {
            FoundScript foundScript = ActiveScripts.Where(x => x.ID == toScript.ID).FirstOrDefault();

            if (foundScript != null)
            {
                try
                {
                    if (foundScript.IsScriptReady())
                        foundScript.Script.RaiseScriptCommandReceived(toScript, command);

                    return true;
                }
                catch (Exception ex)
                {
                    Notification.ShowNotification(NotificationType.Error, DateTime.UtcNow.AddSeconds(8), string.Format("An error occured in {0} ScriptCommandReceived.", foundScript.Name), ex.Message, string.Format("ERROR_IN_SCRIPT_{0}", foundScript.Name));
                    Console.PrintError(string.Format("An error occured while processing ScriptCommandReceived event for script {0}. Aborting script. Details: {1}", foundScript.Name, ex.ToString()));
                    AbortScript(foundScript.ID);
                }
            }

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

        public Guid StartNewTimerInternel(int interval, Action actionToExecute)
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

    }
}
