using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;

using GTA;

using static IVSDKDotNet.Native.Natives;

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

        // Message
        private static string[] NEW_LINE_CHARS = new string[] { "\r\n", "\r", "\n" };
        private static string theStringToShow;
        private static DateTime messageShowUntil;
        private static bool canShowMessage;

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

        public static void SetMessageTime(int milliseconds)
        {
            messageShowUntil = DateTime.UtcNow.AddMilliseconds(milliseconds);
        }
        public static void SetMessageToShow(string str)
        {
            theStringToShow = str;
        }
        public static void DrawMessage()
        {
            if (string.IsNullOrWhiteSpace(theStringToShow))
                return;

            string str = theStringToShow;

            if (!canShowMessage)
            {
                if (DateTime.UtcNow < messageShowUntil)
                {
                    canShowMessage = true;
                }
                else
                {
                    return;
                }
            }
            else
            {
                if (DateTime.UtcNow > messageShowUntil)
                {
                    canShowMessage = false;
                    return;
                }
            }

            if (str.Length <= 99)
            {
                if (str.Contains("\r\n") || str.Contains("\r") || str.Contains("\n"))
                {
                    string[] parts = str.Split(NEW_LINE_CHARS, StringSplitOptions.None);

                    for (int i = 0; i < parts.Length; i++)
                    {
                        SET_TEXT_SCALE(0.22f, 0.25f);
                        DISPLAY_TEXT_WITH_LITERAL_STRING(0.0048f, 0.0083f + i * 0.022f, "STRING", parts[i]);
                    }
                }
                else
                {
                    SET_TEXT_SCALE(0.22f, 0.25f);
                    DISPLAY_TEXT_WITH_LITERAL_STRING(0.0048f, 0.0083f, "STRING", str);
                }
            }
            else
            {
                // Put the string in a new line until it is below 99
                List<string> newLines = new List<string>();

                while (str.Length > 99)
                {
                    // Get the first 99 chars from the original string
                    string subStr = str.Substring(0, 99);

                    // Check if they contain a line break char
                    string[] parts = subStr.Split(NEW_LINE_CHARS, StringSplitOptions.None);

                    // Check if there were any line break chars splitted
                    if (parts.Length > 0)
                    {
                        // Check if there were any line break chars splitted
                        for (int i = 0; i < parts.Length; i++)
                            newLines.Add(parts[i]);
                    }
                    else
                    {
                        // Add sub string to list
                        newLines.Add(subStr);
                    }

                    // Now actually remove the first 99 chars from the original string
                    str = str.Remove(0, 99);
                }

                // Add the remaining string to the list
                if (str.Length != 0)
                    newLines.Add(str);

                // Draw all the lines
                for (int i = 0; i < newLines.Count; i++)
                {
                    SET_TEXT_SCALE(0.22f, 0.25f);
                    DISPLAY_TEXT_WITH_LITERAL_STRING(0.0048f, 0.0083f + i * 0.022f, "STRING", newLines[i]);
                }
            }
        }

    }
}
