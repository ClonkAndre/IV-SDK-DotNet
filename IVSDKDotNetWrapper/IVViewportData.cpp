#include "pch.h"
#include "IVViewportData.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVViewportData::IVViewportData(tViewportData* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeData = nativePtr;
	}

}