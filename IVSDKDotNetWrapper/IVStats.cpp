#include "pch.h"
#include "IVStats.h"

namespace IVSDKDotNet
{
	// - - - Methods / Functions - - -
	float IVStats::GetStatValue(uint16_t index)
	{
		return CStats::GetStatValue(index);
	}
	void IVStats::SetStatValue(uint16_t index, float newValue)
	{
		CStats::SetStatValue(index, newValue);
	}
}