#include "pch.h"
#include "IVControlledByInfo.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVControlledByInfo::IVControlledByInfo(bool isNetwork, bool isPlayer)
	{
		m_bIsControlledByNetwork = isNetwork;
		m_bIsPlayer = isPlayer;
	}
	IVControlledByInfo::IVControlledByInfo(CControlledByInfo& native)
	{
		m_bIsControlledByNetwork = native.m_isControlledByNetwork;
		m_bIsPlayer = native.m_isPlayer;
	}

	// - - - Methods / Functions - - -
	IVControlledByInfo IVControlledByInfo::LocalAIControl()
	{
		return IVControlledByInfo(false, false);
	}
	IVControlledByInfo IVControlledByInfo::LocalPlayerControl()
	{
		return IVControlledByInfo(false, true);
	}
	IVControlledByInfo IVControlledByInfo::NetworkNpcControl()
	{
		return IVControlledByInfo(true, false);
	}
	IVControlledByInfo IVControlledByInfo::NetworkPlayerControl()
	{
		return IVControlledByInfo(true, true);
	}




}