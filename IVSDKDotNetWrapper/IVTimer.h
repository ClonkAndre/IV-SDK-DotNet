#pragma once

namespace IVSDKDotNet
{
	public ref class IVTimer
	{
	public:
		static property uint8_t CodePause
		{
		public:
			uint8_t get()
			{
				return CTimer::m_CodePause;
			}
			void set(uint8_t value)
			{
				CTimer::m_CodePause = value;
			}
		}
		static property uint8_t UserPause
		{
		public:
			uint8_t get()
			{
				return CTimer::m_UserPause;
			}
			void set(uint8_t value)
			{
				CTimer::m_UserPause = value;
			}
		}
		static property uint32_t FrameCounter
		{
		public:
			uint32_t get()
			{
				return CTimer::m_FrameCounter;
			}
			void set(uint32_t value)
			{
				CTimer::m_FrameCounter = value;
			}
		}
		static property uint32_t TimeInMilliseconds
		{
		public:
			uint32_t get()
			{
				return CTimer::m_snTimeInMilliseconds;
			}
			void set(uint32_t value)
			{
				CTimer::m_snTimeInMilliseconds = value;
			}
		}
		static property float MinTimeStep
		{
		public:
			float get()
			{
				return CTimer::ms_fMinTimeStep;
			}
			void set(float value)
			{
				CTimer::ms_fMinTimeStep = value;
			}
		}
		static property float MaxTimeStep
		{
		public:
			float get()
			{
				return CTimer::ms_fMaxTimeStep;
			}
			void set(float value)
			{
				CTimer::ms_fMaxTimeStep = value;
			}
		}
		static property float TimeStep
		{
		public:
			float get()
			{
				return CTimer::ms_fTimeStep;
			}
			void set(float value)
			{
				CTimer::ms_fTimeStep = value;
			}
		}
		static property float TimeStepNonClipped
		{
		public:
			float get()
			{
				return CTimer::ms_fTimeStepNonClipped;
			}
			void set(float value)
			{
				CTimer::ms_fTimeStepNonClipped = value;
			}
		}
		static property float TimeScale
		{
		public:
			float get()
			{
				return CTimer::ms_fTimeScale;
			}
			void set(float value)
			{
				CTimer::ms_fTimeScale = value;
			}
		}
		static property float TimeScale2
		{
		public:
			float get()
			{
				return CTimer::ms_fTimeScale2;
			}
			void set(float value)
			{
				CTimer::ms_fTimeScale2 = value;
			}
		}
		static property float TimeScale3
		{
		public:
			float get()
			{
				return CTimer::ms_fTimeScale3;
			}
			void set(float value)
			{
				CTimer::ms_fTimeScale3 = value;
			}
		}

	public:
		static bool GetIsPaused();
	};
}