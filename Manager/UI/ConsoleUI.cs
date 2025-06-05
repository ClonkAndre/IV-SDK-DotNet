using IVSDKDotNet;
using IVSDKDotNet.Enums;
using IVSDKDotNet.Native;
using Manager.Classes;
using Manager.Classes.Attributes;
using Manager.Classes.Scripts;
using Manager.Managers;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Globalization;
using System.Linq;
using System.Numerics;
using System.Reflection;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Windows.Forms;

namespace Manager.UI
{
    public static class ConsoleUI
    {

        #region Variables
        private static List<LocalConsoleCommand> localConsoleCommands;

        private static string[] autoCompleteCommands;
        private static string lastConsoleCommand;

        // Suggestions Popup
        private static bool popupOpen;
        private static bool isHoveringPopup;

        private static int selectionIndex;

        // Input
        private static string input;
        private static bool clearSelection;

        // Other
        public static bool IsConsoleOpen;
        private static bool wasOpened;
        private static bool canScrollToEnd;
        #endregion

        #region Delegates and Events
        // Delegates
        public delegate void ConsoleCommandDelegate(string command, string[] args);

        // Events
        public static event ConsoleCommandDelegate OnConsoleCommand;
        #endregion

        #region Methods
        public static void Init()
        {
            input = string.Empty;

            localConsoleCommands = new List<LocalConsoleCommand>();
            RegisterDefaultCommands();
        }
        public static void Shutdown()
        {
            Close();

            if (localConsoleCommands != null)
            {
                localConsoleCommands.Clear();
                localConsoleCommands = null;
            }
        }

        private static void RegisterDefaultCommands()
        {
            // Get all the methods of this class and check their attributes
            MethodInfo[] methods = typeof(ConsoleUI).GetMethods(BindingFlags.NonPublic | BindingFlags.Static);

            for (int i = 0; i < methods.Length; i++)
            {
                MethodInfo method = methods[i];

                // Get the names attribute of the method
                LocalCommandNameAttribute namesAttribute = method.GetCustomAttribute<LocalCommandNameAttribute>();

                // If this it null then this method is not supposed to be a console command
                if (namesAttribute == null)
                    continue;

                // Create command
                LocalConsoleCommand command = new LocalConsoleCommand(method);

                command.SetNameFromAttribute(namesAttribute);
                command.SetDescriptionFromAttribute(method.GetCustomAttribute<LocalCommandDescAttribute>());
                command.SetOptionsFromAttribute(method.GetCustomAttribute<LocalCommandOptionsAttribute>());
                command.SetSuggestionsFromAttribute(method.GetCustomAttribute<LocalCommandSuggestionsAttribute>());

                // Register the command
                localConsoleCommands.Add(command);
            }

            // Sort commands by name
            localConsoleCommands.OrderBy(x => x.GetFirstName());

            // Build array of commands for auto complete
            autoCompleteCommands = localConsoleCommands.SelectMany(x => x.GetNames()).ToArray();
        }

        public static void ToggleConsole()
        {
            if (IsConsoleOpen)
                Close();
            else
                Open();
        }
        public static void Open()
        {
            IsConsoleOpen = true;
            wasOpened = true;
        }
        public static void Close()
        {
            IsConsoleOpen = false;
            input = string.Empty;
            selectionIndex = 0;
        }
        public static void Clear()
        {
            Logger.ClearLogItems();
        }

        public static void ResetLastConsoleCommand()
        {
            lastConsoleCommand = null;
        }

