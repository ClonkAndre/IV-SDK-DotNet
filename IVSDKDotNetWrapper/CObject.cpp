#include "pch.h"
#include "CObject.h"

namespace IVSDKDotNet {

	CObject::CObject(Native_CObject* nativePtr) : CPhysical(nativePtr)
	{
		ObjectPointer = nativePtr;
	}

}