using System;

namespace Manager.Classes.Attributes
{
    internal class LocalCommandSuggestionsAttribute : Attribute
    {

        #region Variables
        public string[] Suggestions;
        public DynamicConsoleCommandSuggestions DynamicSuggestions;
        #endregion

        #region Constructor
        public LocalCommandSuggestionsAttribute(string[] suggestions = default, DynamicConsoleCommandSuggestions dynamicSuggestions = DynamicConsoleCommandSuggestions.DontUse)
        {
            Suggestions = suggestions;
            DynamicSuggestions = dynamicSuggestions;
        }
        #endregion

    }
}
