#include "pch.h"
#include "IVBoundBox.h"

namespace IVSDKDotNet
{
    // - - - Constructor - - -
    IVBoundBox::IVBoundBox(CBoundBox* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeBoundBox = nativePtr;
    }
}