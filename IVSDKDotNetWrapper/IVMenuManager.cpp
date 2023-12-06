#include "pch.h"
#include "IVMenuManager.h"

namespace IVSDKDotNet
{
	// - - - Methods / Functions - - -
	uint32_t IVMenuManager::GetSetting(eSettings setting)
	{
		return AddressSetter::GetRef<uint32_t>(0xCC7A00 + (uint32_t)setting, 0xCFC0D0 + (uint32_t)setting);
	}
	void IVMenuManager::SetSetting(eSettings setting, uint32_t value)
	{
		AddressSetter::GetRef<uint32_t>(0xCC7A00 + (uint32_t)setting, 0xCFC0D0 + (uint32_t)setting) = value;
	}
}