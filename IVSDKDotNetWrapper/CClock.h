#pragma once

#include "pch.h"

class Native_CClock
{
public:
	static uint32_t GetGameClockForcedMinutes()					{ return AddressSetter::GetRef<uint32_t>(0xDD52F0, 0xD51684); }
	static void SetGameClockForcedMinutes(uint32_t value)		{ AddressSetter::GetRef<uint32_t>(0xDD52F0, 0xD51684) = value; }

	static uint32_t GetGameClockForcedHours()					{ return AddressSetter::GetRef<uint32_t>(0xDD5308, 0xD5169C); }
	static void SetGameClockForcedHours(uint32_t value)			{ AddressSetter::GetRef<uint32_t>(0xDD5308, 0xD5169C) = value; }

	static uint32_t GetCurrentDay()								{ return AddressSetter::GetRef<uint32_t>(0xDD5310, 0xD516A4); }
	static void SetCurrentDay(uint32_t value)					{ AddressSetter::GetRef<uint32_t>(0xDD5310, 0xD516A4) = value; }

	static uint32_t GetGameClockSeconds()						{ return AddressSetter::GetRef<uint32_t>(0xDD530C, 0xD516A0); }
	static void SetGameClockSeconds(uint32_t value)				{ AddressSetter::GetRef<uint32_t>(0xDD530C, 0xD516A0) = value; }

	static uint32_t GetGameClockMinutes()						{ return AddressSetter::GetRef<uint32_t>(0xDD52FC, 0xD51690); }
	static void SetGameClockMinutes(uint32_t value)				{ AddressSetter::GetRef<uint32_t>(0xDD52FC, 0xD51690) = value; }

	static uint32_t GetGameClockHours()							{ return AddressSetter::GetRef<uint32_t>(0xDD5300, 0xD51694); }
	static void SetGameClockHours(uint32_t value)				{ AddressSetter::GetRef<uint32_t>(0xDD5300, 0xD51694) = value; }

	static uint32_t GetGameClockDays()							{ return AddressSetter::GetRef<uint32_t>(0xDD5314, 0xD516A8); }
	static void SetGameClockDays(uint32_t value)				{ AddressSetter::GetRef<uint32_t>(0xDD5314, 0xD516A8) = value; }

	static uint32_t GetGameClockMonth()							{ return AddressSetter::GetRef<uint32_t>(0xDD52F8, 0xD5168C); }
	static void SetGameClockMonth(uint32_t value)				{ AddressSetter::GetRef<uint32_t>(0xDD52F8, 0xD5168C) = value; }

	static uint32_t GetMillisecondsPerGameMinute()				{ return AddressSetter::GetRef<uint32_t>(0xDD5304, 0xD51698); }
	static void SetMillisecondsPerGameMinute(uint32_t value)	{ AddressSetter::GetRef<uint32_t>(0xDD5304, 0xD51698) = value; }

};

namespace IVSDKDotNet {

	public ref class CClock
	{
	public:

		static property uint32_t GameClockForcedMinutes {
			public:
				uint32_t get()					{ return Native_CClock::GetGameClockForcedMinutes(); }
				void	 set(uint32_t value)	{ Native_CClock::SetGameClockForcedMinutes(value); }
		}
		static property uint32_t GameClockForcedHours {
			public:
				uint32_t get()					{ return Native_CClock::GetGameClockForcedHours(); }
				void	 set(uint32_t value)	{ Native_CClock::SetGameClockForcedHours(value); }
		}

		static property uint32_t CurrentDay {
			public:
				uint32_t get()					{ return Native_CClock::GetCurrentDay(); }
				void	 set(uint32_t value)	{ Native_CClock::SetCurrentDay(value); }
		}

		static property uint32_t GameClockSeconds {
			public:
				uint32_t get()					{ return Native_CClock::GetGameClockSeconds(); }
				void	 set(uint32_t value)	{ Native_CClock::SetGameClockSeconds(value); }
		}
		static property uint32_t GameClockMinutes {
			public:
				uint32_t get()					{ return Native_CClock::GetGameClockMinutes(); }
				void	 set(uint32_t value)	{ Native_CClock::SetGameClockMinutes(value); }
		}
		static property uint32_t GameClockHours {
			public:
				uint32_t get()					{ return Native_CClock::GetGameClockHours(); }
				void	 set(uint32_t value)	{ Native_CClock::SetGameClockHours(value); }
		}

		static property uint32_t GameClockDays {
			public:
				uint32_t get()					{ return Native_CClock::GetGameClockDays(); }
				void	 set(uint32_t value)	{ Native_CClock::SetGameClockDays(value); }
		}
		static property uint32_t GameClockMonth {
			public:
				uint32_t get()					{ return Native_CClock::GetGameClockMonth(); }
				void	 set(uint32_t value)	{ Native_CClock::SetGameClockMonth(value); }
		}

		static property uint32_t MillisecondsPerGameMinute {
			public:
				uint32_t get()					{ return Native_CClock::GetMillisecondsPerGameMinute(); }
				void	 set(uint32_t value)	{ Native_CClock::SetMillisecondsPerGameMinute(value); }
		}

	};

}

