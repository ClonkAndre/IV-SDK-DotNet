#include "pch.h"
#include "IVControlRemapInfo.h"

namespace IVSDKDotNet
{
	// - - - Constructor - - -
	IVControlRemapInfo::IVControlRemapInfo(tControlRemapInfo* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeControlRemapInfo = nativePtr;
	}
}