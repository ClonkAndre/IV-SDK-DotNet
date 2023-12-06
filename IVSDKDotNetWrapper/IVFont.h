#pragma once

namespace IVSDKDotNet
{
	public ref class IVFont
	{
	public:
		static void Initialise();
		static void SetScale(SizeF scale);
		static void SetScale(float x, float y);
		static void SetColor(Color color);
	};
}