using System;
using System.Collections.Generic;
using System.Drawing;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Text.RegularExpressions;
using System.Threading;
using System.Windows.Forms;

using IVSDKDotNet.Enums;
using IVSDKDotNet.Native;

namespace Manager {
    public class Console {

        #region Variables
        public List<Line> Items;
        public List<string> InputHistory;
        public Dictionary<string, Action<string[]>> Commands;
        private string[] splitStr;

        // Style
        private SizeF TextScale;

        // Input
        public Keys OpenCloseKey;
        private string input;
        private bool showCaret;
        private Guid caretTimerID;

        // Navigation
        public bool IsConsoleVisible;
        private int selectedIndex = 0;
        private int maxItemsVisibleAtOnce = 16;
        private int viewRangeStart = 0, viewRangeEnd = 16;
        private int inputHistoryIndex = -1;

        // Animation
        private uint windowAlpha = 0;
        private int textAlpha = 0;
        #endregion

        #region Struct
        public struct Line
        {
            #region Variables
            public DateTime AddTime;
            public eConsoleLogStyle Style;
            public string Text;
            #endregion

            #region Constructor
            public Line(DateTime addTime, eConsoleLogStyle style, string text)
            {
                AddTime = addTime;
                Style = style;
                Text = text;
            }
            #endregion
        }
        #endregion

        #region Methods
        public void Open()
        {
            if (IsConsoleVisible)
                return;

            IsConsoleVisible = true;
            NavigateToBottom();

            caretTimerID = Main.managerInstance.StartNewTimerInternel(600, () => {
                showCaret = !showCaret;
            });
        }
        public void Close()
        {
            if (!IsConsoleVisible)
                return;

            Main.managerInstance.AbortTaskOrTimer(caretTimerID);

            IsConsoleVisible = false;
            input = string.Empty;
            windowAlpha = 0;
            textAlpha = 0;
            selectedIndex = 0;
            maxItemsVisibleAtOnce = 16;
            viewRangeStart = 0;
            viewRangeEnd = 16;
            inputHistoryIndex = -1;
        }
        public void Clear()
        {
            selectedIndex = 0;
            maxItemsVisibleAtOnce = 16;
            viewRangeStart = 0;
            viewRangeEnd = 16;
            Items.Clear();
        }

        private void WriteLogFile()
        {
            try {
                File.WriteAllLines("IVSDKDotNet.log", Items.Select(x => string.Format("[{0}] {1}", x.AddTime.ToString(), x.Text)));
            }
            catch (Exception) { }
        }

        private void Print(eConsoleLogStyle style, string str)
        {
            if (string.IsNullOrWhiteSpace(str)) {
                Items.Add(new Line(DateTime.UtcNow, style, ""));
                NavigateToBottom();
                return;
            }

            if (str.Length > 98) {

                string correctedStr = str;

                // Do parsing
                do {
                    string tmp = correctedStr.Substring(0, 98);
                    correctedStr = correctedStr.Remove(0, 98);

                    if (tmp.Contains(Environment.NewLine)) { // Contains custom new line character
                        string[] arr = tmp.Split(splitStr, StringSplitOptions.RemoveEmptyEntries);
                        for (int i = 0; i < arr.Length; i++) {
                            string line = arr[i];
                            Items.Add(new Line(DateTime.UtcNow, style, line));
                        }
                    }
                    else { // Contains no new line characters
                        Items.Add(new Line(DateTime.UtcNow, style, tmp));
                    }
                } while (correctedStr.Length > 98);
                
                // Add last string
                if (correctedStr.Length <= 98) {
                    if (correctedStr.Contains(Environment.NewLine)) { // Contains custom new line character
                        string[] arr = correctedStr.Split(splitStr, StringSplitOptions.RemoveEmptyEntries);
                        for (int i = 0; i < arr.Length; i++) {
                            string line = arr[i];
                            Items.Add(new Line(DateTime.UtcNow, style, line));
                        }
                    }
                    else { // Contains no new line characters
                        Items.Add(new Line(DateTime.UtcNow, style, correctedStr));
                    }
                }
            }
            else {
                Items.Add(new Line(DateTime.UtcNow, style, str));
            }

            // Write log file
            WriteLogFile();

            // Jump to the latest item added in the console
            NavigateToBottom();
        }
        public void Print(string str)
        {
            Print(eConsoleLogStyle.Default, str);
        }
        public void PrintDebug(string str)
        {
#if DEBUG
            Print(eConsoleLogStyle.Debug, str);
#endif
        }
        public void PrintWarning(string str)
        {
            Print(eConsoleLogStyle.Warning, str);
        }
        public void PrintError(string str)
        {
            Print(eConsoleLogStyle.Error, str);
        }

