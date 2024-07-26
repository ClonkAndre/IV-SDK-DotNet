#include "pch.h"
#include "IVPhoneInfo.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVPhoneInfo::IVPhoneInfo(sPhoneInfo* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativePhoneInfo = nativePtr;
	}

	// - - - Methods / Functions - - -
	IVPhoneInfo^ IVPhoneInfo::FromUIntPtr(UIntPtr ptr)
	{
		UINTPTR_ZERO_CHECK_WITH_RETURN(ptr, nullptr);
		return gcnew IVPhoneInfo((sPhoneInfo*)ptr.ToPointer());
	}
	UIntPtr IVPhoneInfo::GetUIntPtr()
	{
		NULLPTR_CHECK_WITH_RETURN(NativePhoneInfo, UIntPtr::Zero);
		return UIntPtr(NativePhoneInfo);
	}

}