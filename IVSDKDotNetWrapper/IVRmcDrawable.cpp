#include "pch.h"
#include "IVRmcDrawable.h"

namespace IVSDKDotNet
{
    // - - - Constructor - - -
    IVRmcDrawable::IVRmcDrawable(rage::rmcDrawable* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeRmcDrawable = nativePtr;
    }
}