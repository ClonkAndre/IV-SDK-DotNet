#include "pch.h"
#include "CDynamicEntity.h"

namespace IVSDKDotNet {

	CDynamicEntity::CDynamicEntity(Native_CDynamicEntity* entity) : CEntity(entity)
	{
		m_cEntity = entity;
	}

	GTAMatrix CDynamicEntity::GetBoneMatrix(int boneID)
	{
		Native_CMatrix* m = m_cEntity->GetBoneMatrix(boneID);
		return GTAMatrix(
			Vector3(m->right.x, m->right.y, m->right.z),
			Vector3(m->up.x, m->up.y, m->up.z),
			Vector3(m->at.x, m->at.y, m->at.z),
			Vector3(m->pos.x, m->pos.y, m->pos.z));
	}
	GTAMatrix CDynamicEntity::GetBoneMatrix2(int boneID)
	{
		Native_CMatrix* m = m_cEntity->GetBoneMatrix2(boneID);
		return GTAMatrix(
			Vector3(m->right.x, m->right.y, m->right.z),
			Vector3(m->up.x, m->up.y, m->up.z),
			Vector3(m->at.x, m->at.y, m->at.z),
			Vector3(m->pos.x, m->pos.y, m->pos.z));
	}

}