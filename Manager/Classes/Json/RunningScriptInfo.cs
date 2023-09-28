using System;

namespace Manager.Classes.Json
{
    public class RunningScriptInfo
    {

        #region Variables
        public string Name;
        public string FullPath;
        public Guid ScriptID;
        public Guid IVLauncherWorkshopID;
        #endregion

        #region Constructor
        internal RunningScriptInfo(string name, string fullPath, Guid scriptId, Guid ivLauncherWorkshopID)
        {
            Name = name;
            FullPath = fullPath;
            ScriptID = scriptId;
            IVLauncherWorkshopID = ivLauncherWorkshopID;
        }
        internal RunningScriptInfo()
        {
            
        }
        #endregion

    }
}
