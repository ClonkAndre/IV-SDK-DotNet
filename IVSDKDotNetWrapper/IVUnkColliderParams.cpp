#include "pch.h"
#include "IVUnkColliderParams.h"

namespace IVSDKDotNet
{
    // - - - Constructor - - -
    IVUnkColliderParams2::IVUnkColliderParams2(rage::tUnkColliderParams2* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeColliderParams2 = nativePtr;
    }
    IVUnkColliderParams::IVUnkColliderParams(rage::tUnkColliderParams* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeColliderParams = nativePtr;
    }
}