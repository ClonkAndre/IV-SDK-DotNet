#pragma once

class Native_CDynamicEntity : public Native_CEntity
{
public:
	uint8_t pad6[0x8];													// 070-078
	uint32_t* m_pAnim;													// 078-07C
	uint8_t pad7[0x94];													// 07C-110

	// used for reading bone positions e.g. seat locations
	Native_CMatrix* GetBoneMatrix(int boneID)
	{
		return ((Native_CMatrix * (__thiscall*)(Native_CDynamicEntity*, int))(AddressSetter::Get(0x5C7710, 0x4F1930)))(this, boneID);
	}

	// used for transform modifications e.g. popup lights, firetruck/apc cannon but 1:1 identical to the above
	Native_CMatrix* GetBoneMatrix2(int boneID)
	{
		return ((Native_CMatrix * (__thiscall*)(Native_CDynamicEntity*, int))(AddressSetter::Get(0xD9100, 0x315390)))(this, boneID);
	}
};
VALIDATE_SIZE(Native_CDynamicEntity, 0x110);
VALIDATE_OFFSET(Native_CDynamicEntity, m_pAnim, 0x78);

namespace IVSDKDotNet {

	public ref class CDynamicEntity : CEntity
	{
	public:
		CDynamicEntity(Native_CDynamicEntity* entity);

		GTAMatrix GetBoneMatrix(int boneID);
		GTAMatrix GetBoneMatrix2(int boneID);

	private:
		Native_CDynamicEntity* m_cEntity;
	};

}