        private void NavigateUp()
        {
            if (Items.Count != 0) {
                if (selectedIndex == 0) {
                    selectedIndex = (Items.Count - 1);
                    viewRangeStart = (Items.Count - 1) - (maxItemsVisibleAtOnce - 1);
                    viewRangeEnd = Items.Count;
                }
                else {
                    selectedIndex--;
                    if (selectedIndex < viewRangeStart) {
                        viewRangeStart--;
                        viewRangeEnd--;
                    }
                }
            }
        }
        private void NavigateDown()
        {
            if (Items.Count != 0) {
                if (selectedIndex == (Items.Count - 1)) {
                    selectedIndex = 0;
                    viewRangeStart = 0;
                    viewRangeEnd = maxItemsVisibleAtOnce;
                }
                else {
                    selectedIndex++;
                    if (selectedIndex >= viewRangeEnd) {
                        viewRangeStart++;
                        viewRangeEnd++;
                    }
                }
            }
        }
        private void NavigateToBottom()
        {
            selectedIndex = (Items.Count - 1);
            viewRangeStart = (Items.Count - 1) - (maxItemsVisibleAtOnce - 1);
            viewRangeEnd = Items.Count;
        }

        private void DrawText(string str, PointF pos, SizeF scale, Color color)
        {
            Natives.SET_TEXT_SCALE(scale.Width, scale.Height);
            Natives.SET_TEXT_COLOUR(color.R, color.G, color.B, color.A);
            Natives.SET_TEXT_DROPSHADOW(false, 0, 0, 0, 0);
            Natives.DISPLAY_TEXT_WITH_LITERAL_STRING(pos.X, pos.Y, "NF_SERVER_NAME", str);
        }
        #endregion

        #region Functions
        private Color GetColorFromConsoleLogStyle(int alpha, eConsoleLogStyle style)
        {
            switch (style) {
                case eConsoleLogStyle.Default: return Color.FromArgb(alpha, 255, 255, 255);
                case eConsoleLogStyle.Debug:   return Color.FromArgb(alpha, 134, 56, 255);
                case eConsoleLogStyle.Warning: return Color.FromArgb(alpha, 214, 207, 0);
                case eConsoleLogStyle.Error:   return Color.FromArgb(alpha, 205, 0, 0);
            }
            return Color.FromArgb(alpha, 255, 255, 255);
        }

        public bool RegisterCommand(Guid fromScript, string name, Action<string[]> actionToExecute)
        {
            string nameToLower = name.ToLower();

            if (Commands.ContainsKey(nameToLower))
                return false;
            if (string.IsNullOrWhiteSpace(nameToLower))
                return false;

            Commands.Add(nameToLower, actionToExecute);
            if (fromScript != Guid.Empty) Main.managerInstance.AddConsoleCommandToScript(fromScript, nameToLower);

            return true;
        }
        public bool ExecuteCommand(string name)
        {
            try {
                if (string.IsNullOrWhiteSpace(name))
                    return false;

                string[] args = Regex.Split(name, @"\s+");

                if (!Commands.ContainsKey(args[0].ToLower()))
                    return false;

                Commands[args[0].ToLower()]?.Invoke(args);

                return true;
            }
            catch (Exception ex) {
                PrintError(string.Format("[IV-SDK DotNet] An error occured while executing console command '{0}'. Details: {1}", name, ex.ToString()));
            }
            return false;
        }
        #endregion

