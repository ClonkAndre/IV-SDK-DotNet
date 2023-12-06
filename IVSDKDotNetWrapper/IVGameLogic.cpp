#include "pch.h"
#include "IVGameLogic.h"

namespace IVSDKDotNet
{
	bool IVGameLogic::Save()
	{
		return CGameLogic::Save();
	}
	bool IVGameLogic::Load()
	{
		return CGameLogic::Load();
	}
	void IVGameLogic::RestorePlayerStuffDuringResurrection(IVPed^ pPlayerPed, Vector3 newCoors, float newHeading)
	{
		NULLPTR_CHECK(pPlayerPed);

		CVector vec;
		vec.x = newCoors.X;
		vec.y = newCoors.Y;
		vec.z = newCoors.Z;

		CGameLogic::RestorePlayerStuffDuringResurrection(pPlayerPed->NativePed, vec, newHeading);
	}
}