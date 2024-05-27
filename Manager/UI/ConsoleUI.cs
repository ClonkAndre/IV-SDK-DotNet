using System;
using System.Collections.Generic;
using System.Drawing;
using System.Diagnostics;
using System.Globalization;
using System.Numerics;
using System.Text.RegularExpressions;
using System.Threading;
using System.Windows.Forms;
using System.Linq;

using IVSDKDotNet;
using IVSDKDotNet.Enums;
using IVSDKDotNet.Native;

using Manager.Classes;

namespace Manager.UI
{
    public class ConsoleUI
    {

        #region Variables
        private Dictionary<string, Action<string[]>> localCommands;

        private List<string> inputHistory;
        private int inputHistoryIndex;

        // Input
        private string input;

        // Other
        public bool IsConsoleOpen;
        private bool wasOpened;
        #endregion

        #region Delegates and Events
        // Delegates
        public delegate void ConsoleCommandDelegate(string command, string[] args);

        // Events
        public event ConsoleCommandDelegate OnConsoleCommand;
        #endregion

        #region Methods
        public void Open()
        {
            IsConsoleOpen = true;
            wasOpened = true;
        }
        public void Close()
        {
            IsConsoleOpen = false;
            input = string.Empty;
        }
        public void Clear()
        {
            Logger.ClearLogItems();
        }
        #endregion

        #region Functions
        private Color GetColorFromConsoleLogStyle(int alpha, eConsoleLogStyle style)
        {
            switch (style)
            {
                case eConsoleLogStyle.Default: return Color.FromArgb(alpha, 255, 255, 255);
                case eConsoleLogStyle.Debug:   return Color.FromArgb(alpha, 134, 56, 255);
                case eConsoleLogStyle.Warning: return Color.FromArgb(alpha, 214, 207, 0);
                case eConsoleLogStyle.Error:   return Color.FromArgb(alpha, 205, 0, 0);
            }
            return Color.FromArgb(alpha, 255, 255, 255);
        }

        private bool RegisterLocalCommand(string name, Action<string[]> actionToExecute)
        {
            string nameToLower = name.ToLower();

            if (localCommands.ContainsKey(nameToLower))
                return false;

            // Add command to commands list
            localCommands.Add(nameToLower, actionToExecute);

            return true;
        }
        public bool ExecuteCommand(string name)
        {
            if (string.IsNullOrWhiteSpace(name))
                return false;

            string[] args = Regex.Split(name, @"\s+");
            string command = args[0].ToLower();

            // Skip first console command argument (which is the command name and we do not care about that we want the actual arguments)
            args = args.Skip(1).ToArray();

            // Raise event and let subscribers know
            OnConsoleCommand?.Invoke(command, args);

            // Check if this is a local command
            if (localCommands.ContainsKey(command))
            {
                // Execute local command
                localCommands[command]?.Invoke(args);
                return true;
            }

            // Command is not a local command, go through each registered script commands
            Main.Instance.ActiveScripts.ForEach(x =>
            {
                // Execute script command
                if (x.ConsoleCommands.ContainsKey(command))
                    x.ConsoleCommands[command]?.Invoke(args);
            });

            return true;
        }
        #endregion

