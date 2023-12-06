#include "pch.h"
#include "IVSkyDome.h"

namespace IVSDKDotNet
{
    // - - - Constructor - - -
    IVSkyDome::IVSkyDome(rage::SkyDome* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeSkyDome = nativePtr;
    }
}