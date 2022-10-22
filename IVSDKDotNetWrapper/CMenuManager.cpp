#include "pch.h"
#include "CMenuManager.h"

namespace IVSDKDotNet {

	CMenuManager::tControlRemapInfo::tControlRemapInfo(Native_tControlRemapInfo* unmanagedtControlRemapInfo)
	{
		ControlID = unmanagedtControlRemapInfo->m_nControlId;
		DontShowInMenu = unmanagedtControlRemapInfo->m_bDontShowInMenu;
		BoundKey = unmanagedtControlRemapInfo->m_nBoundKey;
		ControlName = gcnew String(unmanagedtControlRemapInfo->m_sControlName);
		AltControlName = gcnew String(unmanagedtControlRemapInfo->m_sAltControlName);
	}

}