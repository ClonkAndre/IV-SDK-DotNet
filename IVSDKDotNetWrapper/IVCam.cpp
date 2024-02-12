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
	IVCam^ IVCam::FromUIntPtr(UIntPtr ptr)
	{
		UINTPTR_ZERO_CHECK_WITH_RETURN(ptr, nullptr);
		return gcnew IVCam((CCam*)ptr.ToPointer());
	}
	UIntPtr IVCam::GetUIntPtr()
	{
		NULLPTR_CHECK_WITH_RETURN(NativeCam, UIntPtr::Zero);
		return UIntPtr(NativeCam);
	}

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