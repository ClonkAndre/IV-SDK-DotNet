#include "pch.h"
#include "IVFrontEnd.h"

namespace IVSDKDotNet
{
	void IVFrontEnd::SwitchOnWaypoint(int unk_8, Vector2 pos, bool snapToHoveringBlip, [OutAttribute] Vector3% outPos)
	{
		CVector outVec;
		CFrontEnd::SwitchOnWaypoint(unk_8, pos.X, pos.Y, snapToHoveringBlip, &outVec);
		outPos = Vector3(outVec.x, outVec.y, outVec.z);
	}
	void IVFrontEnd::SwitchOnWaypoint(int unk_8, float x, float y, bool snapToHoveringBlip, [OutAttribute] Vector3% outPos)
	{
		SwitchOnWaypoint(unk_8, Vector2(x, y), snapToHoveringBlip, outPos);
	}
	void IVFrontEnd::SwitchOffWaypoint()
	{
		CFrontEnd::SwitchOffWaypoint();
	}
	void IVFrontEnd::ToggleWaypoint()
	{
		CFrontEnd::ToggleWaypoint();
	}
}