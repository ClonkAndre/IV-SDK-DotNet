#include "pch.h"
#include "IVHandlingData.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVHandlingDataModelFlags::IVHandlingDataModelFlags(tHandlingData* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeHandlingData = nativePtr;
	}
	IVHandlingDataHandlingFlags::IVHandlingDataHandlingFlags(tHandlingData* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeHandlingData = nativePtr;
	}
	IVHandlingData::IVHandlingData(tHandlingData* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeHandlingData = nativePtr;
	}

}