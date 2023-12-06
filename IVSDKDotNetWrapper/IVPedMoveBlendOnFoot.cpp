#include "pch.h"
#include "IVPedMoveBlendOnFoot.h"

namespace IVSDKDotNet
{
	// - - - Constructor - - -
	IVPedMoveBlendOnFoot::IVPedMoveBlendOnFoot(CPedMoveBlendOnFoot* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativePedMoveBlendOnFoot = nativePtr;
	}
}