#include "pch.h"
#include "IVTaskSimpleNMHighFall.h"

namespace IVSDKDotNet
{

    // - - - Constructor - - -
    IVTaskSimpleNMHighFall::IVTaskSimpleNMHighFall(CTaskSimpleNMHighFall* nativePtr) : IVTaskSimple(nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeTask = nativePtr;
    }

    // - - - Methods / Functions - - -
    IVTaskSimpleNMHighFall^ IVTaskSimpleNMHighFall::Create(uint32_t nUnk, uint32_t nUnk2, uint32_t nUnk3, uint32_t nUnk4)
    {
        CTaskSimpleNMHighFall* ptr = new CTaskSimpleNMHighFall(nUnk, nUnk2, nUnk3, nUnk4);
        NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);
        return gcnew IVTaskSimpleNMHighFall(ptr);
    }

}