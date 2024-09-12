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

}