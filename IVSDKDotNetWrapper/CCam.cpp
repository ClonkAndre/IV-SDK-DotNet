#include "pch.h"
#include "CCam.h"

namespace IVSDKDotNet {

	// =========================================================================
	// ================================= CCam ==================================
	// =========================================================================
	CCam::CCam(Native_CCam* nativePtr)
	{
		CamPointer = nativePtr;
	}

	CCam^ CCam::GetCamOfType(int type, int unk)
	{
		return gcnew CCam(CamPointer->GetCamOfType(type, unk));
	}

	UIntPtr CCam::GetUIntPtr()
	{
		return UIntPtr(CamPointer);
	}

	CCam^ CCam::Activate()
	{
		return gcnew CCam(CamPointer->Activate());
	}

	bool CCam::Process()
	{
		return CamPointer->Process();
	}

	// =========================================================================
	// ========================== CCamFollowVehicle ============================
	// =========================================================================
	CCamFollowVehicle::CCamFollowVehicle(Native_CCamFollowVehicle* nativePtr) : CCam(nativePtr)
	{
		VehCameraPointer = nativePtr;
	}

}