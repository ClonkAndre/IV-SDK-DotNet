#include "pch.h"
#include "IVStuntJump.h"

namespace IVSDKDotNet
{
    // - - - Constructor - - -
    IVStuntJump::IVStuntJump(CStuntJump* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeStuntJump = nativePtr;
    }
}