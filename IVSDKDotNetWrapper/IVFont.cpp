#include "pch.h"
#include "IVFont.h"

namespace IVSDKDotNet
{
	void IVFont::Initialise()
	{
		CFont::Initialise();
	}
	void IVFont::SetScale(SizeF scale)
	{
		CFont::SetScale(scale.Width, scale.Height);
	}
	void IVFont::SetScale(float x, float y)
	{
		SetScale(SizeF(x, y));
	}
	void IVFont::SetColor(Color color)
	{
		CFont::SetColor(color.R, color.G, color.B, color.A);
	}
}