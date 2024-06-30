using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;

using GTA;

namespace Manager.Classes
{
    internal static class SHDNStuff
    {

        #region Variables
        // Lists
        public static Queue<Font> FontsToBeCreated;

        // States
        public static bool EnableVerboseLogging;
        public static bool NativeCallLoggingEnabled;
        public static bool WereScriptHookDotNetScriptsLoadedThisSession;

        // Other
        public static Script CurrentConstructingScript;
        public static Script CurrentTickScript;
        public static Script CurrentMouseDownScript;
        public static Script CurrentMouseUpScript;
        public static Script CurrentScriptCommandScript;
        public static Script CurrentPerFrameDrawingScript;

        public static Version CurrentSHDNVersion;
        #endregion

        public static void Init()
        {
            FontsToBeCreated = new Queue<Font>();

            // Get current ScriptHookDotNet Version
            CurrentSHDNVersion = typeof(GTA.Blip).Assembly.GetName().Version;
        }
        public static void Cleanup()
        {
            FontsToBeCreated.Clear();
        }

        public static void SetCurrentScript(ScriptEvent forEvent, object script)
        {
            switch (forEvent)
            {
                case ScriptEvent.ctor:
                    CurrentConstructingScript = script as Script;
                    break;
                case ScriptEvent.Tick:
                    CurrentTickScript = script as Script;
                    break;
                case ScriptEvent.MouseDown:
                    CurrentMouseDownScript = script as Script;
                    break;
                case ScriptEvent.MouseUp:
                    CurrentMouseUpScript = script as Script;
                    break;
                case ScriptEvent.ScriptCommand:
                    CurrentScriptCommandScript = script as Script;
                    break;
                case ScriptEvent.PerFrameDrawing:
                    CurrentPerFrameDrawingScript = script as Script;
                    break;
            }
        }
        public static object GetCurrentScript(ScriptEvent ofEvent)
        {
            switch (ofEvent)
            {
                case ScriptEvent.ctor:
                    return CurrentConstructingScript;
                case ScriptEvent.Tick:
                    return CurrentTickScript;
                case ScriptEvent.MouseDown:
                    return CurrentMouseDownScript;
                case ScriptEvent.MouseUp:
                    return CurrentMouseUpScript;
                case ScriptEvent.ScriptCommand:
                    return CurrentScriptCommandScript;
                case ScriptEvent.PerFrameDrawing:
                    return CurrentPerFrameDrawingScript;
            }

            return null;
        }

        public static void ProcessCache()
        {
            if (!CLR.CLRBridge.DisableScriptHookDotNetLoading)
                ContentCache.RemoveNonExisting();
        }

        public static void LoadIncludedScriptHookDotNetAssembly()
        {
            //if (CLR.CLRBridge.DisableScriptHookDotNetLoading)
            //    return;

            try
            {
                string path = CLR.CLRBridge.IVSDKDotNetBinaryPath + "\\ScriptHookDotNet.dll";

                if (File.Exists(path))
                {
                    Assembly a = Assembly.UnsafeLoadFrom(path);

                    if (a != null)
                        Logger.LogDebug("Loaded included ScriptHookDotNet.dll assembly");
                }
            }
            catch (Exception ex)
            {
#if DEBUG
                Helper.WriteToDebugOutput(Priority.High, "FAILED TO LOAD INCLUDED ScriptHookDotNet.dll ASSEMBLY! Details: {0}", ex);
                System.Diagnostics.Debugger.Break();
#else
                Logger.LogWarning("! ! ! WARNING: Failed to load included ScriptHookDotNet.dll! Make sure it's inside the 'IVSDKDotNet -> bin' directory! Game might crash now..");
                Logger.LogWarning("Additional Details: " + ex.ToString());
#endif
            }
        }

    }
}
