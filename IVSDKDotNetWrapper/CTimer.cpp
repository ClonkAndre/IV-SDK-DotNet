#include "pch.h"
#include "CTimer.h"

namespace IVSDKDotNet {

	bool CTimer::GetIsPaused()
	{
		return Native_CTimer::GetIsPaused();
	}

}