# FAQ / Q&A

Frequently Asked Questions about **IV-SDK .NET**.

---

### ❓ What is IV-SDK .NET?

IV-SDK .NET is a framework that lets you run custom scripts in GTA IV using .NET languages like C# and VB.NET.

---

### ❓ What version of GTA IV is supported?

Currently, IV-SDK .NET only has support for version 1.0.8.0 and 1.0.7.0 of GTA IV.

---

### ❓ Will IV-SDK .NET ever get support for the latest versions of GTA IV?

Ideally yes, but I can't do it alone. There are people out there who are great at reverse engineering, if you happen to be one of them, and want to help with this process, feel free to contact me! Or if you know someone, feel free to ask them if they wanna help!

---

### ❓ Can IV-SDK .NET load ScriptHookDotNet scripts?

Yes! Version [1.2](https://github.com/ClonkAndre/IV-SDK-DotNet/releases/tag/1.2) of IV-SDK .NET introduced experimental loading of ScriptHookDotNet scripts, which has since kept on improving, and will continue on improving.

---

### ❓ Where do I put my scripts?

Place your compiled IV-SDK .NET scripts (`.ivsdk.dll`) in the `scripts` folder which can be found in the `IVSDKDotNet` directory within the game directory.  
For ScriptHookDotNet scripts, place the compiled scripts (`.net.dll`) in the `scripts` folder within the game directory. Raw scripts such as `.vb` or `.cs` are currently not supported by IV-SDK .NET.

---

### ❓ I'm getting a message about a detected incompability with ScriptHookDotNet. What should I do?

Since IV-SDK .NET ships with its own, modified version of ScriptHookDotNet.dll, you generally dont need the old ScriptHookDotNet loader anymore.  
Decide if you want to use the old ScriptHookDotNet loader (older, potentionally slower and unstable), or the newer ScriptHookDotNet loader of IV-SDK .NET and continue with either section below.  

🧓🏽 *I want to use the old ScriptHookDotNet loader*:
1. Set `LoadScriptHookDotNetScripts` to `false` in the IV-SDK .NET `config.ini` file inside the `IVSDKDotNet` directory within the game directory.

✅ After you've done that, IV-SDK .NET and ScriptHookDotNet should now both run simultaneously.

🫅🏽 *I want to use the ScriptHookDotNet loader of IV-SDK .NET*:
1. Remove the following files from your game directory: `ScriptHookDotNet.dll` and `ScriptHookDotNet.asi`  
ℹ️ Note that some ScriptHookDotNet mods require the `ScriptHook.dll` and `AdvancedHook.dll`/`AdvancedHookInit.asi` libraries, so you should keep those.
2. Make sure `LoadScriptHookDotNetScripts` is set to `true` in the IV-SDK .NET `config.ini` file inside the `IVSDKDotNet` directory within the game directory.

✅ After you've done that, IV-SDK .NET should now take care of loading and managing your ScriptHookDotNet scripts.

---

### ❓ My game crashes after installing IV-SDK .NET. What should I do?

1. Make sure you have all prerequisites installed (see [Installation Guide](Installation.md)).
2. Double-check file locations.
3. Check the `IVSDKDotNet.log` file for error messages.

---

### ❓ Can I write scripts in languages other than C#?

Yes! Any .NET language that compiles to a compatible `.dll` should work (e.g., VB.NET).

---

### ❓ How do I open the ConsoleUI or ManagerUI?

See [ConsoleUI Introduction](ConsoleUI.md) and [ManagerUI Introduction](ManagerUI.md) for details.

---

### ❓ Where can I get help or report bugs?

Please open an issue on the [GitHub Issues page](https://github.com/ClonkAndre/IV-SDK-DotNet/issues).  
Additionally, you can join my [discord server](https://discord.gg/QtAgvkMeJ5) and ask for help in the #help channel. Make sure to check out the #support and #modding-help forum too because your question might already be answered.

---

[Back to Home](Home.md)