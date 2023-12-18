#include "pch.h"
#include "IVCam.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVCam::IVCam(CCam* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeCam = nativePtr;
	}

	// - - - Methods / Functions - - -
	IVCam^ IVCam::GetCamOfType(int type, int unk)
	{
		NULLPTR_CHECK_WITH_RETURN(NativeCam, nullptr);
		return gcnew IVCam(NativeCam->GetCamOfType(type, unk));
	}
	IVCam^ IVCam::Activate()
	{
		NULLPTR_CHECK_WITH_RETURN(NativeCam, nullptr);
		return gcnew IVCam(NativeCam->Activate());
	}
	bool IVCam::Process()
	{
		NULLPTR_CHECK_WITH_RETURN(NativeCam, false);
		return NativeCam->Process();
	}

}