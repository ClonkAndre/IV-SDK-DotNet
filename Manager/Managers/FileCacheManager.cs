using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;

namespace Manager.Managers
{
    internal static class FileCacheManager
    {

        #region Consts
        private const string DEPENDENCY_FILTER = "*.dll";
        private const string GENERAL_FILTER = "*.asi|*.dll";
        private const string SCRIPTS_FILTER = "*.ivsdk.dll|*.net.dll|*.cs|*.vb";
        private const string ASI_FILTER = ".asi";
        #endregion

        #region Variables
        private static bool wasInitialized;

        private static string currDir;
        private static string scriptsFolder;
        private static string pluginsFolder;
        private static string updateFolder;
        private static string ivsdkdotnetBinFolder;
        private static string ivsdkdotnetScriptsFolder;

        private static ConcurrentDictionary<Folder, string[]> cachedFiles;
        private static FileSystemWatcher[] watchers;
        #endregion

        #region Events

        // Public
        public delegate void OnDirectoryChangedDelegate(WatcherChangeTypes eventType, EventArgs e);
        public static event OnDirectoryChangedDelegate OnDirectoryChanged;

        // Local
        private static void FileManager_Created(object sender, FileSystemEventArgs e)
        {
            RaiseChangedEvent(sender, WatcherChangeTypes.Created, e);
        }
        private static void FileManager_Deleted(object sender, FileSystemEventArgs e)
        {
            RaiseChangedEvent(sender, WatcherChangeTypes.Deleted, e);
        }
        private static void FileManager_Renamed(object sender, RenamedEventArgs e)
        {
            RaiseChangedEvent(sender, WatcherChangeTypes.Renamed, e);
        }

        #endregion

        #region Methods
        public static void Init()
        {
            if (wasInitialized)
                return;

            // Get current directory
            try
            {
                currDir = Path.GetDirectoryName(Environment.GetCommandLineArgs()[0]);
            }
            catch (Exception ex)
            {
                Logger.LogErrorEx("Failed to get current directory from command line for the FileCacheManager! Trying to use fallback path. Details: {0}", ex);
                currDir = Environment.CurrentDirectory;
            }

            Logger.LogEx("The FileCacheManager was initialized for this directory: {0}", currDir);
            Helper.WriteToDebugOutput(Priority.Default, "The FileCacheManager was initialized for this directory: {0}", currDir);

            // Construct paths
            scriptsFolder =             Path.Combine(currDir, "scripts");
            pluginsFolder =             Path.Combine(currDir, "plugins");
            updateFolder =              Path.Combine(currDir, "update");
            ivsdkdotnetBinFolder =      Path.Combine(currDir, "IVSDKDotNet", "bin");
            ivsdkdotnetScriptsFolder =  Path.Combine(currDir, "IVSDKDotNet", "scripts");

            // Store files from certain folders for later lookup
            cachedFiles = new ConcurrentDictionary<Folder, string[]>();
            cachedFiles.TryAdd(Folder.Main,                     Helper.GetFilesInDirectoryNoThrow(currDir,                  GENERAL_FILTER,     SearchOption.TopDirectoryOnly));
            cachedFiles.TryAdd(Folder.Scripts,                  Helper.GetFilesInDirectoryNoThrow(scriptsFolder,            SCRIPTS_FILTER,     SearchOption.TopDirectoryOnly));
            cachedFiles.TryAdd(Folder.Plugins,                  Helper.GetFilesInDirectoryNoThrow(pluginsFolder,            ASI_FILTER,         SearchOption.TopDirectoryOnly));
            cachedFiles.TryAdd(Folder.Update,                   Helper.GetFilesInDirectoryNoThrow(updateFolder,             ASI_FILTER,         SearchOption.TopDirectoryOnly));
            cachedFiles.TryAdd(Folder.IVSDKDotNet_bin,          Helper.GetFilesInDirectoryNoThrow(ivsdkdotnetBinFolder,     DEPENDENCY_FILTER,  SearchOption.TopDirectoryOnly));
            cachedFiles.TryAdd(Folder.IVSDKDotNet_Scripts,      Helper.GetFilesInDirectoryNoThrow(ivsdkdotnetScriptsFolder, SCRIPTS_FILTER,     SearchOption.TopDirectoryOnly));

            // Install file system watchers for directories whos files might change
            watchers = new FileSystemWatcher[3]
            {
                CreateWatcher(currDir),
                CreateWatcher(scriptsFolder),
                CreateWatcher(ivsdkdotnetScriptsFolder),
            };

            for (int i = 0; i < watchers.Length; i++)
            {
                FileSystemWatcher watcher = watchers[i];

                if (watcher == null)
                    continue;

                watcher.Created += FileManager_Created;
                watcher.Deleted += FileManager_Deleted;
                watcher.Renamed += FileManager_Renamed;
                watcher.EnableRaisingEvents = true;
            }

            wasInitialized = true;
        }
        public static void Shutdown()
        {
            if (!wasInitialized)
                return;

            wasInitialized = false;

            if (watchers != null)
            {
                for (int i = 0; i < watchers.Length; i++)
                {
                    FileSystemWatcher watcher = watchers[i];

                    if (watcher == null)
                        continue;

                    watcher.EnableRaisingEvents = false;
                    watcher.Created -= FileManager_Created;
                    watcher.Deleted -= FileManager_Deleted;
                    watcher.Renamed -= FileManager_Renamed;
                    watcher.Dispose();
                }
                watchers = null;
            }
            if (cachedFiles != null)
            {
                cachedFiles.Clear();
                cachedFiles = null;
            }
        }

