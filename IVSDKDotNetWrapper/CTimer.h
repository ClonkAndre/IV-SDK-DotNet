#pragma once

class Native_CTimer
{
public:
	static uint8_t	GetCodePause()					{ return AddressSetter::GetRef<uint8_t>(0xDDDF42, 0xCFCC3A); }
	static void		SetCodePause(uint8_t value)		{ AddressSetter::GetRef<uint8_t>(0xDDDF42, 0xCFCC3A) = value; }

	static uint8_t	GetUserPause()					{ return AddressSetter::GetRef<uint8_t>(0xDDDF41, 0xCFCC39); }
	static void		SetUserPause(uint8_t value)		{ AddressSetter::GetRef<uint8_t>(0xDDDF41, 0xCFCC39) = value; }

	static uint32_t GetFrameCounter()				{ return AddressSetter::GetRef<uint32_t>(0xDDDF38, 0xCFCC30); }
	static void		SetFrameCounter(uint32_t value) { AddressSetter::GetRef<uint32_t>(0xDDDF38, 0xCFCC30) = value; }

	static uint32_t GetTimeInMilliseconds()					{ return AddressSetter::GetRef<uint32_t>(0xDDDE74, 0xCFCB6C); }
	static void		SetTimeInMilliseconds(uint32_t value)	{ AddressSetter::GetRef<uint32_t>(0xDDDE74, 0xCFCB6C) = value; }

	static float	GetMinTimeStep()				{ return AddressSetter::GetRef<float>(0xB1D9E4, 0xB2E09C); }
	static void		SetMinTimeStep(float value)		{ AddressSetter::GetRef<float>(0xB1D9E4, 0xB2E09C) = value; }

	static float	GetMaxTimeStep()				{ return AddressSetter::GetRef<float>(0xB1D9E8, 0xB2E0A0); }
	static void		SetMaxTimeStep(float value)		{ AddressSetter::GetRef<float>(0xB1D9E8, 0xB2E0A0) = value; }

	static float	GetTimeStep()					{ return AddressSetter::GetRef<float>(0xDDDE7C, 0xCFCB74); }
	static void		SetTimeStep(float value)		{ AddressSetter::GetRef<float>(0xDDDE7C, 0xCFCB74) = value; }

	static float	GetTimeStepNonClipped()				{ return AddressSetter::GetRef<float>(0xDDDEBC, 0xCFCBB4); }
	static void		SetTimeStepNonClipped(float value)	{ AddressSetter::GetRef<float>(0xDDDEBC, 0xCFCBB4) = value; }

	// Set by scripts
	static float	GetTimeScale()					{ return AddressSetter::GetRef<float>(0xB1D9D8, 0xB2E090); }
	static void		SetTimeScale(float value)		{ AddressSetter::GetRef<float>(0xB1D9D8, 0xB2E090) = value; }

	// Set by scripts
	static float	GetTimeScale2()					{ return AddressSetter::GetRef<float>(0xB1D9DC, 0xB2E094); }
	static void		SetTimeScale2(float value)		{ AddressSetter::GetRef<float>(0xB1D9DC, 0xB2E094) = value; }

	// Changes for death camera
	static float	GetTimeScale3()					{ return AddressSetter::GetRef<float>(0xB1D9E0, 0xB2E098); }
	static void		SetTimeScale3(float value)		{ AddressSetter::GetRef<float>(0xB1D9E0, 0xB2E098) = value; }

	static bool GetIsPaused()
	{
		return ((uint32_t(__cdecl*)())(AddressSetter::Get(0x44370, 0xAD0B0)))();
	}
};

namespace IVSDKDotNet {

	public ref class CTimer
	{
	public:

		static bool GetIsPaused();

		static property uint8_t CodePause {
			public:
				uint8_t		get()				{ return Native_CTimer::GetCodePause(); }
				void		set(uint8_t value)	{ Native_CTimer::SetCodePause(value); }
		}

		static property uint8_t UserPause {
			public:
				uint8_t		get()				{ return Native_CTimer::GetUserPause(); }
				void		set(uint8_t value)	{ Native_CTimer::SetUserPause(value); }
		}

		static property uint32_t FrameCounter {
			public:
				uint32_t	get()				{ return Native_CTimer::GetFrameCounter(); }
				void		set(uint32_t value)	{ Native_CTimer::SetFrameCounter(value); }
		}

		static property uint32_t TimeInMilliseconds {
			public:
				uint32_t	get()				{ return Native_CTimer::GetTimeInMilliseconds(); }
				void		set(uint32_t value)	{ Native_CTimer::SetTimeInMilliseconds(value); }
		}

		static property float MinTimeStep {
			public:
				float		get()				{ return Native_CTimer::GetMinTimeStep(); }
				void		set(float value)	{ Native_CTimer::SetMinTimeStep(value); }
		}

		static property float MaxTimeStep {
			public:
				float		get()				{ return Native_CTimer::GetMaxTimeStep(); }
				void		set(float value)	{ Native_CTimer::SetMaxTimeStep(value); }
		}

		static property float TimeStep {
			public:
				float		get()				{ return Native_CTimer::GetTimeStep(); }
				void		set(float value)	{ Native_CTimer::SetTimeStep(value); }
		}

		static property float TimeStepNonClipped {
			public:
				float		get()				{ return Native_CTimer::GetTimeStepNonClipped(); }
				void		set(float value)	{ Native_CTimer::SetTimeStepNonClipped(value); }
		}

		/// <summary>
		/// Gets or sets the time scale by scripts.
		/// This is usually set by scripts.
		/// </summary>
		static property float TimeScale {
			public:
				float		get()				{ return Native_CTimer::GetTimeScale(); }
				void		set(float value)	{ Native_CTimer::SetTimeScale(value); }
		}

		/// <summary>
		/// Gets or sets the time scale by scripts.
		/// This is usually set by scripts.
		/// </summary>
		static property float TimeScale2 {
			public:
				float		get()				{ return Native_CTimer::GetTimeScale2(); }
				void		set(float value)	{ Native_CTimer::SetTimeScale2(value); }
		}

		/// <summary>
		/// Gets or sets the time scale for death camera.
		/// </summary>
		static property float TimeScale3 {
			public:
				float		get()				{ return Native_CTimer::GetTimeScale3(); }
				void		set(float value)	{ Native_CTimer::SetTimeScale3(value); }
		}

	};

}