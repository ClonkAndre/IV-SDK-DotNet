using System;
using System.Threading;
using System.Threading.Tasks;

namespace Manager.Classes
{

    public class TaskData
    {
        #region Variables and Properties
        // Variables
        private AdvancedTask _source;
        private object _customData;

        // Properties
        public AdvancedTask Source
        {
            get { return _source; }
            private set { _source = value; }
        }
        public object CustomData
        {
            get { return _customData; }
            private set { _customData = value; }
        }
        #endregion

        #region Constructor
        public TaskData(AdvancedTask source, object customData)
        {
            _source = source;
            _customData = customData;
        }
        #endregion
    }

    public class CustomTask : IDisposable
    {
        #region Variables and Properties
        // Variables
        private bool _disposed;
        private Guid _id;
        private Guid _ownerID;
        private Task _task;
        private CancellationTokenSource _taskController;

        // Properties
        public bool IsDisposed
        {
            get { return _disposed; }
            private set { _disposed = value; }
        }
        public Guid ID
        {
            get
            {
                if (IsDisposed)
                    return Guid.Empty;

                return _id;
            }
            private set
            {
                if (IsDisposed)
                    return;

                _id = value;
            }
        }
        public Guid OwnerID
        {
            get
            {
                if (IsDisposed)
                    return Guid.Empty;

                return _ownerID;
            }
            private set
            {
                if (IsDisposed)
                    return;

                _ownerID = value;
            }
        }
        public Task Task
        {
            get
            {
                if (IsDisposed)
                    return null;

                return _task;
            }
            private set
            {
                if (IsDisposed)
                    return;

                _task = value;
            }
        }
        public CancellationTokenSource CancellationController
        {
            get
            {
                if (IsDisposed)
                    return null;

                return _taskController;
            }
            private set
            {
                if (IsDisposed)
                    return;

                _taskController = value;
            }
        }
        #endregion

        #region Constructor
        public CustomTask(Guid id, Guid ownerId)
        {
            ID = id;
            OwnerID = ownerId;
            CancellationController = new CancellationTokenSource();
        }
        #endregion

        #region Methods
        public void Dispose()
        {
            if (IsDisposed)
                return;

            if (_task != null)
            {
                _task.Dispose();
                _task = null;
            }
            if (_taskController != null)
            {
                if (!_taskController.IsCancellationRequested)
                    _taskController.Cancel();

                _taskController.Dispose();
                _taskController = null;
            }

            IsDisposed = true;
        }
        #endregion

        #region Functions
        public bool RequestCancellation()
        {
            if (IsDisposed)
                return false;

            try
            {
                if (CancellationController != null)
                {
                    CancellationController.Cancel();
                    return true;
                }
            }
            catch (Exception) {}

            return false;
        }
        public bool IsCancellationRequested()
        {
            if (IsDisposed)
                return false;

            try
            {
                if (CancellationController != null)
                    return CancellationController.Token.IsCancellationRequested;
            }
            catch (Exception) { }

            return false;
        }

        public bool Wait(int millisecondsTimeout)
        {
            if (IsDisposed)
                return false;

            try
            {
                if (CancellationController != null)
                    return CancellationController.Token.WaitHandle.WaitOne(millisecondsTimeout);
            }
            catch (Exception) {}

            return false;
        }

        public bool Start(AdvancedTask source, TaskCreationOptions options, Func<object> func, Action<TaskData> continueWithAction)
        {
            if (IsDisposed)
                return false;
            if (Task != null)
                return false;

            try
            {
                // Try start task
                Task = Task.Factory.StartNew(func, CancellationController.Token, options, TaskScheduler.Default).ContinueWith(t =>
                {
                    continueWithAction?.Invoke(new TaskData(source, t.Result));
                });
            }
            catch (Exception) {}

            return Task != null;
        }
        #endregion
    }

    public class AdvancedTask : IDisposable
    {
        #region Variables and Properties
        // Variables
        private bool _disposed;
        private CustomTask _actualTask;

        private TaskUseCase _useCase;
        
        private int _timerInterval = 100;
        private bool _pauseTimer;

        // Properties
        public bool IsDisposed
        {
            get { return _disposed; }
            private set { _disposed = value; }
        }

