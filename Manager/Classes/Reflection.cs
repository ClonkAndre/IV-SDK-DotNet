using System;
using System.Reflection;

namespace Manager.Classes
{
    internal class Reflection
    {

        #region Functions
        internal static bool Init()
        {
            return LocalRAGE.Init();
        }
        #endregion

        internal class LocalRAGE
        {
            internal static bool Init()
            {
                try
                {
                    Type rageClassType = typeof(IVSDKDotNet.RAGE);

                    // Find methods
                    BindingFlags searchFlags = BindingFlags.Static | BindingFlags.NonPublic;
                    raiseOnWindowFocusChangedMethod = rageClassType.GetMethod("RaiseOnWindowFocusChanged", searchFlags);

                    // Validate
                    if (raiseOnWindowFocusChangedMethod == null)
                        throw new MissingMethodException("RAGE", "RaiseOnWindowFocusChanged");

                    return true;
                }
                catch (MissingMethodException ex)
                {
                    Logger.LogError(string.Format("Failed to find RAGE method: {0}! Some features of IV-SDK .NET might be unavailable, and certain scripts that use that specific feature, might not work as expected.", ex.Message));
                }
                catch (Exception ex)
                {
                    Logger.LogError(string.Format("Unexpected error while trying to find RAGE methods! Some features of IV-SDK .NET might be unavailable, and certain scripts that use that specific feature, might not work as expected.{0}" +
                        "Details: {0}", Environment.NewLine, ex));
                }

                return false;
            }

            // RaiseOnWindowFocusChanged
            private static MethodInfo raiseOnWindowFocusChangedMethod;
            public static bool IsRaiseOnWindowFocusChangedAvailable() => raiseOnWindowFocusChangedMethod != null;
            public static void RaiseOnWindowFocusChanged(bool focused)
            {
                if (IsRaiseOnWindowFocusChangedAvailable())
                    raiseOnWindowFocusChangedMethod.Invoke(null, new object[] { focused });
            }
        }

    }
}
