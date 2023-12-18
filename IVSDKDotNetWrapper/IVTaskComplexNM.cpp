#include "pch.h"
#include "IVTaskComplexNM.h"

namespace IVSDKDotNet
{

    // - - - Constructor - - -
    IVTaskComplexNM::IVTaskComplexNM(CTaskComplexNM* nativePtr) : IVTaskComplex(nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeTask = nativePtr;
    }

    // - - - Methods / Functions - - -
    IVTaskComplexNM^ IVTaskComplexNM::Create(uint32_t nUnk, uint32_t nUnk2, IVTaskSimple^ pSubTask, float fUnk)
    {
        NULLPTR_CHECK_WITH_RETURN(pSubTask, nullptr);

        CTaskComplexNM* ptr = new CTaskComplexNM(nUnk, nUnk2, pSubTask->NativeSimpleTask, fUnk);
        NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);

        return gcnew IVTaskComplexNM(ptr);
    }

}