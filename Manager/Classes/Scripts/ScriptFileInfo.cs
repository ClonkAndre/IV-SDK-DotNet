using System.IO;

namespace Manager.Classes.Scripts
{
    /// <summary>
    /// Contains information about the script file.
    /// </summary>
    public class ScriptFileInfo
    {

        #region Variables
        public string FullPath;
        public string FileName;
        public string FileNameWithoutExtension;

        public bool IsIVSDKDotNetScript;
        public bool IsScriptHookDotNetScript;
        #endregion

        #region Constructor
        public ScriptFileInfo(string fullPath)
        {
            FullPath = fullPath;
        }
        #endregion

        #region Functions
        public bool Exists()
        {
            return File.Exists(FullPath);
        }
        public bool Parse()
        {
            if (!Exists())
            {
                Logger.LogWarningEx("Could not load script because the file does not exists. Path: {0}", FullPath);
                return false;
            }

            FileName = Path.GetFileName(FullPath);

            // Removes the last extensions of the file name which would be .dll in this case leaving only the .ivsdk or .net part
            string fileNameWithoutBaseExtension = Path.GetFileNameWithoutExtension(FullPath);

            // Check for which SDK this script is supposed to be
            IsIVSDKDotNetScript =       fileNameWithoutBaseExtension.Contains(".ivsdk");
            IsScriptHookDotNetScript =  fileNameWithoutBaseExtension.Contains(".net");

            // Check if fileName contains both the .ivsdk AND .net part
            if (IsIVSDKDotNetScript && IsScriptHookDotNetScript)
            {
                Logger.LogWarningEx("Couldn't determine if file '{0}' is supposed to be a IV-SDK .NET (.ivsdk) or ScriptHookDotNet (.net) script.", FileName);
                return false;
            }

            // Check if fileName contains neither the .ivsdk OR .net part
            if (!IsIVSDKDotNetScript && !IsScriptHookDotNetScript)
            {
                Logger.LogWarningEx("The file '{0}' is not a IV-SDK .NET or ScriptHookDotNet script file.", FileName);
                return false;
            }

            // Remove extensions from file because we figured out for which SDK this script is
            FileNameWithoutExtension = fileNameWithoutBaseExtension.Replace(".ivsdk", "").Replace(".net", "");

            return true;
        }

        /// <summary>
        /// Checks if the given <paramref name="str"/> matches with either the <see cref="FileName"/> or <see cref="FileNameWithoutExtension"/>.
        /// </summary>
        /// <param name="str">The given string to compare to.</param>
        /// <param name="makeLowercase">Makes every string lowercase before performing the check.</param>
        /// <param name="relaxedComparison">When set to <see langword="true"/>, does not directly compare the file names by the given <paramref name="str"/>, and instead checks if each file name contains the chars in the given <paramref name="str"/>.</param>
        /// <returns><see langword="true"/> if matches with either the <see cref="FileName"/> or <see cref="FileNameWithoutExtension"/>, Otherwise, <see langword="false"/>.</returns>
        public bool DoesStringMatchWithAnyFileName(string str, bool makeLowercase = false, bool relaxedComparison = false)
        {
            string fileName = FileName;
            string fileNameWithoutExtension = FileNameWithoutExtension;

            if (makeLowercase)
            {
                fileName = FileName.ToLower();
                fileNameWithoutExtension = FileNameWithoutExtension.ToLower();
                str = str.ToLower();
            }

            if (relaxedComparison)
                return fileName.Contains(str) || fileNameWithoutExtension.Contains(str);
            else
                return str == fileName || str == fileNameWithoutExtension;
        }

        public FileStream OpenStream()
        {
            return File.OpenRead(FullPath);
        }
        #endregion

    }
}