        #region Commands
        private void RegisterDefaultCommands()
        {
            RegisterLocalCommand("Help", (string[] args) => { HelpCommand(); });
            RegisterLocalCommand("Clear", (string[] args) => { Clear(); });
            RegisterLocalCommand("CheckForUpdates", (string[] args) => { Main.Instance.UpdateChecker.CheckForUpdates(false); });
            RegisterLocalCommand("Autosave", (string[] args) => { Natives.DO_AUTO_SAVE(); });
            RegisterLocalCommand("Save", (string[] args) => { Natives.ACTIVATE_SAVE_MENU(); });
            RegisterLocalCommand("SavePlayerPos", (string[] args) => { SavePlayerPosCommand(); });
            RegisterLocalCommand("AbortScripts", (string[] args) => { Main.Instance.AbortScripts(ScriptType.All, AbortReason.Manual, true); });
            RegisterLocalCommand("AbortScript", (string[] args) => { AbortScriptCommand(args); });
            RegisterLocalCommand("ReloadScripts", (string[] args) => { Main.Instance.LoadScripts(); });
            RegisterLocalCommand("GetRunningScripts", (string[] args) => { Logger.Log(string.Format("There are currently {0} scripts running.", Main.Instance.ActiveScripts.Count.ToString()), true); });
            RegisterLocalCommand("LoadScript", (string[] args) => { LoadScriptCommand(args); });
            RegisterLocalCommand("StartAPI", (string[] args) => { Main.Instance.ConnectionManager.Start(true); });
            RegisterLocalCommand("StopAPI", (string[] args) => { Main.Instance.ConnectionManager.Stop(); });
            RegisterLocalCommand("Manager", (string[] args) => { ManagerUI.IsConfigUIOpened = !ManagerUI.IsConfigUIOpened; });
            RegisterLocalCommand("Quit", (string[] args) => { QuitCommand(); });
        }
        private void HelpCommand()
        {
            Logger.Log("- - - - - - - Commands - - - - - - -", true);
            Logger.Log("Help                - Shows all commands of IV-SDK .NET with a description.", true);
            Logger.Log("Clear               - Clears the IV-SDK .NET console.", true);
            Logger.Log("CheckForUpdates     - Checks if there is a new update for IV-SDK .NET available.", true);
            Logger.Log("Autosave            - Triggers an auto save.", true);
            Logger.Log("Save                - Opens the save menu.", true);
            Logger.Log("SavePlayerPos       - Saves the players coordinates and heading to clipboard.", true);
            Logger.Log("AbortScripts        - Aborts all currently running scripts.", true);
            Logger.Log("AbortScript         - Tries to abort a single script.", true);
            Logger.Log("ReloadScripts       - Aborts and reloads all scripts.", true);
            Logger.Log("GetRunningScripts   - Gets number of running scripts.", true);
            Logger.Log("LoadScript          - Tries to load a single script.", true);
            Logger.Log("StartAPI            - Starts the API so clients can connect to IV-SDK .NET.", true);
            Logger.Log("StopAPI             - Stops the API so clients can no longer connect to IV-SDK .NET.", true);
            Logger.Log("Manager             - Opens the Manager Window from which you can for example change some IV-SDK .NET settings, or control scripts.", true);
            Logger.Log("Quit                - Tries to force quit GTA IV.", true);
        }
        private void SavePlayerPosCommand()
        {
            try
            {
                IVPed playerPed = IVPed.FromUIntPtr(IVPlayerInfo.FindThePlayerPed());
                if (playerPed != null)
                {
                    Vector3 playerPos = playerPed.Matrix.Pos;

                    bool success = false;
                    string str = string.Format("X: {0} Y: {1} Z: {2} H: {3}",
                        playerPos.X.ToString(CultureInfo.InvariantCulture),                 // 0
                        playerPos.Y.ToString(CultureInfo.InvariantCulture),                 // 1
                        playerPos.Z.ToString(CultureInfo.InvariantCulture),                 // 2
                        playerPed.CurrentHeading.ToString(CultureInfo.InvariantCulture));   // 3

                    Thread cpThread = new Thread(() => {
                        Clipboard.SetText(str);
                        success = Clipboard.GetText().Equals(str);
                    });
                    cpThread.SetApartmentState(ApartmentState.STA);
                    cpThread.Start();
                    cpThread.Join();

                    if (success)
                        Logger.Log("Current player position and heading saved to clipboard!");
                    else
                        Logger.LogError("Unknown error while trying to save current player position and heading to clipboard.");
                }
                else
                {
                    Logger.LogWarning("Could not save player position and heading to clipbard. Player was null. Ensure that you're actually calling this command while in-game.");
                }
            }
            catch (Exception ex)
            {
                Logger.LogError(string.Format("An error occured while trying to save player position and heading to clipboard! Details: {0}", ex.ToString()));
            }
        }
        private void AbortScriptCommand(string[] args)
        {
            if (args.Length > 1)
            {
                string scriptName = args[1];
                FoundScript fs = Main.Instance.GetFoundScript(scriptName);

                if (fs != null)
                    Main.Instance.AbortScriptInternal(AbortReason.Manager, fs, true);
                else
                    Logger.LogWarning(string.Format("Could not find script {0}. Script might already be aborted.", scriptName));
            }
            else
                Logger.LogWarning("AbortScript usage: AbortScript TheScriptToLoad");
        }
        private void LoadScriptCommand(string[] args)
        {
            if (args.Length > 1)
                Main.Instance.LoadScript(args[1]);
            else
                Logger.LogWarning("LoadScript usage: LoadScript TheScriptToLoad.ivsdk.dll");
        }
        private void QuitCommand()
        {
            Process p = Main.Instance.GTAIVProcess;
            if (p != null)
            {
                Main.Instance.Cleanup();
                Thread.Sleep(1000);
                p.Kill();
            }
            else
            {
                Logger.LogWarning("Could not close GTA IV. GTAIVProcess is null.");
            }
        }
        #endregion

