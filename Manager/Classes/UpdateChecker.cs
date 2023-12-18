using System;
using System.Net;

namespace Manager.Classes
{
    public class UpdateChecker
    {

        #region Variables
        private WebClient webClient;
        private bool silentCheck;

        private string currentVersion;
        private string versionDownloadURL;
        #endregion

        #region Structs
        public struct VersionCheckInfo
        {
            #region Properties
            public bool NewVersionAvailable { get; private set; }
            public bool IsSilentCheck { get; private set; }
            public string NewVersion { get; private set; }
            public string CurrentVersion { get; private set; }
            #endregion

            #region Constructor
            public VersionCheckInfo(bool newVerAvailable, bool isSilentCheck, string newVersion, string currentVersion)
            {
                NewVersionAvailable = newVerAvailable;
                IsSilentCheck = isSilentCheck;
                NewVersion = newVersion;
                CurrentVersion = currentVersion;
            }
            #endregion

            #region Methods
            public void UpdateInfos(bool newVerAvailable, bool isSilentCheck, string newVersion, string currentVersion)
            {
                NewVersionAvailable = newVerAvailable;
                IsSilentCheck = isSilentCheck;
                NewVersion = newVersion;
                CurrentVersion = currentVersion;
            }
            #endregion
        }
        #endregion

        #region Events
        public delegate void VersionCheckCompletedDelegate(VersionCheckInfo result);
        public event VersionCheckCompletedDelegate VersionCheckCompleted;

        public delegate void VersionCheckFailedDelegate(Exception e);
        public event VersionCheckFailedDelegate VersionCheckFailed;
        #endregion

        #region Constructor
        public UpdateChecker(string _currentVersion, string _versionDownloadURL)
        {
            webClient = new WebClient();
            webClient.DownloadStringCompleted += WebClient_DownloadStringCompleted;
            currentVersion = _currentVersion;
            versionDownloadURL = _versionDownloadURL;
        }
        #endregion

        #region Methods
        private void WebClient_DownloadStringCompleted(object sender, DownloadStringCompletedEventArgs e)
        {
            try
            {
                if (e.Error == null)
                {
                    if (!e.Cancelled)
                    {

                        VersionCheckInfo vci = new VersionCheckInfo();

                        if (string.Compare(currentVersion, e.Result) <= -1) // Update available
                            vci.UpdateInfos(true, silentCheck, e.Result, currentVersion);
                        else // No update available
                            vci.UpdateInfos(false, silentCheck, string.Empty, currentVersion);

                        VersionCheckCompleted?.Invoke(vci);

                    }
                    else
                    {
                        VersionCheckFailed?.Invoke(new Exception("An unknown error occurred while receiving version info."));
                    }
                }
                else
                {
                    VersionCheckFailed?.Invoke(e.Error);
                }
            }
            catch (Exception ex)
            {
                VersionCheckFailed?.Invoke(ex);
            }
        }
        public void CheckForUpdates(bool silent)
        {
            try
            {
                silentCheck = silent;
                ServicePointManager.Expect100Continue = true;
                ServicePointManager.SecurityProtocol = SecurityProtocolType.Tls12;
                webClient.DownloadStringAsync(new Uri(versionDownloadURL));
            }
            catch (Exception ex)
            {
                VersionCheckFailed?.Invoke(ex);
            }
        }
        #endregion

    }
}
