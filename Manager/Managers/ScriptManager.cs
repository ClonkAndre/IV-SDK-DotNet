using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Windows.Forms;

using IVSDKDotNet;

using Manager.Classes;
using Manager.Classes.Scripts;
using Manager.UI;

namespace Manager.Managers
{
    internal static class ScriptManager
    {

        #region Variables
        private static bool wasInitialized;

        // TODO: Maybe make this a ConcurrentDictionary for faster loopups and thread safety
        // Would need to figure out what i could use as the key for the dictionary as the scripts guid is only set after the script constructed...
        private static object lockObj = new object();
        private static List<FoundScript> activeScripts;

        public static DateTime TimeSinceLastScriptLoad;
        #endregion

        #region Methods

        public static void Init()
        {
            if (wasInitialized)
                return;

            activeScripts = new List<FoundScript>();

            wasInitialized = true;
        }
        public static void Shutdown()
        {
            if (!wasInitialized)
                return;

            wasInitialized = false;

            if (activeScripts != null)
            {
                activeScripts.Clear();
                activeScripts = null;
            }
        }

        public static void ClearActiveScripts()
        {
            if (!wasInitialized)
                return;

            activeScripts.Clear();
        }

        public static void LoadScriptsInternal()
        {
            if (!wasInitialized)
                return;

            Helper.WriteToDebugOutput(Priority.Default, "- - - About to load both IV-SDK .NET and ScriptHookDotNet scripts... - - -");

            LoadIVSDKDotNetScripts();
            LoadSHDNScripts();
        }
        public static void LoadIVSDKDotNetScripts()
        {
            if (!wasInitialized)
                return;

            Helper.WriteToDebugOutput(Priority.Default, "- About to load IV-SDK .NET scripts... -");

            //if (!Directory.Exists(CLR.CLRBridge.IVSDKDotNetScriptsPath))
            //{
            //    Directory.CreateDirectory(CLR.CLRBridge.IVSDKDotNetScriptsPath);
            //    return;
            //}

            // Abort currently loaded IV-SDK .NET scripts
            AbortScripts(ScriptType.IVSDKDotNet, AbortReason.Manager);

            // Load IV-SDK .NET scripts
            //string[] scriptFiles = Directory.GetFiles(CLR.CLRBridge.IVSDKDotNetScriptsPath, "*.ivsdk.dll", SearchOption.TopDirectoryOnly).OrderBy(x => Path.GetFileName(x)).ToArray();
            string[] scriptFiles = FileCacheManager.GetCachedFiles(Folder.IVSDKDotNet_Scripts).OrderBy(x => Path.GetFileName(x)).ToArray();

            int count = 0;

            for (int i = 0; i < scriptFiles.Length; i++)
            {
                if (LoadAssembly(scriptFiles[i]))
                    count++;
            }

            // Log
            Helper.WriteToDebugOutput(Priority.Default, "- Finished loading IV-SDK .NET scripts! -");
            Logger.LogEx("Finished loading {0} IV-SDK .NET script(s).", count);

            TimeSinceLastScriptLoad = DateTime.Now;
        }
        public static void LoadSHDNScripts()
        {
            if (!wasInitialized)
                return;

            if (CLR.CLRBridge.DisableScriptHookDotNetLoading)
            {
                NotificationUI.ShowNotification(NotificationType.Warning, DateTime.UtcNow.AddSeconds(7d), "Could not load ScriptHookDotNet mods", "The IV-SDK .NET ScriptHookDotNet mod loader got disabled because the old ScriptHookDotNet is currently installed.", "SHDN_MOD_LOADING_IS_DISABLED");
                return;
            }
            if (!Config.LoadScriptHookDotNetScripts)
                return;

            Helper.WriteToDebugOutput(Priority.Default, "- About to load ScriptHookDotNet scripts... -");

            //string shdnScriptsPath = string.Format("{0}\\scripts", IVGame.GameStartupPath);

            //if (!Directory.Exists(shdnScriptsPath))
            //    return;

            // Abort currently loaded ScriptHookDotNet scripts
            AbortScripts(ScriptType.ScriptHookDotNet, AbortReason.Manager);

            // Load ScriptHookDotNet scripts
            //string[] scriptFiles = Directory.GetFiles(shdnScriptsPath, "*.net.dll", SearchOption.TopDirectoryOnly).OrderBy(x => Path.GetFileName(x)).ToArray();
            string[] scriptFiles = FileCacheManager.GetCachedFiles(Folder.Scripts).OrderBy(x => Path.GetFileName(x)).ToArray();

            int count = 0;

            for (int i = 0; i < scriptFiles.Length; i++)
            {
                if (LoadAssembly(scriptFiles[i]))
                    count++;
            }

            // Log
            Helper.WriteToDebugOutput(Priority.Default, "- Finished loading ScriptHookDotNet scripts! -");
            Logger.Log(string.Format("Finished loading {0} ScriptHookDotNet script(s).", count));

            TimeSinceLastScriptLoad = DateTime.Now;
        }

