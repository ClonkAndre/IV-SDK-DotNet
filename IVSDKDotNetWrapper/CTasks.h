#pragma once

class Native_CTaskComplexDie : public Native_CTaskComplex
{
public:
	Native_CTaskComplexDie(uint32_t unk, uint32_t unk2, uint32_t unk3_44, uint32_t unk4_190, float fBlendDelta, float fAnimSpeed, uint32_t unk5_1)
	{
		((void(__thiscall*)(Native_CTaskComplexDie*, uint32_t, uint32_t, uint32_t, uint32_t, float, float, uint32_t))(AddressSetter::Get(0x6BC6C0, 0x818240)))(this, unk, unk2, unk3_44, unk4_190, fBlendDelta, fAnimSpeed, unk5_1);
	}
};

class Native_CTaskComplexMobileMakeCall : public Native_CTaskComplex
{
public:
	Native_CTaskComplexMobileMakeCall(char* speechLine, bool bUnk_1, bool bUnk2)
	{
		((void(__thiscall*)(Native_CTaskComplexMobileMakeCall*, char*, bool, bool))(AddressSetter::Get(0x4F5E00, 0x7AF830)))(this, speechLine, bUnk_1, bUnk2);
	}
};

class Native_CTaskComplexNewGetInVehicle : public Native_CTaskComplex
{
public:
	Native_CTaskComplexNewGetInVehicle(Native_CVehicle* veh, int32_t getInType, uint32_t unk27, int32_t unk, float fUnk)
	{
		((void(__thiscall*)(Native_CTaskComplexNewGetInVehicle*, Native_CVehicle*, int32_t, uint32_t, int32_t, float))(AddressSetter::Get(0x62BCF0, 0x86DFD0)))(this, veh, getInType, unk27, unk, fUnk);
	}
};

class Native_CTaskComplexNM : public Native_CTaskComplex
{
public:
	//CTaskComplexNM::CTaskComplexNM(v35, 2000, 10000, v34, COERCE_INT(0.0))
	Native_CTaskComplexNM(uint32_t nUnk, uint32_t nUnk2, uint32_t* pSubTask, float fUnk)
	{
		((void(__thiscall*)(Native_CTaskComplexNM*, uint32_t, uint32_t, uint32_t*, float))(AddressSetter::Get(0x85DBE0, 0x7D9100)))(this, nUnk, nUnk2, pSubTask, fUnk);
	}
};

class Native_CTaskComplexPlayerOnFoot : public Native_CTaskComplex
{
public:
	Native_CTaskComplexPlayerOnFoot()
	{
		((void(__thiscall*)(Native_CTaskComplexPlayerOnFoot*))(AddressSetter::Get(0x5AD950, 0x65A1F0)))(this);
	}
};

class Native_CTaskSimpleNMHighFall : public Native_CTaskSimple
{
public:
	//CTaskSimpleNMHighFall::CTaskSimpleNMHighFall(v33, 1000, 10000, 0, 0)
	Native_CTaskSimpleNMHighFall(uint32_t nUnk, uint32_t nUnk2, uint32_t nUnk3, uint32_t nUnk4)
	{
		((void(__thiscall*)(Native_CTaskSimpleNMHighFall*, uint32_t, uint32_t, uint32_t, uint32_t))(AddressSetter::Get(0x8616F0, 0x7DCC10)))(this, nUnk, nUnk2, nUnk3, nUnk4);
	}
};

class Native_CTaskSimpleNMJumpRollFromRoadVehicle : public Native_CTaskSimple
{
public:
	Native_CTaskSimpleNMJumpRollFromRoadVehicle(uint32_t time, uint32_t time2)
	{
		((void(__thiscall*)(Native_CTaskSimpleNMJumpRollFromRoadVehicle*, uint32_t, uint32_t))(AddressSetter::Get(0x85CCB0, 0x7D81B0)))(this, time, time2);
	}
};

class Native_CTaskSimpleSidewaysDive : public Native_CTaskSimple
{
public:
	Native_CTaskSimpleSidewaysDive(bool bDirection)
	{
		((void(__thiscall*)(Native_CTaskSimpleSidewaysDive*, bool))(AddressSetter::Get(0xEDBC0, 0x302F30)))(this, bDirection);
	}
};

class Native_CTaskComplexClimbLadder : public Native_CTaskComplex
{
public:
	Native_CTaskComplexClimbLadder(Native_CObject* ladder, int32_t type, uint32_t unk0)
	{
		((void(__thiscall*)(Native_CTaskComplexClimbLadder*, Native_CObject*, int32_t, uint32_t))(AddressSetter::Get(0x8AD9D0, 0x8756F0)))(this, ladder, type, unk0);
	}
};

class Native_CTaskComplexInWater : public Native_CTaskComplex
{
public:
	Native_CTaskComplexInWater(uint32_t unk, uint32_t unk2, bool bUnk)
	{
		((void(__thiscall*)(Native_CTaskComplexInWater*, uint32_t, uint32_t, bool))(AddressSetter::Get(0x61EC00, 0x762950)))(this, unk, unk2, bUnk);
	}
};

