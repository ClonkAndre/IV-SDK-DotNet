#include "pch.h"
#include "IVCamera.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVCamera::IVCamera(CCamera* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeCamera = nativePtr;
	}

	// - - - Methods / Functions - - -
	IVCam^ IVCamera::CreateCam(int type, IVCam^ unk, IVCam^ unk2)
	{
		NULLPTR_CHECK_WITH_RETURN(NativeCamera, nullptr);
		NULLPTR_CHECK_WITH_RETURN(unk, nullptr);
		NULLPTR_CHECK_WITH_RETURN(unk2, nullptr);

		CCam* cam = NativeCamera->CreateCam(type, unk->NativeCam, unk2->NativeCam);
		NULLPTR_CHECK_WITH_RETURN(cam, nullptr);

		return gcnew IVCam(cam);
	}

}