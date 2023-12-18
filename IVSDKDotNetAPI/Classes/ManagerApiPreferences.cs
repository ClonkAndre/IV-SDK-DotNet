namespace IVSDKDotNetAPI.Classes
{
    /// <summary>
    /// Contains Information about the User's API Settings Preferences in the IV-SDK .NET's config.ini File.
    /// </summary>
    public class ManagerApiPreferences
    {
        #region Variables
        /// <summary>
        /// If the User wants to receive a on-screen Notification if an API Client connected.
        /// </summary>
        public bool ShowNotificationOnConnection;

        /// <summary>
        /// If the User allows connected API Clients to remotely reload the IV-SDK .NET Scripts.
        /// </summary>
        public bool AllowRemoteReloadScripts;
        /// <summary>
        /// If the User allows connected API Clients to remotely load a single IV-SDK .NET Script.
        /// </summary>
        public bool AllowRemoteLoadScripts;
        /// <summary>
        /// If the User allows connected API Clients to remotely abort a single IV-SDK .NET Script.
        /// </summary>
        public bool AllowRemoteAbortScripts;
        /// <summary>
        /// If the User allows connected API Client to remotely call GTA IV Native Functions.
        /// </summary>
        public bool AllowRemoteNativeFunctionCalls;
        #endregion

        #region Constructor
        internal ManagerApiPreferences()
        {
            
        }
        #endregion
    }
}
