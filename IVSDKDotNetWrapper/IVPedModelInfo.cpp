#include "pch.h"
#include "IVPedModelInfo.h"

namespace IVSDKDotNet
{
	// - - - Constructor - - -
	IVPedModelInfo::IVPedModelInfo(CPedModelInfo* nativePtr) : IVBaseModelInfo(nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativePedModelInfo = nativePtr;
	}
}


