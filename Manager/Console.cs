using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text.RegularExpressions;
using System.Windows.Forms;

using IVSDKDotNet.Enums;
using IVSDKDotNet.Native;

namespace Manager {
    public class Console {

        #region Variables
        private Main managerInstance;

        public List<Line> Items;
        public List<string> InputHistory;
        public Dictionary<string, Action<string[]>> Commands;
        private string[] splitStr;

        // Style
        private SizeF TextScale;

        // Input
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
            public eConsoleLogStyle Style;
            public string Text;
            #endregion

            #region Constructor
            public Line(eConsoleLogStyle style, string text)
            {
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

            caretTimerID = managerInstance.StartNewLocalTimer(600, () => {
                showCaret = !showCaret;
            });
        }
        public void Close()
        {
            if (!IsConsoleVisible)
                return;

            managerInstance.AbortTaskOrTimer(caretTimerID);

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

        private void Print(eConsoleLogStyle style, string str)
        {
            if (string.IsNullOrWhiteSpace(str)) {
                Items.Add(new Line(style, ""));
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
                            Items.Add(new Line(style, arr[i]));
                        }
                    }
                    else { // Contains no new line characters
                        Items.Add(new Line(style, tmp));
                    }
                } while (correctedStr.Length > 98);
                
                // Add last string
                if (correctedStr.Length <= 98) {
                    if (correctedStr.Contains(Environment.NewLine)) { // Contains custom new line character
                        string[] arr = correctedStr.Split(splitStr, StringSplitOptions.RemoveEmptyEntries);
                        for (int i = 0; i < arr.Length; i++) {
                            Items.Add(new Line(style, arr[i]));
                        }
                    }
                    else { // Contains no new line characters
                        Items.Add(new Line(style, correctedStr));
                    }
                }
            }
            else {
                Items.Add(new Line(style, str));
            }

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
            if (fromScript != Guid.Empty) managerInstance.AddConsoleCommandToScript(fromScript, nameToLower);

            return true;
        }
        public bool ExecuteCommand(string name)
        {
            try {
                if (string.IsNullOrWhiteSpace(name))
                    return false;

                string cmd = name.ToLower();

                if (!Commands.ContainsKey(cmd))
                    return false;

                string[] args = Regex.Split(name, @"\s+");
                Commands[cmd]?.Invoke(args);

                return true;
            }
            catch (Exception ex) {
                PrintError(string.Format("[IV-SDK DotNet] An error occured while executing console command '{0}'. Details: {1}", name, ex.ToString()));
            }
            return false;
        }
        #endregion

        #region Commands
        private void HelpCommand(string[] args)
        {
            Print("- - - - - - - Commands - - - - - - -");
            Print("Clear               - Clears the IV-SDK .NET console.");
            Print("CheckForUpdates     - Checks if there is a new update for IV-SDK .NET available.");
            Print("Autosave            - Triggers an auto save.");
            Print("Save                - Opens the save menu.");
            Print("AbortScripts        - Aborts all currently running scripts.");
            Print("ReloadScripts       - Aborts and reloads all scripts.");
            Print("GetRunningScripts   - Gets number of running scripts.");
        }
        #endregion

        #region Constructor
        internal Console(Main main)
        {
            managerInstance = main;

            input = string.Empty;

            splitStr = new string[1] { Environment.NewLine };
            Items = new List<Line>();
            InputHistory = new List<string>();

            TextScale = new SizeF(.213f, .25f);

            // Create commands dictionary and register default commands
            Commands = new Dictionary<string, Action<string[]>>();
            RegisterCommand(Guid.Empty, "Help",                 (string[] args) => { HelpCommand(args); });
            RegisterCommand(Guid.Empty, "Clear",                (string[] args) => { Clear(); });
            RegisterCommand(Guid.Empty, "CheckForUpdates",      (string[] args) => { managerInstance.UpdateChecker.CheckForUpdates(false); });
            RegisterCommand(Guid.Empty, "Autosave",             (string[] args) => { Natives.DO_AUTO_SAVE(); });
            RegisterCommand(Guid.Empty, "Save",                 (string[] args) => { Natives.ACTIVATE_SAVE_MENU(); });
            RegisterCommand(Guid.Empty, "AbortScripts",         (string[] args) => { managerInstance.AbortScripts(true); });
            RegisterCommand(Guid.Empty, "ReloadScripts",        (string[] args) => { managerInstance.LoadScripts(); });
            RegisterCommand(Guid.Empty, "GetRunningScripts",    (string[] args) => { Print(string.Format("There are currently {0} scripts running.", managerInstance.ActiveScripts.Count.ToString())); ; });
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
            if (e.KeyCode == Keys.F4) {
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