        public static void LoadScript(string name)
        {
            if (!wasInitialized)
                return;

            //if (!Directory.Exists(CLR.CLRBridge.IVSDKDotNetScriptsPath))
            //{
            //    Directory.CreateDirectory(CLR.CLRBridge.IVSDKDotNetScriptsPath);
            //    return;
            //}

            // Check if script with this name is already loaded
            FoundScript fs = GetFoundScript(name);

            if (fs != null)
            {
                Logger.LogWarningEx("Script {0} is already loaded.", name);
                return;
            }

            //// Get path to script file
            string scriptPath = FileCacheManager.GetFullPathOfCachedFile(name, Folder.Scripts | Folder.IVSDKDotNet_Scripts);
            //string scriptPath = string.Format("{0}\\{1}", CLR.CLRBridge.IVSDKDotNetScriptsPath, name);

            //// Check if file exists
            //if (!File.Exists(scriptPath))
            //{
            //    Logger.LogWarningEx("File {0} does not exists in the scripts folder!", name);
            //    return;
            //}
            if (string.IsNullOrEmpty(scriptPath))
            {
                Logger.LogWarningEx("Could not find script file {0}!", name);
                return;
            }

            // Try to load script
            if (LoadAssembly(scriptPath))
                Logger.LogEx("Script {0} got loaded!", name);
        }

        public static void CreateAndLaunchAllScriptThreads()
        {
            if (!wasInitialized)
                return;

            activeScripts.ForEach(fs =>
            {
                fs.CreateAndLaunchThread();
            });
        }

        public static void AbortScripts(ScriptType scriptsToAbort, AbortReason reason, bool showMessage = false)
        {
            if (!wasInitialized)
                return;

            if (GetActiveScriptsCount() == 0)
            {
                if (showMessage)
                    Logger.Log("There are no scripts to abort.");

                return;
            }

            Helper.WriteToDebugOutput(Priority.High, "- - - About to abort all scripts of type '{0}'! Reason: {1} - - -", scriptsToAbort, reason);

            lock (lockObj)
            {
                switch (scriptsToAbort)
                {
                    case ScriptType.All:
                        {
                            FoundScript[] arr = activeScripts.Where(x => x.CanScriptBeAborted(reason, false)).ToArray();

                            // Let plugins know
                            PluginManager.RaiseOnBeforeScriptsAbort(arr.Select(x => x.ID).ToArray());

                            for (int i = 0; i < arr.Length; i++)
                                arr[i].Abort(reason, showMessage);

                            ClearActiveScripts();

                            // Let plugins know
                            PluginManager.RaiseOnAfterScriptsAbort();

                            //// IV-SDK .NET scripts
                            //ActiveScripts.ForEach(x =>
                            //{
                            //    if (x.IsIVSDKDotNetScript)
                            //        x.Abort(reason, showMessage);
                            //});
                            //ActiveScripts.RemoveAll(x =>
                            //{
                            //    // Dont remove script from list if it cannot be aborted
                            //    if (!x.CanScriptBeAborted(reason, false))
                            //        return false;

                            //    return x.IsIVSDKDotNetScript;
                            //});

                            //// ScriptHookDotNet scripts
                            //ActiveScripts.ForEach(x =>
                            //{
                            //    if (x.IsScriptHookDotNetScript)
                            //        x.Abort(reason, showMessage);
                            //});
                            //ActiveScripts.RemoveAll(x => x.IsScriptHookDotNetScript);

                            // Get rid of registered textures that couldn't be assigned to any script
                            Main.Instance.DestroyGlobalRegisteredTextures();

                            // Clear ScriptHookDotNet Cache
                            SHDNContentCacheManager.ForceRemoveAll();
                        }
                        break;
                    case ScriptType.IVSDKDotNet:
                        {
                            FoundScript[] arr = activeScripts.Where(x => x.CanScriptBeAborted(reason, false)).ToArray();

                            // Let plugins know
                            PluginManager.RaiseOnBeforeScriptsAbort(arr.Select(x => x.ID).ToArray());

                            for (int i = 0; i < arr.Length; i++)
                                arr[i].Abort(reason, showMessage);

                            //// IV-SDK .NET scripts
                            //ActiveScripts.ForEach(x =>
                            //{
                            //    if (x.IsIVSDKDotNetScript)
                            //        x.Abort(reason, showMessage);
                            //});

                            activeScripts.RemoveAll(x =>
                            {
                                // Dont remove script from list if it cannot be aborted
                                if (!x.CanScriptBeAborted(reason, false))
                                    return false;

                                return x.IsIVSDKDotNetScript;
                            });

                            // Let plugins know
                            PluginManager.RaiseOnAfterScriptsAbort();
                        }
                        break;
                    case ScriptType.ScriptHookDotNet:
                        {
                            FoundScript[] arr = activeScripts.Where(x => x.IsScriptHookDotNetScript).ToArray();

                            // Let plugins know
                            PluginManager.RaiseOnBeforeScriptsAbort(arr.Select(x => x.ID).ToArray());

                            for (int i = 0; i < arr.Length; i++)
                                arr[i].Abort(reason, showMessage);

                            //// ScriptHookDotNet scripts
                            //ActiveScripts.ForEach(x =>
                            //{
                            //    if (x.IsScriptHookDotNetScript)
                            //        x.Abort(reason, showMessage);
                            //});

                            activeScripts.RemoveAll(x => x.IsScriptHookDotNetScript);

                            // Let plugins know
                            PluginManager.RaiseOnAfterScriptsAbort();

                            // Clear ScriptHookDotNet Cache
                            SHDNContentCacheManager.ForceRemoveAll();
                        }
                        break;
                }
            }

            Helper.WriteToDebugOutput(Priority.High, "- - - Finished aborting scripts. - - -");

            // Force garbage collection
            GC.Collect();
            GC.WaitForPendingFinalizers();
            GC.Collect();
        }
        public static void AbortScriptTasks(Guid scriptId)
        {
            if (!wasInitialized)
                return;

            AdvancedTask[] tasks = Main.Instance.ActiveTasks.Where(x => x.OwnerID == scriptId).ToArray();

            if (tasks.Length == 0)
                return;

            for (int i = 0; i < tasks.Length; i++)
            {
                AdvancedTask advancedTask = tasks[i];

                advancedTask.PauseTimer = true;
                advancedTask.RequestCancellation();
            }
        }

