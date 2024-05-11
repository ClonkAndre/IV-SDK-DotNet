#include "pch.h"
#include "IVPhoneInfo.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVPhoneInfo::IVPhoneInfo(sPhoneInfo* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativePhoneInfo = nativePtr;
	}

}