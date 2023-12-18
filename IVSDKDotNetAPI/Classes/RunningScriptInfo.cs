using System;

namespace IVSDKDotNetAPI.Classes
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
        internal RunningScriptInfo()
        {

        }
        #endregion

    }
}
