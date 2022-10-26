using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using System.Reflection;
using System.Windows.Forms;

using IVSDKDotNet;
using IVSDKDotNet.Enums;
using IVSDKDotNet.Manager;

namespace Manager {

    #region Public Enums
    public enum TaskUseCase
    {
        TickRaiser,
        GameLoadRaiser,
        GameLoadPriorityRaiser,
        MountDeviceRaiser,
        DrawingRaiser,
        ProcessCameraRaiser,
        ProcessAutomobileRaiser,
        ProcessPadRaiser,
        Timer,
        Custom
    }
    public enum NotificationType
    {
        Default,
        Error
    }
    #endregion

    #region Public Classes
    public class AdvancedTask
    {
        #region Variables
        public Task task;
        public CancellationTokenSource taskController;
        public CancellationToken token;

        public Guid ID;
        public FoundScript Owner;
        public TaskUseCase TaskUseCase;
        public int SleepTime = 100;
        public bool ShouldPause;
        #endregion

        #region Structs
        public struct InvokeData {

            #region Variables
            public AdvancedTask STask;
            public object CustomData;
            #endregion

            #region Constructor
            public InvokeData(AdvancedTask sTask, object customData)
            {
                STask = sTask;
                CustomData = customData;
            }
            #endregion

        }
        #endregion

        #region Constructor
        public AdvancedTask(Guid id, FoundScript taskOwner, TaskUseCase useCase, int sleepTime)
        {
            ID = id;
            Owner = taskOwner;
            TaskUseCase = useCase;
            SleepTime = sleepTime;
            taskController = new CancellationTokenSource();
            token = taskController.Token;
        }
        public AdvancedTask(Guid id, FoundScript taskOwner, TaskUseCase useCase)
        {
            ID = id;
            Owner = taskOwner;
            TaskUseCase = useCase;
            taskController = new CancellationTokenSource();
            token = taskController.Token;
        }
        public AdvancedTask(Guid id, FoundScript taskOwner)
        {
            ID = id;
            Owner = taskOwner;
            taskController = new CancellationTokenSource();
            token = taskController.Token;
        }
        public AdvancedTask(FoundScript taskOwner)
        {
            ID = Guid.Empty;
            Owner = taskOwner;
            taskController = new CancellationTokenSource();
            token = taskController.Token;
        }
        #endregion

        #region Methods
        public void Dispose()
        {
            if (task != null) {
                task.Dispose();
                task = null;
            }
            if (taskController != null) {
                taskController.Dispose();
                taskController = null;
            }
        }
        public void Abort()
        {
            if (taskController != null) taskController.Cancel();
        }

        public void Wait(int time)
        {
            if (taskController != null) taskController.Token.WaitHandle.WaitOne(time);
        }
        public void Pause()
        {
            ShouldPause = true;
        }
        public void Resume()
        {
            ShouldPause = false;
        }
        #endregion

        #region Functions
        /// <summary>
        /// Starts the <see cref="ServerTask"/>.
        /// </summary>
        /// <param name="options">The options of this task.</param>
        /// <param name="func">The function that should be executed by this task.</param>
        /// <param name="continueWithAction">The action that should be executed when the <paramref name="func"/> has finished executing.</param>
        /// <returns>True if the task got started, otherwise false.</returns>
        public bool Start(TaskCreationOptions options, Func<object> func, Action<InvokeData> continueWithAction)
        {
            if (task == null) {
                task = Task.Factory.StartNew(func, token, options, TaskScheduler.Default).ContinueWith(t => {
                    continueWithAction?.Invoke(new InvokeData(this, t.Result));
                });

                return task != null;
            }
            return false;
        }
        #endregion

        #region Statics
        /// <summary>
        /// Creates and starts a new task.
        /// </summary>
        /// <param name="id">The ID of this task.</param>
        /// <param name="taskOwner">Who owns this task.</param>
        /// <param name="useCase">The use case of this task.</param>
        /// <param name="options">The options of this task.</param>
        /// <param name="sleepTime">Sets how long the task should sleep for. The default is <b>100</b> milliseconds.</param>
        /// <param name="func">The function that should be executed by this task.</param>
        /// <param name="continueWithAction">The action that should be executed when the <paramref name="func"/> has finished executing.</param>
        /// <returns>A new instance of the <see cref="AdvancedTask"/> class.</returns>
        public static AdvancedTask StartNew(Guid id, FoundScript taskOwner, TaskUseCase useCase, TaskCreationOptions options, int sleepTime, Func<object> func, Action<InvokeData> continueWithAction)
        {
            AdvancedTask st = new AdvancedTask(id, taskOwner);
            st.TaskUseCase = useCase;
            st.SleepTime = sleepTime;

            st.task = Task.Factory.StartNew(func, st.token, options, TaskScheduler.Default).ContinueWith(t => {
                continueWithAction?.Invoke(new InvokeData(st, t.Result));
            });

            return st;
        }

