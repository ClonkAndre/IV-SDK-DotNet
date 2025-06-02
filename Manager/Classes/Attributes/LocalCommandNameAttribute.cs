using System;

namespace Manager.Classes.Attributes
{
    internal class LocalCommandNameAttribute : Attribute
    {

        #region Variables
        public string[] CommandNames;
        #endregion

        #region Constructor
        public LocalCommandNameAttribute(params string[] names)
        {
            // Convert names to lowercase
            for (int i = 0; i < names.Length; i++)
            {
                names[i] = names[i].ToLower();
            }

            CommandNames = names;
        }
        #endregion

    }
}
