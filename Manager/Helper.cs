﻿using System;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Numerics;
using System.Reflection;

using IVSDKDotNet;

namespace Manager
{
    internal class Helper
    {

        #region Classes
        public class ProcessHelper
        {

            #region DllImports
            [DllImport("user32.dll")]
            [return: MarshalAs(UnmanagedType.Bool)]
            private static extern bool GetWindowPlacement(IntPtr hWnd, ref WINDOWPLACEMENT lpwndpl);

            [DllImport("user32.dll", CharSet = CharSet.Auto, ExactSpelling = true)]
            private static extern IntPtr GetForegroundWindow();


            [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
            private static extern int GetWindowThreadProcessId(IntPtr handle, out int processId);
            #endregion

            #region Structs
            private struct WINDOWPLACEMENT
            {
                public int length;
                public int flags;
                public int showCmd;
                public System.Drawing.Point ptMinPosition;
                public System.Drawing.Point ptMaxPosition;
                public System.Drawing.Rectangle rcNormalPosition;
            }
            #endregion

            /// <summary>
            /// Gets the current window state of the given <see cref="Process"/>.
            /// </summary>
            /// <param name="p">Target <see cref="Process"/>.</param>
            /// <returns>
            /// -1 : MainWindowHandle of given <see cref="Process"/> is null.<br/>
            /// 1  : <see cref="Process"/> Window is <b>Normalized</b>.<br/>
            /// 2  : <see cref="Process"/> Window is <b>Minimized</b>.<br/>
            /// 3  : <see cref="Process"/> Window is <b>Maximized</b>.
            /// </returns>
            public static int GetProcessWindowState(Process p)
            {
                if (p.MainWindowHandle != IntPtr.Zero)
                {
                    WINDOWPLACEMENT placement = new WINDOWPLACEMENT();
                    GetWindowPlacement(p.MainWindowHandle, ref placement);
                    return placement.showCmd;
                }
                return -1;
            }

            /// <summary>
            /// Gets if the given <see cref="Process"/> has focus.
            /// </summary>
            /// <param name="p">Target <see cref="Process"/>.</param>
            /// <returns>True if the <see cref="Process"/> is in focus, otherwise false.</returns>
            public static bool IsProcessInFocus(Process p)
            {
                var activatedHandle = GetForegroundWindow();

                if (activatedHandle == IntPtr.Zero)
                    return false; // No window is currently activated

                int procId = p.Id;
                int activeProcId;
                GetWindowThreadProcessId(activatedHandle, out activeProcId);

                return activeProcId == procId;
            }

        }
        #endregion

        #region ImGUI
        public static void AskToOpenWebPageButton(bool useSmallButton, string buttonText, Vector2 size, Uri uri)
        {
            string id = "Open " + uri.ToString();

            if (useSmallButton)
            {
                if (ImGuiIV.SmallButton(buttonText))
                    ImGuiIV.OpenPopup(id);
            }
            else
            {
                if (ImGuiIV.Button(buttonText, size))
                    ImGuiIV.OpenPopup(id);
            }

            AskToOpenWebPage(id, uri);
        }
        public static void AskToOpenWebPage(string name, Uri uri)
        {
            if (uri == null)
                return;

            ImGuiIV.CreateSimplePopupDialog(name, string.Format("This link takes you to {1} ({2}).{0}Do you want to go there?", Environment.NewLine, uri.Host, uri), true, true, true, "Yes", "No", () => Process.Start(uri.ToString()), null);
        }
        #endregion

        #region Methods
        public static void WriteToDebugOutput(Priority priority, string str, params object[] args)
        {
#if DEBUG
            if (!Main.Instance.AllowWriteToDebugOutput)
                return;
            if (Debugger.IsAttached)
                Debugger.Log((int)priority, "IV-SDK .NET", string.Format(str + "\n", args));
#endif
        }
        public static void BreakInDebugger()
        {
#if DEBUG
            if (Debugger.IsAttached)
                Debugger.Break();
#endif
        }
        #endregion

