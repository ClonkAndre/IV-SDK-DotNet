using System.Collections.Generic;

namespace Manager.Classes.Json.Script
{
    public class ScriptConfig
    {
        #region Variables
        public List<ScriptDependencyInfo> DependencyInfo;
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
            return DependencyInfo != null && DependencyInfo.Count > 0;
        }
        public bool HasIncompatibleMods()
        {
            return IncompatibleMods != null && IncompatibleMods.Count > 0;
        }
        #endregion
    }
}
