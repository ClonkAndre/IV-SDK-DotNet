using System;

namespace Manager.Classes
{
    public class RegisteredEvent
    {

        #region Variables
        public Delegate SourceEvent;
        public Delegate TargetMethod;
        #endregion

        #region Constructor
        public RegisteredEvent(Delegate sourceEvent, Delegate targetMethod)
        {
            SourceEvent = sourceEvent;
            TargetMethod = targetMethod;
        }
        #endregion

        public void RemoveSubscription()
        {
            try
            {
                Delegate.Remove(SourceEvent, TargetMethod);
            }
            catch (Exception ex)
            {
                Logger.LogDebug(string.Format("Failed to remove subscription from event {0}! Details: {1}", SourceEvent.Method.Name, ex));
            }
        }

    }
}
