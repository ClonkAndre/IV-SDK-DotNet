#pragma once

class Native_CHudColours
{
public:
	static Native_CRGBA* GetHudColour() { return (Native_CRGBA*)AddressSetter::Get(0xDE4D40, 0xDE8038); } // ms_HudColour[73]
};

namespace IVSDKDotNet {

	public ref class CHudColours
	{
	public:

		static Color GetHudColour();

	};

}



