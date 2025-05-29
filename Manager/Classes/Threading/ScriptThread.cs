using Manager.Classes.Scripts;

namespace Manager.Classes.Threading
{
    public class ScriptThread : NetThread
    {

        #region Variables
        public FoundScript OwnerScript;
        #endregion

        #region Constructor
        public ScriptThread(FoundScript owner) : base(ThreadType.ScriptThread)
        {
            OwnerScript = owner;
        }
        #endregion

        public override void OnStartup()
        {
            OwnerScript.ConstructScript();
        }

        public override void OnTick()
        {
            OwnerScript.RaiseThreadedTick();
        }

        public override void OnEnd()
        {

        }

    }
}