class Native_CTaskComplexWander : public Native_CTaskComplex
{
public:
	uint8_t pad[0x80];											// 00-80
	float m_fUnk;												// 80-84 set to 0 upon initializing CTaskComplexWanderStandard

	Native_CTaskComplexWander(uint32_t moveState, float initialDir, bool bSensibly, float targetRadius, uint32_t unk1)
	{
		((void(__thiscall*)(Native_CTaskComplexWander*, uint32_t, float, bool, float, uint32_t))(AddressSetter::Get(0x618C70, 0x7FA900)))(this, moveState, initialDir, bSensibly, targetRadius, unk1);
	}
};

class Native_CTaskComplexWanderStandard : public Native_CTaskComplexWander
{
public:
	Native_CTaskComplexWanderStandard(uint32_t moveState, float initialDir, bool bSensibly, float targetRadius, uint32_t unk1) : Native_CTaskComplexWander(moveState, initialDir, bSensibly, targetRadius, unk1)
	{
		// this was probably inlined
		*(uint32_t*)this = AddressSetter::Get(0x969794, 0x995474); // set vftable
		this->m_fUnk = 0;
	}
};

class Native_CTaskComplexPlayerSettingsTask : public Native_CTaskComplex
{
public:
	uint8_t pad[0x14];										// 00-14
	uint32_t m_nUnk0;										// 14-18
	int32_t m_nUnkNeg1;										// 18-1C
	int32_t m_nUnkNeg1_2;									// 1C-20
	uint32_t m_nUnkFromPed;									// 20-24 pedPtr + 0xE80

	Native_CTaskComplexPlayerSettingsTask(uint32_t unkFromPed)
	{
		// this was inlined
		((void(__thiscall*)(Native_CTaskComplex*))(AddressSetter::Get(0x628AF0, 0x703040)))(this); // CTaskComplex::CTaskComplex
		m_nUnk0 = 0;
		m_nUnkNeg1 = -1;
		m_nUnkNeg1_2 = -1;
		m_nUnkFromPed = unkFromPed;
	}
};
//VALIDATE_OFFSET(Native_CTaskComplexPlayerSettingsTask, m_nUnk0, 0x14);
//VALIDATE_OFFSET(Native_CTaskComplexPlayerSettingsTask, m_nUnkNeg1, 0x18);
//VALIDATE_OFFSET(Native_CTaskComplexPlayerSettingsTask, m_nUnkNeg1_2, 0x1C);
//VALIDATE_OFFSET(Native_CTaskComplexPlayerSettingsTask, m_nUnkFromPed, 0x20);

namespace IVSDKDotNet {

	/// <summary>
	///	TASK_DIE does this but it's not required: CPed.SetHealth(0.0f, 0);
	/// </summary>
	public ref class CTaskComplexDie
	{
	public:
		static UIntPtr Create(uint32_t unk, uint32_t unk2, uint32_t unk3_44, uint32_t unk4_190, float fBlendDelta, float fAnimSpeed, uint32_t unk5_1);
	};

	public ref class CTaskComplexMobileMakeCall
	{
	public:
		static UIntPtr Create(String^ speechLine, bool bUnk1, bool bUnk2);
	};

	public ref class CTaskComplexNewGetInVehicle
	{
	public:
		static UIntPtr Create(CVehicle^ veh, eNewGetInVehicleType getInType, uint32_t unk27, int32_t unk, float fUnk);
	};

	public ref class CTaskComplexNM
	{
	public:
		static UIntPtr Create(uint32_t nUnk, uint32_t nUnk2, UIntPtr pSubTask, float fUnk);
	};

	public ref class CTaskComplexPlayerOnFoot
	{
	public:
		static UIntPtr Create();
	};

	public ref class CTaskSimpleNMHighFall
	{
	public:
		static UIntPtr Create(uint32_t nUnk, uint32_t nUnk2, uint32_t nUnk3, uint32_t nUnk4);
	};

	public ref class CTaskSimpleNMJumpRollFromRoadVehicle
	{
	public:
		static UIntPtr Create(uint32_t time, uint32_t time2);
	};

	public ref class CTaskSimpleSidewaysDive
	{
	public:
		static UIntPtr Create(bool bDirection);
	};

	public ref class CTaskComplexClimbLadder
	{
	public:
		static UIntPtr Create(CObject^ ladder, int32_t type, uint32_t unk0);
	};

	public ref class CTaskComplexInWater
	{
	public:
		static UIntPtr Create(uint32_t unk, uint32_t unk2, bool bUnk);
	};

	public ref class CTaskComplexWander
	{
	public:
		static UIntPtr Create(uint32_t moveState, float initialDir, bool bSensibly, float targetRadius, uint32_t unk1);
	};

	public ref class CTaskComplexWanderStandard
	{
	public:
		static UIntPtr Create(uint32_t moveState, float initialDir, bool bSensibly, float targetRadius, uint32_t unk1);
	};

	public ref class CTaskComplexPlayerSettingsTask
	{
	public:
		static UIntPtr Create(uint32_t unkFromPed);
	};

}