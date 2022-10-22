#include "pch.h"
#include "CRGBA.h"

namespace IVSDKDotNet {

	CRGBA::CRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	{
		R = r;
		G = g;
		B = b;
		A = a;
	}

	CRGBFloat::CRGBFloat(float r, float g, float b)
	{
		R = r;
		G = g;
		B = b;
	}

}