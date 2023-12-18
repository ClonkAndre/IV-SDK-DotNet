#include "pch.h"
#include "IVGrcTexture.h"

namespace IVSDKDotNet
{
    // - - - Constructor - - -
    IVGrcTexture::IVGrcTexture(rage::grcTexture* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeTexture = nativePtr;
    }
    IVGrcTexturePC::IVGrcTexturePC(rage::grcTexturePC* nativePtr) : IVGrcTexture(nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeTexturePC = nativePtr;
    }
}