#pragma once

namespace IVSDKDotNet
{
	public ref class IVCutsceneMgr
	{
	public:
		static property uint32_t Running
		{
		public:
			uint32_t get()
			{
				return CCutsceneMgr::ms_running;
			}
			void set(uint32_t value)
			{
				CCutsceneMgr::ms_running = value;
			}
		}

	public:
		static bool IsRunning();

	};
}