# The IV-SDK .NET Configuration file (`config.ini`)

The `config.ini` file controls the core settings and behavior of **IV-SDK .NET**.  
It is located in your `IVSDKDotNet` directory inside GTA IV's main folder.  
This page explains each section and option in detail so you can customize IV-SDK .NET to your needs.

---

### `[DEBUG]` Section

| Option                          | Default   | Description                                                                                   |
|----------------------------------|-----------|-----------------------------------------------------------------------------------------------|
| `LaunchDebugger`                 | false     | If true, launches the debugger on startup (for development/troubleshooting).                  |
| `DisablePluginsLoadOnStartup`    | false     | If true, prevents all plugins from loading automatically at startup.                          |
| `DisableScriptLoadOnStartup`     | false     | If true, prevents all scripts from loading automatically at startup.                          |

---

### `[Main]` Section

| Option                            | Default   | Description                                                                                                           |
|------------------------------------|-----------|-----------------------------------------------------------------------------------------------------------------------|
| `CreateLogFilesInMainDirectory`    | true      | If true, log files are in GTA IV’s main directory as `IVSDKDotNet.log`. If false, they are in `IVSDKDotNet/logs`.   |                           |
| `EnableAutomaticUpdateCheck`       | true      | If true, the Manager periodically checks for new IV-SDK .NET releases.                                                |

---

### `[Keys]` Section

Defines hotkeys for interacting with IV-SDK .NET.  
You can use [any valid key name](https://docs.microsoft.com/en-us/dotnet/api/system.windows.forms.keys?view=windowsdesktop-6.0) and combine with modifiers (`Control`, `Alt`, `Shift`).

| Option                 | Default     | Description                                                                                                    |
|------------------------|------------------|----------------------------------------------------------------------------------------------------------------|
| `SwitchCursorKey`      | Control+F8       | Show/hide the mouse cursor for script windows, ConsoleUI, and ManagerUI. Disables GTA IV mouse input if shown. |
| `OpenManagerWindowKey` | Control+F10      | Open/close the IV-SDK .NET Manager window.                                                                     |
| `OpenConsoleKey`       | F4               | Open/close the in-game ConsoleUI.                                                                              |
| `ReloadScriptsKey`     | Control+F11      | Reload all scripts at once.                                                                                    |

---

### `[Scripts]` Section

Script loading and compatibility options.

| Option                      | Default | Description                                                                                                               |
|-----------------------------|---------|---------------------------------------------------------------------------------------------------------------------------|
| `AllowScriptsToForceNoAbort`| true    | If true, scripts with this property cannot be aborted by global abort commands (they act more like ASI mods).             |
| `PauseExecutionWhenNotInFocus` | true | Pauses all scripts when GTA IV loses window focus (e.g., alt-tab).                                                        |
| `DoNotLoadLegacyScripts`    | false   | If true, blocks loading of scripts built with old IVSDKDotNetWrapper versions. Shows a notification if blocked.           |
| `ReloadScriptsOnReload`     | false   | If true, reloads all scripts when loading a save, starting a new game, or switching episodes.                             |
| `LoadScriptHookDotNetScripts` | true  | If true, loads ScriptHookDotNet mods from the main `scripts` folder.                                                      |

---

### `[Plugins]` Section

| Option              | Default | Description                                                                                           |
|---------------------|---------|-------------------------------------------------------------------------------------------------------|
| `AllowPluginLoading`| true    | If true, loads IV-SDK .NET Manager plugins from `IVSDKDotNet/plugins`. Accessible in ManagerUI.        |

---

### `[Notification]` Section

| Option               | Default | Description                                                                                     |
|----------------------|---------|-------------------------------------------------------------------------------------------------|
| `ShowNotifications`  | true    | If false, disables all on-screen notifications. Not recommended, as you may miss important info. |

---

### `[Style]` Section

Customize the look and feel of IV-SDK .NET windows.

| Option                              | Default | Description                                                                                 |
|--------------------------------------|---------|---------------------------------------------------------------------------------------------|
| `ImGuiStyle`                        | dark    | Sets ImGui window style. Options: `dark`, `classic`, `light`.                               |
| `UseCustomThemeForManagerAndConsole` | true    | If true, Manager and Console windows use a custom theme rather than the above style.         |
| `GlobalFontScale` | 1.0    | Adjusts the scale of all fonts in ImGui-based windows (e.g., Manager and Console).         |

---

### `[API]` Section

Controls the in-game API for external tools or integrations.

| Option                           | Default | Description                                                                                                     |
|-----------------------------------|---------|-----------------------------------------------------------------------------------------------------------------|
| `AllowConnections`                | false   | If true, allows apps to connect to the Manager via API (e.g., to see running scripts, reload them, etc.).      |
| `ShowNotificationOnConnection`    | true    | If true, notifies you when an external app connects via API.                                                    |
| `AllowRemoteReloadScripts`        | true    | If true, external API clients can reload scripts.                                                               |
| `AllowRemoteLoadScripts`          | true    | If true, external API clients can load scripts.                                                                 |
| `AllowRemoteAbortScripts`         | true    | If true, external API clients can abort scripts.                                                                |
| `AllowRemoteNativeFunctionCalls`  | true    | If true, external clients can call GTA IV native functions (e.g., `ADD_EXPLOSION`). Disable for extra security. |

---

## Example: `config.ini`

```ini
[DEBUG]
LaunchDebugger=false
DisablePluginsLoadOnStartup=false
DisableScriptLoadOnStartup=false

[Main]
CreateLogFilesInMainDirectory=true
EnableAutomaticUpdateCheck=true

[Keys]
SwitchCursorKey=Control+F8
OpenManagerWindowKey=Control+F10
OpenConsoleKey=F4
ReloadScriptsKey=Control+F11

[Scripts]
AllowScriptsToForceNoAbort=true
PauseExecutionWhenNotInFocus=true
DoNotLoadLegacyScripts=false
ReloadScriptsOnReload=false
LoadScriptHookDotNetScripts=true

[Plugins]
AllowPluginLoading=true

[Notification]
ShowNotifications=true

[Style]
ImGuiStyle=dark
UseCustomThemeForManagerAndConsole=true
GlobalFontScale=1.0

[API]
AllowConnections=false
ShowNotificationOnConnection=true
AllowRemoteReloadScripts=true
AllowRemoteLoadScripts=true
AllowRemoteAbortScripts=true
AllowRemoteNativeFunctionCalls=true
```

---

## 📝 Tips

- Lines starting with `;` are comments and are ignored by IV-SDK .NET.
- For valid key names, see [Microsoft's documentation](https://docs.microsoft.com/en-us/dotnet/api/system.windows.forms.keys?view=windowsdesktop-6.0).
- For more info about the ScriptHookDotNet mod loader from IV-SDK .NET, see the [FAQ](FAQ.md).

---

[Back to Home](Home.md)