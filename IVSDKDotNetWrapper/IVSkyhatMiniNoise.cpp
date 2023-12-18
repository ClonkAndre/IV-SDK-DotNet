#include "pch.h"
#include "IVSkyhatMiniNoise.h"

namespace IVSDKDotNet
{
    // - - - Constructor - - -
    IVSkyhatMiniNoise::IVSkyhatMiniNoise(rage::SkyhatMiniNoise* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeSkyhatMiniNoise = nativePtr;
    }
}