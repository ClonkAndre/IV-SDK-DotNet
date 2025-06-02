using System;
using System.Collections.Concurrent;
using System.Collections.Generic;

using IVSDKDotNet.Enums;
using IVSDKDotNet.Hooking;

namespace Manager.Managers
{
    internal static class MinHookManager
    {

        #region Variables
        private static bool wasInitialized;
        private static ConcurrentDictionary<uint, string> registeredHooks;
        private static ConcurrentQueue<uint> deleteQueue;
        #endregion

        #region Methods
        public static void Init()
        {
            if (wasInitialized)
                return;

            registeredHooks = new ConcurrentDictionary<uint, string>();
            deleteQueue = new ConcurrentQueue<uint>();

            wasInitialized = true;
        }
        public static void Shutdown()
        {
            if (!wasInitialized)
                return;

            wasInitialized = false;

            if (registeredHooks != null)
            {
                registeredHooks.Clear();
                registeredHooks = null;
            }
            if (deleteQueue != null)
            {
                deleteQueue = null;
            }
        }

        public static void Process()
        {
            if (!wasInitialized)
                return;

            // Process delete queue
            while (deleteQueue.TryDequeue(out uint key))
            {
                registeredHooks.TryRemove(key, out string ownerScript);
            }

            // Remove hooks from scripts that are no longer running
            foreach (KeyValuePair<uint, string> entry in registeredHooks)
            {
                if (!ScriptManager.DoesFoundScriptExists(entry.Value))
                {
                    deleteQueue.Enqueue(entry.Key);

                    eMinHookStatus status = ManagedMinHook.DisableHook(entry.Key);

                    Helper.WriteToDebugOutput(Priority.Default, "Disabling and removing hook {0} of script {1} because script is no longer running. DisableHook result: {2}", entry.Key.ToString("X"), entry.Value, status);
                }
            }
        }
        #endregion

        #region Functions
        public static int GetRegisteredHooksCount()
        {
            if (!wasInitialized)
                return 0;

            return registeredHooks.Count;
        }

        public static bool RegisterHook(uint address, string ownerScript)
        {
            if (!wasInitialized)
                return false;
            if (registeredHooks.ContainsKey(address))
                return false;

            bool result = registeredHooks.TryAdd(address, ownerScript);

            if (result)
                Helper.WriteToDebugOutput(Priority.Default, "Script '{0}' added hook for address {1}.", ownerScript, address.ToString("X"));

            return result;
        }
        #endregion

    }
}
