#include "pch.h"
#include "IVRenderPhases.h"

namespace IVSDKDotNet
{
	// - - - Constructor - - -
	IVRenderPhases::IVRenderPhases(tRenderPhases* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeRenderPhases = nativePtr;
	}

	// - - - Methods / Functions - - -
	IVRenderPhases IVRenderPhases::FromUIntPtr(UIntPtr ptr)
	{
		UINTPTR_ZERO_CHECK_WITH_RETURN(ptr, IVRenderPhases());
		return IVRenderPhases((tRenderPhases*)ptr.ToPointer());
	}
	UIntPtr IVRenderPhases::GetUIntPtr()
	{
		NULLPTR_CHECK_WITH_RETURN(NativeRenderPhases, UIntPtr::Zero);
		return UIntPtr(NativeRenderPhases);
	}
}