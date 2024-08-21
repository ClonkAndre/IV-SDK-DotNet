#include "pch.h"
#include "IVDrawRadioHudTextDC.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVDrawRadioHudTextDC::IVDrawRadioHudTextDC(CDrawRadioHudTextDC* nativePtr) : IVBaseDC(nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeDrawRadioHudTextDC = nativePtr;
	}

}