        public static void HandleScriptException(FoundScript target, string eventErrorOccuredIn, Exception ex, bool exceptionWithinCtor = false, double notifySecondsVisible = 8.0d)
        {
            if (!wasInitialized)
                return;

            // Stop script so it doesn't raise any events anymore
            target.Stop();

            string scriptName = target.EntryPoint.FullName;

            // Figure out what kind of exception we got, so we can add a possible solution text to the notification
            string possibleSolution = null;

            if (ex is MissingFieldException || ex is MissingMemberException || ex is MissingMethodException || ex is TypeLoadException)
            {
                possibleSolution = "Possible Solution: Make sure the MOD itself, its DEPENDENCIES and IV-SDK .NET is up-to-date.";
            }
            else if (ex is FileNotFoundException || ex is DirectoryNotFoundException)
            {
                possibleSolution = "Possible Solution: Make sure the target file/directory is within its desired location, it's not renamed or deleted.";
            }
            else if (ex is UnauthorizedAccessException)
            {
                possibleSolution = "Possible Solution: Make sure GTA has sufficient permissions for the current directory e.g. not within a program files folder, or any other system protected folder.";
            }
            else if (ex is NotImplementedException)
            {
                possibleSolution = "Let the mod developer know that something was marked as not implemented yet.";
            }
            else if (ex is IVSDKDotNet.Exceptions.NativeNotFoundException)
            {
                possibleSolution = "Let the mod developer know, make sure the native was spelled correctly if you are the dev, or open up a new issue on the IV-SDK .NET GitHub repository.";
            }

            // Show and Log the error
            ScriptType scriptType = target.ScriptType;

            string notificationMsg = string.Format("[{0}] An error occured in {1} {2}. More details in console.", scriptType, scriptName, eventErrorOccuredIn);

            if (exceptionWithinCtor)
                notificationMsg = string.Format("[{0}] An error occured while constructing script {1}! More details in console.", scriptType, scriptName);

            NotificationContent content = new NotificationContent(
                notificationMsg,
                ex.Message,
                possibleSolution);

            NotificationUI.ShowNotificationEx(
                NotificationType.Error,
                DateTime.UtcNow.AddSeconds(notifySecondsVisible),
                content,
                string.Concat("ERROR_IN_SCRIPT_", scriptName));

            if (!exceptionWithinCtor)
            {
                Logger.LogErrorEx("Exception caught in '{0}' event of {1} script '{2}'. Error details available below. The script will now abort.", eventErrorOccuredIn, scriptType, scriptName);

                if (possibleSolution != null)
                    Logger.LogError(possibleSolution);

                Logger.LogErrorEx("Details: {0}", ex);
            }

            // Abort script
            AbortScriptInternal(AbortReason.Manager, target, true, true);
        }
        public static void HandleScriptIdConflict(ScriptType scriptType, object script, string fullName)
        {
            if (!wasInitialized)
                return;
            if (script == null)
                return;

            // Dispose script
            switch (scriptType)
            {
                case ScriptType.IVSDKDotNet:

                    ((Script)script).Dispose();

                    // Log to console
                    Logger.LogErrorEx("Could not load IV-SDK .NET script '{0}' because its ID conflicts with the ID of another loaded script.", fullName);

                    break;
                case ScriptType.ScriptHookDotNet:

                    ((GTA.Script)script).Dispose();

                    // Log to console
                    Logger.LogErrorEx("Could not load ScriptHookDotNet script '{0}' because its ID conflicts with the ID of another loaded script.", fullName);

                    break;
            }

            Logger.LogError("Possible Solution: Reload the scripts to get rid of the ID conflict. Or let the mod developer know if this issue keeps occuring.");

            // Show notification
            NotificationContent content = new NotificationContent(
                string.Format("Could not load IV-SDK .NET script '{0}'!", fullName),
                "The ID of this script conflicts with another ID of an already loaded script.",
                "Possible Solution: Reload the scripts to get rid of the ID conflict. Or let the mod developer know if this issue keeps occuring.");

            NotificationUI.ShowNotificationEx(
                NotificationType.Error,
                DateTime.UtcNow.AddSeconds(8d),
                content,
                null);
        }