        /// <summary>
        /// Creates and starts a new task.
        /// </summary>
        /// <param name="taskOwner">Who owns this task.</param>
        /// <param name="useCase">The use case of this task.</param>
        /// <param name="options">The options of this task.</param>
        /// <param name="sleepTime">Sets how long the task should sleep for. The default is <b>100</b> milliseconds.</param>
        /// <param name="func">The function that should be executed by this task.</param>
        /// <param name="continueWithAction">The action that should be executed when the <paramref name="func"/> has finished executing.</param>
        /// <returns>A new instance of the <see cref="AdvancedTask"/> class.</returns>
        public static AdvancedTask StartNew(FoundScript taskOwner, TaskUseCase useCase, TaskCreationOptions options, int sleepTime, Func<object> func, Action<InvokeData> continueWithAction)
        {
            AdvancedTask st = new AdvancedTask(taskOwner);
            st.TaskUseCase = useCase;
            st.SleepTime = sleepTime;

            st.task = Task.Factory.StartNew(func, st.token, options, TaskScheduler.Default).ContinueWith(t => {
                continueWithAction?.Invoke(new InvokeData(st, t.Result));
            });

            return st;
        }

        // Timer
        public static object TimerStatic(AdvancedTask at, Action actionToExecute)
        {
            try {
                while (!at.token.IsCancellationRequested) {

                    if (at.ShouldPause) {
                        at.taskController.Token.WaitHandle.WaitOne(at.SleepTime);
                        continue;
                    }

                    actionToExecute?.Invoke();

                    // Sleep
                    at.taskController.Token.WaitHandle.WaitOne(at.SleepTime);
                }
            }
            catch (Exception ex) {
                Main.managerInstance.console.PrintError(string.Format("An error occured in Timer {0} for Script {1}. Details: {2}", at.ID.ToString(), at.Owner.Name, ex.ToString()));
            }

            return null;
        }

        // Delayed Action things
        /// <summary>
        /// Automatically gets rid of the given task.
        /// <para>Should be used with the <see cref="DelayedAction(string, TimeSpan, Action{DelayedAction, object}, object)"/> constructor.</para>
        /// </summary>
        /// <param name="a">Reference to the <see cref="DelayedAction"/>.</param>
        /// <param name="obj">Extra parameters. In this case the <see cref="ServerTask"/> that should be disposed.</param>
        public static void TaskDisposer(DelayedAction a, object obj)
        {
            AdvancedTask st = (AdvancedTask)obj;
            if (st != null) {
                st.Dispose();
                st.Owner.ScriptTasks.Remove(st);
            }
        }

        /// <summary>
        /// Automatically gets rid of the given task.
        /// <para>Should be used with the <see cref="DelayedAction(string, TimeSpan, Action{DelayedAction, object}, object)"/> constructor.</para>
        /// </summary>
        /// <param name="a">Reference to the <see cref="DelayedAction"/>.</param>
        /// <param name="obj">Extra parameters. In this case the <see cref="ServerTask"/> that should be disposed.</param>
        public static void LocalTaskDisposer(DelayedAction a, object obj)
        {
            AdvancedTask st = (AdvancedTask)obj;
            if (st != null) {
                st.Dispose();
                Main.LocalTasks.Remove(st);
            }
        }
        #endregion
    }
    public class DelayedAction
    {
        #region Properties
        public Guid ID { get; private set; }
        public string Purpose { get; private set; }
        public DateTime ExecuteIn { get; set; }
        public Action<DelayedAction, object> ActionToExecute { get; private set; }
        public object Parameter { get; private set; }
        #endregion

        #region Constructor
        public DelayedAction(Guid id, string purpose, DateTime executeIn, Action<DelayedAction, object> actionToExecute, object parameter)
        {
            ID = id;
            Purpose = purpose;
            ExecuteIn = executeIn;
            ActionToExecute = actionToExecute;
            Parameter = parameter;
        }
        public DelayedAction(string purpose, DateTime executeIn, Action<DelayedAction, object> actionToExecute, object parameter)
        {
            Purpose = purpose;
            ExecuteIn = executeIn;
            ActionToExecute = actionToExecute;
            Parameter = parameter;
        }
        #endregion
    }
    public class FoundScript
    {
        #region Variables
        public Guid ID;
        public string Name;
        public string FullPath;
        public bool Running;

