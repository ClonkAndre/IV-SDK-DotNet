#pragma once

namespace IVSDKDotNet
{
	public ref class IVProjectileInfo
	{
	public:
		static bool AddProjectile(IVEntity^ pEntProjOwner, int projType, IVMatrix^ pMatrix, Vector3 vecStart, Vector3 vecEnd, IVEntity^ pTargetEntity, bool noMPSync, IVObject^ pProjectileObject);
	};
}