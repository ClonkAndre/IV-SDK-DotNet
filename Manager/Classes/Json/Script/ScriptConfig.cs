using System;
using System.Collections.Generic;

namespace Manager.Classes.Json.Script
{
    public class ScriptConfig
    {
        #region Variables
        public bool ForceNoAbort;
        public Guid IVLauncherWorkshopID;

        public List<ScriptDependencyInfo> Dependencies;
        public List<string> IncompatibleMods;
        #endregion

        #region Constructor
        internal ScriptConfig()
        {
            
        }
        #endregion

        #region Functions
        public bool HasDependencyInfo()
        {
            return Dependencies != null && Dependencies.Count > 0;
        }
        public bool HasIncompatibleMods()
        {
            return IncompatibleMods != null && IncompatibleMods.Count > 0;
        }
        #endregion
    }
}
