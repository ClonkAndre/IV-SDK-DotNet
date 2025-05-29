using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Threading.Tasks;

using Manager.Managers;

namespace Manager.Classes.Tasks
{
    internal class MainThreadTaskScheduler : TaskScheduler
    {

        #region Variables
        private ConcurrentQueue<Task> queuedTasks;
        private Action<Task> onTaskExecutedAction;
        #endregion

        #region Constructor
        public MainThreadTaskScheduler(Action<Task> onTaskExecuted)
        {
            queuedTasks = new ConcurrentQueue<Task>();
            onTaskExecutedAction = onTaskExecuted;
        }
        #endregion

        /// <summary>
        /// Tries to execute pending tasks.
        /// </summary>
        public void TryExecutePending()
        {
            while (queuedTasks.TryDequeue(out Task task))
            {
                if (TryExecuteTask(task))
                    onTaskExecutedAction?.Invoke(task);
            }
        }

        protected override void QueueTask(Task task)
        {
            queuedTasks.Enqueue(task);
        }

        protected override bool TryExecuteTaskInline(Task task, bool taskWasPreviouslyQueued)
        {
            // Only allow inline execution when called from within the main thread
            if (ThreadManager.IsCurrentThreadTheMainThread())
            {
                bool result = TryExecuteTask(task);

                if (result)
                    onTaskExecutedAction?.Invoke(task);

                return result;
            }

            return false;
        }

        protected override IEnumerable<Task> GetScheduledTasks()
        {
            return queuedTasks.ToArray();
        }

    }
}