        #region Constructor
        internal ConsoleUI()
        {
            input = string.Empty;

            // Lists
            inputHistory = new List<string>();

            // Create commands dictionary and register default commands
            localCommands = new Dictionary<string, Action<string[]>>();
            RegisterDefaultCommands();
        }
        #endregion

        public void DoUI()
        {
            if (!IsConsoleOpen)
                return;

            // Get the main Viewport
            ImGuiIV_Viewport vp = ImGuiIV.MainViewport;

            // Begin the IV-SDK .NET Console Window
            ImGuiIV.Begin("IV-SDK .NET Console", ref IsConsoleOpen, eImGuiWindowFlags.NoCollapse);

            if (vp.IsValid)
            {
                ImGuiIV.SetWindowPos(new Vector2(5f, 5f), eImGuiCond.FirstUseEver);
                ImGuiIV.SetWindowSize(new Vector2(vp.Size.X - 10f, vp.Size.Y / 2.5f), eImGuiCond.FirstUseEver);
            }

            // Console log
            if (ImGuiIV.BeginListBox("##IVSDKDotNetConsoleLogLB", new Vector2(ImGuiIV.FloatMin, 2f * -ImGuiIV.GetTextLineHeightWithSpacing())))
            {
                // Get logged items
                List<Logger.tLogItem> items = Logger.GetLogItems();

                for (int i = 0; i < items.Count; i++)
                {
                    Logger.tLogItem item = items[i];

                    // Add item to ListBox with the right color
                    ImGuiIV.PushStyleColor(eImGuiCol.ImGuiCol_Text, GetColorFromConsoleLogStyle(255, item.Style));
                    ImGuiIV.TextWrapped(item.ToString());
                    ImGuiIV.PopStyleColor();
                }

                ImGuiIV.EndListBox();
            }

            // Send command button
            if (ImGuiIV.Button("Send") || ImGuiIV.IsKeyReleased(eImGuiKey.ImGuiKey_Enter))
            {
                if (!string.IsNullOrWhiteSpace(input))
                {
                    inputHistory.Add(input);
                    Logger.Log(input, true);
                    ExecuteCommand(input);
                }

                input = string.Empty;
            }
            ImGuiIV.SameLine();
            ImGuiIV.SetNextItemWidth(-1f);

            // Console input history
            if (ImGuiIV.IsKeyPressed(eImGuiKey.ImGuiKey_UpArrow, false))
            {
                if (inputHistory.Count != 0)
                {
                    inputHistoryIndex++;
                    if (inputHistoryIndex > inputHistory.Count - 1)
                        inputHistoryIndex = 0;

                    input = inputHistory[inputHistoryIndex];
                }
            }
            else if (ImGuiIV.IsKeyPressed(eImGuiKey.ImGuiKey_DownArrow, false))
            {
                if (inputHistory.Count != 0)
                {
                    inputHistoryIndex--;
                    if (inputHistoryIndex < 0)
                        inputHistoryIndex = inputHistory.Count - 1;

                    input = inputHistory[inputHistoryIndex];
                }
            }

            // Delete all current text entered in the console text field
            if (ImGuiIV.IsKeyPressed(eImGuiKey.ImGuiKey_Delete, false))
                input = string.Empty;

            // Insert the text that is currently saved in clipboard into the text field
            if (ImGuiIV.IsKeyPressed(eImGuiKey.ImGuiKey_Insert, false))
            {
                string clipboardText = Clipboard.GetText();
                if (!string.IsNullOrWhiteSpace(clipboardText))
                    input += clipboardText;
            }

            if (wasOpened)
            {
                ImGuiIV.SetKeyboardFocusHere();
                wasOpened = false;
            }

            // Input field
            ImGuiIV.InputText("##inputTextBox", ref input);

            ImGuiIV.End();
        }

        public void KeyDown(KeyEventArgs e)
        {
            // Open/Close Console
            if (e.KeyCode == Config.ConsoleOpenCloseKey)
            {
                if (IsConsoleOpen)
                    Close();
                else
                    Open();
            }
        }

    }
}