        #region Commands
        private void HelpCommand()
        {
            Print("- - - - - - - Commands - - - - - - -");
            Print("Clear               - Clears the IV-SDK .NET console.");
            Print("CheckForUpdates     - Checks if there is a new update for IV-SDK .NET available.");
            Print("Autosave            - Triggers an auto save.");
            Print("Save                - Opens the save menu.");
            Print("SavePlayerPos       - Saves the players coordinates and heading to clipboard.");
            Print("ReloadConfig        - Reloads the IV-SDK .NET config.ini file.");
            Print("AbortScripts        - Aborts all currently running scripts.");
            Print("ReloadScripts       - Aborts and reloads all scripts.");
            Print("GetRunningScripts   - Gets number of running scripts.");
            Print("LoadScript          - Tries to load a single script.");
            Print("Quit                - Tries to force quit GTA IV.");
        }
        private void SavePlayerPosCommand()
        {
            try {
                Natives.GET_PLAYER_CHAR(Natives.CONVERT_INT_TO_PLAYERINDEX(Natives.GET_PLAYER_ID()), out int playerChar);
                Natives.GET_CHAR_COORDINATES(playerChar, out Vector3 playerPos);
                Natives.GET_CHAR_HEADING(playerChar, out float playerHeading);

                bool success = false;
                string str = string.Format("X: {0} Y: {1} Z: {2} H: {3}",
                    playerPos.X.ToString(CultureInfo.InvariantCulture),         // 0
                    playerPos.Y.ToString(CultureInfo.InvariantCulture),         // 1
                    playerPos.Z.ToString(CultureInfo.InvariantCulture),         // 2
                    playerHeading.ToString(CultureInfo.InvariantCulture));      // 3

                Thread cpThread = new Thread(() => {
                    Clipboard.SetText(str);
                    success = Clipboard.GetText().Equals(str);
                });
                cpThread.SetApartmentState(ApartmentState.STA);
                cpThread.Start();
                cpThread.Join();

                if (success) {
                    Print("Current player coordinates saved to clipboard!");
                }
                else {
                    Print("Current player coordinates did not got saved to clipboard.");
                }
            }
            catch (Exception ex) {
                PrintError(string.Format("An error occured while trying to save player pos and heading to clipboard. Details: {0}", ex.ToString()));
            }
        }
        private void LoadScriptCommand(string[] args)
        {
            if (args.Length > 1) {
                Main.managerInstance.LoadScript(args[1]);
            }
            else {
                PrintWarning("LoadScript usage: LoadScript TheScriptToLoad.ivsdk.dll");
            }
        }
        private void QuitCommand()
        {
            Process p = Main.managerInstance.GTAIVProcess;
            if (p != null) {
                Main.managerInstance.Cleanup();
                Thread.Sleep(1000);
                p.Kill();
            }
            else {
                Main.managerInstance.console.PrintWarning("Could not close GTA IV. GTAIVProcess is null.");
            }
        }
        #endregion

        #region Constructor
        internal Console()
        {
            input = string.Empty;

            splitStr = new string[1] { Environment.NewLine };
            Items = new List<Line>();
            InputHistory = new List<string>();

            TextScale = new SizeF(.213f, .25f);

            // Create commands dictionary and register default commands
            Commands = new Dictionary<string, Action<string[]>>();
            RegisterCommand(Guid.Empty, "Help",                 (string[] args) => { HelpCommand(); });
            RegisterCommand(Guid.Empty, "Clear",                (string[] args) => { Clear(); });
            RegisterCommand(Guid.Empty, "CheckForUpdates",      (string[] args) => { Main.managerInstance.UpdateChecker.CheckForUpdates(false); });
            RegisterCommand(Guid.Empty, "Autosave",             (string[] args) => { Natives.DO_AUTO_SAVE(); });
            RegisterCommand(Guid.Empty, "Save",                 (string[] args) => { Natives.ACTIVATE_SAVE_MENU(); });
            RegisterCommand(Guid.Empty, "SavePlayerPos",        (string[] args) => { SavePlayerPosCommand(); });
            RegisterCommand(Guid.Empty, "ReloadConfig",         (string[] args) => { Main.managerInstance.LoadConfig(false); });
            RegisterCommand(Guid.Empty, "AbortScripts",         (string[] args) => { Main.managerInstance.AbortScripts(true); });
            RegisterCommand(Guid.Empty, "ReloadScripts",        (string[] args) => { Main.managerInstance.LoadScripts(); });
            RegisterCommand(Guid.Empty, "GetRunningScripts",    (string[] args) => { Print(string.Format("There are currently {0} scripts running.", Main.managerInstance.ActiveScripts.Count.ToString())); });
            RegisterCommand(Guid.Empty, "LoadScript",           (string[] args) => { LoadScriptCommand(args); });
            RegisterCommand(Guid.Empty, "Quit",                 (string[] args) => { QuitCommand(); });
        }
        #endregion