        #endregion

        #region Functions

        public static List<FoundScript> GetActiveScripts()
        {
            if (!wasInitialized)
                return null;

            return activeScripts;
        }
        public static int GetActiveScriptsCount()
        {
            if (!wasInitialized)
                return 0;

            return activeScripts.Count;
        }

        public static bool AreAllScriptsConstructed()
        {
            if (!wasInitialized)
                return false;

            return activeScripts.All(x => x.WasConstructed());
        }
        public static bool GetConstructedScriptsCount(out int constructedScripts, out int scriptsToConstruct)
        {
            if (!wasInitialized)
            {
                constructedScripts = 0;
                scriptsToConstruct = 0;
                return false;
            }

            constructedScripts = activeScripts.Count(x => x.WasConstructed());
            scriptsToConstruct = activeScripts.Count(x => !x.CanScriptConstructInstantly());
            return true;
        }

        public static Script[] GetIVSDKDotNetScripts()
        {
            if (!wasInitialized)
                return Array.Empty<Script>();

            return activeScripts.Where(x => x.IsIVSDKDotNetScript).Select(x => x.GetScriptAs<Script>()).ToArray();
        }
        public static GTA.Script[] GetScriptHookDotNetScripts()
        {
            if (!wasInitialized)
                return Array.Empty<GTA.Script>();

            return activeScripts.Where(x => x.IsScriptHookDotNetScript).Select(x => x.GetScriptAs<GTA.Script>()).ToArray();
        }

        public static Script GetIVSDKDotNetScript(Guid id)
        {
            if (!wasInitialized)
                return null;

            return GetIVSDKDotNetScripts().Where(x => x.ID == id).FirstOrDefault();
        }
        public static Script GetIVSDKDotNetScript(string name)
        {
            if (!wasInitialized)
                return null;

            return activeScripts.Where(x => x.TheFileInfo.DoesStringMatchWithAnyFileName(name) || x.EntryPoint.FullName == name || x.IsIVSDKDotNetScript).Select(x => x.GetScriptAs<Script>()).FirstOrDefault();
        }
        public static GTA.Script GetScriptHookDotNetScript(Guid id)
        {
            if (!wasInitialized)
                return null;

            return GetScriptHookDotNetScripts().Where(x => x.GUID == id).FirstOrDefault();
        }

        public static string[] GetEntryPointNameOfActiveScripts()
        {
            if (!wasInitialized)
                return null;

            return activeScripts.Where(x => x.WasConstructed()).Select(x => x.GetEntryPointName()).ToArray();
        }