        private static void DoSuggestionsPopup(Vector2 popupPos)
        {
            if (!ImGuiIV.BeginPopup("ivsdkdotnetConsoleSuggestionsPopup", eImGuiWindowFlags.NoFocusOnAppearing))
                return;

            // Set position of the popup menu
            ImGuiIV.SetWindowPos(popupPos);

            // Set focus to popup menu only when hovering over it with the mouse
            Vector2 windowPos = ImGuiIV.GetWindowPos();
            Vector2 windowSize = ImGuiIV.GetWindowSize();
            if (ImGuiIV.IsMouseHoveringRect(new RectangleF(windowPos.X, windowPos.Y, windowSize.X, windowSize.Y), false))
            {
                ImGuiIV.SetWindowFocus("ivsdkdotnetConsoleSuggestionsPopup");
                isHoveringPopup = true;
            }
            else
            {
                isHoveringPopup = false;
                if (ImGuiIV.IsWindowFocused(eImGuiFocusedFlags.ChildWindows))
                    ImGuiIV.SetWindowFocus(null);
            }

            // Parse input
            string[] args = Regex.Split(input, @"\s+");
            string command = args[0].ToLower();

            bool shouldClosePopup = true;

            if (args.Length < 3)
            {
                if (args.Length == 1)
                    shouldClosePopup = ShowSuggestedCommands(command);
                else
                    shouldClosePopup = ShowSuggestedCommandsOfCommand(command, args[1]);
            }

            if (shouldClosePopup || !popupOpen)
                ImGuiIV.CloseCurrentPopup();

            ImGuiIV.EndPopup();
        }
        private static bool ShowSuggestedCommands(string command) // Returns true if the popup should be closed
        {
            string[] autoCompleteCommandsFiltered = autoCompleteCommands.Where(x => x.Contains(command)).ToArray();

            if (autoCompleteCommandsFiltered.Length == 0)
                return true;

            // Navigate through suggestions list
            if (ImGuiIV.IsKeyPressed(eImGuiKey.ImGuiKey_UpArrow, false))
            {
                if (selectionIndex <= 0)
                {
                    selectionIndex = autoCompleteCommandsFiltered.Length - 1;
                }
                else
                {
                    selectionIndex--;
                }
            }
            if (ImGuiIV.IsKeyPressed(eImGuiKey.ImGuiKey_DownArrow, false))
            {
                if (selectionIndex >= autoCompleteCommandsFiltered.Length - 1)
                {
                    selectionIndex = 0;
                }
                else
                {
                    selectionIndex++;
                }
            }
            if (ImGuiIV.IsKeyPressed(eImGuiKey.ImGuiKey_Tab) /*|| ImGuiIV.IsKeyPressed(eImGuiKey.ImGuiKey_RightArrow)*/)
            {
                ImGuiIV.SetActiveID(0, ImGuiIV.GetCurrentWindow());
                //ImGuiIV.SetItemDefaultFocus();
                //ImGuiIV.SetKeyboardFocusHere(-1);
                wasOpened = true;
                clearSelection = true;

                input = autoCompleteCommandsFiltered[selectionIndex];
            }

            // Add filtered commands to suggestions list
            for (int i = 0; i < autoCompleteCommandsFiltered.Length; i++)
            {
                if (ImGuiIV.Selectable(autoCompleteCommandsFiltered[i], selectionIndex == i))
                    input = autoCompleteCommandsFiltered[i];

                // Show the description of the command when hovering over this item
                if (ImGuiIV.IsItemHovered())
                    ImGuiIV.SetTooltip(GetLocalConsoleCommand(autoCompleteCommandsFiltered[i]).Description);

                //string command = autoCompleteCommandsFiltered[i].ToLower();

                //if (command.Contains(inputToLower))
                //{
                //    if (ImGuiIV.Selectable(autoCompleteCommandsFiltered[i], selectionIndex == i))
                //        input = autoCompleteCommandsFiltered[i];
                //}
            }

            return false; // Dont close popup
        }
        private static bool ShowSuggestedCommandsOfCommand(string command, string arg0) // Returns true if the popup should be closed
        {
            LocalConsoleCommand localConsoleCommand = GetLocalConsoleCommand(command);

            if (localConsoleCommand == null)
                return true;
            if (!localConsoleCommand.HasSuggestions)
                return true;

            // Get suggestions
            string[] suggestions = null;

            switch (localConsoleCommand.DynamicSuggestions)
            {
                case DynamicConsoleCommandSuggestions.ActiveScripts:
                    suggestions = ScriptManager.GetEntryPointNameOfActiveScripts();
                    break;
                case DynamicConsoleCommandSuggestions.ConsoleCommands:
                    suggestions = autoCompleteCommands;
                    break;
                default:
                    suggestions = localConsoleCommand.Suggestions;
                    break;
            }

            if (suggestions == null || suggestions.Length == 0)
                return true;

            // Navigate through suggestions list
            if (ImGuiIV.IsKeyPressed(eImGuiKey.ImGuiKey_UpArrow, false))
            {
                if (selectionIndex <= 0)
                {
                    selectionIndex = suggestions.Length - 1;
                }
                else
                {
                    selectionIndex--;
                }
            }
            if (ImGuiIV.IsKeyPressed(eImGuiKey.ImGuiKey_DownArrow, false))
            {
                if (selectionIndex >= suggestions.Length - 1)
                {
                    selectionIndex = 0;
                }
                else
                {
                    selectionIndex++;
                }
            }
            if (ImGuiIV.IsKeyPressed(eImGuiKey.ImGuiKey_Tab))
            {
                ImGuiIV.SetActiveID(0, ImGuiIV.GetCurrentWindow());
                //ImGuiIV.SetItemDefaultFocus();
                //ImGuiIV.SetKeyboardFocusHere(-1);
                wasOpened = true;
                clearSelection = true;

                if (string.IsNullOrWhiteSpace(arg0))
                    input = input.Insert(command.Length + 1, suggestions[selectionIndex]);
                else
                    input = input.Replace(arg0, suggestions[selectionIndex]);
            }
            
            // Add suggestions to suggestions list
            for (int i = 0; i < suggestions.Length; i++)
            {
                if (ImGuiIV.Selectable(suggestions[i], selectionIndex == i))
                {
                    if (string.IsNullOrWhiteSpace(arg0))
                        input = input.Insert(command.Length + 1, suggestions[i]);
                    else
                        input = input.Replace(arg0, suggestions[i]);
                }
            }

            return false; // Dont close popup
        }
        #endregion

