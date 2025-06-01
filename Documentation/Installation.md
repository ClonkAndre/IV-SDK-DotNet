# Installation Guide

Follow these steps to install **IV-SDK .NET** and start running custom scripts in GTA IV.

---

### 1. Prerequisites

- A legal copy of Grand Theft Auto IV version 1.0.8.0 or 1.0.7.0
- [ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases)
- [.NET Framework 4.7.2 or higher](https://dotnet.microsoft.com/en-us/download/dotnet-framework)
- [All-in-one x86 Visual C++ Redistributable Runtimes](https://github.com/abbodi1406/vcredist/releases)
- [DirectX June 2010](https://www.microsoft.com/en-us/download/details.aspx?id=8109)

### ℹ️ Notes
- .NET Framework 4.7.2 comes preinstalled with Windows 10 version 1809 and higher.
- When downgraded using the [GTA IV Downgrader](https://gtaforums.com/topic/976691-gta-iv-downgrader), you should already have an ASI Loader, the Visual C++ Redistributables and DirectX (as long as you chose to install them).

---

### 2. Download IV-SDK .NET

- Download the latest release from the [IV-SDK .NET Releases](https://github.com/ClonkAndre/IV-SDK-DotNet/releases) page.

### ℹ️ Notes
- Some mods may also require the [ClonksCodingLib.GTAIV.dll](https://github.com/ClonkAndre/ClonksCodingLib.GTAIV/releases) library. Always check the mod page on what kind of dependencies it has.

---

### 3. Installation Steps

1. **Extract the files:**  
   Unzip the downloaded archive.

2. **Copy files:**  
   Copy all contents from the archive into your GTA IV game directory (where `GTAIV.exe` is located).

3. **First Run:**  
   Launch GTA IV as usual.  
   If installed correctly, you should see a popup appearing if this is your first time running IV-SDK .NET.

---

### 4. Running Scripts

- IV-SDK .NET scripts can be distinguished by the `.ivsdk.dll` extension, place them into the `scripts` folder, which can be found within the `IVSDKDotNet` directory within the game directory.

### ℹ️ Notes
- Since version [1.2](https://github.com/ClonkAndre/IV-SDK-DotNet/releases/tag/1.2) of IV-SDK .NET, it is now possible to also load ScriptHookDotNet scripts. For more information, check out the [FAQ](FAQ.md) page.

---

### 5. Troubleshooting

- **Game crashes or fails to start?**
  - Try running GTA IV again.
  - Ensure all prerequisites are installed.
  - Ensure you installed IV-SDK .NET on a version of GTA IV which is supported.
  - Check that files are in the correct directory.
  - Try running as Administrator.
- **Scripts not loading?**
  - Ensure the scripts you are trying to load are valid IV-SDK .NET scripts.
  - Check the `IVSDKDotNet.log` file within the game directory for error messages.

---

### 6. Updating IV-SDK .NET

- Overwrite old files with new ones from each release.
- Always make backups!

---

[Back to Home](Home.md)