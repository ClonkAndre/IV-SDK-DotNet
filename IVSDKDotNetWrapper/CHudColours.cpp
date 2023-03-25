#include "pch.h"
#include "CHudColours.h"

namespace IVSDKDotNet {

	Color CHudColours::GetHudColour()
	{
		Native_CRGBA* r = Native_CHudColours::GetHudColour();

		if (r)
			return Color::FromArgb(r->a, r->r, r->g, r->b);

		return Color::Empty;
	}

}