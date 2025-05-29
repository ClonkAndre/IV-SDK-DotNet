using System;

namespace Manager.Classes.Attributes
{
    internal class LocalCommandDescAttribute : Attribute
    {

        #region Variables
        public string Description;
        #endregion

        #region Constructor
        public LocalCommandDescAttribute(string desc)
        {
            Description = desc;
        }
        #endregion

    }
}
