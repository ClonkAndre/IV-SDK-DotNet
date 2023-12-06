#include "pch.h"
#include "IVPadValues.h"

namespace IVSDKDotNet
{
	// - - - Constructor - - -
	IVPadValues::IVPadValues(tPadValues* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativePadValues = nativePtr;
	}
}