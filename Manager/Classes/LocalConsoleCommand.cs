using System;
using System.Linq;
using System.Reflection;

using Manager.Classes.Attributes;

namespace Manager.Classes
{
    internal class LocalConsoleCommand
    {

        #region Variables
        /// <summary>
        /// All the possible names with which this command can be invoked.
        /// </summary>
        public string[] theNames;
        /// <summary>
        /// Describes what this command does.
        /// </summary>
        public string Description;
        /// <summary>
        /// Will be shown when the user wants to get help about a single command.
        /// </summary>
        public string[] DetailedDescription;

        /// <summary>
        /// The action that should be invoked when this command was called.
        /// </summary>
        private MethodInfo theMethod;

        // Options
        /// <summary>
        /// Gets if this command can only be called once in-game.
        /// </summary>
        public bool CanOnlyBeCalledOnceInGame;
        /// <summary>
        /// Gets the amount of required arguments.
        /// </summary>
        public int RequiredArgumentsCount;

        // Suggestions
        /// <summary>
        /// Gets if this command has any suggestions.
        /// </summary>
        public bool HasSuggestions;
        /// <summary>
        /// The suggestions to show for this command.
        /// </summary>
        public string[] Suggestions;
        /// <summary>
        /// The dynamic suggestions to show for this command.
        /// </summary>
        public DynamicConsoleCommandSuggestions DynamicSuggestions;
        #endregion

        #region Constructor
        public LocalConsoleCommand(MethodInfo method)
        {
            theMethod = method;
        }
        #endregion

        #region Methods
        public void Invoke(string[] args)
        {
            theMethod.Invoke(null, new object[1] { args });
        }

        public void SetNameFromAttribute(LocalCommandNameAttribute attr, string[] setFromThisArray = null)
        {
            if (attr == null && setFromThisArray == null)
                return;

            theNames = attr != null ? attr.CommandNames : setFromThisArray;
        }
        public void SetDescriptionFromAttribute(LocalCommandDescAttribute attr, string setFromThisString = null)
        {
            if (attr == null && setFromThisString == null)
                return;

            Description = attr != null ? attr.ShortDescription : setFromThisString;

            if (attr != null)
            {
                DetailedDescription = attr.DetailedDescription;
            }
        }
        public void SetOptionsFromAttribute(LocalCommandOptionsAttribute attr)
        {
            if (attr == null)
                return;

            CanOnlyBeCalledOnceInGame = attr.CanOnlyBeCalledOnceInGame;
            RequiredArgumentsCount = attr.RequiredArgumentsCount;
        }
        public void SetSuggestionsFromAttribute(LocalCommandSuggestionsAttribute attr)
        {
            if (attr == null)
                return;

            HasSuggestions = true;
            Suggestions = attr.Suggestions;
            DynamicSuggestions = attr.DynamicSuggestions;
        }
        #endregion

        #region Functions
        public bool ContainsGivenCommandName(string name)
        {
            return theNames.Contains(name);
        }

        public string[] GetNames()
        {
            return theNames;
        }
        public string GetFirstName()
        {
            return theNames[0];
        }
        #endregion

    }
}
