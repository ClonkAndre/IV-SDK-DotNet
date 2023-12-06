#include "pch.h"
#include "IVAudioZones.h"

namespace IVSDKDotNet
{
	void IVAudioZones::Update(bool bForceUpdate, Vector3 TestCoors)
	{
		CVector vec = { TestCoors.X, TestCoors.Y, TestCoors.Z };
		CAudioZones::Update(bForceUpdate, vec);
	}
}