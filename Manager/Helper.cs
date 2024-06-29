using System;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Numerics;
using System.Reflection;

using IVSDKDotNet;

namespace Manager
{
    internal static class Helper
    {

        #region Classes
        /// <summary>
        /// Some helper functions in use with <see cref="Process"/>.
        /// </summary>
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
            if (Debugger.IsAttached)
                Debugger.Log((int)priority, "IV-SDK .NET", string.Format(str + "\n", args));
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
        #endregion

    }
}