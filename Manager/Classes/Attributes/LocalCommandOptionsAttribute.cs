using System;

namespace Manager.Classes.Attributes
{
    internal class LocalCommandOptionsAttribute : Attribute
    {

        #region Variables
        public bool CanOnlyBeCalledOnceInGame;
        public int RequiredArgumentsCount;
        #endregion

        #region Constructor
        public LocalCommandOptionsAttribute(bool canOnlyBeCalledOnceInGame = false, int requiredArgumentsCount = 0)
        {
            CanOnlyBeCalledOnceInGame = canOnlyBeCalledOnceInGame;
            RequiredArgumentsCount = requiredArgumentsCount;
        }
        #endregion

    }
}
