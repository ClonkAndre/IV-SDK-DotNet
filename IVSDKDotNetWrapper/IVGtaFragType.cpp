#include "pch.h"
#include "IVGtaFragType.h"

namespace IVSDKDotNet
{
    // - - - Constructor - - -
    IVGtaFragType::IVGtaFragType(gtaFragType* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeGtaFragType = nativePtr;
    }
}