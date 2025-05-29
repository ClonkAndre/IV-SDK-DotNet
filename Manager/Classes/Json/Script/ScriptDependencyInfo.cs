using System;

namespace Manager.Classes.Json.Script
{
    public class ScriptDependencyInfo
    {

        #region Variables
        public string FileName;
        public string SpecificVersion;
        public string DownloadURL;
        public Guid IVLauncherWorkshopID;
        #endregion

        #region Constructor
        public ScriptDependencyInfo()
        {
            
        }
        #endregion

        public override string ToString()
        {
            return string.Concat(FileName, ", Version: ", SpecificVersion);
        }

    }
}
