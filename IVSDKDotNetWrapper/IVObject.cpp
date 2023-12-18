#include "pch.h"
#include "IVObject.h"

namespace IVSDKDotNet
{
	// - - - Constructor - - -
	IVObject::IVObject(CObject* nativePtr) : IVPhysical(nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeObject = nativePtr;
	}
}