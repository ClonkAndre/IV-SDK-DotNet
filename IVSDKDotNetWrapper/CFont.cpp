#include "pch.h"
#include "CFont.h"

namespace IVSDKDotNet {

	void CFont::Initialise()
	{
		Native_CFont::Initialise();
	}

	void CFont::SetScale(float x, float y)
	{
		Native_CFont::SetScale(x, y);
	}

	void CFont::SetColor(Color color)
	{
		Native_CFont::SetColor(color.R, color.G, color.B, color.A);
	}
	void CFont::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	{
		Native_CFont::SetColor(r, g, b, a);
	}

}