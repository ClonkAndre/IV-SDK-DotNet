#include "pch.h"
#include "IVTask.h"

namespace IVSDKDotNet
{

    // - - - Constructor - - -
    IVTask::IVTask(CTask* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeBaseTask = nativePtr;
    }
    IVTaskComplex::IVTaskComplex(CTaskComplex* nativePtr) : IVTask(nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeComplexTask = nativePtr;
    }
    IVTaskSimple::IVTaskSimple(CTaskSimple* nativePtr) : IVTask(nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeSimpleTask = nativePtr;
    }

}