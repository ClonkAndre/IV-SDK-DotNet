#include "pch.h"
#include "IVPhInst.h"

namespace IVSDKDotNet
{
    // - - - Constructor - - -
    IVPhInst::IVPhInst(rage::phInst* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativePhInst = nativePtr;
    }
}