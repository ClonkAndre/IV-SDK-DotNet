using System;
using System.Reflection;

namespace Manager.Classes
{
    internal class Reflection
    {
        #region Variables
        // ImGuiIV
        private static MethodInfo callCreateTextureFromFileMethod;

        // RAGE
        private static MethodInfo callOnWindowFocusChangedMethod;
        #endregion

        #region Functions
        internal static bool Initialize()
        {
            return InitImGuiIVMethods()
                && InitRageMethods();
        }
        private static bool InitImGuiIVMethods()
        {
            try
            {
                Type imGuiIVClassType = typeof(IVSDKDotNet.ImGuiIV);

                // Find methods
                callCreateTextureFromFileMethod = imGuiIVClassType.GetMethod("CreateTextureFromMemory", BindingFlags.Static | BindingFlags.NonPublic);

                // Validate
                if (callCreateTextureFromFileMethod == null)
                    throw new MissingMethodException("ImGuiIV", "CreateTextureFromMemory");

                return true;
            }
            catch (MissingMethodException ex)
            {
                Logger.LogError(string.Format("Failed to find ImGuiIV method: {0}! Some features of IV-SDK .NET might be unavailable, and certain scripts that use that specific feature, might not work as expected.", ex.Message));
            }
            catch (Exception ex)
            {
                Logger.LogError(string.Format("Unexpected error while trying to find ImGuiIV methods! Some features of IV-SDK .NET might be unavailable, and certain scripts that use that specific feature, might not work as expected.{0}" +
                    "Details: {0}", Environment.NewLine, ex));
            }

            return false;
        }
        private static bool InitRageMethods()
        {
            try
            {
                Type rageClassType = typeof(IVSDKDotNet.RAGE);

                // Find methods
                callOnWindowFocusChangedMethod = rageClassType.GetMethod("RaiseOnWindowFocusChanged", BindingFlags.Static | BindingFlags.NonPublic);

                // Validate
                if (callOnWindowFocusChangedMethod == null)
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

        #region RAGE
        public static bool IsCallOnWindowFocusChangedAvailable() => callOnWindowFocusChangedMethod != null;
        public static void CallOnWindowFocusChanged(bool focused)
        {
            if (IsCallOnWindowFocusChangedAvailable())
                callOnWindowFocusChangedMethod.Invoke(null, new object[] { focused });
        }
        #endregion

        #region ImGuiIV
        public static bool IsCallCreateTextureFromFileAvailable() => callCreateTextureFromFileMethod != null;
        public static IntPtr CallCreateTextureFromFile(byte[] data)
        {
            if (!IsCallCreateTextureFromFileAvailable())
                return IntPtr.Zero;

            return (IntPtr)callCreateTextureFromFileMethod.Invoke(null, new object[] { data });
        }
        #endregion
    }
}
