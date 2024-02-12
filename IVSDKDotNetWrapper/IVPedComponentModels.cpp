#include "pch.h"
#include "IVPedComponentModels.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVPedComponentModels::IVPedComponentModels(tPedComponentModels* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativePedComponentModels = nativePtr;
	}

	// - - - Methods / Functions - - -
	IVPedComponentModels^ IVPedComponentModels::FromUIntPtr(UIntPtr ptr)
	{
		UINTPTR_ZERO_CHECK_WITH_RETURN(ptr, nullptr);
		return gcnew IVPedComponentModels((tPedComponentModels*)ptr.ToPointer());
	}
	UIntPtr IVPedComponentModels::GetUIntPtr()
	{
		NULLPTR_CHECK_WITH_RETURN(NativePedComponentModels, UIntPtr::Zero);
		return UIntPtr(NativePedComponentModels);
	}

}