        #region Functions
        public static bool ExecuteCommand(string input)
        {
            if (string.IsNullOrWhiteSpace(input))
                return false;

            // Parse input
            string[] args = Regex.Split(input, @"\s+");
            string command = args[0].ToLower();

            lastConsoleCommand = command;

            // Skip first console command argument (which is the command name and we do not care about that we want the actual arguments)
            args = args.Skip(1).ToArray();

            // Raise event and let subscribers know
            OnConsoleCommand?.Invoke(command, args);

            // Check if this is a local command
            LocalConsoleCommand localCommand = GetLocalConsoleCommand(command);

            if (localCommand != null)
            {
                // Check if command can be executed
                if (localCommand.CanOnlyBeCalledOnceInGame && IVPlayerInfo.FindThePlayerPed() == UIntPtr.Zero)
                {
                    Logger.LogWarning("Cannot execute this command when not in-game yet.");
                    return false;
                }
                if (localCommand.RequiredArgumentsCount != 0)
                {
                    if (args.Length < localCommand.RequiredArgumentsCount)
                    {
                        Logger.LogWarningEx("Cannot execute this command because it requires {0} argument(s) and you only passed in {1}.", localCommand.RequiredArgumentsCount, args.Length);
                        return false;
                    }
                }

                // Execute local command
                localCommand.Invoke(args);
                return true;
            }

            // Command is not a local command, go through each registered script commands
            // TODO: This can be made better
            ScriptManager.GetActiveScripts().ForEach(x =>
            {
                // Execute script command
                if (x.ConsoleCommands.ContainsKey(command))
                    x.ConsoleCommands[command]?.Invoke(args);
            });

            return true;
        }
        public static string GetLastConsoleCommand()
        {
            return lastConsoleCommand;
        }

        private static LocalConsoleCommand GetLocalConsoleCommand(string command)
        {
            return localConsoleCommands.Where(x => x.ContainsGivenCommandName(command)).FirstOrDefault();
        }
        private static Color GetColorFromConsoleLogStyle(int alpha, eConsoleLogStyle style)
        {
            switch (style)
            {
                case eConsoleLogStyle.Default:
                    {
                        if (Config.ImGuiStyle.ToLower() == "light" && !Config.UseCustomThemeForManagerAndConsole)
                            return Color.FromArgb(alpha, 0, 0, 0);
                        else
                            return Color.FromArgb(alpha, 255, 255, 255);
                    }
                case eConsoleLogStyle.Debug: return Color.FromArgb(alpha, 134, 56, 255);
                case eConsoleLogStyle.Warning: return Color.FromArgb(alpha, 214, 207, 0);
                case eConsoleLogStyle.Error: return Color.FromArgb(alpha, 205, 0, 0);
            }
            return Color.FromArgb(alpha, 255, 255, 255);
        }
        #endregion

