using System;
using System.ComponentModel;
using System.Runtime.InteropServices;
using System.Security;

namespace Manager.Windows {
    internal class WndProcHook : IDisposable {

        #region DLLImports
        [SecurityCritical, SecuritySafeCritical]
        public static IntPtr SetWindowLongPtr(IntPtr hWnd, int nIndex, IntPtr newValue)
        {
            return IntPtr.Size == 4
                ? SetWindowLong32(hWnd, nIndex, newValue)
                : SetWindowLongPtr64(hWnd, nIndex, newValue);
        }

        [DllImport("user32.dll", EntryPoint = "SetWindowLong")]
        public static extern IntPtr SetWindowLong32(IntPtr hWnd, int nIndex, IntPtr newValue);

        [DllImport("user32.dll", EntryPoint = "SetWindowLongPtr")]
        public static extern IntPtr SetWindowLongPtr64(IntPtr hWnd, int nIndex, IntPtr newValue);

        [DllImport("user32.dll")]
        public static extern IntPtr CallWindowProc(IntPtr lpPrevWndFunc, IntPtr hWnd, int msg, IntPtr wParam, IntPtr lParam);
        #endregion

        #region Variables
        private const int GWL_WNDPROC = -4;

        private bool disposedValue;
        private WindowProc newCallback;
        private IntPtr oldCallback;
        #endregion

        #region Events and Delegates

        // Delegates
        public delegate IntPtr WindowProc(IntPtr hWnd, int msg, IntPtr wParam, IntPtr lParam);
        public delegate void OnWndMessageDelegate(IntPtr hWnd, int msg, IntPtr wParam, IntPtr lParam);

        // Events
        public event OnWndMessageDelegate OnWndMessage;

        #endregion

        #region Constructor
        public WndProcHook()
        {

        }
        #endregion

        #region Disposing
        public void Dispose()
        {
            if (!disposedValue) {
                newCallback = null;
                oldCallback = IntPtr.Zero;
                disposedValue = true;
            }
        }
        #endregion

        #region Methods
        public void Init(IntPtr hWnd)
        {
            if (disposedValue)
                throw new ObjectDisposedException("This class was disposed.");

            // Hook WndProc Message
            Main.managerInstance.console.PrintDebug("[WndProcHook] Initializing WndProc Hook");
            newCallback = OnWndProc;
            oldCallback = SetWindowLongPtr(hWnd, GWL_WNDPROC, Marshal.GetFunctionPointerForDelegate(newCallback));

            // Validate oldCallback pointer
            if (oldCallback == IntPtr.Zero)
                throw new Win32Exception(Marshal.GetLastWin32Error());

            // Log
            Main.managerInstance.console.PrintDebug("[WndProcHook] Done!");
        }
        #endregion

        protected virtual IntPtr OnWndProc(IntPtr hWnd, int msg, IntPtr wParam, IntPtr lParam)
        {
            OnWndMessage?.Invoke(hWnd, msg, wParam, lParam);
            return CallWindowProc(oldCallback, hWnd, msg, wParam, lParam);
        }

    }
}
