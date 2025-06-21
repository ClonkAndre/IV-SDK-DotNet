using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;

using IVSDKDotNet;

using Manager.Classes;
using Manager.Classes.Scripts;

namespace Manager.Managers
{
    internal static class DXManager
    {

        #region Variables
        private static bool wasInitialized;
        private static ConcurrentDictionary<IntPtr, TextureResource> registeredTextures;
        #endregion

        #region Methods
        public static void Init()
        {
            if (wasInitialized)
                return;

            registeredTextures = new ConcurrentDictionary<IntPtr, TextureResource>();

            wasInitialized = true;
        }
        public static void Shutdown()
        {
            if (!wasInitialized)
                return;

            wasInitialized = false;

            if (registeredTextures != null)
            {
                registeredTextures.Clear();
                registeredTextures = null;
            }
        }

        public static void Process()
        {
            if (!wasInitialized)
                return;

            // Check for textures which can be removed
            foreach (KeyValuePair<IntPtr, TextureResource> entries in registeredTextures)
            {
                if (entries.Value.WasReleased)
                {
                    Helper.WriteToDebugOutput(Priority.Default, "Texture '{0}' (OwnerScriptID: {1}) was set as released. About to unregister from DXManager.", entries.Key, entries.Value.OwnerScriptID);
                    UnregisterTexture(entries.Key);
                }
            }
        }

        public static void DestroyAllTexturesOfThisScript(Guid id)
        {
            if (!wasInitialized)
                return;

            Helper.WriteToDebugOutput(Priority.Medium, "Getting rid of all textures of script '{0}'!", id);

            foreach (KeyValuePair<IntPtr, TextureResource> entries in registeredTextures)
            {
                if (entries.Value.OwnerScriptID == id)
                {
                    IntPtr ptr = entries.Key;
                    ImGuiIV.ReleaseTexture(ref ptr);
                }
            }
        }

        public static void ForceDestroyAllTexturesOfScriptType(ScriptType type)
        {
            if (!wasInitialized)
                return;

            Helper.WriteToDebugOutput(Priority.Medium, "Getting rid of all textures for script type '{0}'!", type);

            foreach (KeyValuePair<IntPtr, TextureResource> entries in registeredTextures)
            {
                FoundScript fs = ScriptManager.GetFoundScript(entries.Value.OwnerScriptID);

                if (fs == null)
                    continue;

                if (fs.ScriptType == type)
                {
                    IntPtr ptr = entries.Key;
                    ImGuiIV.ReleaseTexture(ref ptr);
                }
            }
        }
        public static void ForceDestroyAllTextures()
        {
            if (!wasInitialized)
                return;

            Helper.WriteToDebugOutput(Priority.Medium, "Getting rid of ALL textures!");

            foreach (KeyValuePair<IntPtr, TextureResource> entries in registeredTextures)
            {
                entries.Value.Release();
            }
        }
        #endregion

        #region Functions
        public static int GetRegisteredTexturesCount()
        {
            if (!wasInitialized)
                return 0;

            return registeredTextures.Count;
        }

        public static bool RegisterTexture(IntPtr ptr, string ownerScript, string tag = null)
        {
            if (!wasInitialized)
                return false;
            if (registeredTextures.ContainsKey(ptr))
                return false; // This texture was already registered!

            // Try get id of owner script from name
            Guid ownerScriptID = Guid.Empty;

            if (!string.IsNullOrWhiteSpace(ownerScript))
            {
                FoundScript fs = ScriptManager.GetFoundScript(ownerScript);

                if (fs != null)
                    ownerScriptID = fs.ID;
            }
            else
            {
                ownerScript = "!!! NO SCRIPT NAME PROVIDED !!!";
            }

            // Add texture
            bool result = registeredTextures.TryAdd(ptr, new TextureResource(ptr, ownerScriptID, tag));

            if (result)
                Helper.WriteToDebugOutput(Priority.Medium, "Registered texture '{0}' to DXManager for script '{1}' ({2}).", ptr, ownerScript, ownerScriptID);
            else
                Helper.WriteToDebugOutput(Priority.High, "Failed to register texture '{0}' to DXManager for script '{1}' ({2})!", ptr, ownerScript, ownerScriptID);

            return result;
        }
        public static bool UnregisterTexture(IntPtr ptr)
        {
            if (!wasInitialized)
                return false;

            // Remove texture
            bool result = registeredTextures.TryRemove(ptr, out TextureResource resource);

            if (result)
            {
                resource.WasReleased = true;
                Helper.WriteToDebugOutput(Priority.Medium, "Unregistered texture '{0}' from DXManager of script '{1}'.", ptr, resource.OwnerScriptID);
            }
            else
            {
                Helper.WriteToDebugOutput(Priority.High, "Failed to unregister texture '{0}' from DXManager!", ptr);
            }

            return result;
        }

        public static bool TryGetTextureByTag(string tag, out IntPtr texturePtr)
        {
            if (!wasInitialized)
            {
                texturePtr = IntPtr.Zero;
                return false;
            }

            IntPtr foundTexture = registeredTextures.Where(x => x.Value.Tag == tag).Select(x => x.Key).FirstOrDefault();

            if (foundTexture == IntPtr.Zero)
            {
                texturePtr = IntPtr.Zero;
                return false;
            }

            texturePtr = foundTexture;
            return true;
        }

        public static IntPtr[] GetAllRegisteredTextures()
        {
            if (!wasInitialized)
                return Array.Empty<IntPtr>();

            return registeredTextures.Select(x => x.Key).ToArray();
        }
        public static IntPtr[] GetRegisteredTexturesOfScript(Guid script)
        {
            if (!wasInitialized)
                return Array.Empty<IntPtr>();

            return registeredTextures.Where(x => x.Value.OwnerScriptID == script).Select(x => x.Key).ToArray();
        }
        #endregion

    }
}
