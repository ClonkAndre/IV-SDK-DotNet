#include "pch.h"
#include "IVTaskComplexWanderStandard.h"

namespace IVSDKDotNet
{

    // - - - Constructor - - -
    IVTaskComplexWanderStandard::IVTaskComplexWanderStandard(CTaskComplexWanderStandard* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeTask = nativePtr;
    }

    // - - - Methods / Functions - - -
    IVTaskComplexWanderStandard^ IVTaskComplexWanderStandard::Create(uint32_t moveState, float initialDir, bool bSensibly, float targetRadius, uint32_t unk1)
    {
        CTaskComplexWanderStandard* ptr = new CTaskComplexWanderStandard(moveState, initialDir, bSensibly, targetRadius, unk1);
        NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);
        return gcnew IVTaskComplexWanderStandard(ptr);
    }

}