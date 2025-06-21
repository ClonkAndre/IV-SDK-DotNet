using System;

using IVSDKDotNet.Internal;

namespace Manager.Classes
{
    internal class TextureResource
    {

        #region Variables
        public IntPtr TexturePointer;
        public Guid OwnerScriptID;
        public string Tag;
        public bool WasReleased;
        #endregion

        #region Constructor
        public TextureResource(IntPtr txtPtr, Guid ownerScriptID, string tag)
        {
            TexturePointer = txtPtr;
            OwnerScriptID = ownerScriptID;
            Tag = tag;
        }
        #endregion

        public bool Release()
        {
            WasReleased = true;
            return ManagedD3D9.ReleaseTexture(ref TexturePointer);
        }

    }
}
