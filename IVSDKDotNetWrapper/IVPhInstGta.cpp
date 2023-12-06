#include "pch.h"
#include "IVPhInstGta.h"

namespace IVSDKDotNet
{

    // - - - Constructor - - -
    IVPhInstGta::IVPhInstGta(phInstGta* nativePtr) : IVPhInst(nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativePhInstGta = nativePtr;
    }

    // - - - Methods / Functions - - -
    IVPhInstGta^ IVPhInstGta::DetachFragmentGroup(uint32_t groupId)
    {
        NULLPTR_CHECK_WITH_RETURN(NativePhInstGta, nullptr);

        phInstGta* ptr = NativePhInstGta->DetachFragmentGroup(groupId);
        NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);

        return gcnew IVPhInstGta(ptr);
    }

}