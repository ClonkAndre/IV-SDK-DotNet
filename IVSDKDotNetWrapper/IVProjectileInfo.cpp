#include "pch.h"
#include "IVProjectileInfo.h"

namespace IVSDKDotNet
{
	// - - - Methods / Functions - - -
	bool IVProjectileInfo::AddProjectile(IVEntity^ pEntProjOwner, int projType, IVMatrix^ pMatrix, Vector3 vecStart, Vector3 vecEnd, IVEntity^ pTargetEntity, bool noMPSync, IVObject^ pProjectileObject)
	{
		//NULLPTR_CHECK_WITH_RETURN(pEntProjOwner, false);
		//NULLPTR_CHECK_WITH_RETURN(pTargetEntity, false);
		//NULLPTR_CHECK_WITH_RETURN(pMatrix, false);
		//NULLPTR_CHECK_WITH_RETURN(pMatrix->NativeMatrix, false);

		CVector* nVecStart = new CVector();
		nVecStart->x = vecStart.X;
		nVecStart->y = vecStart.Y;
		nVecStart->z = vecStart.Z;
		CVector* nVecEnd = new CVector();
		nVecEnd->x = vecEnd.X;
		nVecEnd->y = vecEnd.Y;
		nVecEnd->z = vecEnd.Z;

		bool result = CProjectileInfo::AddProjectile(
			pEntProjOwner == nullptr ? nullptr : pEntProjOwner->NativeEntity,
			projType,
			pMatrix == nullptr ? nullptr : pMatrix->NativeMatrix,
			nVecStart,
			nVecEnd,
			pTargetEntity == nullptr ? nullptr : pTargetEntity->NativeEntity,
			noMPSync,
			pProjectileObject == nullptr ? nullptr : pProjectileObject->NativeObject);

		delete nVecStart;
		delete nVecEnd;

		return result;
	}
}