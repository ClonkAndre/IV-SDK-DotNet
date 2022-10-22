#include "pch.h"
#include "audRadioAudioEntity.h"

namespace IVSDKDotNet {

	CRadioStation::CRadioStation(Native_CRadioStation* unmanagedRadioStation)
	{
		m_cUnmanagedRadioStation = unmanagedRadioStation;
		Name = gcnew String(m_cUnmanagedRadioStation->m_sName);
		IsFrozen = m_cUnmanagedRadioStation->m_bFrozen;
	}

	audRadioAudioEntity::audRadioAudioEntity(Native_audRadioAudioEntity unmanagedRadioAudioEntity)
	{
		CurrentRadioStation = unmanagedRadioAudioEntity.m_nCurrentRadioStation;
	}

}