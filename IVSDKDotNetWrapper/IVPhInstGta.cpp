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
    IVPhInstGta^ IVPhInstGta::FromUIntPtr(UIntPtr ptr)
    {
        UINTPTR_ZERO_CHECK_WITH_RETURN(ptr, nullptr);
        return gcnew IVPhInstGta((phInstGta*)ptr.ToPointer());
    }
    UIntPtr IVPhInstGta::GetUIntPtr()
    {
        NULLPTR_CHECK_WITH_RETURN(NativePhInstGta, UIntPtr::Zero);
        return UIntPtr(NativePhInstGta);
    }

    IVPhInstGta^ IVPhInstGta::DetachFragmentGroup(uint32_t groupId)
    {
        NULLPTR_CHECK_WITH_RETURN(NativePhInstGta, nullptr);

        phInstGta* ptr = NativePhInstGta->DetachFragmentGroup(groupId);
        NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);

        return gcnew IVPhInstGta(ptr);
    }

}