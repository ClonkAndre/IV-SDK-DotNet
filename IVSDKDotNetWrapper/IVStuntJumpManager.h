#pragma once

namespace IVSDKDotNet
{
	public ref class IVStuntJumpManager
	{
	public:
		static property bool Active
		{
		public:
			bool get()
			{
				return CStuntJumpManager::m_bActive;
			}
			void set(bool value)
			{
				CStuntJumpManager::m_bActive = value;
			}
		}
		static property uint32_t NumCompleted
		{
		public:
			uint32_t get()
			{
				return CStuntJumpManager::m_iNumCompleted;
			}
			void set(uint32_t value)
			{
				CStuntJumpManager::m_iNumCompleted = value;
			}
		}
		static property uint32_t NumJumps
		{
		public:
			uint32_t get()
			{
				return CStuntJumpManager::m_iNumJumps;
			}
			void set(uint32_t value)
			{
				CStuntJumpManager::m_iNumJumps = value;
			}
		}

	public:
		static bool Save();
		static bool Load();

	};
}