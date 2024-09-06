#pragma once

namespace IVSDKDotNet
{
	public ref class IVProjectileInfo
	{
	public:
		/// <summary>
		/// Adds a projectile to the world.
		/// </summary>
		/// <param name="pEntProjOwner">The owner of the projectile.</param>
		/// <param name="projType">The projectile type. Only '4' (Grenade), '5' (Molotov) and '6' (Rocket) worked for me.</param>
		/// <param name="pMatrix">The actual position of the projectile.</param>
		/// <param name="vecStart">Start pos of the projectile? (The actual position of the projectile is read from the given matrix so no idea what this does.)</param>
		/// <param name="vecEnd">End pos (or direction) of the projectile?</param>
		/// <param name="pTargetEntity">Can be null.</param>
		/// <param name="noMPSync">If the projectile should be synced over the network or not.</param>
		/// <param name="pProjectileObject">The projectile object to shoot. Can be null.</param>
		/// <returns></returns>
		static bool AddProjectile(IVEntity^ pEntProjOwner, int projType, IVMatrix^ pMatrix, Vector3 vecStart, Vector3 vecEnd, IVEntity^ pTargetEntity, bool noMPSync, IVObject^ pProjectileObject);
	};
}