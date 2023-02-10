#include "pch.h"
#include "CPed.h"

namespace IVSDKDotNet {

	CPed::CPed(uint32_t handle, Native_CPed* native)
	{
		m_iHandle = handle;
		m_cNativePed = native;
	}

	void CPed::ProcessWeaponSwitch()
	{
		m_cNativePed->ProcessWeaponSwitch();
	}
	void CPed::SetHealth(float health, int unk)
	{
		m_cNativePed->SetHealth(health, unk);
	}
	void CPed::AddHealth(float health)
	{
		m_cNativePed->AddHealth(health);
	}
	void CPed::ProcessHeading()
	{
		m_cNativePed->ProcessHeading();
	}

}