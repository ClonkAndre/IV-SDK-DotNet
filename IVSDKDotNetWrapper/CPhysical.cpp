#include "pch.h"
#include "CPhysical.h"

namespace IVSDKDotNet {

	CPhysical::CPhysical(Native_CPhysical* native) : CDynamicEntity(native)
	{
		m_cNativePhysical = native;
	}

	bool CPhysical::ProcessWater()
	{
		return m_cNativePhysical->ProcessWater();
	}
	float CPhysical::GetHealth()
	{
		return m_cNativePhysical->GetHealth();
	}

}