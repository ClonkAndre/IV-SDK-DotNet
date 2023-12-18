#include "pch.h"
#include "IVPopulation.h"

namespace IVSDKDotNet
{
	// - - - Methods / Functions - - -
	void IVPopulation::Initialise()
	{
		CPopulation::Initialise();
	}
	void IVPopulation::RemovePed(IVPed^ pPed, bool unk)
	{
		NULLPTR_CHECK(pPed);
		CPopulation::RemovePed(pPed->NativePed, unk);
	}
}