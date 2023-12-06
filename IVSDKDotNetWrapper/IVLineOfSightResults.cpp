#include "pch.h"
#include "IVLineOfSightResults.h"

namespace IVSDKDotNet
{
    // - - - Methods / Functions - - -
    IVLineOfSightResults::IVLineOfSightResults(tLineOfSightResults* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeLineOfSightResults = nativePtr;
    }
}