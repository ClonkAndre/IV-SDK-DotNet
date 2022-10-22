#include "pch.h"
#include "rage.h"

namespace IVSDKDotNet {

	IntPtr RAGE::GetHWND()
	{
		return IntPtr(Native_RAGE::GetHWND());
	}

}