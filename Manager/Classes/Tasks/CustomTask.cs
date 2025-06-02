using System;
using System.Threading;
using System.Threading.Tasks;

namespace Manager.Classes.Tasks
{
    internal class CustomTask
    {

        #region Variables
        public Guid ID;
        public Task TheTask;
        public CancellationTokenSource TokenSource;
        #endregion

        #region Constructor
        private CustomTask()
        {
            ID = Guid.NewGuid();
            TokenSource = new CancellationTokenSource();
        }
        #endregion

        #region Methods
        protected void SetTask(Task task)
        {
            TheTask = task;
        }
        #endregion

        public static CustomTask StartNew(Action actionToExecute, TaskCreationOptions options, TaskScheduler scheduler)
        {
            CustomTask task = new CustomTask();
            task.SetTask(Task.Factory.StartNew(actionToExecute, task.TokenSource.Token, options, scheduler));
            return task;
        }

    }
}
