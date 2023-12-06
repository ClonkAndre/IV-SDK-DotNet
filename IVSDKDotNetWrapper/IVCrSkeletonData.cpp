#include "pch.h"
#include "IVCrSkeletonData.h"

namespace IVSDKDotNet
{
    // - - - Constructor - - -
    IVCrSkeletonData::IVCrSkeletonData(rage::crSkeletonData* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeCrSkeletonData = nativePtr;
    }
}