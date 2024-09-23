#pragma once

namespace IVSDKDotNet
{
	public value struct IVControlledByInfo
	{
	public:
		bool IsControlledByNetwork()
		{
			return m_bIsControlledByNetwork;
		}
		bool IsControlledByLocalAi()
		{
			return (!m_bIsControlledByNetwork && !m_bIsPlayer);
		}
		bool IsControlledByNetworkAi()
		{
			return (m_bIsControlledByNetwork && !m_bIsPlayer);
		}
		bool IsControlledByLocalOrNetworkAi()
		{
			return !m_bIsPlayer;
		}
		bool IsControlledByLocalPlayer()
		{
			return (!m_bIsControlledByNetwork && m_bIsPlayer);
		}
		bool IsControlledByNetworkPlayer()
		{
			return (m_bIsControlledByNetwork && m_bIsPlayer);
		}
		bool IsControlledByLocalOrNetworkPlayer()
		{
			return m_bIsPlayer;
		}

	public:
		IVControlledByInfo(bool isNetwork, bool isPlayer);

		static IVControlledByInfo LocalAIControl();
		static IVControlledByInfo LocalPlayerControl();
		static IVControlledByInfo NetworkNpcControl();
		static IVControlledByInfo NetworkPlayerControl();

	internal:
		IVControlledByInfo(CControlledByInfo& native);

	internal:
		bool m_bIsControlledByNetwork;
		bool m_bIsPlayer;
	};
}