#pragma once

namespace IVSDKDotNet
{
	public ref class IVWanted
	{
	public:
		static property uint32_t MaximumWantedLevel
		{
		public:
			uint32_t get()
			{
				return CWanted::MaximumWantedLevel;
			}
			void set(uint32_t value)
			{
				CWanted::MaximumWantedLevel = value;
			}
		}
		static property uint32_t nMaximumWantedLevel
		{
		public:
			uint32_t get()
			{
				return CWanted::nMaximumWantedLevel;
			}
			void set(uint32_t value)
			{
				CWanted::nMaximumWantedLevel = value;
			}
		}
	};
}