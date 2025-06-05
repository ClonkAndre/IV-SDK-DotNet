namespace Manager.Classes
{
    internal class VersionCheckResult
    {
        #region Properties
        public bool IsSilentCheck;
        public bool IsNewVersionAvailable;
        public string TheNewVersion;
        #endregion

        #region Constructor
        public VersionCheckResult(bool newVerAvailable, bool isSilentCheck, string newVersion)
        {
            IsNewVersionAvailable = newVerAvailable;
            IsSilentCheck = isSilentCheck;
            TheNewVersion = newVersion;
        }
        #endregion
    }
}
