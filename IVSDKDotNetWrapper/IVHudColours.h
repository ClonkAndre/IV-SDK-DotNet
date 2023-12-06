#pragma once

namespace IVSDKDotNet
{
	public ref class IVHudColours
	{
	public:
		static property Color HudColour
		{
		public:
			Color get()
			{
				CRGBA* v = CHudColours::ms_HudColour;
				NULLPTR_CHECK_WITH_RETURN(v, Color::Empty);
				return Color::FromArgb(v->a, v->r, v->g, v->b);
			}
			void set(Color value)
			{
				CRGBA* v = CHudColours::ms_HudColour;
				NULLPTR_CHECK(v);

				v->a = value.A;
				v->r = value.R;
				v->g = value.G;
				v->b = value.B;
			}
		}
	};
}