        public static FoundScript GetFoundScript(Guid id)
        {
            if (!wasInitialized)
                return null;

            return activeScripts.Where(x => x.ID == id).FirstOrDefault();
        }
        public static FoundScript GetFoundScript(string name)
        {
            if (!wasInitialized)
                return null;
            if (string.IsNullOrWhiteSpace(name))
                return null;

            return activeScripts.Where(x => x.TheFileInfo.DoesStringMatchWithAnyFileName(name, true)
                    || x.EntryPoint.FullName.ToLower() == name.ToLower()).FirstOrDefault();
        }

        public static bool DoesFoundScriptExists(Guid id)
        {
            if (!wasInitialized)
                return false;

            return activeScripts.Any(x => x.ID == id);
        }
        public static bool DoesFoundScriptExists(string name)
        {
            if (!wasInitialized)
                return false;

            return activeScripts.Any(x => x.TheFileInfo.DoesStringMatchWithAnyFileName(name, true)
                || x.EntryPoint.FullName.ToLower() == name.ToLower());
        }

        public static bool AddFoundScript(FoundScript script)
        {
            if (!wasInitialized)
                return false;
            if (ContainsFoundScript(script))
                return false;

            activeScripts.Add(script);
            return true;
        }
        public static bool ContainsFoundScript(FoundScript script)
        {
            if (!wasInitialized)
                return false;

            return activeScripts.Contains(script);
        }
        public static bool RemoveFoundScript(FoundScript script)
        {
            if (!wasInitialized)
                return false;

            return activeScripts.Remove(script);
        }

        public static bool AbortScriptInternal(AbortReason reason, FoundScript script, bool showMessage, bool forceAbort = false)
        {
            if (!wasInitialized)
                return false;

            if (script != null)
            {
                if (showMessage)
                    Logger.Log(string.Format("Aborting script {0}...", script.EntryPoint.FullName));

                script.Abort(reason, showMessage, forceAbort);

                bool result = RemoveFoundScript(script);
                GC.Collect();
                return result;
            }

            return false;
        }
        public static bool AbortScriptInternal(AbortReason reason, Guid id, bool showMessage, bool forceAbort = false)
        {
            if (!wasInitialized)
                return false;

            return AbortScriptInternal(reason, GetFoundScript(id), showMessage, forceAbort);
        }

