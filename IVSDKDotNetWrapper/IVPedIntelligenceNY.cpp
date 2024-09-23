#include "pch.h"
#include "IVPedIntelligenceNY.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVPedIntelligenceNY::IVPedIntelligenceNY(CPedIntelligenceNY* nativePedIntelligenceNY) : IVPedIntelligence(nativePedIntelligenceNY)
	{
		NULLPTR_CHECK(nativePedIntelligenceNY);
		NativePedIntelligenceNY = nativePedIntelligenceNY;
	}

	// - - - Methods / Functions - - -
	IVPedIntelligenceNY^ IVPedIntelligenceNY::FromUIntPtr(UIntPtr ptr)
	{
		UINTPTR_ZERO_CHECK_WITH_RETURN(ptr, nullptr);
		return gcnew IVPedIntelligenceNY((CPedIntelligenceNY*)ptr.ToPointer());
	}
	UIntPtr IVPedIntelligenceNY::GetUIntPtr()
	{
		NULLPTR_CHECK_WITH_RETURN(NativePedIntelligenceNY, UIntPtr::Zero);
		return UIntPtr(NativePedIntelligenceNY);
	}

}