        public Type EntryPoint;
        public FieldInfo[] PublicFields;
        public Script Script;
        public List<AdvancedTask> ScriptTasks;
        public List<string> ConsoleCommands;

        private Task cleanUpTask;
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
            Running = true;
        }
        #endregion
        
        #region Method
        public void Abort(bool showMessage)
        {
            if (cleanUpTask != null)
                return;

            Running = false;
            cleanUpTask = Task.Run(() => {
                try {
                    // Delete all console commands registered by this script
                    for (int i = 0; i < ConsoleCommands.Count; i++) {
                        string command = ConsoleCommands[i];
                        if (Main.managerInstance.console.Commands.ContainsKey(command)) Main.managerInstance.console.Commands.Remove(command);
                    }
                    ConsoleCommands.Clear();

                    // Stop all active script tasks
                    if (ScriptTasks.Count != 0) {

                        DateTime taskCleanUpStartTime = DateTime.Now;
                        Task[] scriptTasks = new Task[ScriptTasks.Count];

                        // Put all active tasks in task array and cancel them
                        for (int i = 0; i < ScriptTasks.Count; i++) {
                            AdvancedTask sTask = ScriptTasks[i];
                            scriptTasks[i] = sTask.task;
                            sTask.taskController.Cancel();
                        }

                        // Wait until all tasks are completed
                        Task.WaitAll(scriptTasks);

                        // Dispose and remove all tasks from user
                        for (int i = 0; i < ScriptTasks.Count; i++) {
                            AdvancedTask sTask = ScriptTasks[i];
                            sTask.Dispose();
                            ScriptTasks.RemoveAt(i);
                        }

                        // Log how long this process took
                        TimeSpan timeResult = (taskCleanUpStartTime - DateTime.Now);
                        Main.managerInstance.console.PrintDebug(string.Format("{0} active tasks stopped for script {1}. This process took {2}.{3} seconds.", scriptTasks.Length.ToString(), Name, timeResult.Seconds, timeResult.Milliseconds));

                    }
                    ScriptTasks.Clear();

                    // Dispose script
                    Script.Dispose();
                    Script = null;

                    return null;
                }
                catch (Exception ex) {
                    return ex;
                }
            }).ContinueWith(r => {
                if (r.Result != null) {
                    Main.managerInstance.console.PrintError(string.Format("An error occured while aborting script {0}. Details: {1}", Name, r.Result.ToString()));
                }
                else {
                    if (showMessage) Main.managerInstance.console.Print(string.Format("Successfully aborted script {0}.", Name));
                }

                // Clean everything else
                ID = Guid.Empty;
                Name = null;
                FullPath = null;
                EntryPoint = null;
            });
        }
        #endregion
    }
    #endregion

    public class Main : ManagerScript {

        #region Variables
        internal static Main managerInstance;

        public List<FoundScript> ActiveScripts;
        public static List<AdvancedTask> LocalTasks;
        private List<DelayedAction> delayedActions;

        public UpdateChecker UpdateChecker;
        public Notification notification;
        public Console console;

        private KeyWatchDog keyWatchDog;
        private SettingsFile settings;

        private string ivsdkdotnetPath, scriptsPath;
        private bool firstFrame = true;
        #endregion

        #region Events
        private void UpdateChecker_VersionCheckFailed(Exception e)
        {
            notification.ShowNotification(NotificationType.Error, DateTime.Now.AddSeconds(5), "An error occured while checking for IV-SDK .NET updates", "Check the IV-SDK .NET console for more details.", "UPDATE_CHECK_FAILED");
            console.PrintError(string.Format("Error while checking for updates. Details: {0}", e.ToString()));
        }
        private void UpdateChecker_VersionCheckCompleted(UpdateChecker.VersionCheckInfo result)
        {
            if (result.NewVersionAvailable) {
                notification.ShowNotification(NotificationType.Default, DateTime.Now.AddSeconds(7), "New IV-SDK .NET update available!", string.Format("Version {0} of IV-SDK .NET is available to download.", result.NewVersion), "NEW_UPDATE_AVAILABLE");
                console.Print(string.Format("Version {0} of IV-SDK .NET is available!", result.NewVersion));
            }
            else {
                console.Print("There is currently no new IV-SDK .NET update available.");
            }
        }
        #endregion

        #region Constructor
        public Main()
        {
            managerInstance = this;

            // Set paths
            ivsdkdotnetPath = Application.StartupPath + "\\IVSDKDotNet";
            scriptsPath = ivsdkdotnetPath + "\\scripts";

            // Initialize manager stuff
            ActiveScripts = new List<FoundScript>();
            LocalTasks = new List<AdvancedTask>();
            delayedActions = new List<DelayedAction>();

            UpdateChecker = new UpdateChecker("0.3", "https://www.dropbox.com/s/smaz6ij8dkzd7nh/version.txt?dl=1");
            UpdateChecker.VersionCheckFailed += UpdateChecker_VersionCheckFailed;
            UpdateChecker.VersionCheckCompleted += UpdateChecker_VersionCheckCompleted;

            notification = new Notification(this);
            console = new Console(this);

#if DEBUG
            console.Print("IV-SDK .NET DEBUG version 0.3 by ItsClonkAndre");
#else
            console.Print("IV-SDK .NET Release version 0.3 by ItsClonkAndre");
#endif

            keyWatchDog = new KeyWatchDog();
            keyWatchDog.KeyDown += KeyWatchDog_KeyDown;
            keyWatchDog.KeyUp += KeyWatchDog_KeyUp;

            // Load IV-SDK .NET settings
            settings = new SettingsFile(string.Format("{0}\\config.ini", ivsdkdotnetPath));
            if (!settings.Load()) console.PrintWarning("Could not load IV-SDK .NET config.ini! Using default settings.");
            console.OpenCloseKey = settings.GetKey("Console", "OpenCloseKey", Keys.F4);
        }
        #endregion

        #region Raisers
        public override void RaiseTick()
        {
            DateTime dtNow = DateTime.Now;

            // Execute Delayed Actions if there are any
            for (int i = 0; i < delayedActions.Count; i++) {
                DelayedAction dA = delayedActions[i];
                if (dtNow >= dA.ExecuteIn) {
                    try {
                        if (dA.ActionToExecute != null) {
                            if (!string.IsNullOrEmpty(dA.Purpose)) console.PrintDebug(string.Format("[DEBUG] Delayed Action triggered. Purpose: {0}", dA.Purpose));
                            dA.ActionToExecute.Invoke(dA, dA.Parameter);
                        }
                        delayedActions.RemoveAt(i);
                    }
                    catch (Exception ex) {
                        console.PrintError(string.Format("An error occured while executing delayed action. DA Purpose: {0}, Details: {1}", dA.Purpose, ex.ToString()));
                    }
                }
            }

            // Check for key presses
            if (keyWatchDog != null) keyWatchDog.ProcessCheck();

            // Draw local things
            if (notification != null)   notification.Draw();
            if (console != null)        console.Draw();

            // Do stuff on first frame
            if (firstFrame) {
                UpdateChecker.CheckForUpdates(true);
                firstFrame = false;
            }

            // Raise all script Tick events
            for (int i = 0; i < ActiveScripts.Count; i++) {
                FoundScript fs = ActiveScripts[i];
                if (fs != null) {
                    try {
                        if (fs.Running) fs.Script.RaiseTick();
                    }
                    catch (Exception ex) {
                        notification.ShowNotification(NotificationType.Error, DateTime.Now.AddSeconds(8), string.Format("An error occured in {0} Tick.", fs.Name), ex.Message, string.Format("ERROR_IN_SCRIPT_{0}", fs.Name));
                        console.PrintError(string.Format("An error occured while processing Tick event for script {0}. Aborting script. Details: {1}", fs.Name, ex.ToString()));
                        AbortScript(fs.ID);
                    }
                }
            }
        }
        public override void RaiseGameLoad()
        {
            for (int i = 0; i < ActiveScripts.Count; i++) {
                FoundScript fs = ActiveScripts[i];
                if (fs != null) {
                    try {
                        if (fs.Running) fs.Script.RaiseGameLoad();
                    }
                    catch (Exception ex) {
                        notification.ShowNotification(NotificationType.Error, DateTime.Now.AddSeconds(8), string.Format("An error occured in {0} GameLoad.", fs.Name), ex.Message, string.Format("ERROR_IN_SCRIPT_{0}", fs.Name));
                        console.PrintError(string.Format("An error occured while processing GameLoad event for script {0}. Aborting script. Details: {1}", fs.Name, ex.ToString()));
                        AbortScript(fs.ID);
                    }
                }
            }
        }
        public override void RaiseGameLoadPriority()
        {
            for (int i = 0; i < ActiveScripts.Count; i++) {
                FoundScript fs = ActiveScripts[i];
                if (fs != null) {
                    try {
                        if (fs.Running) fs.Script.RaiseGameLoadPriority();
                    }
                    catch (Exception ex) {
                        notification.ShowNotification(NotificationType.Error, DateTime.Now.AddSeconds(8), string.Format("An error occured in {0} GameLoadPriority.", fs.Name), ex.Message, string.Format("ERROR_IN_SCRIPT_{0}", fs.Name));
                        console.PrintError(string.Format("An error occured while processing GameLoadPriority event for script {0}. Aborting script. Details: {1}", fs.Name, ex.ToString()));
                        AbortScript(fs.ID);
                    }
                }
            }
        }
        public override void RaiseMountDevice()
        {
            for (int i = 0; i < ActiveScripts.Count; i++) {
                FoundScript fs = ActiveScripts[i];
                if (fs != null) {
                    try {
                        if (fs.Running) fs.Script.RaiseMountDevice();
                    }
                    catch (Exception ex) {
                        notification.ShowNotification(NotificationType.Error, DateTime.Now.AddSeconds(8), string.Format("An error occured in {0} MountDevice.", fs.Name), ex.Message, string.Format("ERROR_IN_SCRIPT_{0}", fs.Name));
                        console.PrintError(string.Format("An error occured while processing MountDevice event for script {0}. Aborting script. Details: {1}", fs.Name, ex.ToString()));
                        AbortScript(fs.ID);
                    }
                }
            }
        }
        public override void RaiseDrawing()
        {
            for (int i = 0; i < ActiveScripts.Count; i++) {
                FoundScript fs = ActiveScripts[i];
                if (fs != null) {
                    try {
                        if (fs.Running) fs.Script.RaiseDrawing();
                    }
                    catch (Exception ex) {
                        notification.ShowNotification(NotificationType.Error, DateTime.Now.AddSeconds(8), string.Format("An error occured in {0} Drawing.", fs.Name), ex.Message, string.Format("ERROR_IN_SCRIPT_{0}", fs.Name));
                        console.PrintError(string.Format("An error occured while processing Drawing event for script {0}. Aborting script. Details: {1}", fs.Name, ex.ToString()));
                        AbortScript(fs.ID);
                    }
                }
            }
        }
        public override void RaiseProcessCamera()
        {
            for (int i = 0; i < ActiveScripts.Count; i++) {
                FoundScript fs = ActiveScripts[i];
                if (fs != null) {
                    try {
                        if (fs.Running) fs.Script.RaiseProcessCamera();
                    }
                    catch (Exception ex) {
                        notification.ShowNotification(NotificationType.Error, DateTime.Now.AddSeconds(8), string.Format("An error occured in {0} ProcessCamera.", fs.Name), ex.Message, string.Format("ERROR_IN_SCRIPT_{0}", fs.Name));
                        console.PrintError(string.Format("An error occured while processing ProcessCamera event for script {0}. Aborting script. Details: {1}", fs.Name, ex.ToString()));
                        AbortScript(fs.ID);
                    }
                }
            }
        }
        public override void RaiseProcessAutomobile()
        {
            for (int i = 0; i < ActiveScripts.Count; i++) {
                FoundScript fs = ActiveScripts[i];
                if (fs != null) {
                    try {
                        if (fs.Running) fs.Script.RaiseProcessAutomobile();
                    }
                    catch (Exception ex) {
                        notification.ShowNotification(NotificationType.Error, DateTime.Now.AddSeconds(8), string.Format("An error occured in {0} ProcessAutomobile.", fs.Name), ex.Message, string.Format("ERROR_IN_SCRIPT_{0}", fs.Name));
                        console.PrintError(string.Format("An error occured while processing ProcessAutomobile event for script {0}. Aborting script. Details: {1}", fs.Name, ex.ToString()));
                        AbortScript(fs.ID);
                    }
                }
            }
        }
        public override void RaiseProcessPad()
        {
            for (int i = 0; i < ActiveScripts.Count; i++) {
                FoundScript fs = ActiveScripts[i];
                if (fs != null) {
                    try {
                        if (fs.Running) fs.Script.RaiseProcessPad();
                    }
                    catch (Exception ex) {
                        notification.ShowNotification(NotificationType.Error, DateTime.Now.AddSeconds(8), string.Format("An error occured in {0} ProcessPad.", fs.Name), ex.Message, string.Format("ERROR_IN_SCRIPT_{0}", fs.Name));
                        console.PrintError(string.Format("An error occured while processing ProcessPad event for script {0}. Aborting script. Details: {1}", fs.Name, ex.ToString()));
                        AbortScript(fs.ID);
                    }
                }
            }
        }

        private void KeyWatchDog_KeyDown(object sender, KeyEventArgs e)
        {
            // Raise local things
            if (console != null) console.KeyDown(e);

            // Raise all script KeyDown events
            for (int i = 0; i < ActiveScripts.Count; i++) {
                FoundScript fs = ActiveScripts[i];
                if (fs != null) {
                    try {
                        if (fs.Running) fs.Script.RaiseKeyDown(e);
                    }
                    catch (Exception ex) {
                        notification.ShowNotification(NotificationType.Error, DateTime.Now.AddSeconds(8), string.Format("An error occured in {0} KeyDown.", fs.Name), ex.Message, string.Format("ERROR_IN_SCRIPT_{0}", fs.Name));
                        console.PrintError(string.Format("An error occured while processing KeyDown event for script {0}. Aborting script. Details: {1}", fs.Name, ex.ToString()));
                        AbortScript(fs.ID);
                    }
                }
            }
        }
        private void KeyWatchDog_KeyUp(object sender, KeyEventArgs e)
        {
            for (int i = 0; i < ActiveScripts.Count; i++) {
                FoundScript fs = ActiveScripts[i];
                if (fs != null) {
                    try {
                        if (fs.Running) fs.Script.RaiseKeyUp(e);
                    }
                    catch (Exception ex) {
                        notification.ShowNotification(NotificationType.Error, DateTime.Now.AddSeconds(8), string.Format("An error occured in {0} KeyUp.", fs.Name), ex.Message, string.Format("ERROR_IN_SCRIPT_{0}", fs.Name));
                        console.PrintError(string.Format("An error occured while processing KeyUp event for script {0}. Aborting script. Details: {1}", fs.Name, ex.ToString()));
                        AbortScript(fs.ID);
                    }
                }
            }
        }
        #endregion

        #region Console Overrides
        public override void OpenConsole()
        {
            console.Open();
        }
        public override void CloseConsole()
        {
            console.Close();
        }
        public override void ClearConsole()
        {
            console.Clear();
        }

        public override void PrintToConsole(string str)
        {
            console.Print(str);
        }
        public override void PrintDebugToConsole(string str)
        {
            console.PrintDebug(str);
        }
        public override void PrintWarnToConsole(string str)
        {
            console.PrintWarning(str);
        }
        public override void PrintErrorToConsole(string str)
        {
            console.PrintError(str);
        }

        public override bool RegisterConsoleCommand(Guid fromScript, string name, Action<string[]> actionToExecute)
        {
            return console.RegisterCommand(fromScript, name, actionToExecute);
        }
        public override bool ExecuteConsoleCommand(string name)
        {
            return console.ExecuteCommand(name);
        }
        #endregion

        #region Methods
        public override void LoadScripts()
        {
            if (!Directory.Exists(scriptsPath)) {
                Directory.CreateDirectory(scriptsPath);
                return;
            }

            AbortScripts(false);

            string[] scriptFiles = Directory.GetFiles(scriptsPath, "*.ivsdk.dll");
            for (int i = 0; i < scriptFiles.Length; i++) {
                LoadAssembly(scriptFiles[i]);
            }

            // Log
            console.Print(string.Format("Loaded {0} of {1} scripts!", ActiveScripts.Count.ToString(), scriptFiles.Length.ToString()));
        }
        private void LoadAssembly(string path)
        {
            try {
                using (FileStream fs = new FileStream(path, FileMode.Open, FileAccess.Read)) {

                    byte[] fileByteArray = Helper.GetByteArray(fs);
                    Assembly assembly = Assembly.Load(fileByteArray);
                    string assemblyName = assembly.GetName().Name.Split('.')[0];

                    // Get types from assembly
                    Type[] containedTypes = assembly.GetTypes();
                    for (int i = 0; i < containedTypes.Length; i++) {
                        Type containedType = containedTypes[i];

                        if (containedType.IsSubclassOf(typeof(Script))) {

                            // Log
                            console.Print(string.Format("Found script: {0}", containedType.FullName));

                            // Create new instance of type for assembly
                            Script script = (Script)assembly.CreateInstance(containedType.FullName);

                            if (script != null) {

                                // Register AssemblyResolve event
                                script.ScriptDomain.AssemblyResolve += ScriptDomain_AssemblyResolve;

                                // Check for script settings file
                                string settingsFilePath = string.Format("{0}\\{1}.ini", scriptsPath, assemblyName);
                                if (File.Exists(settingsFilePath)) {
                                    script.Settings = new SettingsFile(settingsFilePath);
                                    script.Settings.Load();
                                }

                                // Check if FoundScript with this assembly name already exists in ActiveScripts list
                                FoundScript foundScript = GetFoundScript(assemblyName);
                                if (foundScript != null) { // FoundScript object with this assembly name already exists in ActiveScripts list. Create new instance for this class which inherits from Script
                                    // Todo
                                }
                                else { // No FoundScript object found with this assembly name in ActiveScripts list. Create new FoundScript object and add to ActiveScripts list
                                    foundScript = new FoundScript(script.ID, containedType, script);
                                    foundScript.Name = assemblyName;
                                    foundScript.FullPath = path;

                                    ActiveScripts.Add(foundScript); // Add script to ActiveScripts list.

                                    // Call script initialize event
                                    foundScript.Script.RaiseInitialized();
                                }

                                return;
                            }

                        }
                    }

                }
            }
            catch (ReflectionTypeLoadException ex) {

                Exception[] exs = ex.LoaderExceptions;
                for (int i = 0; i < exs.Length; i++) {
                    Exception e = exs[i];
                    console.PrintError(string.Format("A ReflectionTypeLoadException occured while trying to load script '{0}'. Details: {1}", Path.GetFileName(path), e.ToString()));
                }

            }
            catch (Exception ex) {
                console.PrintError(string.Format("An exception occured while trying to load script '{0}'. Details: {1}", Path.GetFileName(path), ex.ToString()));
            }
        }
        private Assembly ScriptDomain_AssemblyResolve(object sender, ResolveEventArgs args)
        {
            string requestingAssemblyName = args.RequestingAssembly.GetName().Name;
            FoundScript foundScript = GetFoundScript(requestingAssemblyName);

            try {
                if (foundScript != null) {

                    string assemblyName = args.Name.Split(',')[0];
                    string scriptsDir = Path.GetDirectoryName(foundScript.FullPath);
                    string customDir = string.Format("{0}\\{1}", CGame.GameStartupPath, foundScript.Script.CustomAssembliesPath);

                    string fileFullPath = string.Empty;

                    // Debug
                    console.PrintDebug(string.Format("Script {0} is requesting assembly: {1}", foundScript.Name, args.Name));

                    // Load Assembly by AssemblyLocation set by script
                    switch (foundScript.Script.AssembliesLocation) {

                        case eAssembliesLocation.GameRootDirectory:
                            console.PrintWarning(string.Format("Script {0} was requesting assembly {1} but it was not found in the root directory of GTA IV!", foundScript.Name, assemblyName));
                            return null;

                        case eAssembliesLocation.ScriptsDirectory:

                            fileFullPath = string.Format("{0}\\{1}.dll", scriptsDir, assemblyName);
                            if (File.Exists(fileFullPath))
                                return Assembly.UnsafeLoadFrom(fileFullPath);

                            console.PrintWarning(string.Format("Script {0} was requesting assembly {1} but it was not found in the scripts directory!", foundScript.Name, assemblyName));
                            return null;

                        case eAssembliesLocation.Custom:

                            fileFullPath = string.Format("{0}\\{1}.dll", customDir, assemblyName);
                            if (File.Exists(fileFullPath))
                                return Assembly.UnsafeLoadFrom(fileFullPath);

                            console.PrintWarning(string.Format("Script {0} was requesting assembly {1} but it was not found in the custom directory ({2})!", foundScript.Name, assemblyName, foundScript.Script.CustomAssembliesPath));
                            return null;
                    }
                }
                else {
                    console.PrintWarning(string.Format("Could not find requesting script {0}! Assemblies couldn't get loaded for this script.", requestingAssemblyName));
                }
            }
            catch (Exception ex) {
                console.PrintError(string.Format("An error occured while loading assembly {0} for Script {1}. Details: {2}", args.Name, foundScript != null ? foundScript.Name : "UNKNOWN", ex.ToString()));
            }
            return null;
        }

        public void AddConsoleCommandToScript(Guid id, string command)
        {
            FoundScript s = GetFoundScript(id);
            if (s != null) {
                if (!s.ConsoleCommands.Contains(command)) s.ConsoleCommands.Add(command);
            }
        }

        public override void AbortScripts(bool showMessage)
        {
            if (ActiveScripts.Count != 0) {
                ActiveScripts.ForEach(x => x.Abort(showMessage));
                ActiveScripts.Clear();
            }
            else {
                if (showMessage) console.Print("There are no scripts to abort.");
            }
        }

        public void StartDelayedAction(Guid id, string purpose, DateTime executeIn, Action<DelayedAction, object> actionToExecute, object parameter)
        {
            delayedActions.Insert(delayedActions.Count, new DelayedAction(id, purpose, executeIn, actionToExecute, parameter));
        }

        public override void WaitInTask(Guid id, int waitTimeInMilliseconds)
        {
            // ActiveScripts
            for (int i = 0; i < ActiveScripts.Count; i++) {
                for (int s = 0; s < ActiveScripts[i].ScriptTasks.Count; s++) {
                    AdvancedTask at = ActiveScripts[i].ScriptTasks[s];
                    if (at.ID == id) at.Wait(waitTimeInMilliseconds);
                }
            }

            // local tasks
            for (int i = 0; i < LocalTasks.Count; i++) {
                AdvancedTask at = LocalTasks[i];
                if (at.ID == id) at.Wait(waitTimeInMilliseconds);
            }
        }
        public void AbortTaskOrTimer(Guid id)
        {
            // ActiveScripts
            for (int i = 0; i < ActiveScripts.Count; i++) {
                for (int s = 0; s < ActiveScripts[i].ScriptTasks.Count; s++) {
                    AdvancedTask at = ActiveScripts[i].ScriptTasks[s];
                    if (at.ID == id) at.Abort();
                }
            }

            // local tasks
            for (int i = 0; i < LocalTasks.Count; i++) {
                AdvancedTask at = LocalTasks[i];
                if (at.ID == id) at.Abort();
            }
        }
        public void ChangeTimerState(Guid id, bool pause)
        {
            // ActiveScripts
            for (int i = 0; i < ActiveScripts.Count; i++) {
                for (int s = 0; s < ActiveScripts[i].ScriptTasks.Count; s++) {
                    AdvancedTask at = ActiveScripts[i].ScriptTasks[s];
                    if (at.ID == id) at.ShouldPause = pause;
                }
            }

            // local tasks
            for (int i = 0; i < LocalTasks.Count; i++) {
                AdvancedTask at = LocalTasks[i];
                if (at.ID == id) at.ShouldPause = pause;
            }
        }
        #endregion

        #region Functions
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
            FoundScript script = ActiveScripts.Where(x => x.ID == id).FirstOrDefault();

            if (script != null) {
                console.Print(string.Format("Aborting script {0}...", script.Name));
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

        public override Guid StartNewTask(Guid forScript, Func<object> funcToExecute)
        {
            FoundScript s = GetFoundScript(forScript);

            if (s != null) {
                AdvancedTask task = new AdvancedTask(Guid.NewGuid(), s, TaskUseCase.Custom);

                bool r = task.Start(TaskCreationOptions.None, funcToExecute, (AdvancedTask.InvokeData args) => {
                    StartDelayedAction(args.STask.ID, string.Format("Disposing and deleting task {0} of script {1}. CFSM: TaskDisposer in AdvancedTask class", args.STask.ID.ToString(), args.STask.Owner.Name), DateTime.Now.AddSeconds(5), AdvancedTask.TaskDisposer, args.STask);
                });

                if (r) {
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

            if (s != null) {
                AdvancedTask task = new AdvancedTask(Guid.NewGuid(), s, TaskUseCase.Timer, interval);

                bool r = task.Start(TaskCreationOptions.None, () => AdvancedTask.TimerStatic(task, actionToExecute), (AdvancedTask.InvokeData args) => {
                    StartDelayedAction(args.STask.ID, string.Format("Disposing and deleting task {0} of script {1}. CFSM: TaskDisposer in AdvancedTask class", args.STask.ID.ToString(), args.STask.Owner.Name), DateTime.Now.AddSeconds(5), AdvancedTask.TaskDisposer, args.STask);
                });

                if (r) {
                    s.ScriptTasks.Add(task);
                    return task.ID;
                }

                return Guid.Empty;
            }

            return Guid.Empty;
        }

        public Guid StartNewLocalTimer(int interval, Action actionToExecute)
        {
            AdvancedTask task = new AdvancedTask(Guid.NewGuid(), null, TaskUseCase.Timer, interval);

            bool r = task.Start(TaskCreationOptions.None, () => AdvancedTask.TimerStatic(task, actionToExecute), (AdvancedTask.InvokeData args) => {
                StartDelayedAction(args.STask.ID, string.Format("Disposing and deleting task {0} of Manager. CFSM: LocalTaskDisposer in AdvancedTask class", args.STask.ID.ToString()), DateTime.Now.AddSeconds(5), AdvancedTask.LocalTaskDisposer, args.STask);
            });

            if (r) {
                LocalTasks.Add(task);
                return task.ID;
            }

            return Guid.Empty;
        }
        #endregion

    }
}
