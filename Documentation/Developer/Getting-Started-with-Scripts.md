# Getting Started for Developers

Welcome to scripting with **IV-SDK .NET**!  
This guide will help you set up your development environment and create your first script for Grand Theft Auto IV.

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

In order to start creating scripts for IV-SDK .NET, we need to reference the `IVSDKDotNetWrapper.dll` (shipped with your IV-SDK .NET installation) to the project.  
You can either manually search for the `IVSDKDotNetWrapper.dll` file on your system, or use `NuGet`, which will take care of adding the reference, and also allows you to easily update to newer versions of the `IVSDKDotNetWrapper.dll`.

- **Manual reference**: Right-click your project in the **Solution Explorer**, `Add` -> `Reference...` -> Browse and select the `IVSDKDotNetWrapper.dll` file (Usually found in your GTA IV installation), click on `OK`.
- **Using NuGet**: Right-click your project in the **Solution Explorer**, `Manage NuGet Packages...` -> Browse for `IVSDKDotNet` and install the latest package. Visual Studio will now take care of the rest.

### 3. Add the `.ivsdk` extension to your assembly name

To not have to manually add the `.ivsdk` extension to our compiled dll file everytime we build our project, right-click your project in the **Solution Explorer**, `Properties` -> `Application` now add the `.ivsdk` suffix to the `Assembly name` (e.g. MyScript.ivsdk).  
The `.ivsdk` extension will tell IV-SDK .NET that this file is a IV-SDK .NET script.

### 4. Basic Script Example

```C#
using System;
using IVSDKDotNet;

public class Class1 : Script // <- It's very important that we add ": Script" here! This will tell IV-SDK .NET that this class is the entry-point of our script.
{
  public Class1()
  {
    // Subscribing to the "Tick" event
    Tick += Class1_Tick;
  }

  public void Class1_Tick(object sender, EventArgs e)
  {
    // This code runs every game tick!
    ShowSubtitleMessage("Hello from IV-SDK .NET!");
  }
}
```

### ℹ️ It is good practice to rename `Class1` to something more obvious like `Main`, so we know that this is the Main class.

### 5. Compiling
1. Press <kbd>Control+B</kbd> (default Visual Studio keybind), or right-click your project in the **Solution Explorer** and hit `Build`.
2. Place the resulting `.ivsdk.dll` file into the `scripts` folder which can be found in the `IVSDKDotNet` directory within the game directory.  

---

### ⚡ Running Your Script

1. Start GTA IV, and if everything went correctly, the script should now be loaded!
2. Use the in-game [ConsoleUI](../ConsoleUI.md) or [ManagerUI](../ManagerUI.md) to load, unload, or reload your script dynamically.

---

### 🚀 Visual Studio Templates (Coming Soon!)

We're working on creating official **Visual Studio project templates** to make starting new scripts even easier.  
**TODO:** Link to the templates once they are available.

---

### 🧑‍💻 Tips

- Use the [Public Fields Window](Public-Fields-Window.md) for real-time inspection and modification of your script's public fields.
- Use the in-game console for output and debugging.
- You can find all available native functions of GTA IV on [Pastebin](https://pastebin.com/H77F9V38), and on [GTAMods Wiki](https://gtamods.com/wiki/List_of_native_functions_(GTA_IV)), where most of them are even documented.
- Feel free to get inspired by other IV-SDK .NET scripts on [GitHub](https://github.com/topics/iv-sdk-net).

---

[Back to Home](../Home.md)