        #region Commands
        [LocalCommandName("help")]
        [LocalCommandDesc("Lists all commands with brief descriptions, or shows detailed info for a specific command.")]
        [LocalCommandSuggestions(dynamicSuggestions: DynamicConsoleCommandSuggestions.ConsoleCommands)]
        private static void HelpCommand(string[] args)
        {
            if (args.Length != 0) // Show description of a single command
            {
                string command = args[0];
                
                // Try to find the command
                LocalConsoleCommand localConsoleCommand = GetLocalConsoleCommand(command);

                if (localConsoleCommand == null)
                {
                    Logger.LogWarningEx("Could not find command with the name '{0}'.", command);
                    return;
                }

                if (localConsoleCommand.CanOnlyBeCalledOnceInGame)
                    Logger.LogWarning("Note that this command can only be called once in-game!");

                if (localConsoleCommand.DetailedDescription != null)
                {
                    for (int i = 0; i < localConsoleCommand.DetailedDescription.Length; i++)
                    {
                        string desc = localConsoleCommand.DetailedDescription[i];

                        // To avoid needing to populate the array with the same string as the short description,
                        // we can simply use this wildcard which will tell us to use the short description.
                        if (desc[0] == '*')
                            desc = localConsoleCommand.Description;

                        Logger.Log(desc);
                    }
                }
                else
                {
                    Logger.Log(localConsoleCommand.Description);
                }
            }
            else // Show all commands
            {
                Logger.LogWarning("======================== COMMANDS ========================");
                Logger.LogWarningEx("There are currently {0} local commands available.", localConsoleCommands.Count);

                for (int i = 0; i < localConsoleCommands.Count; i++)
                {
                    LocalConsoleCommand command = localConsoleCommands[i];
                    Logger.LogEx("{0} - {1}", string.Join(", ", command.GetNames()), command.Description);
                }

                Logger.LogWarning("==========================================================");
            }
        }

        [LocalCommandName("clear")]
        [LocalCommandDesc("Clears the console.")]
        private static void ClearCommand(string[] args)
        {
            Clear();
        }

        [LocalCommandName("forceflush")]
        [LocalCommandDesc("Forces the console output to be written to the log file.")]
        private static void ForceFlush(string[] args)
        {
            Logger.ForceFlush();
        }

        [LocalCommandName("checkforupdates")]
        [LocalCommandDesc("Checks if there is an update available for IV-SDK .NET.")]
        private static void CheckForUpdatesCommand(string[] args)
        {
            Main.Instance.UpdateChecker.CheckForUpdates(false);
        }

        [LocalCommandName("autosave")]
        [LocalCommandDesc("Performs an instant autosave.")]
        [LocalCommandOptions(canOnlyBeCalledOnceInGame: true)]
        private static void Autosave(string[] args)
        {
            Natives.DO_AUTO_SAVE();
        }

        [LocalCommandName("save")]
        [LocalCommandDesc("Opens the save menu.")]
        [LocalCommandOptions(canOnlyBeCalledOnceInGame: true)]
        private static void Save(string[] args)
        {
            Natives.ACTIVATE_SAVE_MENU();
        }

        [LocalCommandName("saveplayerpos")]
        [LocalCommandDesc("Saves the current position and heading of the player.")]
        [LocalCommandOptions(canOnlyBeCalledOnceInGame: true)]
        private static void SavePlayerPosCommand(string[] args)
        {
            try
            {
                Natives.GET_CHAR_COORDINATES(Main.Instance.PlayerPedHandle, out Vector3 playerPos);
                Natives.GET_CHAR_HEADING(Main.Instance.PlayerPedHandle, out float playerHeading);

                string str = string.Format("X: {0}, Y: {1}, Z: {2}, H: {3}",
                    playerPos.X.ToString(CultureInfo.InvariantCulture),      // 0
                    playerPos.Y.ToString(CultureInfo.InvariantCulture),      // 1
                    playerPos.Z.ToString(CultureInfo.InvariantCulture),      // 2
                    playerHeading.ToString(CultureInfo.InvariantCulture));   // 3

                Thread cpThread = new Thread(() => Clipboard.SetText(str));
                cpThread.SetApartmentState(ApartmentState.STA);
                cpThread.Start();
                cpThread.Join();

                Logger.Log("Current player position and heading should've been saved to clipboard!");
            }
            catch (Exception ex)
            {
                Logger.LogError(string.Format("An error occured while trying to save player position and heading to clipboard! Details: {0}", ex.ToString()));
            }
        }

        [LocalCommandName("abortscripts")]
        [LocalCommandDesc("Aborts all currently running scripts.")]
        private static void AbortScriptsCommand(string[] args)
        {
            ScriptManager.AbortScripts(ScriptType.All, AbortReason.Console, true);
        }

