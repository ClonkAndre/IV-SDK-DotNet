#include "pch.h"
#include "CCamera.h"

namespace IVSDKDotNet {

	CCamera::CCamera(Native_CCamera* nativePtr)
	{
		CameraPointer = nativePtr;
	}

	CCamera^ CCamera::GetTheCamera()
	{
		return gcnew CCamera(&AddressSetter::GetRef<Native_CCamera>(0xB21A6C, 0xB488E8));
	}
	CCam^ CCamera::GetFinalCam()
	{
		return gcnew CCam(AddressSetter::GetRef<Native_CCam*>(0xB21A70, 0xB488EC));
	}

	CCam^ CCamera::CreateCam(int type, CCam^ unk, CCam^ unk2)
	{
		return gcnew CCam(CameraPointer->CreateCam(type, unk->CamPointer, unk2->CamPointer));
	}

}