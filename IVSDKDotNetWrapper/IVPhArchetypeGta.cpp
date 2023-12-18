#include "pch.h"
#include "IVPhArchetypeGta.h"

namespace IVSDKDotNet
{
    // - - - Constructor - - -
    IVPhArchetypeGta::IVPhArchetypeGta(phArchetypeGta* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativePhArchetypeGta = nativePtr;
    }
}