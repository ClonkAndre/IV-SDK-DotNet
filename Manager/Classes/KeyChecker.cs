using System;
using System.Windows.Forms;

using Manager.UI;

namespace Manager.Classes
{
    /// <summary>
    /// Contains key checks seperated from the Main.cs file to keep it a bit clean.
    /// </summary>
    internal class KeyChecker
    {

        #region Functions
        /// <summary>
        /// Checks if a key was pressed. This also supports modifier keys.
        /// </summary>
        /// <param name="keyString">The key string to check for. Example: Control+F10</param>
        /// <param name="e">The args which store the key press data.</param>
        /// <returns>true if the key was pressed. Otherwise, false.</returns>
        private static bool CheckIsKeyPressed(string keyString, KeyEventArgs e)
        {
            Keys parsedModifier = Keys.None;
            Keys parsedKey = Keys.None;

            if (keyString.Contains("+"))
            {
                string[] arr = keyString.Split('+');

                if (Enum.TryParse(arr[0], out Keys result))
                    parsedModifier = result;
                if (Enum.TryParse(arr[1], out Keys result2))
                    parsedKey = result2;
            }
            else
            {
                if (Enum.TryParse(keyString, out Keys result))
                    parsedKey = result;
            }

            if (parsedModifier != Keys.None)
            {
                if (e.Modifiers == parsedModifier && e.KeyCode == parsedKey)
                    return true;
            }
            else
            {
                if (e.KeyCode == parsedKey)
                    return true;
            }

            return false;
        }
        #endregion

        public static void CheckAll(KeyEventArgs e)
        {
            CheckSwitchCursorKeyPressed(e);
            CheckOpenManagerWindowKeyPressed(e);
            CheckOpenConsoleKeyPressed(e);
            CheckReloadScriptsKeyPressed(e);
        }

        public static void CheckSwitchCursorKeyPressed(KeyEventArgs e)
        {
            //Keys switchCursorModifier = Keys.None;
            //Keys switchCursorKey = Keys.None;

            //if (Config.SwitchCursorKey.Contains("+"))
            //{
            //    string[] arr = Config.SwitchCursorKey.Split('+');
                
            //    if (Enum.TryParse(arr[0], out Keys result))
            //        switchCursorModifier = result;
            //    if (Enum.TryParse(arr[1], out Keys result2))
            //        switchCursorKey = result2;
            //}
            //else
            //{
            //    if (Enum.TryParse(Config.SwitchCursorKey, out Keys result))
            //        switchCursorKey = result;
            //}

            //if (switchCursorModifier != Keys.None)
            //{
            //    if (e.Modifiers == switchCursorModifier && e.KeyCode == switchCursorKey)
            //        Main.Instance.SwitchImGuiForceCursorProperty = true;
            //}
            //else
            //{
            //    if (e.KeyCode == switchCursorKey)
            //        Main.Instance.SwitchImGuiForceCursorProperty = true;
            //}

            if (CheckIsKeyPressed(Config.SwitchCursorKey, e))
                Main.Instance.SwitchImGuiForceCursorProperty = true;
        }
        public static void CheckOpenManagerWindowKeyPressed(KeyEventArgs e)
        {
            if (CheckIsKeyPressed(Config.OpenManagerWindowKey, e))
                ManagerUI.IsConfigUIOpened = !ManagerUI.IsConfigUIOpened;
        }
        public static void CheckOpenConsoleKeyPressed(KeyEventArgs e)
        {
            if (CheckIsKeyPressed(Config.OpenConsoleKey, e))
                ConsoleUI.ToggleConsole();
        }
        public static void CheckReloadScriptsKeyPressed(KeyEventArgs e)
        {
            if (CheckIsKeyPressed(Config.ReloadScriptsKey, e))
            {
                Main.Instance.LoadScripts();
                NotificationUI.ShowNotification(NotificationType.Info, DateTime.UtcNow.AddSeconds(3.5d), "Scripts reloaded", "All scripts were reloaded by hotkey.", "RELOADED_SCRIPTS_BY_HOTKEY");
            }
        }

    }
}