        private static bool HandleScriptHookDotNetAssemblyLoading(ScriptFileInfo scriptFileInfo, Assembly assembly)
        {
            Type[] entryPointTypes = assembly.GetTypes().Where(x => x.IsSubclassOf(typeof(GTA.Script))).ToArray();

            if (entryPointTypes.Length == 0)
            {
                Logger.LogWarningEx("Could not load ScriptHookDotNet script '{0}' because no entry-point could be found.", scriptFileInfo.FileName);
                return false;
            }

            for (int i = 0; i < entryPointTypes.Length; i++)
            {
                Type entryPointType = entryPointTypes[i];

                // Log
                Logger.Log(string.Format("Found ScriptHookDotNet script '{0}' within file '{1}'. It will construct at a later point.", entryPointType.FullName, scriptFileInfo.FileName));

                // Create new FoundScript object for each script inside the given assembly
                // The FoundScript object does not actually get initialized fully.
                // When the constructor of the GTA.Script gets called, it will handle the initialization of the FoundScript object (SHDN_LateInitializeScript function will get called).
                FoundScript foundScript = new FoundScript(scriptFileInfo, assembly, entryPointType);

                // We need to put it in the list early for ScriptHookDotNet so the SHDN_LateInitializeScript function can find the script in the ActiveScripts list.
                AddFoundScript(foundScript);
            }

            return true;
        }
        public static bool LoadAssembly(string path)
        {
            if (!wasInitialized)
                return false;
            if (string.IsNullOrWhiteSpace(path))
                return false;

            ScriptFileInfo scriptFileInfo = new ScriptFileInfo(path);

            if (!scriptFileInfo.Parse())
                return false;

            // Check if script is already loaded
            FoundScript foundScript = GetFoundScript(scriptFileInfo.FileNameWithoutExtension);

            if (foundScript != null)
            {
                Logger.LogWarningEx("Not loading script '{0}' because it is already loaded.", scriptFileInfo.FileName);
                return false;
            }

            // Try loading the assembly and get the script entry-point type from the loaded assembly
            try
            {
                using (FileStream fs = scriptFileInfo.OpenStream())
                {
                    // Load the assembly into the domain
                    Assembly assembly = Assembly.Load(Helper.GetByteArray(fs));

                    // If script is a ScriptHookDotNet script then handle it differently
                    if (scriptFileInfo.IsScriptHookDotNetScript)
                    {
                        return HandleScriptHookDotNetAssemblyLoading(scriptFileInfo, assembly);
                    }

                    // Get the first class that inherites from the IVSDKDotNet.Script class
                    // TODO: Add the ability for the dev to mark more then 1 class as a IV-SDK .NET Script within an assembly?
                    Type entryPointType = assembly.GetTypes().Where(x => x.IsSubclassOf(typeof(Script))).FirstOrDefault();

                    // Could not find any classes that inherit the IVSDKDotNet.Script class
                    if (entryPointType == null)
                    {
                        Logger.LogWarningEx("Could not load IV-SDK .NET script '{0}' because the entry-point could not be found.", scriptFileInfo.FileName);
                        return false;
                    }

                    // Log
                    Logger.LogEx("Found IV-SDK .NET script '{0}' within file '{1}'.", entryPointType.FullName, scriptFileInfo.FileName);

                    // Check if script was made with an older IVSDKDotNetWrapper version and user wants to prevent older scripts from loading
                    if (Config.DoNotLoadLegacyScripts)
                    {
                        AssemblyName referencedWrapperAssembly = assembly.GetReferencedAssemblies().Where(x => x.Name == "IVSDKDotNetWrapper").FirstOrDefault();

                        if (referencedWrapperAssembly.Version < CLR.CLRBridge.Version)
                        {

                            Logger.LogWarningEx("Script '{0}' did not get loaded because it was created with an older version of the IVSDKDotNetWrapper.dll ({1}) and the setting 'DoNotLoadLegacyScripts' is set to true." +
                                " The current version of the IVSDKDotNetWrapper.dll is: {2}", scriptFileInfo.FileName, referencedWrapperAssembly.Version, CLR.CLRBridge.Version);

                            NotificationUI.ShowNotification(NotificationType.Error, DateTime.UtcNow.AddSeconds(6d),
                                string.Format("Script {0} did not get loaded.", scriptFileInfo.FileName),
                                "Check console for details.",
                                "COULD_NOT_LOAD_SCRIPT");

                            return false;
                        }
                    }

                    // Create new FoundScript object
                    foundScript = new FoundScript(scriptFileInfo, assembly, entryPointType);

                    // Instantly add to active scripts list
                    AddFoundScript(foundScript);

                    // Try get the script config
                    if (foundScript.GetScriptConfig())
                    {
                        // Check if required dependencies are present
                        if (!foundScript.AreScriptConfigDependenciesPresent())
                        {
                            RemoveFoundScript(foundScript);

                            // Show message to user
                            string desc = "Could not load this script because it requires some dependencies which are not present in your main directory.";
                            StringBuilder sb = new StringBuilder(desc);
                            sb.AppendLine(Environment.NewLine);
                            sb.AppendLine("Required Dependencies");
                            sb.AppendLine(string.Join(Environment.NewLine, foundScript.Config.Dependencies));

                            Main.Instance.AddPendingPopup(new ImPopup(scriptFileInfo.FileName, sb.ToString(), true, "OK", null, null, null));

                            Logger.LogWarningEx("Could not load IV-SDK .NET script '{0}' because there are some required dependencies missing.", scriptFileInfo.FileName);

                            return false;
                        }

                        // Check if incompatible mods are present
                        if (foundScript.AreScriptConfigIncompatibleModsPresent())
                        {
                            string scriptFileName = scriptFileInfo.FileName;

                            StringBuilder sb = new StringBuilder();
                            sb.AppendLine("Not loading this script because you've some mods that are incompatible with this script.");
                            sb.Append("You can try to load this script anyway, but you might encounter some bugs or incompatibilities.");
                            sb.AppendLine(Environment.NewLine);
                            sb.AppendLine("Incompatible Modifications");
                            sb.AppendLine("- " + string.Join(", ", foundScript.Config.IncompatibleMods));

                            Main.Instance.AddPendingPopup(new ImPopup(scriptFileInfo.FileName, sb.ToString(), new System.Numerics.Vector2(600f, 0f), true, "OK", "Load anyway", 
                                () =>
                                {
                                    RemoveFoundScript(foundScript);
                                    Logger.LogWarningEx("Not loading IV-SDK .NET script '{0}' because you've some mods that are incompatible with this script.", scriptFileName);
                                },
                                () =>
                                {
                                    Logger.LogWarningEx("User decided to load IV-SDK .NET script '{0}' anyway, even tho they have incompatible mods installed.", scriptFileName);

                                    // Construct script instantly if allowed to
                                    if (foundScript.CanScriptConstructInstantly())
                                    {
                                        // Try construct the script
                                        if (!foundScript.ConstructScript())
                                            RemoveFoundScript(foundScript); // Construction failed. Remove from active scripts list
                                    }
                                    else
                                    {
                                        Logger.LogEx("IV-SDK .NET script '{0}' will construct at a later point.", scriptFileName);
                                    }
                                }));

                            return false;
                        }
                    }

                    // Construct script instantly if allowed to
                    if (foundScript.CanScriptConstructInstantly())
                    {
                        // Try construct the script
                        if (!foundScript.ConstructScript())
                        {
                            RemoveFoundScript(foundScript); // Construction failed. Remove from active scripts list
                            return false;
                        }
                    }
                    else
                    {
                        Logger.LogEx("IV-SDK .NET script '{0}' will construct at a later point.", scriptFileInfo.FileName);
                    }

                    return true;
                }
            }
            catch (ReflectionTypeLoadException ex)
            {
                Logger.LogError("=======================================================================================");
                Logger.LogErrorEx("A ReflectionTypeLoadException occured while trying to load script '{0}'!", scriptFileInfo.FileName);
                Logger.LogErrorEx("Details: {0}", ex);

                Exception[] exs = ex.LoaderExceptions;
                for (int i = 0; i < exs.Length; i++)
                {
                    Exception e = exs[i];
                    Logger.LogErrorEx("- LoaderException #{0}: {1}", i + 1, e);
                }
                Logger.LogError("=======================================================================================");

#if DEBUG
                // Throw on exception when manager is a debug build and a debugger is attached
                if (Debugger.IsAttached)
                    throw;
#endif
            }
            catch (Exception ex)
            {
                Logger.LogError("=======================================================================================");
                Logger.LogErrorEx("An exception occured while trying to load script '{0}'!", scriptFileInfo.FileName);
                Logger.LogErrorEx("Details: {0}", ex);
                Logger.LogError("=======================================================================================");

#if DEBUG
                // Throw on exception when manager is a debug build and a debugger is attached
                if (Debugger.IsAttached)
                    throw;
#endif
            }

            return false;
        }

