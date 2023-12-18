#include "pch.h"
#include "IVDraw.h"

namespace IVSDKDotNet
{

    // - - - Constructor - - -
    IVDraw::IVDraw(CDraw* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeDraw = nativePtr;
    }

    // - - - Methods/Functions - - -
    float IVDraw::CalculateAspectRatio(bool bUnk)
    {
        NULLPTR_CHECK_WITH_RETURN(NativeDraw, 0.0F);
        return NativeDraw->CalculateAspectRatio(bUnk);
    }

}