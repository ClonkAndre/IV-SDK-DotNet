using System;
using System.Windows.Forms;

using Manager.UI;

namespace Manager.Classes
{
    /// <summary>
    /// Contains stuff that checks for stuff seperated from the Main.cs file to keep it a bit clean.
    /// </summary>
    internal class Checker
    {

        public static void CheckSwitchCursorKeyPressed(KeyEventArgs e)
        {
            Keys switchCursorModifier = Keys.None;
            Keys switchCursorKey = Keys.None;

            if (Config.SwitchCursorKey.Contains("+"))
            {
                string[] arr = Config.SwitchCursorKey.Split('+');
                
                if (Enum.TryParse(arr[0], out Keys result))
                    switchCursorModifier = result;
                if (Enum.TryParse(arr[1], out Keys result2))
                    switchCursorKey = result2;
            }
            else
            {
                if (Enum.TryParse(Config.SwitchCursorKey, out Keys result))
                    switchCursorKey = result;
            }

            if (switchCursorModifier != Keys.None)
            {
                if (e.Modifiers == switchCursorModifier && e.KeyCode == switchCursorKey)
                    Main.Instance.SwitchImGuiForceCursorProperty = true;
            }
            else
            {
                if (e.KeyCode == switchCursorKey)
                    Main.Instance.SwitchImGuiForceCursorProperty = true;
            }
        }

        public static void CheckOpenManagerWindowKeyPressed(KeyEventArgs e)
        {
            Keys openManagerWindowKeyModifier = Keys.None;
            Keys openManagerWindowKey = Keys.None;

            if (Config.OpenManagerWindowKey.Contains("+"))
            {
                string[] arr = Config.OpenManagerWindowKey.Split('+');

                if (Enum.TryParse(arr[0], out Keys result))
                    openManagerWindowKeyModifier = result;
                if (Enum.TryParse(arr[1], out Keys result2))
                    openManagerWindowKey = result2;
            }
            else
            {
                if (Enum.TryParse(Config.OpenManagerWindowKey, out Keys result))
                    openManagerWindowKey = result;
            }

            if (openManagerWindowKeyModifier != Keys.None)
            {
                if (e.Modifiers == openManagerWindowKeyModifier && e.KeyCode == openManagerWindowKey)
                    ManagerUI.IsConfigUIOpened = !ManagerUI.IsConfigUIOpened;
            }
            else
            {
                if (e.KeyCode == openManagerWindowKey)
                    ManagerUI.IsConfigUIOpened = !ManagerUI.IsConfigUIOpened;
            }
        }

    }
}
