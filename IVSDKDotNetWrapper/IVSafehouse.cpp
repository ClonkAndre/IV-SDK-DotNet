#include "pch.h"
#include "IVSafehouse.h"

namespace IVSDKDotNet
{
	// - - - Constructor - - -
	IVSafehouse::IVSafehouse(CRestart::tSafehouse* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeSafehouse = nativePtr;
	}
}