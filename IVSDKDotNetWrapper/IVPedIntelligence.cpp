#include "pch.h"
#include "IVPedIntelligence.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVPedIntelligence::IVPedIntelligence(CPedIntelligence* nativePedIntelligence)
	{
		NULLPTR_CHECK(nativePedIntelligence);
		NativePedIntelligence = nativePedIntelligence;
	}

	// - - - Methods / Functions - - -
	IVPedIntelligence^ IVPedIntelligence::FromUIntPtr(UIntPtr ptr)
	{
		UINTPTR_ZERO_CHECK_WITH_RETURN(ptr, nullptr);
		return gcnew IVPedIntelligence((CPedIntelligence*)ptr.ToPointer());
	}
	UIntPtr IVPedIntelligence::GetUIntPtr()
	{
		NULLPTR_CHECK_WITH_RETURN(NativePedIntelligence, UIntPtr::Zero);
		return UIntPtr(NativePedIntelligence);
	}

}