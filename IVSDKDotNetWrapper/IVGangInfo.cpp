#include "pch.h"
#include "IVGangInfo.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVGangInfo::IVGangInfo(CGangInfo* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeGangInfo = nativePtr;
	}

}