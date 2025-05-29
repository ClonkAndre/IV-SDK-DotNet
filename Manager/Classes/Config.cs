using IVSDKDotNet;

namespace Manager.Classes
{
    internal class Config
    {

        #region Variables
        private static SettingsFile theSettingsFile;

        // DEBUG
        public static bool LaunchDebugger;
        public static bool DisablePluginsLoadOnStartup;
        public static bool DisableScriptLoadOnStartup;

        // Main
        public static bool CreateLogFilesInMainDirectory;
        public static bool EnableAutomaticUpdateCheck;

        // Keys
        public static string SwitchCursorKey;
        public static string OpenManagerWindowKey;
        public static string OpenConsoleKey;
        public static string ReloadScriptsKey;

        // Scripts
        public static bool AllowScriptsToForceNoAbort;
        public static bool PauseScriptExecutionWhenNotInFocus;
        public static bool DoNotLoadLegacyScripts;
        public static bool ReloadScriptsOnReload;
        public static bool LoadScriptHookDotNetScripts;

        // Plugins
        public static bool AllowPluginLoading;

        // Notification
        public static bool ShowNotifications;

        // Style
        public static string ImGuiStyle;
        public static bool UseCustomThemeForManagerAndConsole;

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

            // Section: DEBUG
            LaunchDebugger =                settings.GetBoolean("DEBUG", "LaunchDebugger", false);
            DisablePluginsLoadOnStartup =   settings.GetBoolean("DEBUG", "DisablePluginsLoadOnStartup", false);
            DisableScriptLoadOnStartup =    settings.GetBoolean("DEBUG", "DisableScriptLoadOnStartup", false);

            // Section: Main
            CreateLogFilesInMainDirectory = settings.GetBoolean("Main", "CreateLogFilesInMainDirectory", true);
            EnableAutomaticUpdateCheck =    settings.GetBoolean("Main", "EnableAutomaticUpdateCheck", true);

            // Section: Keys
            SwitchCursorKey =           settings.GetValue("Keys", "SwitchCursorKey", "Control+F8");
            OpenManagerWindowKey =      settings.GetValue("Keys", "OpenManagerWindowKey", "Control+F10");
            OpenConsoleKey =            settings.GetValue("Keys", "OpenConsoleKey", "F4");
            ReloadScriptsKey =          settings.GetValue("Keys", "ReloadScriptsKey", "Control+F11");

            // Section: Scripts
            AllowScriptsToForceNoAbort =            settings.GetBoolean("Scripts", "AllowScriptsToForceNoAbort", true);
            PauseScriptExecutionWhenNotInFocus =    settings.GetBoolean("Scripts", "PauseExecutionWhenNotInFocus", true);
            DoNotLoadLegacyScripts =                settings.GetBoolean("Scripts", "DoNotLoadLegacyScripts", false);
            ReloadScriptsOnReload =                 settings.GetBoolean("Scripts", "ReloadScriptsOnReload", false);
            LoadScriptHookDotNetScripts =           settings.GetBoolean("Scripts", "LoadScriptHookDotNetScripts", true);

            // Section: Plugins
            AllowPluginLoading = settings.GetBoolean("Plugins", "AllowPluginLoading", true);

            // Section: Notification
            ShowNotifications = settings.GetBoolean("Notification", "ShowNotifications", true);

            // Section: Style
            ImGuiStyle =                            settings.GetValue("Style", "ImGuiStyle", "dark");
            UseCustomThemeForManagerAndConsole =    settings.GetBoolean("Style", "UseCustomThemeForManagerAndConsole", true);

            // Section: API
            AllowRemoteConnections =            settings.GetBoolean("API", "AllowConnections", false);
            ShowNotificationOnConnection =      settings.GetBoolean("API", "ShowNotificationOnConnection", true);
            ServerPort =                (ushort)settings.GetInteger("API", "PortOverride", 57315);
            MaxServerClients =          (ushort)settings.GetInteger("API", "MaxClientsOverride", 1);
            AllowRemoteReloadScripts =          settings.GetBoolean("API", "AllowRemoteReloadScripts", true);
            AllowRemoteLoadScripts =            settings.GetBoolean("API", "AllowRemoteLoadScripts", true);
            AllowRemoteAbortScripts =           settings.GetBoolean("API", "AllowRemoteAbortScripts", true);

            AllowRemoteNativeFunctionCalls =    settings.GetBoolean("API", "AllowRemoteNativeFunctionCalls", true);
        }

        public static bool SaveSettings()
        {
            // Section: Main
            theSettingsFile.SetBoolean("Main", "CreateLogFilesInMainDirectory", CreateLogFilesInMainDirectory);
            theSettingsFile.SetBoolean("Main", "EnableAutomaticUpdateCheck", EnableAutomaticUpdateCheck);

            // Section: Keys
            theSettingsFile.SetValue("Keys", "SwitchCursorKey", SwitchCursorKey);
            theSettingsFile.SetValue("Keys", "OpenManagerWindowKey", OpenManagerWindowKey);
            theSettingsFile.SetValue("Keys", "OpenConsoleKey", OpenConsoleKey);
            theSettingsFile.SetValue("Keys", "ReloadScriptsKey", ReloadScriptsKey);

            // Section: Scripts
            theSettingsFile.SetBoolean("Scripts", "AllowScriptsToForceNoAbort", AllowScriptsToForceNoAbort);
            theSettingsFile.SetBoolean("Scripts", "PauseExecutionWhenNotInFocus", PauseScriptExecutionWhenNotInFocus);
            theSettingsFile.SetBoolean("Scripts", "DoNotLoadLegacyScripts", DoNotLoadLegacyScripts);
            theSettingsFile.SetBoolean("Scripts", "ReloadScriptsOnReload", ReloadScriptsOnReload);
            theSettingsFile.SetBoolean("Scripts", "LoadScriptHookDotNetScripts", LoadScriptHookDotNetScripts);

            // Section: Plugins
            theSettingsFile.SetBoolean("Plugins", "AllowPluginLoading", AllowPluginLoading);

            // Section: Notification
            theSettingsFile.SetBoolean("Notification", "ShowNotifications", ShowNotifications);

            // Section: Style
            theSettingsFile.SetValue("Style", "ImGuiStyle", ImGuiStyle);
            theSettingsFile.SetBoolean("Style", "UseCustomThemeForManagerAndConsole", UseCustomThemeForManagerAndConsole);

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

            // Section: Keys
            SwitchCursorKey = "Control+F8";
            OpenManagerWindowKey = "Control+F10";
            OpenConsoleKey = "F4";
            ReloadScriptsKey = "Control+F11";

            // Section: Scripts
            AllowScriptsToForceNoAbort = true;
            PauseScriptExecutionWhenNotInFocus = true;
            DoNotLoadLegacyScripts = false;
            ReloadScriptsOnReload = false;
            LoadScriptHookDotNetScripts = true;

            // Section: Plugins
            AllowPluginLoading = true;

            // Section: Notification
            ShowNotifications = true;

            // Section: Style
            ImGuiStyle = "dark";
            UseCustomThemeForManagerAndConsole = true;

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