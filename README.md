<p align="center">
  <img width="210" height="200" src="https://user-images.githubusercontent.com/39125931/197342023-e20e0ed9-6082-4635-8b8b-57581fba79ee.png">
</p>

#
IV-SDK .NET is a .NET Wrapper created by [ItsClonkAndre](https://github.com/ClonkAndre) for the original [IV-SDK](https://github.com/Zolika1351/iv-sdk) made by [Zolika1351](https://github.com/Zolika1351).  
It allows you to run and create scripts for GTA IV in any .NET language out there.

## Limitations
Not everything from IV-SDK was ported over to IV-SDK .NET yet. More things will be ported/added from time to time. You can make this process quicker when you fork this project, and create a **[Pull Request](https://github.com/ClonkAndre/IV-SDK-DotNet/pulls)** with the added things.  

## Documentation
Not created yet. Check out the [TestScript](https://github.com/ClonkAndre/IV-SDK-DotNet/tree/main/TestScript) to see how you could create a script.  
  
The process is pretty easy tho: Create a new C# Class Library (choose whatever .NET language you would like to develop a script for), add a reference to **IVSDKDotNetWrapper.dll** and derive your main class from "**IVSDKDotNetWrapper.Script**". If you want to compile the script you have to add **.ivsdk** to your **Assembly name** in the Project **Properties** so it will be compiled as "**YourScript.ivsdk.dll**".  

If you need help with IV-SDK .NET, ask in the [#modding-help](https://discord.com/channels/528764831508070410/1174780962652045384) forum inside our [discord server](https://discord.gg/QtAgvkMeJ5)!

**Very** useful pages for looking up native functions
- https://pastebin.com/n7CAnpZB
- https://gtamods.com/wiki/List_of_native_functions_(GTA_IV)

## Requirements
- IV-SDK .NET requires GTA IV 1080 or 1070 like IV-SDK does. Other versions are not supported.
- ASI loader.
- .NET Framework 4.7.2 (Should be installed on windows 10 version 1803 and up by default)
- Visual C++ 2005 Redistributable x86 which should already be installed on your PC if you've downgraded your game with the [GTA IV Downgrader](https://gtaforums.com/topic/976691-gta-iv-downgrader).
- DirectX June 2010 SDK which should also already be installed on your PC if you've downgraded your game with the [GTA IV Downgrader](https://gtaforums.com/topic/976691-gta-iv-downgrader).

## How to Contribute
Do you have an idea on how to improve IV-SDK .NET? Or did you happen to run into a bug? Please share your idea or the bug you found in the **[issues page](https://github.com/ClonkAndre/IV-SDK-DotNet/issues)**. Or even better: feel free to fork and contribute to this project with a **[Pull Request](https://github.com/ClonkAndre/IV-SDK-DotNet/pulls)**.
