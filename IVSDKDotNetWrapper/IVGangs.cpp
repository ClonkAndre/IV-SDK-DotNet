#include "pch.h"
#include "IVGangs.h"

namespace IVSDKDotNet
{
	bool IVGangs::Save()
	{
		return CGangs::Save();;
	}
	bool IVGangs::Load()
	{
		return CGangs::Load();;
	}
}