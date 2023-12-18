#pragma once

namespace IVSDKDotNet
{
	public ref class IVReplay
	{
	public:
		static property uint32_t Mode
		{
		public:
			uint32_t get()
			{
				return CReplay::Mode;
			}
			void set(uint32_t value)
			{
				CReplay::Mode = value;
			}
		}
	};
}