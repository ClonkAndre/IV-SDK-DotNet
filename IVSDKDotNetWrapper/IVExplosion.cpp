#include "pch.h"
#include "IVExplosion.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVExplosionInfo::IVExplosionInfo(tExplosionInfo* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeExplosionInfo = nativePtr;
	}

}