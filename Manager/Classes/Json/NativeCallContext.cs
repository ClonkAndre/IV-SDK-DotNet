using System;

namespace Manager.Classes.Json
{
    public class NativeCallContext
    {

        #region Variables
        public string Name;
        public object[] Arguments;
        public Type[] ArgumentTypes;
        #endregion

        #region Constructor
        internal NativeCallContext()
        {

        }
        #endregion

    }
}
