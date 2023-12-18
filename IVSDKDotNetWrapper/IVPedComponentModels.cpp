#include "pch.h"
#include "IVPedComponentModels.h"

namespace IVSDKDotNet
{
	// - - - Constructor - - -
	IVPedComponentModels::IVPedComponentModels(tPedComponentModels* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativePedComponentModels = nativePtr;
	}
}