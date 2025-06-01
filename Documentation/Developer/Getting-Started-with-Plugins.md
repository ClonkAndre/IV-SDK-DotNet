# Getting Started for Developers

This guide will help you set up your development environment and create your first plugin for the IV-SDK .NET [ManagerUI](../ManagerUI.md).

---

### 🛠️ Prerequisites

- **.NET Framework 4.7.2 or higher**  
- **Visual Studio 2019/2022** (recommended)
- Basic knowledge of **C#** or **VB.NET**

---

### 📦 Project Setup
### ℹ️ Check out the IV-SDK .NET Templates down below to get started even quicker!

### 1. Create a Class Library

1. Open Visual Studio.
2. Create a new **Class Library (.NET Framework)** project.
3. Target **.NET Framework 4.7.2 or higher**.

### 2. Reference IVSDKDotNetWrapper.dll

In order to start creating plugins for the IV-SDK .NET Manager, we need to reference the `IVSDKDotNetWrapper.dll` (shipped with your IV-SDK .NET installation) to the project.  
You can either manually search for the `IVSDKDotNetWrapper.dll` file on your system, or use `NuGet`, which will take care of adding the reference, and also allows you to easily update to newer versions of the `IVSDKDotNetWrapper.dll`.

- **Manual reference**: Right-click your project in the **Solution Explorer**, `Add` -> `Reference...` -> Browse and select the `IVSDKDotNetWrapper.dll` file (Usually found in your GTA IV installation), click on `OK`.
- **Using NuGet**: Right-click your project in the **Solution Explorer**, `Manage NuGet Packages...` -> Browse for `IVSDKDotNet` and install the latest package. Visual Studio will now take care of the rest.

### 3. Add the `.plug` extension to your assembly name

To not have to manually add the `.plug` extension to our compiled dll file everytime we build our project, right-click your project in the **Solution Explorer**, `Properties` -> `Application` now add the `.plug` suffix to the `Assembly name` (e.g. MyPlugin.plug).  
The `.plug` extension will tell IV-SDK .NET that this file is a plugin for the IV-SDK .NET Manager.

### 4. Basic Plugin Example

```C#
using System;
using IVSDKDotNet;
using IVSDKDotNet.Manager;

public class Class1 : ManagerPlugin // <- It's very important that we add ": ManagerPlugin" here! This will tell IV-SDK .NET that this class is the entry-point of our plugin.
{
    public Class1() : base("DISPLAY_NAME", "AUTHOR_NAME")
    {
        OnImGuiGlobalRendering  += Class1_OnImGuiGlobalRendering;
        OnImGuiManagerRendering += Class1_OnImGuiManagerRendering;
    }

    private void Class1_OnImGuiGlobalRendering(IntPtr devicePtr, ImGuiIV_DrawingContext ctx)
    {
        // In here you can use ImGui as you would normally use it...

        // Example:
        if (ImGuiIV.Begin("TestPluginWindow"))
        {
            ImGuiIV.TextUnformatted("Hello");
        }
        ImGuiIV.End();
    }
    private void Class1_OnImGuiManagerRendering(IntPtr devicePtr)
    {
        // In here you can directly use ImGui widgets as they will be shown within the plugin's collapsing header within the IV-SDK .NET Manager "Plugins" tab.
        ImGuiIV.Text("This will show up in the 'DISPLAY_NAME by AUTHOR_NAME' collapsing header within the IV-SDK .NET Manager Plugins tab.");
    }
}
```

### ℹ️ It is good practice to rename `Class1` to something more obvious like `Main`, so we know that this is the Main class.

### 5. Compiling
1. Press <kbd>Control+B</kbd> (default Visual Studio keybind), or right-click your project in the **Solution Explorer** and hit `Build`.
2. Place the resulting `.plug.dll` file into the `plugins` folder which can be found in the `IVSDKDotNet` directory within the game directory.  

---

### ⚡ Running Your Plugin

1. Start GTA IV, and if everything went correctly, the plugin should now be loaded!
2. To interact with your plugin, check out the `Plugins` tab within the [ManagerUI](../ManagerUI.md).

---

### 🚀 Visual Studio Templates (Coming Soon!)

We're working on creating official **Visual Studio project templates** to make starting new plugins even easier.  
**TODO:** Link to the templates once they are available.

---

### 🧑‍💻 Tips

- Use the in-game console for output and debugging.
- Feel free to get inspired by other IV-SDK .NET plugins on [GitHub](https://github.com/topics/iv-sdk-net).

---

[Back to Home](../Home.md)