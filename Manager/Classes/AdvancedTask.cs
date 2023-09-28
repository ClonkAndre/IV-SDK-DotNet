using System;
using System.Threading;
using System.Threading.Tasks;

namespace Manager.Classes
{
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
        public struct InvokeData
        {

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
            if (task != null)
            {
                task.Dispose();
                task = null;
            }
            if (taskController != null)
            {
                taskController.Dispose();
                taskController = null;
            }
        }
        public void Abort()
        {
            if (taskController != null)
                taskController.Cancel();
        }

        public void Wait(int time)
        {
            if (taskController != null)
                taskController.Token.WaitHandle.WaitOne(time);
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
        /// Starts the <see cref="AdvancedTask"/>.
        /// </summary>
        /// <param name="options">The options of this task.</param>
        /// <param name="func">The function that should be executed by this task.</param>
        /// <param name="continueWithAction">The action that should be executed when the <paramref name="func"/> has finished executing.</param>
        /// <returns>True if the task got started, otherwise false.</returns>
        public bool Start(TaskCreationOptions options, Func<object> func, Action<InvokeData> continueWithAction)
        {
            if (task == null)
            {
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
            try
            {
                while (!at.token.IsCancellationRequested)
                {

                    if (at.ShouldPause)
                    {
                        at.taskController.Token.WaitHandle.WaitOne(at.SleepTime);
                        continue;
                    }

                    actionToExecute?.Invoke();

                    // Sleep
                    at.taskController.Token.WaitHandle.WaitOne(at.SleepTime);
                }
            }
            catch (Exception ex)
            {
                Main.Instance.Console.PrintError(string.Format("An error occured in Timer {0} for Script {1}. Details: {2}", at.ID.ToString(), at.Owner.Name, ex.ToString()));
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
            if (st != null)
            {
                st.Dispose();
                Main.Instance.LocalTasks.Remove(st);
            }
        }
        #endregion
    }
}
