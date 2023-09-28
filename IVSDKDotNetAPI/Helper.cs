using System;
using System.Reflection;

namespace IVSDKDotNetAPI
{
    internal static class Helper
    {

        #region Functions
        public static string GetFullNameOfCallingAssembly()
        {
            return Assembly.GetEntryAssembly()?.FullName;
        }
        public static string GetNameOfCallingAssembly()
        {
            return Assembly.GetEntryAssembly()?.GetName().Name;
        }
        #endregion

    }
}
