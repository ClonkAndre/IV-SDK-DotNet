#include "pch.h"
#include "CMenuManager.h"

namespace IVSDKDotNet {

	// =========================================================================
	// ========================== tControlRemapInfo ============================
	// =========================================================================
	tControlRemapInfo::tControlRemapInfo(Native_tControlRemapInfo* unmanagedtControlRemapInfo)
	{
		ControlID = unmanagedtControlRemapInfo->m_nControlId;
		DontShowInMenu = unmanagedtControlRemapInfo->m_bDontShowInMenu;
		BoundKey = unmanagedtControlRemapInfo->m_nBoundKey;
		ControlName = gcnew String(unmanagedtControlRemapInfo->m_sControlName);
		AltControlName = gcnew String(unmanagedtControlRemapInfo->m_sAltControlName);
	}



	// =========================================================================
	// ============================= CMenuManager ==============================
	// =========================================================================
	void CMenuManager::SetAddressSetting(eSettings setting, uint32_t value)
	{
		AddressSetter::GetRef<uint32_t>(0xCC7A00 + (uint32_t)setting, 0xCFC0D0 + (uint32_t)setting) = value;
	}
	uint32_t CMenuManager::GetAddressSetting(eSettings setting)
	{
		return AddressSetter::GetRef<uint32_t>(0xCC7A00 + (int)setting, 0xCFC0D0 + (int)setting);
	}



}