        [LocalCommandName("abortscript")]
        [LocalCommandDesc("Aborts a single script.", new string[] { "*", "Example usage: abortscript MyScript.ivsdk.dll" })]
        [LocalCommandOptions(requiredArgumentsCount: 1)]
        [LocalCommandSuggestions(dynamicSuggestions: DynamicConsoleCommandSuggestions.ActiveScripts)]
        private static void AbortScriptCommand(string[] args)
        {
            string scriptName = args[0];
            FoundScript fs = ScriptManager.GetFoundScript(scriptName);

            if (fs != null)
                ScriptManager.AbortScriptInternal(AbortReason.Manager, fs, true);
            else
                Logger.LogWarning(string.Format("Could not find script {0}. Script might already be aborted.", scriptName));
        }

        [LocalCommandName("reloadscripts")]
        [LocalCommandDesc("Reloads all scripts.")]
        private static void ReloadScriptsCommand(string[] args)
        {
            ScriptManager.LoadScriptsInternal();
        }

        [LocalCommandName("loadscript")]
        [LocalCommandDesc("Loads a single script.", new string[] { "*", "Example usage: loadscript MyScript.ivsdk.dll" })]
        [LocalCommandOptions(requiredArgumentsCount: 1)]
        private static void LoadScriptCommand(string[] args)
        {
            ScriptManager.LoadScript(args[1]);
        }

        [LocalCommandName("startapi")]
        [LocalCommandDesc("Starts the IV-SDK .NET Manager API.")]
        private static void StartAPICommand(string[] args)
        {
            Main.Instance.ConnectionManager.Start(true);
        }

        [LocalCommandName("stopapi")]
        [LocalCommandDesc("Stops the IV-SDK .NET Manager API.")]
        private static void StopAPICommand(string[] args)
        {
            Main.Instance.ConnectionManager.Stop();
        }

        [LocalCommandName("manager", "mgr")]
        [LocalCommandDesc("Toggles the manager window of IV-SDK .NET.")]
        private static void ToggleManagerWindowCommand(string[] args)
        {
            ManagerUI.IsConfigUIOpened = !ManagerUI.IsConfigUIOpened;
        }

        [LocalCommandName("publicfields", "pf")]
        [LocalCommandDesc("Toggles the public fields window of a script.", new string[] { "*", "Example usage: publicfields MyScript.ivsdk.dll" })]
        [LocalCommandOptions(requiredArgumentsCount: 1)]
        [LocalCommandSuggestions(dynamicSuggestions: DynamicConsoleCommandSuggestions.ActiveScripts)]
        private static void TogglePublicFieldsWindow(string[] args)
        {
            string scriptName = args[0];

            if (scriptName == null)
            {
                Logger.LogWarning("publicfields usage: publicfields MyScript.Main (actual name) OR publicfields MyScript/MyScript.ivsdk.dll (file name)");
                return;
            }

            FoundScript foundScript = ScriptManager.GetFoundScript(scriptName);

            if (foundScript == null)
            {
                Logger.LogWarning("Could not find script by that name.");
                return;
            }

            if (!foundScript.WasConstructed())
                return;

            // Toggle window
            foundScript.PublicFieldsWindowOpen = !foundScript.PublicFieldsWindowOpen;
        }

        [LocalCommandName("teleport", "tp")]
        [LocalCommandDesc("Teleports the player to the given coordinates.", new string[] { "*", "Example usage: teleport X, Y, Z" })]
        [LocalCommandOptions(canOnlyBeCalledOnceInGame: true, requiredArgumentsCount: 3)]
        private static void TeleportCommand(string[] args)
        {
            // 0 = X
            // 1 = Y
            // 2 = Z
            bool res1 = float.TryParse(args[0], out float x);
            bool res2 = float.TryParse(args[1], out float y);
            bool res3 = float.TryParse(args[2], out float z);

            if (!res1 || !res2 || !res3)
            {
                Logger.LogWarning("Teleport usage: teleport X Y Z");
                return;
            }

            // Teleport
            ThreadManager.AddToMainThreadQueue(() =>
            {
                IVPed.FromUIntPtr(IVPlayerInfo.FindThePlayerPed()).Teleport(new Vector3(x, y, z), false, true);
                Logger.LogEx("Teleported the player to location X: {0}, Y: {1}, Z: {2}", x, y, z);
            });
        }

        [LocalCommandName("docs")]
        [LocalCommandDesc("Opens the official IV-SDK .NET GitHub Documentation in your default webbrowser.")]
        private static void DocsCommand(string[] args)
        {
            Process.Start("https://github.com/ClonkAndre/IV-SDK-DotNet/blob/main/Documentation/Home.md");
        }

