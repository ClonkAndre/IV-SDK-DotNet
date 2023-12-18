#include "pch.h"
#include "IVZone.h"

namespace IVSDKDotNet
{
    // - - - Constructor - - -
    IVZone::IVZone(CZone* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeZone = nativePtr;
    }
}