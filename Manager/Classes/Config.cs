using System;
using System.Windows.Forms;

using IVSDKDotNet;

namespace Manager.Classes
{
    internal class Config
    {

        #region Variables
        private static SettingsFile theSettingsFile;

        // Main
        public static bool CreateLogFilesInMainDirectory;
        public static int MaxLogsFiles;

        public static string SwitchCursorKey;
        public static string OpenManagerWindowKey;

        // Scripts
        public static bool PauseScriptExecutionWhenNotInFocus;
        public static bool DoNotLoadLegacyScripts;
        public static bool ReloadScriptsOnReload;

        // Console
        public static Keys ConsoleOpenCloseKey;

        // API
        public static bool AllowRemoteConnections;
        public static ushort ServerPort;
        public static ushort MaxServerClients;
        public static bool ShowNotificationOnConnection;
        public static bool AllowRemoteReloadScripts;
        public static bool AllowRemoteLoadScripts;
        public static bool AllowRemoteAbortScripts;
        public static bool AllowRemoteNativeFunctionCalls;
        #endregion

        public static void ApplySettings(SettingsFile settings)
        {
            theSettingsFile = settings;

            // Section: Main
            CreateLogFilesInMainDirectory = settings.GetBoolean("Main", "CreateLogFilesInMainDirectory", true);
            MaxLogsFiles = settings.GetInteger("Main", "MaxLogsFiles", 5);

            SwitchCursorKey = settings.GetValue("Main", "SwitchCursorKey", "Control+F8");
            OpenManagerWindowKey = settings.GetValue("Main", "OpenManagerWindowKey", "Control+F10");

            // Section: Scripts
            PauseScriptExecutionWhenNotInFocus = settings.GetBoolean("Scripts", "PauseExecutionWhenNotInFocus", true);
            DoNotLoadLegacyScripts = settings.GetBoolean("Scripts", "DoNotLoadLegacyScripts", true);
            ReloadScriptsOnReload = settings.GetBoolean("Scripts", "ReloadScriptsOnReload", false);

            // Section: Console
            ConsoleOpenCloseKey = settings.GetKey("Console", "OpenCloseKey", Keys.F4);

            // Section: API
            AllowRemoteConnections = settings.GetBoolean("API", "AllowConnections", false);
            ShowNotificationOnConnection = settings.GetBoolean("API", "ShowNotificationOnConnection", true);
            ServerPort = (ushort)settings.GetInteger("API", "PortOverride", 57315);
            MaxServerClients = (ushort)settings.GetInteger("API", "MaxClientsOverride", 1);
            AllowRemoteReloadScripts = settings.GetBoolean("API", "AllowRemoteReloadScripts", true);
            AllowRemoteLoadScripts = settings.GetBoolean("API", "AllowRemoteLoadScripts", true);
            AllowRemoteAbortScripts = settings.GetBoolean("API", "AllowRemoteAbortScripts", true);

            AllowRemoteNativeFunctionCalls = settings.GetBoolean("API", "AllowRemoteNativeFunctionCalls", true);
        }

        public static bool SaveSettings()
        {
            // Section: Main
            theSettingsFile.SetBoolean("Main", "CreateLogFilesInMainDirectory", CreateLogFilesInMainDirectory);
            theSettingsFile.SetInteger("Main", "MaxLogsFiles", MaxLogsFiles);

            theSettingsFile.SetValue("Main", "SwitchCursorKey", SwitchCursorKey);
            theSettingsFile.SetValue("Main", "OpenManagerWindowKey", OpenManagerWindowKey);

            // Section: Scripts
            theSettingsFile.SetBoolean("Scripts", "PauseExecutionWhenNotInFocus", PauseScriptExecutionWhenNotInFocus);
            theSettingsFile.SetBoolean("Scripts", "DoNotLoadLegacyScripts", DoNotLoadLegacyScripts);
            theSettingsFile.SetBoolean("Scripts", "ReloadScriptsOnReload", ReloadScriptsOnReload);

            // Section: Console
            theSettingsFile.SetKey("Console", "OpenCloseKey", ConsoleOpenCloseKey);

            // Section: API
            theSettingsFile.SetBoolean("API", "AllowConnections", AllowRemoteConnections);
            theSettingsFile.SetBoolean("API", "ShowNotificationOnConnection", ShowNotificationOnConnection);
            theSettingsFile.SetInteger("API", "PortOverride", ServerPort);
            theSettingsFile.SetInteger("API", "MaxClientsOverride", MaxServerClients);
            theSettingsFile.SetBoolean("API", "AllowRemoteReloadScripts", AllowRemoteReloadScripts);
            theSettingsFile.SetBoolean("API", "AllowRemoteLoadScripts", AllowRemoteLoadScripts);
            theSettingsFile.SetBoolean("API", "AllowRemoteAbortScripts", AllowRemoteAbortScripts);
            theSettingsFile.SetBoolean("API", "AllowRemoteNativeFunctionCalls", AllowRemoteNativeFunctionCalls);

            return theSettingsFile.Save();
        }
        public static void RestoreDefaults()
        {
            // Section: Main
            CreateLogFilesInMainDirectory = true;
            MaxLogsFiles = 5;

            SwitchCursorKey = "Control+F8";
            OpenManagerWindowKey = "Control+F10";

            // Section: Scripts
            PauseScriptExecutionWhenNotInFocus = true;
            DoNotLoadLegacyScripts = true;
            ReloadScriptsOnReload = false;

            // Section: Console
            ConsoleOpenCloseKey = Keys.F4;

            // Section: API
            AllowRemoteConnections = false;
            ShowNotificationOnConnection = true;
            ServerPort = 57315;
            MaxServerClients = 1;
            AllowRemoteReloadScripts = true;
            AllowRemoteLoadScripts = true;
            AllowRemoteAbortScripts = true;
            AllowRemoteNativeFunctionCalls = true;
        }

    }
}