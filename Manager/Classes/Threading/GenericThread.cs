using System;

namespace Manager.Classes.Threading
{
    public class GenericThread : NetThread
    {

        #region Variables
        private Action onTickAction;
        private Action onStartupAction;
        private Action onEndAction;
        #endregion

        #region Constructor
        public GenericThread(Action onTick, Action onStartup = null, Action onEnd = null) : base(ThreadType.GenericThread)
        {
            onTickAction = onTick;
            onStartupAction = onStartup;
            onEndAction = onEnd;
        }
        #endregion

        public override void OnStartup()
        {
            onStartupAction?.Invoke();
        }
        public override void OnTick()
        {
            onTickAction?.Invoke();
        }
        public override void OnEnd()
        {
            onEndAction?.Invoke();
        }

    }
}
