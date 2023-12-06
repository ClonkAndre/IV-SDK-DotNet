#include "pch.h"
#include "IVPhSleep.h"

namespace IVSDKDotNet
{
    // - - - Constructor - - -
    IVPhSleep::IVPhSleep(rage::phSleep* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeSleep = nativePtr;
    }
}