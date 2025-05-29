class CDynamicEntity : public CEntity
{
public:
	uint8_t pad6[0x8];													// 070-078
	uint32_t* m_pAnim;													// 078-07C
	uint8_t pad7[0x94];													// 07C-110

	// used for reading bone positions e.g. seat locations
	CMatrix* GetBoneMatrix(int boneID)
	{
		return ((CMatrix*(__thiscall*)(CDynamicEntity*, int))(AddressSetter::Get("CDynamicEntity", "GetBoneMatrix")))(this, boneID);
	}

	// used for transform modifications e.g. popup lights, firetruck/apc cannon but 1:1 identical to the above
	CMatrix* GetBoneMatrix2(int boneID)
	{
		return ((CMatrix * (__thiscall*)(CDynamicEntity*, int))(AddressSetter::Get("CDynamicEntity", "GetBoneMatrix2")))(this, boneID);
	}

	// prolly rather goes into m_pAnim
	uint32_t* PlayAnimation(int animGroupId, int animId, int flags, int unkMaybeBlendData, float unk1)
	{
		return ((uint32_t * (__thiscall*)(uint32_t*, int, int, int, int, float))(AddressSetter::Get("CDynamicEntity", "PlayAnimation")))(m_pAnim, animGroupId, animId, flags, unkMaybeBlendData, unk1);
	}
};

VALIDATE_SIZE(CDynamicEntity, 0x110);
VALIDATE_OFFSET(CDynamicEntity, m_pAnim, 0x78);
