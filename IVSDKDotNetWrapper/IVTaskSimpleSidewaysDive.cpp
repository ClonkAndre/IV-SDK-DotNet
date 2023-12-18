#include "pch.h"
#include "IVTaskSimpleSidewaysDive.h"

namespace IVSDKDotNet
{

    // - - - Constructor - - -
    IVTaskSimpleSidewaysDive::IVTaskSimpleSidewaysDive(CTaskSimpleSidewaysDive* nativePtr) : IVTaskSimple(nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeTask = nativePtr;
    }

    // - - - Methods / Functions - - -
    IVTaskSimpleSidewaysDive^ IVTaskSimpleSidewaysDive::Create(bool bDirection)
    {
        CTaskSimpleSidewaysDive* ptr = new CTaskSimpleSidewaysDive(bDirection);
        NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);
        return gcnew IVTaskSimpleSidewaysDive(ptr);
    }

}