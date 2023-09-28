using System;

namespace IVSDKDotNetAPI.Classes
{
    public class NativeCallContext
    {

        #region Variables
        public string Name;
        public object[] Arguments;
        public Type[] ArgumentTypes;
        #endregion

        #region Constructor
        internal NativeCallContext(string name, object[] args)
        {
            Name = name;
            Arguments = args;

            // Get types of arguments
            if (Arguments != null)
            {
                if (Arguments.Length != 0)
                {
                    ArgumentTypes = new Type[Arguments.Length];

                    for (int i = 0; i < Arguments.Length; i++)
                    {
                        if (Arguments[i] == null)
                            continue;

                        ArgumentTypes[i] = Arguments[i].GetType();
                    }
                }
            }
        }
        internal NativeCallContext()
        {
            
        }
        #endregion

    }
}
