using System;
using System.Reflection;

namespace Manager.Classes
{
    internal class Reflection
    {
        #region Variables
        // RAGE
        private static MethodInfo raiseOnWindowFocusChangedMethod;
        #endregion

        #region Functions
        internal static bool Initialize()
        {
            return InitRageMethods();
        }
        private static bool InitRageMethods()
        {
            try
            {
                Type rageClassType = typeof(IVSDKDotNet.RAGE);

                // Find methods
                raiseOnWindowFocusChangedMethod = rageClassType.GetMethod("RaiseOnWindowFocusChanged", BindingFlags.Static | BindingFlags.NonPublic);

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
        #endregion

        public static bool IsRaiseOnWindowFocusChangedAvailable() => raiseOnWindowFocusChangedMethod != null;
        public static void RaiseOnWindowFocusChanged(bool focused)
        {
            if (IsRaiseOnWindowFocusChangedAvailable())
                raiseOnWindowFocusChangedMethod.Invoke(null, new object[] { focused });
        }
    }
}
