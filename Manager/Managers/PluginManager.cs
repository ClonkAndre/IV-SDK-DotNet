using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;

using Manager.Classes;

using IVSDKDotNet.Manager;

namespace Manager.Managers
{
    public class PluginManager
    {

        #region Variables
        // Lists
        public List<FoundPlugin> activePlugins;

        // Other
        private readonly object activePluginsLockObj = new object();
        #endregion

        #region Methods
        // Load stuff
        public void LoadPlugins()
        {
            if (!Directory.Exists(CLR.CLRBridge.IVSDKDotNetPluginsPath))
            {
                Directory.CreateDirectory(CLR.CLRBridge.IVSDKDotNetPluginsPath);
                return;
            }

            // Abort currently loaded IV-SDK .NET Manager plugins
            AbortPlugins(AbortReason.Manager, false);

            // Load IV-SDK .NET Manager plugins
            string[] pluginFiles = Directory.GetFiles(CLR.CLRBridge.IVSDKDotNetPluginsPath, "*.plug", SearchOption.TopDirectoryOnly);

            for (int i = 0; i < pluginFiles.Length; i++)
                LoadAssembly(pluginFiles[i]);

            // Log
            Logger.Log(string.Format("Finished loading {0} IV-SDK .NET Manager plugins.", activePlugins.Count));
        }

        private bool LoadAssembly(string path)
        {
            if (string.IsNullOrWhiteSpace(path))
                return false;

            // Get file name without extension from given path
            string fileName = Path.GetFileNameWithoutExtension(path);

            // Check if plugin is already loaded
            FoundPlugin foundPlugin = GetFoundPlugin(fileName);

            if (foundPlugin != null)
            {
                Logger.LogWarning(string.Format("Not loading IV-SDK .NET Manager plugin '{0}' because it is already loaded.", fileName));
                return false;
            }

            // Try loading the plugin
            try
            {
                using (FileStream fs = new FileStream(path, FileMode.Open, FileAccess.Read))
                {
                    // Get byte array from file stream
                    byte[] fileByteArray = Helper.GetByteArray(fs);

                    // Load the assembly into the domain
                    Assembly assembly = Assembly.Load(fileByteArray);

                    // Get the first class that inherites from the ManagerPlugin class
                    Type scriptType = assembly.GetTypes().Where(x => x.IsSubclassOf(typeof(ManagerPlugin))).FirstOrDefault();

                    // Could not find any classes that inherit the ManagerPlugin class
                    if (scriptType == null)
                    {
                        Logger.LogWarning(string.Format("Could not load IV-SDK .NET Manager plugin '{0}' because the entry-point for the plugin could not be found.", fileName));
                        return false;
                    }

                    // Log
                    Logger.Log(string.Format("Found IV-SDK .NET plugin: {0}", scriptType.FullName));

                    // Create new instance of type for assembly
                    ManagerPlugin plugin = (ManagerPlugin)assembly.CreateInstance(scriptType.FullName);

                    if (plugin == null)
                    {
                        Logger.LogWarning(string.Format("An unknown error occured while trying to create new instance of IV-SDK .NET Manager plugin '{0}'.", fileName));
                        return false;
                    }

                    // Register AssemblyResolve event
                    //script.ScriptDomain.AssemblyResolve += ScriptDomain_AssemblyResolve;

                    // Add script to activePlugins list.
                    activePlugins.Add(new FoundPlugin(fileName, path, assembly, plugin, scriptType));

                    return true;
                }
            }
            catch (ReflectionTypeLoadException ex)
            {
                Exception[] exs = ex.LoaderExceptions;
                for (int i = 0; i < exs.Length; i++)
                {
                    Exception e = exs[i];
                    Logger.LogError(string.Format("A ReflectionTypeLoadException occured while trying to load IV-SDK .NET Manager plugin '{0}'. Details: {1}", fileName, e));
                }

#if DEBUG
                // Throw on exception when manager is a debug build and a debugger is attached
                if (Debugger.IsAttached)
                    throw;
#endif
            }
            catch (Exception ex)
            {
                Logger.LogError(string.Format("An exception occured while trying to load IV-SDK .NET Manager plugin '{0}'. Details: {1}", fileName, ex));

#if DEBUG
                // Throw on exception when manager is a debug build and a debugger is attached
                if (Debugger.IsAttached)
                    throw;
#endif
            }

            return false;
        }

        // Abort stuff
        public void AbortPlugins(AbortReason reason, bool showMessage)
        {
            if (activePlugins.Count == 0)
            {
                if (showMessage)
                    Logger.Log("There are no plugins to abort.");

                return;
            }

            // Abort plugins
            activePlugins.ForEach(x => x.Abort(reason, showMessage));
            activePlugins.Clear();

            // Force garbage collection
            GC.Collect();
            GC.WaitForPendingFinalizers();
            GC.Collect();
        }
        #endregion

        #region Functions
        public FoundPlugin GetFoundPlugin(string name)
        {
            if (string.IsNullOrWhiteSpace(name))
                return null;

            FoundPlugin fp = null;

            lock (activePluginsLockObj)
            {
                fp = activePlugins.Where(x => x.FileName.ToLower() == name.ToLower()
                    || x.EntryPoint.FullName.ToLower() == name.ToLower()).FirstOrDefault();
            }

            return fp;
        }
        public FoundPlugin GetFoundPlugin(Guid id)
        {
            FoundPlugin fp = null;

            lock (activePluginsLockObj)
            {
                fp = activePlugins.Where(x => x.ID == id).FirstOrDefault();
            }

            return fp;
        }
        #endregion

        #region Events

        #endregion

        #region Constructor
        public PluginManager()
        {
            activePlugins = new List<FoundPlugin>();
        }
        #endregion

    }
}
