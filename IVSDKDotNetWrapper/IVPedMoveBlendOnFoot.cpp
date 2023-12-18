#include "pch.h"
#include "IVPedMoveBlendOnFoot.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVPedMoveBlendOnFoot::IVPedMoveBlendOnFoot(CPedMoveBlendOnFoot* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativePedMoveBlendOnFoot = nativePtr;
	}

	// - - - Methods / Functions - - -
	IVPedMoveBlendOnFoot^ IVPedMoveBlendOnFoot::FromUIntPtr(UIntPtr ptr)
	{
		UINTPTR_ZERO_CHECK_WITH_RETURN(ptr, nullptr);
		return gcnew IVPedMoveBlendOnFoot((CPedMoveBlendOnFoot*)ptr.ToPointer());
	}
	UIntPtr IVPedMoveBlendOnFoot::GetUIntPtr()
	{
		NULLPTR_CHECK_WITH_RETURN(NativePedMoveBlendOnFoot, UIntPtr::Zero);
		return UIntPtr(NativePedMoveBlendOnFoot);
	}

}