        public static bool SendScriptCommand(Guid sender, Guid toScript, string command, object[] parameters, out object result)
        {
            // Find target script that should receive the script command
            FoundScript foundScript = GetFoundScript(toScript);

            if (foundScript != null)
            {
                try
                {
                    // Try send script command to target script
                    if (foundScript.RaiseScriptCommandReceived(sender, command, parameters, out object res))
                    {
                        result = res;
                        return true;
                    }
                }
                catch (Exception ex)
                {
                    HandleScriptException(foundScript, "ScriptCommandReceived", ex);
                }
            }

            result = null;
            return false;
        }
        public static bool SendScriptCommand(Guid sender, string toScript, string command, object[] parameters, out object result)
        {
            // Find target script that should receive the script command
            FoundScript foundScript = GetFoundScript(toScript);

            if (foundScript != null)
            {
                try
                {
                    // Try send script command to target script
                    if (foundScript.RaiseScriptCommandReceived(sender, command, parameters, out object res))
                    {
                        result = res;
                        return true;
                    }
                }
                catch (Exception ex)
                {
                    HandleScriptException(foundScript, "ScriptCommandReceived", ex);
                }
            }

            result = null;
            return false;
        }

        #endregion

        #region Raisers
        public static void RaiseTick()
        {
            if (!wasInitialized)
                return;

            activeScripts.ForEach(fs =>
            {
                try
                {
                    fs.RaiseTick();
                }
                catch (Exception ex)
                {
                    HandleScriptException(fs, "Tick", ex);
                }
            });
        }
        public static void RaiseGameLoad()
        {
            if (!wasInitialized)
                return;

            activeScripts.ForEach(fs =>
            {
                try
                {
                    fs.RaiseGameLoad();
                }
                catch (Exception ex)
                {
                    HandleScriptException(fs, "GameLoad", ex);
                }
            });
        }
        public static void RaiseGameLoadPriority()
        {
            if (!wasInitialized)
                return;

            activeScripts.ForEach(fs =>
            {
                try
                {
                    fs.RaiseGameLoadPriority();
                }
                catch (Exception ex)
                {
                    HandleScriptException(fs, "GameLoadPriority", ex);
                }
            });
        }
        public static void RaiseMountDevice()
        {
            if (!wasInitialized)
                return;

            activeScripts.ForEach(fs =>
            {
                try
                {
                    fs.RaiseMountDevice();
                }
                catch (Exception ex)
                {
                    HandleScriptException(fs, "MountDevice", ex);
                }
            });
        }
        public static void RaiseDrawing()
        {
            if (!wasInitialized)
                return;

            activeScripts.ForEach(fs =>
            {
                try
                {
                    fs.RaiseDrawing();
                }
                catch (Exception ex)
                {
                    HandleScriptException(fs, "Drawing", ex);
                }
            });
        }
        public static void RaiseProcessCamera()
        {
            if (!wasInitialized)
                return;

            activeScripts.ForEach(fs =>
            {
                try
                {
                    fs.RaiseProcessCamera();
                }
                catch (Exception ex)
                {
                    HandleScriptException(fs, "ProcessCamera", ex);
                }
            });
        }
        public static void RaiseProcessAutomobile(UIntPtr vehPtr)
        {
            if (!wasInitialized)
                return;

            activeScripts.ForEach(fs =>
            {
                try
                {
                    fs.RaiseProcessAutomobile(vehPtr);
                }
                catch (Exception ex)
                {
                    HandleScriptException(fs, "ProcessAutomobile", ex);
                }
            });
        }
        public static void RaiseProcessPad(UIntPtr padPtr)
        {
            if (!wasInitialized)
                return;

            activeScripts.ForEach(fs =>
            {
                try
                {
                    fs.RaiseProcessPad(padPtr);
                }
                catch (Exception ex)
                {
                    HandleScriptException(fs, "ProcessPad", ex);
                }
            });
        }
        public static void RaiseIngameStartup()
        {
            if (!wasInitialized)
                return;

            activeScripts.ForEach(fs =>
            {
                try
                {
                    fs.RaiseIngameStartup();
                }
                catch (Exception ex)
                {
                    HandleScriptException(fs, "IngameStartup", ex);
                }
            });
        }

