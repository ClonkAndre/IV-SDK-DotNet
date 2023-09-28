using System;

namespace Manager.Classes
{
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
}
