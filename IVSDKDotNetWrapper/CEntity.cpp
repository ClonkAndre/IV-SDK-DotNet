#include "pch.h"
#include "CEntity.h"

namespace IVSDKDotNet {

	CEntity::CEntity(Native_CEntity* entity)
	{
		m_cEntity = entity;
	}

	void CEntity::Teleport(GTAMatrix mat, bool bDontUpdatePhysicsMatrix, bool bImmediately)
	{
		Native_CMatrix* m = new Native_CMatrix(mat.right, mat.up, mat.at, mat.pos);
		m_cEntity->Teleport(m, bDontUpdatePhysicsMatrix, bImmediately);
		delete m;
	}
	void CEntity::Teleport(Vector3 v, bool bDontUpdatePhysicsMatrix, bool bImmediately)
	{
		Native_CVector* pos = new Native_CVector(v.X, v.Y, v.Z);
		m_cEntity->Teleport(pos, bDontUpdatePhysicsMatrix, bImmediately);
		delete pos;
	}

	void CEntity::PreRender(int nUnk, int nUnk2, char alpha, int nUnkNeg1)
	{
		m_cEntity->PreRender(nUnk, nUnk2, alpha, nUnkNeg1);
	}

}