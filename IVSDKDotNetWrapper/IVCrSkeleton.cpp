#include "pch.h"
#include "IVCrSkeleton.h"

namespace IVSDKDotNet
{

    // - - - Constructor - - -
    IVCrSkeleton::IVCrSkeleton(rage::crSkeleton* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeCrSkeleton = nativePtr;
    }

    // - - - Methods / Functions - - -
    IVCrSkeletonData IVCrSkeleton::GetBoneDataByName(String^ sName)
    {
        NULLPTR_CHECK_WITH_RETURN(NativeCrSkeleton, IVCrSkeletonData());
        CHECK_NULL_OR_WHITESPACE_STRING_WITH_RETURN(sName, IVCrSkeletonData());

        msclr::interop::marshal_context ctx;
        rage::crSkeletonData* ptr = NativeCrSkeleton->GetBoneDataByName((char*)ctx.marshal_as<const char*>(sName));
        NULLPTR_CHECK_WITH_RETURN(ptr, IVCrSkeletonData());

        return IVCrSkeletonData(ptr);
    }

}