        public static void RaiseOnD3D9Frame(IntPtr devicePtr, ImGuiIV_DrawingContext ctx)
        {
            if (!wasInitialized)
                return;

            activeScripts.ForEach(fs =>
            {
                try
                {
                    fs.RaiseOnImGuiRendering(devicePtr, ctx);
                }
                catch (Exception ex)
                {
                    HandleScriptException(fs, "OnImGuiRendering", ex);
                }

                // The script itself might've changed the style of ImGui so we need to reset it for the next script
                UIStyles.ResetImGuiStyle();
            });
        }

        public static void RaiseKeyDown(object sender, KeyEventArgs e)
        {
            if (!wasInitialized)
                return;

            activeScripts.ForEach(fs =>
            {
                if (fs.IsScriptHookDotNetScript)
                {
                    fs.QueueOnThreadDispatcher(() =>
                    {
                        try
                        {
                            fs.RaiseKeyDown(sender, e);
                        }
                        catch (Exception ex)
                        {
                            HandleScriptException(fs, "KeyDown", ex);
                        }
                    });
                }
                else
                {
                    try
                    {
                        fs.RaiseKeyDown(sender, e);
                    }
                    catch (Exception ex)
                    {
                        HandleScriptException(fs, "KeyDown", ex);
                    }
                }
            });
        }
        public static void RaiseKeyUp(object sender, KeyEventArgs e)
        {
            if (!wasInitialized)
                return;

            activeScripts.ForEach(fs =>
            {
                if (fs.IsScriptHookDotNetScript)
                {
                    fs.QueueOnThreadDispatcher(() =>
                    {
                        try
                        {
                            fs.RaiseKeyUp(sender, e);
                        }
                        catch (Exception ex)
                        {
                            HandleScriptException(fs, "KeyUp", ex);
                        }
                    });
                }
                else
                {
                    try
                    {
                        fs.RaiseKeyUp(sender, e);
                    }
                    catch (Exception ex)
                    {
                        HandleScriptException(fs, "KeyUp", ex);
                    }
                }
            });
        }

        public static void RaiseOnConsoleCommand(string command, string[] args)
        {
            if (!wasInitialized)
                return;

            activeScripts.ForEach(fs =>
            {
                if (fs.IsScriptHookDotNetScript)
                {
                    fs.QueueOnThreadDispatcher(() =>
                    {
                        try
                        {
                            fs.RaiseOnConsoleCommand(command, args);
                        }
                        catch (Exception ex)
                        {
                            HandleScriptException(fs, "OnConsoleCommand", ex);
                        }
                    });
                }
            });
        }

        public static void RaiseBoundPhoneNumberAction(string currentNumberInput)
        {
            if (!wasInitialized)
                return;

            activeScripts.ForEach(fs =>
            {
                try
                {
                    fs.RaiseBoundPhoneNumberAction(currentNumberInput);
                }
                catch (Exception ex)
                {
                    HandleScriptException(fs, "RaiseBoundPhoneNumberAction", ex);
                }
            });
        }
        #endregion

    }
}