        private static void RaiseChangedEvent(object sender, WatcherChangeTypes eventType, EventArgs e)
        {
            FileSystemWatcher theWatcher = sender as FileSystemWatcher;
            FileSystemEventArgs eventArgs = e as FileSystemEventArgs;

            Helper.WriteToDebugOutput(Priority.Default, "[FileSystemWatcher] Element '{0}' was '{1}' in path '{2}'.", eventArgs.Name, eventType, theWatcher.Path);

            // Update cached files
            if (theWatcher.Path == currDir)
            {
                // Get the new files in dir
                string[] newFiles = Helper.GetFilesInDirectoryNoThrow(currDir, GENERAL_FILTER, SearchOption.TopDirectoryOnly);

                // Get the currently stored files array
                cachedFiles.TryGetValue(Folder.Main, out string[] oldFiles);

                // Only update if the sequences are different
                if (!newFiles.SequenceEqual(oldFiles))
                    cachedFiles.TryUpdate(Folder.Main, newFiles, oldFiles);
            }
            else if (theWatcher.Path == scriptsFolder)
            {
                // Get the new files in dir
                string[] newFiles = Helper.GetFilesInDirectoryNoThrow(scriptsFolder, SCRIPTS_FILTER, SearchOption.TopDirectoryOnly);

                // Get the currently stored files array
                cachedFiles.TryGetValue(Folder.Scripts, out string[] oldFiles);

                // Only update if the sequences are different
                if (!newFiles.SequenceEqual(oldFiles))
                    cachedFiles.TryUpdate(Folder.Scripts, newFiles, oldFiles);
            }
            else if (theWatcher.Path == ivsdkdotnetScriptsFolder)
            {
                // Get the new files in dir
                string[] newFiles = Helper.GetFilesInDirectoryNoThrow(ivsdkdotnetScriptsFolder, SCRIPTS_FILTER, SearchOption.TopDirectoryOnly);

                // Get the currently stored files array
                cachedFiles.TryGetValue(Folder.IVSDKDotNet_Scripts, out string[] oldFiles);

                // Only update if the sequences are different
                if (!newFiles.SequenceEqual(oldFiles))
                    cachedFiles.TryUpdate(Folder.IVSDKDotNet_Scripts, newFiles, oldFiles);
            }

            // Invoke event
            OnDirectoryChanged?.Invoke(eventType, e);
        }
        #endregion

        #region Functions
        public static int GetCachedFilesCount()
        {
            if (!wasInitialized)
                return 0;

            return cachedFiles.Count;
        }

        private static FileSystemWatcher CreateWatcher(string path)
        {
            try
            {
                if (!Directory.Exists(path))
                {
                    Helper.WriteToDebugOutput(Priority.Default, "Creating directory '{0}' for FileSystemWatcher because it did not exist yet.", path);
                    Directory.CreateDirectory(path);
                }

                return new FileSystemWatcher(path);
            }
            catch (Exception ex)
            {
                Logger.LogError("An error occured while creating a new FileSystemWatcher for the FileCacheManager!");
                Logger.LogError("IV-SDK .NET might not be able to find script files or dependencies!");
                Logger.LogErrorEx("Details: {0}", ex);
            }

            return null;
        }

        public static string[] GetCachedFiles(Folder inFolder)
        {
            if (!wasInitialized)
                return Array.Empty<string>();

            if (cachedFiles.TryGetValue(inFolder, out string[] files))
            {
                return files;
            }

            return Array.Empty<string>();
        }
        public static string GetFullPathOfCachedFile(string fileName, Folder hasToBeInFolder = Folder.Any)
        {
            foreach (KeyValuePair<Folder, string[]> item in cachedFiles)
            {
                // Try to find file in cache
                string str = item.Value.FirstOrDefault(x =>
                {
                    if (hasToBeInFolder == Folder.Any)
                        return x.Contains(fileName);
                    else
                        return hasToBeInFolder.HasFlag(item.Key) && x.Contains(fileName);
                });

                if (str != null)
                    return str;
            }

            return null;
        }
        public static string GetFullPathOfCachedFileWithVersionInfo(string fileName, out FileVersionInfo fileVersionInfo, Folder hasToBeInFolder = Folder.Any)
        {
            string path = GetFullPathOfCachedFile(fileName, hasToBeInFolder);

            if (path == null)
            {
                fileVersionInfo = null;
                return null;
            }

            fileVersionInfo = FileVersionInfo.GetVersionInfo(path);
            return path;
        }

        public static bool IsFilePresent(Folder folderToLookInto, string fileName)
        {
            if (folderToLookInto == Folder.Any)
            {
                foreach (KeyValuePair<Folder, string[]> item in cachedFiles)
                {
                    if (item.Value.Any(x => x.Contains(fileName)))
                        return true;
                }
            }
            else
            {
                if (cachedFiles.TryGetValue(folderToLookInto, out string[] files))
                {
                    return files.Any(x => x.Contains(fileName));
                }
            }

            return false;
        }
        public static bool IsFilePresentWithVersionCheck(Folder folderToLookInto, string fileName, string version)
        {
            if (folderToLookInto == Folder.Any)
            {
                foreach (KeyValuePair<Folder, string[]> item in cachedFiles)
                {
                    if (item.Value.Any(x => x.Contains(fileName) && Helper.DoesFileVersionMatchGivenVersionWithWildcards(x, version)))
                        return true;
                }
            }
            else
            {
                if (cachedFiles.TryGetValue(folderToLookInto, out string[] files))
                {
                    return files.Any(x => x.Contains(fileName) && Helper.DoesFileVersionMatchGivenVersionWithWildcards(x, version));
                }
            }

            return false;
        }
        #endregion

    }
}
