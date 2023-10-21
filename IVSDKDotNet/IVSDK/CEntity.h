class CNetworkObject;
class phInstGta;
class CPhysical;
namespace rage { class rmcDrawable; }

struct tObjectDrawable
{
	rage::rmcDrawable* m_pDrawable;											// 000-004
	uint32_t* m_pShaderEffect;											// 004-008 CCustomShaderEffect pointer
	CEntity* m_pEntityPtr;												// 008-00C
};

class CEntity
{
public:
	uint8_t pad[0x10];													// 000-010
	CSimpleTransform m_placement;										// 010-020
	CMatrix* m_pMatrix;													// 020-024
	struct
	{
		unsigned int pad1 : 3;
		unsigned int bIsStatic : 1; // & 8
		unsigned int pad2 : 1;
		unsigned int bIsVisible : 1; // >> 5 & 1 - visible
		unsigned int pad3 : 26;
	} m_nEntityFlags;													// 024-028 >> 5 & 1 - visible
	uint32_t m_nEntityFlags2;											// 028-02C 0x80 - cast shadows
	uint8_t pad1[0x2];													// 02C-02E
	int16_t m_nModelIndex;												// 02E-030
	uint8_t pad2[0x4];													// 030-034
	tObjectDrawable* m_pDrawablePtr;									// 034-038
	phInstGta* m_pInstGta;												// 038-03C cars have fraginst, peds have phinst
	uint8_t pad3[0x10];													// 03C-04C
	uint32_t m_unkDeletePtr;											// 04C-050
	float m_fDrawDistance;												// 050-054
	uint8_t pad4[0xF];													// 054-063
	uint8_t m_nAlpha;													// 063-064
	uint8_t pad5[0x8];													// 064-06C
	CNetworkObject* m_pNetworkObject;									// 06C-070

	void Teleport(CMatrix* mat, bool bDontUpdatePhysicsMatrix, bool bImmediately)
	{
		((void(__thiscall*)(CEntity*, CMatrix*, bool, bool))(*(void***)this)[1])(this, mat, bDontUpdatePhysicsMatrix, bImmediately);
	}

	void Teleport(CVector* v, bool bDontUpdatePhysicsMatrix, bool bImmediately)
	{
		((void(__thiscall*)(CEntity*, CVector*, bool, bool))(*(void***)this)[2])(this, v, bDontUpdatePhysicsMatrix, bImmediately);
	}

	void PreRender(int nUnk, int nUnk2, char alpha, int nUnkNeg1)
	{
		((void(__thiscall*)(CEntity*, int, int, char, int))(*(void***)this)[35])(this, nUnk, nUnk2, alpha, nUnkNeg1);
	}
};

VALIDATE_SIZE(CEntity, 0x70);
VALIDATE_OFFSET(CEntity, m_fDrawDistance, 0x50);
VALIDATE_OFFSET(CEntity, m_nEntityFlags, 0x24);
VALIDATE_OFFSET(CEntity, m_pMatrix, 0x20);
VALIDATE_OFFSET(CEntity, m_pInstGta, 0x38);