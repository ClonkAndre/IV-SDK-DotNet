#pragma once

namespace IVSDKDotNet
{
	public ref class IVClock
	{
	public:
		static property uint32_t GameClockForcedMinutes
		{
		public:
			uint32_t get()
			{
				return CClock::ms_nGameClockForcedMinutes;
			}
			void set(uint32_t value)
			{
				CClock::ms_nGameClockForcedMinutes = value;
			}
		}
		static property uint32_t GameClockForcedHours
		{
		public:
			uint32_t get()
			{
				return CClock::ms_nGameClockForcedHours;
			}
			void set(uint32_t value)
			{
				CClock::ms_nGameClockForcedHours = value;
			}
		}
		static property uint32_t CurrentDay
		{
		public:
			uint32_t get()
			{
				return CClock::CurrentDay;
			}
			void set(uint32_t value)
			{
				CClock::CurrentDay = value;
			}
		}
		static property uint32_t GameClockSeconds
		{
		public:
			uint32_t get()
			{
				return CClock::ms_nGameClockSeconds;
			}
			void set(uint32_t value)
			{
				CClock::ms_nGameClockSeconds = value;
			}
		}
		static property uint32_t GameClockMinutes
		{
		public:
			uint32_t get()
			{
				return CClock::ms_nGameClockMinutes;
			}
			void set(uint32_t value)
			{
				CClock::ms_nGameClockMinutes = value;
			}
		}
		static property uint32_t GameClockHours
		{
		public:
			uint32_t get()
			{
				return CClock::ms_nGameClockHours;
			}
			void set(uint32_t value)
			{
				CClock::ms_nGameClockHours = value;
			}
		}
		static property uint32_t GameClockDays
		{
		public:
			uint32_t get()
			{
				return CClock::ms_nGameClockDays;
			}
			void set(uint32_t value)
			{
				CClock::ms_nGameClockDays = value;
			}
		}
		static property uint32_t GameClockMonth
		{
		public:
			uint32_t get()
			{
				return CClock::ms_nGameClockMonth;
			}
			void set(uint32_t value)
			{
				CClock::ms_nGameClockMonth = value;
			}
		}
		static property uint32_t MillisecondsPerGameMinute
		{
		public:
			uint32_t get()
			{
				return CClock::ms_nMillisecondsPerGameMinute;
			}
			void set(uint32_t value)
			{
				CClock::ms_nMillisecondsPerGameMinute = value;
			}
		}
	};
}