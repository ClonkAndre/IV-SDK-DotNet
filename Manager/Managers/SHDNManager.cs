using System;
using System.Collections.Generic;
using System.Reflection;

using GTA;

using static IVSDKDotNet.Native.Natives;

namespace Manager.Managers
{
    internal static class SHDNManager
    {

        #region Variables
        private static bool wasInitialized;

        // Lists
        private static Queue<Font> fontsToBeCreated;

        // States
        public static bool EnableVerboseLogging;
        public static bool NativeCallLoggingEnabled;

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

        #region Methods
        public static void Init()
        {
            if (wasInitialized)
                return;

            fontsToBeCreated = new Queue<Font>();

            // Get current ScriptHookDotNet Version
            CurrentSHDNVersion = typeof(GTA.Blip).Assembly.GetName().Version;

            wasInitialized = true;
        }
        public static void Shutdown()
        {
            if (!wasInitialized)
                return;

            wasInitialized = false;

            if (fontsToBeCreated != null)
            {
                fontsToBeCreated.Clear();
                fontsToBeCreated = null;
            }
        }

        // Processes all the things for ScriptHookDotNet
        public static void Process()
        {
            if (!wasInitialized)
                return;
            if (CLR.CLRBridge.DisableScriptHookDotNetLoading)
                return;

            // Draw current message
            DrawMessage();

            // Process the content cache
            SHDNContentCacheManager.Process();
        }
        public static void OnBeforeNewImGuiFrame()
        {
            if (!wasInitialized)
                return;

            // Create fonts that wait to be created and added
            while (fontsToBeCreated.Count != 0)
                fontsToBeCreated.Dequeue().Reload();
        }

        public static void AddFont(object obj)
        {
            if (!wasInitialized)
                return;

            fontsToBeCreated.Enqueue(obj as Font);
        }

        public static void SetCurrentScript(int forEvent, object script)
        {
            if (!wasInitialized)
                return;

            switch ((ScriptEvent)forEvent)
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

        // Classic ScriptHookDotNet top-left message
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
            if (!wasInitialized)
                return;
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

        #endregion

        #region Functions
        public static bool LoadIncludedScriptHookDotNetAssembly()
        {
            try
            {
                string path = CLR.CLRBridge.IVSDKDotNetBinaryPath + "\\ScriptHookDotNet.dll";

                Assembly a = Assembly.UnsafeLoadFrom(path);

                if (a != null)
                {
                    Logger.LogDebug("Loaded included ScriptHookDotNet.dll assembly");
                    return true;
                }
            }
            catch (Exception ex)
            {
#if DEBUG
                Helper.WriteToDebugOutput(Priority.High, "FAILED TO LOAD INCLUDED ScriptHookDotNet.dll ASSEMBLY! Details: {0}", ex);
                Helper.BreakInDebugger();
#else
                Logger.LogError("! ! ! Failed to load included ScriptHookDotNet.dll! Make sure it's inside the 'IVSDKDotNet -> bin' directory! Game might crash.");
                Logger.LogErrorEx("Additional Details: {0}", ex);
#endif
            }

            return false;
        }
        public static object GetCurrentScript(int ofEvent)
        {
            if (!wasInitialized)
                return null;

            switch ((ScriptEvent)ofEvent)
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
        #endregion

    }
}
