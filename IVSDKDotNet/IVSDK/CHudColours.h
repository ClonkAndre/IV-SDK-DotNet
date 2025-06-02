#include "eHudColour.h"

class CHudColours
{
public:
	static inline CRGBA* ms_HudColour = (CRGBA*)AddressSetter::Get("CHudColours", "ms_HudColour"); // ms_HudColour[73]
};