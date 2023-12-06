#pragma once

namespace IVSDKDotNet
{
	public ref class IVNetwork
	{
	public:
		static property UIntPtr ClientBroadcastVars
		{
		public:
			UIntPtr get()
			{
				return UIntPtr(CNetwork::m_pClientBroadcastVars);
			}
			void set(UIntPtr value)
			{
				UINTPTR_ZERO_CHECK(value);
				CNetwork::m_pClientBroadcastVars = value.ToPointer();
			}
		}
		static property UIntPtr ClientBroadcastVarSize
		{
		public:
			UIntPtr get()
			{
				return UIntPtr(CNetwork::m_pClientBroadcastVarSize);
			}
			void set(UIntPtr value)
			{
				UINTPTR_ZERO_CHECK(value);
				CNetwork::m_pClientBroadcastVarSize = value.ToPointer();
			}
		}
		static property uint32_t NetworkSession
		{
		public:
			uint32_t get()
			{
				return CNetwork::m_bNetworkSession;
			}
			void set(uint32_t value)
			{
				CNetwork::m_bNetworkSession = value;
			}
		}
		static property uint32_t NetworkStatus
		{
		public:
			uint32_t get()
			{
				return CNetwork::m_nNetworkStatus;
			}
			void set(uint32_t value)
			{
				CNetwork::m_nNetworkStatus = value;
			}
		}
		static property bool IsHostingGame
		{
		public:
			bool get()
			{
				return CNetwork::m_bIsHostingGame;
			}
			void set(bool value)
			{
				CNetwork::m_bIsHostingGame = value;
			}
		}

	public:
		static bool IsNetworkGameRunning();
		static bool IsNetworkSession();
		static void CheckFramerate(bool bUnk, int time);

	};
}

