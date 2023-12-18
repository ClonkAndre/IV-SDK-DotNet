#include "pch.h"
#include "IVValueHistory.h"

namespace IVSDKDotNet
{
	// - - - Constructor - - -
	IVValueHistory::IVValueHistory(tValueHistory* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeValueHistory = nativePtr;
	}
}