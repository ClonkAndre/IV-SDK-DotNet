#include "pch.h"
#include "IVPedDrawableInfo.h"

namespace IVSDKDotNet
{
	// - - - Constructor - - -
	IVPedDrawableInfo::IVPedDrawableInfo(tPedDrawableInfo* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativePedDrawableInfo = nativePtr;
	}
}