using System;
using System.Collections.Generic;

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
        public static bool WereScriptHookDotNetScriptsLoadedThisSession;

        // Other
        public static Script CurrentConstructingScript;
        public static Script CurrentTickScript;
        public static Script CurrentMouseDownScript;
        public static Script CurrentMouseUpScript;
        public static Script CurrentScriptCommandScript;
        public static Script CurrentPerFrameDrawingScript;
        #endregion
        
        public static void Init()
        {
            FontsToBeCreated = new Queue<Font>();
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

    }
}
