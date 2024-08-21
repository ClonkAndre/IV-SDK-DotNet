#include "pch.h"
#include "IVGtaFragType.h"

namespace IVSDKDotNet
{

    // - - - Constructor - - -
    IVGtaFragType::IVGtaFragType(gtaFragType* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeGtaFragType = nativePtr;
    }

    // - - - Methods / Functions - - -
    IVGtaFragType^ IVGtaFragType::FromUIntPtr(UIntPtr ptr)
    {
        UINTPTR_ZERO_CHECK_WITH_RETURN(ptr, nullptr);
        return gcnew IVGtaFragType((gtaFragType*)ptr.ToPointer());
    }
    UIntPtr IVGtaFragType::GetUIntPtr()
    {
        NULLPTR_CHECK_WITH_RETURN(NativeGtaFragType, UIntPtr::Zero);
        return UIntPtr(NativeGtaFragType);
    }

}