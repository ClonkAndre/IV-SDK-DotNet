#include "pch.h"
#include "IVTaskComplexWander.h"

namespace IVSDKDotNet
{

    // - - - Constructor - - -
    IVTaskComplexWander::IVTaskComplexWander(CTaskComplexWander* nativePtr) : IVTaskComplex(nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeTask = nativePtr;
    }

    // - - - Methods / Functions - - -
    IVTaskComplexWander^ IVTaskComplexWander::Create(uint32_t moveState, float initialDir, bool bSensibly, float targetRadius, uint32_t unk1)
    {
        CTaskComplexWander* ptr = new CTaskComplexWander(moveState, initialDir, bSensibly, targetRadius, unk1);
        NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);
        return gcnew IVTaskComplexWander(ptr);
    }

}