        [LocalCommandName("quit", "exit", "close")]
        [LocalCommandDesc("Closes the game.")]
        private static void QuitCommand(string[] args)
        {
            Process p = Main.Instance.GTAIVProcess;

            if (p == null)
            {
                Logger.LogWarning("Could not close GTA IV. GTAIVProcess is null.");
                return;
            }

            CLR.CLRBridge.ForceShutdown();
            Thread.Sleep(1000);
            p.Kill();
        }
        #endregion

        public static void DoUI()
        {
            if (!IsConsoleOpen)
                return;

            // Get the main ImGui Viewport
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
                    ImGuiIV.PushStyleColor(eImGuiCol.Text, GetColorFromConsoleLogStyle(255, item.Style));
                    ImGuiIV.TextUnformatted(item.ToString());
                    ImGuiIV.PopStyleColor();
                }

                // Auto-scroll
                if (canScrollToEnd)
                    ImGuiIV.SetScrollHereY(1f);

                ImGuiIV.EndListBox();
            }

            // Check if mouse is hovering over the listbox for auto-scroll
            Vector2 listBoxItemRectMin = ImGuiIV.GetItemRectMin();
            Vector2 listBoxSize = ImGuiIV.GetItemRectSize();

            canScrollToEnd = !ImGuiIV.IsMouseHoveringRect(new RectangleF(listBoxItemRectMin.X, listBoxItemRectMin.Y, listBoxSize.X, listBoxSize.Y), false);
            
            // Send command button
            ImGuiIV.Spacing(2);
            bool isEnterReleased = ImGuiIV.IsKeyReleased(eImGuiKey.ImGuiKey_Enter) || ImGuiIV.IsKeyReleased(eImGuiKey.ImGuiKey_KeypadEnter);
            if (ImGuiIV.Button("Send", new Vector2(80f, 0f)) || isEnterReleased)
            {
                if (!string.IsNullOrWhiteSpace(input))
                {
                    Logger.Log(input, true);
                    ExecuteCommand(input);
                }

                input = string.Empty;
            }
            ImGuiIV.SameLine();
            ImGuiIV.SetNextItemWidth(-1f);

            if (wasOpened)
            {
                ImGuiIV.SetKeyboardFocusHere();
                wasOpened = false;
            }

            // Input field
            if (ImGuiIV.InputText("##inputTextBox", ref input))
                selectionIndex = 0; // Reset selected index for suggestions popup
            Vector2 textboxRectMin = ImGuiIV.GetItemRectMin();
            Vector2 textboxRectSize = ImGuiIV.GetItemRectSize();

            if (clearSelection)
            {
                ImGuiIV.GetInputTextState("##inputTextBox").ClearSelection();
                clearSelection = false;
            }

            // Delete all current text entered in the console text field
            if (ImGuiIV.IsKeyPressed(eImGuiKey.ImGuiKey_Delete, false))
            {
                ImGuiIV.SetActiveID(0, ImGuiIV.GetCurrentWindow());
                ImGuiIV.SetKeyboardFocusHere(-1);

                input = string.Empty;

                ImGuiIV.GetInputTextState("##inputTextBox").ClearSelection();
            }

            // Insert the text that is currently saved in clipboard into the text field
            if (ImGuiIV.IsKeyPressed(eImGuiKey.ImGuiKey_Insert, false))
            {
                string clipboardText = Clipboard.GetText();
                if (!string.IsNullOrWhiteSpace(clipboardText))
                {
                    ImGuiIV.SetActiveID(0, ImGuiIV.GetCurrentWindow());
                    ImGuiIV.SetKeyboardFocusHere(-1);

                    input = clipboardText;

                    ImGuiIV.GetInputTextState("##inputTextBox").ClearSelection();
                }
            }

            // Check if popup can be opened or not
            if (ImGuiIV.WantsTextInput() && !string.IsNullOrWhiteSpace(input))
            {
                popupOpen = true;

                if (!ImGuiIV.IsPopupOpen("ivsdkdotnetConsoleSuggestionsPopup"))
                    selectionIndex = 0;
            }
            else
            {
                if (!isHoveringPopup)
                    popupOpen = false;
            }

            if (popupOpen)
                ImGuiIV.OpenPopup("ivsdkdotnetConsoleSuggestionsPopup");

            // Suggestions popup
            Vector2 popupPos = textboxRectMin + new Vector2(0f, textboxRectSize.Y) + new Vector2(0f, 15f);
            DoSuggestionsPopup(popupPos);

            ImGuiIV.End();
        }

    }
}
