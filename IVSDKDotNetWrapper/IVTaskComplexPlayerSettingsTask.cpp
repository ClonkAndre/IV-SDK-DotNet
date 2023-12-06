#include "pch.h"
#include "IVTaskComplexPlayerSettingsTask.h"

namespace IVSDKDotNet
{

    // - - - Constructor - - -
    IVTaskComplexPlayerSettingsTask::IVTaskComplexPlayerSettingsTask(CTaskComplexPlayerSettingsTask* nativePtr) : IVTaskComplex(nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeTask = nativePtr;
    }

    // - - - Methods / Functions - - -
    IVTaskComplexPlayerSettingsTask^ IVTaskComplexPlayerSettingsTask::Create(uint32_t unkFromPed)
    {
        CTaskComplexPlayerSettingsTask* ptr = new CTaskComplexPlayerSettingsTask(unkFromPed);
        NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);
        return gcnew IVTaskComplexPlayerSettingsTask(ptr);
    }

}