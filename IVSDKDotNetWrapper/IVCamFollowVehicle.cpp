#include "pch.h"
#include "IVCamFollowVehicle.h"

namespace IVSDKDotNet
{
	
	// - - - Constructor - - -
	IVCamFollowVehicle::IVCamFollowVehicle(CCamFollowVehicle* nativePtr) : IVCam(nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeCam = nativePtr;
	}

}