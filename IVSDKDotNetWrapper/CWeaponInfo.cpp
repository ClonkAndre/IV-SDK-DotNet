#include "pch.h"
#include "CWeaponInfo.h"

namespace IVSDKDotNet {

	// =========================================================================
	// ======================= CWeaponInfo.WeaponFlags =========================
	// =========================================================================
	CWeaponInfo::WeaponFlags::WeaponFlags(CWeaponInfo^ parent)
	{
		m_cParent = parent;
	}


	// =========================================================================
	// ============================= CWeaponInfo ===============================
	// =========================================================================
	CWeaponInfo::CWeaponInfo(Native_CWeaponInfo* nativePtr)
	{
		WeaponInfoPointer = nativePtr;
		m_cWeaponFlags = gcnew WeaponFlags(this);
	}

	CWeaponInfo^ CWeaponInfo::GetWeaponInfo(uint32_t type)
	{
		Native_CWeaponInfo* ptr = Native_CWeaponInfo::GetWeaponInfo(type);

		if (ptr)
			return gcnew CWeaponInfo(ptr);

		return nullptr;
	}


}