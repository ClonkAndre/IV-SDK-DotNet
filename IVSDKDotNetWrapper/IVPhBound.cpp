#include "pch.h"
#include "IVPhBound.h"

namespace IVSDKDotNet
{
    // - - - Constructor - - -
    IVPhBound::IVPhBound(rage::phBound* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeBound = nativePtr;
    }
    IVPhBoundComposite::IVPhBoundComposite(rage::phBoundComposite* nativePtr) : IVPhBound(nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeBoundComposite = nativePtr;
    }
}