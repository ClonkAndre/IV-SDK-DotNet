using System;
using System.Collections.Generic;
using System.Reflection;

using IVSDKDotNet;
using IVSDKDotNet.Manager;

namespace Manager.Classes
{
    public class FoundPlugin
    {
        #region Variables and Properties
        // Script stuff
        public string FileName;
        public string FullPath;
        public bool HasOnFirstD3D9FrameEventBeenRaised;

        public Assembly TheAssembly;
        public ManagerPlugin ThePluginInstance;

        // Types
        public Type EntryPoint;

        // List
        public List<RegisteredEvent> RegisteredEvents;

        // Dear ImGui
        //public List<IntPtr> Textures;

        // Other
        public bool Running;

        // Properties
        public Guid ID
        {
            get
            {
                if (ThePluginInstance == null)
                    return Guid.Empty;

                return ThePluginInstance.ID;
            }
        }
        #endregion

        #region Constructor
        public FoundPlugin(string fileName, string fullPath, Assembly theAssembly, ManagerPlugin pluginInstance, Type entryPoint)
        {
            FileName = fileName;
            FullPath = fullPath;
            TheAssembly = theAssembly;
            ThePluginInstance = pluginInstance;
            EntryPoint = entryPoint;

            // Lists
            //RegisteredEvents = new List<RegisteredEvent>(8);

            Running = true;
        }
        #endregion

        #region Raisers
        public void RaiseUninitialize()
        {
            ThePluginInstance.RaiseUninitialize();
        }
        public void RaiseOnImGuiRendering(IntPtr devicePtr, ImGuiIV_DrawingContext ctx)
        {
            if (!IsReady())
                return;

            // Raise on first D3D9 frame event
            if (!HasOnFirstD3D9FrameEventBeenRaised)
            {
                ThePluginInstance.RaiseOnFirstD3D9Frame(devicePtr);

                HasOnFirstD3D9FrameEventBeenRaised = true;
            }

            ThePluginInstance.RaiseOnImGuiRendering(devicePtr, ctx);
        }
        #endregion

        #region Methods
        public void Abort(AbortReason reason, bool showMessage)
        {
            // Disable the functionality to raise any script events (Except for the Uninitialize event)
            Stop();

            // Raise Uninitialize event
            RaiseUninitialize();

            // Destroy textures created by plugin
            //DestroyScriptTextures();

            // Log
            if (showMessage)
            {
                switch (reason)
                {
                    case AbortReason.Manual:
                        Logger.Log(string.Format("IV-SDK .NET Manager plugin '{0}' was successfully aborted by user.", EntryPoint.FullName));
                        break;
                    case AbortReason.Script:
                        Logger.Log(string.Format("IV-SDK .NET Manager plugin '{0}' was successfully aborted by itself.", EntryPoint.FullName));
                        break;
                    case AbortReason.Manager:
                        Logger.Log(string.Format("Manager successfully aborted plugin '{0}'.", EntryPoint.FullName));
                        break;
                }
            }

            FileName = null;
            FullPath = null;
            TheAssembly = null;
            ThePluginInstance = null;
            EntryPoint = null;
        }
        public void Stop()
        {
            Running = false;
        }
        #endregion

        #region Functions
        /// <summary>
        /// Gets if the <see cref="ManagerPlugin"/> is ready so their events can be executed.
        /// </summary>
        /// <returns>True if the <see cref="ManagerPlugin"/> is ready. Otherwise false.</returns>
        public bool IsReady()
        {
            return Running;
        }
        #endregion
    }
}