        #region Functions
        public static byte[] GetByteArray(Stream input)
        {
            using (MemoryStream ms = new MemoryStream())
            {
                input.CopyTo(ms);
                return ms.ToArray();
            }
        }
        public static string GetContentOfEmbeddedResource(Assembly assembly, string resourceName)
        {
            string fullResourceName = assembly.GetManifestResourceNames().Where(str => str.EndsWith(resourceName)).FirstOrDefault();

            if (string.IsNullOrEmpty(fullResourceName))
                return string.Empty;

            // Get the target resource stream
            Stream stream = assembly.GetManifestResourceStream(fullResourceName);

            if (stream == null)
                return string.Empty;

            // Read the target resource
            using (StreamReader reader = new StreamReader(stream))
            {
                string result = reader.ReadToEnd();
                stream.Dispose();
                return result;
            }
        }

        public static bool DoesFileVersionMatchGivenVersionWithWildcards(string filePath, string version)
        {
            if (string.IsNullOrWhiteSpace(version))
                return true;
            if (!File.Exists(filePath))
                return true;

            // Get wildcard type
            FileVersionWildcards wildcards = GetWildcardsFromVersion(version);

            // Remove the wildcards from the string
            version = version.Replace("=", "").Replace(">", "").Replace("<", "").Trim();

            // Read the file version info
            FileVersionInfo fileVersionInfo = FileVersionInfo.GetVersionInfo(filePath);

            switch (wildcards)
            {
                case FileVersionWildcards.None:
                case FileVersionWildcards.Equal:

                    if (string.Compare(fileVersionInfo.FileVersion, version) == 0)
                        return true;

                    break;

                case FileVersionWildcards.Larger:

                    if (string.Compare(fileVersionInfo.FileVersion, version) == 1)
                        return true;

                    break;
                case FileVersionWildcards.LargerOrEqual:

                    if (string.Compare(fileVersionInfo.FileVersion, version) == 0
                        || string.Compare(fileVersionInfo.FileVersion, version) == 1)
                        return true;

                    break;

                case FileVersionWildcards.Lower:

                    if (string.Compare(fileVersionInfo.FileVersion, version) == -1)
                        return true;

                    break;
                case FileVersionWildcards.LowerOrEqual:

                    if (string.Compare(fileVersionInfo.FileVersion, version) == 0
                        || string.Compare(fileVersionInfo.FileVersion, version) == -1)
                        return true;

                    break;
            }

            return false;
        }
        public static FileVersionWildcards GetWildcardsFromVersion(string version)
        {
            if (string.IsNullOrWhiteSpace(version))
                return FileVersionWildcards.None;
            if (version.Length < 2)
                return FileVersionWildcards.None;

            string firstTwoChars = new string(new char[] { version[0], version[1] });

            if (firstTwoChars.Contains("<") && firstTwoChars.Contains("="))
                return FileVersionWildcards.LowerOrEqual;
            if (firstTwoChars.Contains(">") && firstTwoChars.Contains("="))
                return FileVersionWildcards.LargerOrEqual;

            if (firstTwoChars.Contains("<"))
                return FileVersionWildcards.Lower;
            if (firstTwoChars.Contains(">"))
                return FileVersionWildcards.Larger;

            if (firstTwoChars.Contains("=") || firstTwoChars.Contains("=="))
                return FileVersionWildcards.Equal;

            return FileVersionWildcards.None;
        }

        // The Directory.GetFiles function does not normally support multiple wildcards, so here's a helper function whichs adds support for it
        public static string[] GetFilesInDirectoryNoThrow(string path, string searchPattern, SearchOption searchOption, bool retrieveFileNameOnly = false)
        {
            try
            {
                string[] files = null;

                // Check if searchPattern has multiple wildcasts
                if (!searchPattern.Contains("|"))
                {
                    files = Directory.GetFiles(path, searchPattern, searchOption);
                }
                else
                {
                    string[] wildcasts = searchPattern.Split('|');

                    for (int i = 0; i < wildcasts.Length; i++)
                    {
                        string wildcast = wildcasts[i];

                        if (i == 0)
                        {
                            // Initialize and populate the array
                            files = Directory.GetFiles(path, wildcast, searchOption);
                        }
                        else
                        {
                            // Append to the array
                            files = files.Concat(Directory.GetFiles(path, wildcast, searchOption)).ToArray();
                        }
                    }
                }

                if (retrieveFileNameOnly)
                {
                    // Only get the file name
                    for (int i = 0; i < files.Length; i++)
                    {
                        files[i] = Path.GetFileName(files[i]);
                    }
                }

                return files;
            }
            catch (Exception ex)
            {
                WriteToDebugOutput(Priority.Default, "Failed to get files in directory {0}! Details: {1}", path, ex);
            }

            return Array.Empty<string>();
        }
        #endregion

    }
}