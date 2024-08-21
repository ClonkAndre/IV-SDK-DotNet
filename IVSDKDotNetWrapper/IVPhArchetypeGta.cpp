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

    // - - - Methods / Functions - - -
    IVPhArchetypeGta^ IVPhArchetypeGta::FromUIntPtr(UIntPtr ptr)
    {
        UINTPTR_ZERO_CHECK_WITH_RETURN(ptr, nullptr);
        return gcnew IVPhArchetypeGta((phArchetypeGta*)ptr.ToPointer());
    }
    UIntPtr IVPhArchetypeGta::GetUIntPtr()
    {
        NULLPTR_CHECK_WITH_RETURN(NativePhArchetypeGta, UIntPtr::Zero);
        return UIntPtr(NativePhArchetypeGta);
    }

}