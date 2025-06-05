using System;
using System.Net;
using System.Net.Http;
using System.Threading.Tasks;

using Manager.Classes;

namespace Manager.Managers
{
    internal static class WebManager
    {

        #region Consts
        private const string UPDATE_CHECK_URL = "https://www.dropbox.com/s/smaz6ij8dkzd7nh/version.txt?dl=1";
        private const string DEBUG_UPDATE_CHECK_URL = "https://www.dropbox.com/scl/fi/uro5krf3cinq4i0oce52f/debugVersion.txt?rlkey=mcq2rrgc9wlw35ewemr7gfk2l&dl=1";
        #endregion

        #region Variables
        private static bool wasInitialized;
        private static HttpClient httpClient;
        #endregion

        #region Methods
        public static void Init()
        {
            if (wasInitialized)
                return;

            httpClient = new HttpClient();
            httpClient.Timeout = TimeSpan.FromSeconds(10.0d);

            wasInitialized = true;
        }
        public static void Shutdown()
        {
            if (!wasInitialized)
                return;

            wasInitialized = false;

            if (httpClient != null)
            {
                httpClient.CancelPendingRequests();
                httpClient.Dispose();
                httpClient = null;
            }
        }
        #endregion

        public static Task<string> GetStringAsync(string url)
        {
            if (!wasInitialized)
                return Task.FromException<string>(new Exception("The WebManager was shut down and does no longer accept any requests."));

            ServicePointManager.SecurityProtocol = SecurityProtocolType.Tls12;

            try
            {
                Helper.WriteToDebugOutput(Priority.Default, "[WebManager] Trying to get string from URL '{0}'...", url);

                Task<string> getStringTask = httpClient.GetStringAsync(url);
                getStringTask.Wait();
                return Task.FromResult(getStringTask.Result);
            }
            catch (Exception ex)
            {
                Helper.WriteToDebugOutput(Priority.Default, "[WebManager] Failed to get string async! Details: {0}", ex);
                return Task.FromException<string>(ex);
            }
        }

        public static Task<VersionCheckResult> CheckForUpdates(bool silentCheck)
        {
            if (!wasInitialized)
                return Task.FromException<VersionCheckResult>(new Exception("The WebManager was shut down and does no longer accept any requests."));

            return Task.Run(() =>
            {
                // Try get the current version
#if DEBUG
                Task<string> getCurrentVersionStringTask = GetStringAsync(DEBUG_UPDATE_CHECK_URL);
#else
                Task<string> getCurrentVersionStringTask = GetStringAsync(UPDATE_CHECK_URL);
#endif


                // Wait till the task completes
                getCurrentVersionStringTask.Wait();

                // Check if the task didn't threw an exception
                if (getCurrentVersionStringTask.Exception != null)
                    return Task.FromException<VersionCheckResult>(getCurrentVersionStringTask.Exception);

                // Check for updates and return result
                if (string.Compare(CLR.CLRBridge.Version.ToString(), getCurrentVersionStringTask.Result) <= -1) // Update available
                    return Task.FromResult(new VersionCheckResult(true, silentCheck, getCurrentVersionStringTask.Result));
                else // No update available
                    return Task.FromResult(new VersionCheckResult(false, silentCheck, null));
            });
        }

    }
}
