using Manager.Classes;

namespace Manager.Threading
{
    public class ScriptThread : NetThread
    {

        #region Variables
        public FoundScript OwnerScript;
        #endregion

        #region Constructor
        public ScriptThread(FoundScript owner)
        {
            OwnerScript = owner;
        }
        #endregion

        public override void OnTick()
        {
            //OwnerScript.RaiseThreadedTick();
        }

    }
}
