class CTaskComplexWander : public CTaskComplex
{
public:
	uint8_t pad[0x80];											// 00-80
	float m_fUnk;												// 80-84 set to 0 upon initializing CTaskComplexWanderStandard

	CTaskComplexWander(uint32_t moveState, float initialDir, bool bSensibly, float targetRadius, uint32_t unk1)
	{
		((void(__thiscall*)(CTaskComplexWander*, uint32_t, float, bool, float, uint32_t))(AddressSetter::Get("CTaskComplexWander", "CTaskComplexWander")))(this, moveState, initialDir, bSensibly, targetRadius, unk1);
	}
};

class CTaskComplexWanderStandard : public CTaskComplexWander
{
public:
	CTaskComplexWanderStandard(uint32_t moveState, float initialDir, bool bSensibly, float targetRadius, uint32_t unk1) : CTaskComplexWander(moveState, initialDir, bSensibly, targetRadius, unk1)
	{
		// this was probably inlined
		*(uint32_t*)this = AddressSetter::Get("CTaskComplexWanderStandard", "CTaskComplexWanderStandard"); // set vftable
		this->m_fUnk = 0;
	}
};