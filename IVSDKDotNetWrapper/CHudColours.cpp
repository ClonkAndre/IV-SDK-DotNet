#include "pch.h"
#include "CHudColours.h"

namespace IVSDKDotNet {

	CRGBA^ CHudColours::GetHudColour()
	{
		Native_CRGBA* r = Native_CHudColours::GetHudColour();

		if (r)
			return gcnew CRGBA(r->r, r->g, r->b, r->a);

		return nullptr;
	}

}