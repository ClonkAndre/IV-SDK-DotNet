#pragma once

namespace IVSDKDotNet
{
	public ref class IVPhSleep
	{
	public:
		property float MinVelocity
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSleep, 0.0F);
				return NativeSleep->m_fMinVelocity;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeSleep);
				NativeSleep->m_fMinVelocity = value;
			}
		}

	internal:
		IVPhSleep(rage::phSleep* nativePtr);

	internal:
		rage::phSleep* NativeSleep;
	};
}