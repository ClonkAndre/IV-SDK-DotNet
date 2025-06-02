using System;

namespace Manager.Classes.Attributes
{
    internal class LocalCommandDescAttribute : Attribute
    {

        #region Variables
        public string ShortDescription;
        public string[] DetailedDescription;
        #endregion

        #region Constructor
        public LocalCommandDescAttribute(string shortDesc, string[] detailedDesc = null)
        {
            ShortDescription = shortDesc;
            DetailedDescription = detailedDesc;
        }
        #endregion

    }
}
