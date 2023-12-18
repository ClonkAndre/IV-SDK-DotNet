#include "pch.h"
#include "IVTaskComplexPlayerOnFoot.h"

namespace IVSDKDotNet
{

    // - - - Constructor - - -
    IVTaskComplexPlayerOnFoot::IVTaskComplexPlayerOnFoot(CTaskComplexPlayerOnFoot* nativePtr) : IVTaskComplex(nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeTask = nativePtr;
    }

    // - - - Methods / Functions - - -
    IVTaskComplexPlayerOnFoot^ IVTaskComplexPlayerOnFoot::Create()
    {
        CTaskComplexPlayerOnFoot* ptr = new CTaskComplexPlayerOnFoot();
        NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);
        return gcnew IVTaskComplexPlayerOnFoot(ptr);
    }

}