        public void Draw()
        {
            if (IsConsoleVisible) {

                // Animation
                if (!(windowAlpha >= 200))
                    windowAlpha += 8;
                if (!(textAlpha >= 255))
                    textAlpha += 8;

                if (textAlpha > 255)
                    textAlpha = 255;

                // Draw Console Background
                Natives.DRAW_CURVED_WINDOW(.0045f, .005f, .99f, .3f, windowAlpha);

                // Draw Items
                if (Items.Count < maxItemsVisibleAtOnce) {
                    for (int i = 0; i < Items.Count; i++) {
                        Line item = Items[i];

                        if (selectedIndex == i) {
                            DrawText(">", new PointF(.014f, .015f + i * .0155f), TextScale, Color.FromArgb(textAlpha, 0, 255, 0));
                            DrawText(item.Text, new PointF(.025f, .015f + i * .0155f), TextScale, GetColorFromConsoleLogStyle(textAlpha, item.Style));
                        }
                        else {
                            DrawText(item.Text, new PointF(.014f, .015f + i * .0155f), TextScale, GetColorFromConsoleLogStyle(textAlpha, item.Style));
                        }
                    }
                }
                else {
                    for (int i = viewRangeStart; i < viewRangeEnd; i++) {
                        Line item = Items[i];

                        if (selectedIndex == i) {
                            DrawText(">", new PointF(.014f, .015f + (i - viewRangeStart) * .0155f), TextScale, Color.FromArgb(textAlpha, 0, 255, 0));
                            DrawText(item.Text, new PointF(.025f, .015f + (i - viewRangeStart) * .0155f), TextScale, GetColorFromConsoleLogStyle(textAlpha, item.Style));
                        }
                        else {
                            DrawText(item.Text, new PointF(.014f, .015f + (i - viewRangeStart) * .0155f), TextScale, GetColorFromConsoleLogStyle(textAlpha, item.Style));
                        }
                    }

                    // Up/Down Navigation Arrows
                    DrawText(@"/\", new PointF(.97f, .015f), TextScale, Color.FromArgb(textAlpha, 255, 255, 255));
                    DrawText(@"\/", new PointF(.97f, .275f), TextScale, Color.FromArgb(textAlpha, 255, 255, 255));

                }

                // Draw Input Field
                DrawText(string.Format("> {0}{1}", input, showCaret ? "-" : ""), new PointF(.014f, .275f), TextScale, Color.FromArgb(textAlpha, 255, 255, 255));

            }
        }

        public void KeyDown(KeyEventArgs e)
        {
            // Navigation & Input
            if (IsConsoleVisible) {

                // Navigation
                switch (e.KeyCode) {
                    case Keys.PageUp:
                        NavigateUp();
                        break;
                    case Keys.PageDown:
                        NavigateDown();
                        break;

                    case Keys.Up:
                        if (InputHistory.Count != 0) {

                            inputHistoryIndex--;
                            if (inputHistoryIndex < 0)
                                inputHistoryIndex = 0;

                            string item = InputHistory[inputHistoryIndex];
                            input = item;

                        }
                        break;
                    case Keys.Down:
                        if (InputHistory.Count != 0) {

                            inputHistoryIndex++;
                            if (inputHistoryIndex > InputHistory.Count - 1)
                                inputHistoryIndex = InputHistory.Count - 1;

                            string item = InputHistory[inputHistoryIndex];
                            input = item;

                        }
                        break;
                }

                // Input
                string unicodeKey = IVSDKDotNet.Helper.KeyCodeToUnicode(e.KeyCode);
                switch (e.KeyCode) {

                    case Keys.Back: // Delete chars
                        if (input.Length > 0) {
                            input = input.Remove(input.Length - 1);
                            inputHistoryIndex = -1;
                        }
                        break;

                    case Keys.Return: // Send command
                        if (!string.IsNullOrWhiteSpace(input)) {
                            InputHistory.Add(input);
                            Print(input);
                            ExecuteCommand(input);
                        }
                        input = string.Empty;
                        break;

                    default:
                        input += unicodeKey;
                        break;

                }

            }

            // Open/Close Console
            if (e.KeyCode == OpenCloseKey) {
                if (IsConsoleVisible) {
                    Close();
                }
                else {
                    Open();
                }
            }
        }

    }
}
