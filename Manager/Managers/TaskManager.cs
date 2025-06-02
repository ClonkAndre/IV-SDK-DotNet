using System;
using System.Collections.Generic;
using System.Threading.Tasks;

using Manager.Classes.Tasks;

namespace Manager.Managers
{

    // TODO: Finish the task manager

    internal static class TaskManager
    {

        #region Variables
        private static bool wasInitialized;
        private static bool blockProcessing;

        private static MainThreadTaskScheduler scheduler;
        private static List<CustomTask> tasks;
        #endregion

        #region Methods
        public static void Init()
        {
            if (wasInitialized)
                return;

            if (scheduler == null)
            {
                scheduler = new MainThreadTaskScheduler(null);
            }
            if (tasks == null)
            {
                tasks = new List<CustomTask>();
            }

            wasInitialized = true;
        }
        public static void Shutdown()
        {
            if (!wasInitialized)
                return;

            wasInitialized = false;

            if (tasks != null)
            {
                tasks.Clear();
                tasks = null;
            }
            if (scheduler != null)
            {
                scheduler = null;
            }
        }

        public static void Process()
        {
            if (!wasInitialized)
                return;
            if (blockProcessing)
                return;

            scheduler.TryExecutePending();

            // Remove completed tasks
            for (int i = 0; i < tasks.Count; i++)
            {
                CustomTask task = tasks[i];

                if (task.TheTask.IsCompleted || task.TheTask.IsCanceled || task.TheTask.IsFaulted)
                {
                    tasks.RemoveAt(i);
                    i--;
                }
            }
        }

        public static void CancelAllTasks()
        {
            blockProcessing = true;

            Task[] tasksToCancel = new Task[tasks.Count];

            // Request a cancellation for all active tasks and put all active tasks in task array
            for (int i = 0; i < tasks.Count; i++)
            {
                CustomTask task = tasks[i];

                // Request task to cancel
                task.TokenSource.Cancel();

                // Put actual task in task array
                tasksToCancel[i] = task.TheTask;
            }

            // Wait until all tasks end
            Task.WaitAll(tasksToCancel);
            
            tasks.Clear();

            blockProcessing = false;
        }

        public static void StartNewTask(Action actionToExecute)
        {
            if (!wasInitialized)
                return;

            tasks.Add(CustomTask.StartNew(actionToExecute, TaskCreationOptions.None, scheduler));
        }
        #endregion

        #region Functions
        public static int GetActiveTasksCount()
        {
            if (!wasInitialized)
                return 0;

            return tasks.Count;
        }
        #endregion

    }
}
