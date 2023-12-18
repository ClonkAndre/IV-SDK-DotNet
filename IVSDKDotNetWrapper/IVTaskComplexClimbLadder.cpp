#include "pch.h"
#include "IVTaskComplexClimbLadder.h"

namespace IVSDKDotNet
{

    // - - - Constructor - - -
    IVTaskComplexClimbLadder::IVTaskComplexClimbLadder(CTaskComplexClimbLadder* nativePtr) : IVTaskComplex(nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeTask = nativePtr;
    }

    // - - - Methods / Functions - - -
    IVTaskComplexClimbLadder^ IVTaskComplexClimbLadder::Create(IVObject^ ladder, int32_t type, uint32_t unk0)
    {
        NULLPTR_CHECK_WITH_RETURN(ladder, nullptr);
        CTaskComplexClimbLadder* ptr = new CTaskComplexClimbLadder(ladder->NativeObject, type, unk0);
        NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);
        return gcnew IVTaskComplexClimbLadder(ptr);
    }

}