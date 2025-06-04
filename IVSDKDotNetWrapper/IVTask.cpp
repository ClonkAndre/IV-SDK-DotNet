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

    IVTask^ IVTask::FromUIntPtr(UIntPtr ptr)
    {
        UINTPTR_ZERO_CHECK_WITH_RETURN(ptr, nullptr);
        return gcnew IVTask((CTask*)ptr.ToPointer());
    }
    UIntPtr IVTask::GetUIntPtr()
    {
        NULLPTR_CHECK_WITH_RETURN(NativeBaseTask, UIntPtr::Zero);
        return UIntPtr(NativeBaseTask);
    }

}