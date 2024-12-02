using System;
using System.Runtime.InteropServices;

namespace Manager.Classes
{
    public class Win32
    {

        [DllImport("kernel32.dll")]
        public static extern uint GetCurrentThreadId();

    }
}