        public CustomTask ActualTask
        {
            get
            {
                if (IsDisposed)
                    return null;

                return _actualTask;
            }
            private set
            {
                if (IsDisposed)
                    return;

                _actualTask = value;
            }
        }

        public Guid ID // Will be read from the ActualTask
        {
            get
            {
                if (IsDisposed)
                    return Guid.Empty;

                return ActualTask.ID;
            }
        }
        public Guid OwnerID // Will be read from the ActualTask
        {
            get
            {
                if (IsDisposed)
                    return Guid.Empty;

                return ActualTask.OwnerID;
            }
        }
        public TaskUseCase UseCase
        {
            get
            {
                if (IsDisposed)
                    return TaskUseCase.Unknown;

                return _useCase;
            }
            set
            {
                if (IsDisposed)
                    return;

                _useCase = value;
            }
        }

        public int TimerInterval
        {
            get
            {
                if (IsDisposed)
                    return 100;

                return _timerInterval;
            }
            set
            {
                if (IsDisposed)
                    return;

                _timerInterval = value;
            }
        }
        public bool PauseTimer
        {
            get
            {
                if (IsDisposed)
                    return false;

                return _pauseTimer;
            }
            set
            {
                if (IsDisposed)
                    return;

                _pauseTimer = value;
            }
        }
        #endregion

        #region Constructor
        public AdvancedTask(Guid id, Guid ownerId, TaskUseCase useCase, int timerInterval)
        {
            ActualTask = new CustomTask(id, ownerId);
            UseCase = useCase;
            TimerInterval = timerInterval;
        }
        public AdvancedTask(Guid id, Guid ownerId, TaskUseCase useCase)
        {
            ActualTask = new CustomTask(id, ownerId);
            UseCase = useCase;
            TimerInterval = 100;
        }
        #endregion

        #region Methods
        public void Dispose()
        {
            if (IsDisposed)
                return;

            if (ActualTask != null)
            {
                ActualTask.Dispose();
                ActualTask = null;
            }

            IsDisposed = true;
        }
        #endregion

        #region Functions
        public bool RequestCancellation()
        {
            if (IsDisposed)
                return false;

            if (ActualTask != null)
                return ActualTask.RequestCancellation();

            return false;
        }
        public bool IsCancellationRequested()
        {
            if (IsDisposed)
                return false;

            try
            {
                if (ActualTask != null)
                    return ActualTask.IsCancellationRequested();
            }
            catch (Exception) { }

            return false;
        }
        public bool Wait(int millisecondsTimeout)
        {
            if (IsDisposed)
                return false;

            if (ActualTask != null)
                return ActualTask.Wait(millisecondsTimeout);

            return false;
        }

        /// <summary>
        /// Starts the <see cref="AdvancedTask"/>.
        /// </summary>
        /// <param name="options">The options of this task.</param>
        /// <param name="func">The function that should be executed by this task.</param>
        /// <param name="continueWithAction">The action that should be executed when the <paramref name="func"/> has finished executing.</param>
        /// <returns>True if the task got started, otherwise false.</returns>
        public bool Start(TaskCreationOptions options, Func<object> func, Action<TaskData> continueWithAction)
        {
            if (IsDisposed)
                return false;

            if (ActualTask != null)
                return ActualTask.Start(this, options, func, continueWithAction);

            return false;
        }
        #endregion

        // - - - STATIC STUFF - - -

        // Timer
        public static object TimerStatic(AdvancedTask advancedTask, Action actionToExecute)
        {
            try
            {
                while (!advancedTask.IsCancellationRequested())
                {
                    // Check if timer is paused
                    if (advancedTask.PauseTimer)
                    {
                        advancedTask.Wait(advancedTask.TimerInterval);
                        continue;
                    }

                    // Execute target action
                    actionToExecute?.Invoke();

                    // Sleep
                    advancedTask.Wait(advancedTask.TimerInterval);
                }
            }
            catch (Exception ex)
            {
                Logger.LogError(string.Format("An error occured in Timer {0} for Script {1}. Details: {2}", advancedTask.ID, advancedTask.OwnerID, ex));
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
            if (st != null)
            {
                st.Dispose();
                Main.Instance.ActiveTasks.Remove(st);
            }
        }

    }

}
