using System;

namespace Manager.Classes
{
    public class BoundPhoneNumber
    {
        #region Variables
        public string Number;
        public bool WasDialed;
        public Action DialedAction;
        #endregion

        #region Constructor
        public BoundPhoneNumber(string number, Action dialedAction)
        {
            Number = number;
            DialedAction = dialedAction;
        }
        #endregion

        public void Invoke()
        {
            DialedAction?.Invoke();
        }
    }
}
