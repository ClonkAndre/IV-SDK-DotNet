#include "pch.h"
#include "IVPedDrawableInfo.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVPedDrawableInfo::IVPedDrawableInfo(tPedDrawableInfo* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativePedDrawableInfo = nativePtr;
	}

	// - - - Methods / Functions - - -
	IVPedDrawableInfo^ IVPedDrawableInfo::FromUIntPtr(UIntPtr ptr)
	{
		UINTPTR_ZERO_CHECK_WITH_RETURN(ptr, nullptr);
		return gcnew IVPedDrawableInfo((tPedDrawableInfo*)ptr.ToPointer());
	}
	UIntPtr IVPedDrawableInfo::GetUIntPtr()
	{
		NULLPTR_CHECK_WITH_RETURN(NativePedDrawableInfo, UIntPtr::Zero)
		return UIntPtr(NativePedDrawableInfo);
	}

}