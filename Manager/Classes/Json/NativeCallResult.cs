namespace Manager.Classes.Json
{
    public class NativeCallResult
    {

        #region Variables
        public object Result;
        public object[] Arguments;
        #endregion

        #region Constructor
        internal NativeCallResult(object result, object[] args)
        {
            Result = result;
            Arguments = args;
        }
        internal NativeCallResult()
        {
            
        }
        #endregion

    }
}
