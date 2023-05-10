#include "pch.h"
#include "CPhysical.h"

namespace IVSDKDotNet {

	// =========================================================================
	// ======================= CPhysical.PhysicalFlags =========================
	// =========================================================================
	CPhysical::PhysicalFlags::PhysicalFlags(CPhysical^ parent)
	{
		m_cParent = parent;
	}


	// =========================================================================
	// ============================== CPhysical ================================
	// =========================================================================
	CPhysical::CPhysical(Native_CPhysical* native) : CDynamicEntity(native)
	{
		PhysicalPointer = native;
		m_cPhysicalFlags = gcnew PhysicalFlags(this);
	}

	bool CPhysical::ProcessWater()
	{
		return PhysicalPointer->ProcessWater();
	}
	float CPhysical::GetHealth()
	{
		return PhysicalPointer->GetHealth();
	}


}