#pragma once

class Native_CEntity;
class CNetworkObject;
class phInstGta;
class CPhysical;
namespace rage { class rmcDrawable; }

struct Native_tObjectDrawable
{
	rage::rmcDrawable* m_pDrawable;										// 000-004
	uint32_t* m_pShaderEffect;											// 004-008 CCustomShaderEffect pointer
	Native_CEntity* m_pEntityPtr;										// 008-00C
};

class Native_CEntity
{
public:
	uint8_t pad[0x10];													// 000-010
	Native_CSimpleTransform m_placement;								// 010-020
	Native_CMatrix* m_pMatrix;											// 020-024
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
	Native_tObjectDrawable* m_pDrawablePtr;								// 034-038
	phInstGta* m_pInstGta;												// 038-03C cars have fraginst, peds have phinst
	uint8_t pad3[0x10];													// 03C-04C
	uint32_t m_unkDeletePtr;											// 04C-050
	float m_fDrawDistance;												// 050-054
	uint8_t pad4[0xF];													// 054-063
	uint8_t m_nAlpha;													// 063-064
	uint8_t pad5[0x8];													// 064-06C
	CNetworkObject* m_pNetworkObject;									// 06C-070

	void Teleport(Native_CMatrix* mat, bool bDontUpdatePhysicsMatrix, bool bImmediately)
	{
		((void(__thiscall*)(Native_CEntity*, Native_CMatrix*, bool, bool))(*(void***)this)[1])(this, mat, bDontUpdatePhysicsMatrix, bImmediately);
	}

	void Teleport(Native_CVector* v, bool bDontUpdatePhysicsMatrix, bool bImmediately)
	{
		((void(__thiscall*)(Native_CEntity*, Native_CVector*, bool, bool))(*(void***)this)[2])(this, v, bDontUpdatePhysicsMatrix, bImmediately);
	}

	void PreRender(int nUnk, int nUnk2, char alpha, int nUnkNeg1)
	{
		((void(__thiscall*)(Native_CEntity*, int, int, char, int))(*(void***)this)[35])(this, nUnk, nUnk2, alpha, nUnkNeg1);
	}
};
VALIDATE_SIZE(Native_CEntity, 0x70);
VALIDATE_OFFSET(Native_CEntity, m_fDrawDistance, 0x50);
VALIDATE_OFFSET(Native_CEntity, m_nEntityFlags, 0x24);
VALIDATE_OFFSET(Native_CEntity, m_pMatrix, 0x20);
VALIDATE_OFFSET(Native_CEntity, m_pInstGta, 0x38);

namespace IVSDKDotNet {

	public ref class CEntity
	{
	public:
		CEntity(Native_CEntity* entity);

		void Teleport(GTAMatrix mat, bool bDontUpdatePhysicsMatrix, bool bImmediately);
		void Teleport(Vector3 v, bool bDontUpdatePhysicsMatrix, bool bImmediately);

		void PreRender(int nUnk, int nUnk2, char alpha, int nUnkNeg1);

		property CSimpleTransform Placement {
			public:
				CSimpleTransform	get()						{ return CSimpleTransform(m_cEntity->m_placement); }
				void				set(CSimpleTransform value) { m_cEntity->m_placement = Native_CSimpleTransform(value.Position.X, value.Position.Y, value.Position.Z, value.Heading); }
		}

		property GTAMatrix Matrix {
			public:
				GTAMatrix get() { return GTAMatrix(m_cEntity->m_pMatrix); }
				void set(GTAMatrix value) {
					Native_CMatrix* m = new Native_CMatrix(value.right, value.up, value.at, value.pos);
					m_cEntity->m_pMatrix = m;
					delete m;
				}
		}

		/// <summary>
		/// 0x80 - Cast shadows.
		/// </summary>
		property uint32_t EntityFlags2 {
			public:
				uint32_t	get()				{ return m_cEntity->m_nEntityFlags2; }
				void		set(uint32_t value) { m_cEntity->m_nEntityFlags2 = value; }
		}

		property int16_t ModelIndex {
			public:
				int16_t	get()				{ return m_cEntity->m_nModelIndex; }
				void	set(int16_t value)	{ m_cEntity->m_nModelIndex = value; }
		}

		property uint32_t DeletePtr {
			public:
				uint32_t	get()				{ return m_cEntity->m_unkDeletePtr; }
				void		set(uint32_t value) { m_cEntity->m_unkDeletePtr = value; }
		}

		property float DrawDistance {
			public:
				float	get()				{ return m_cEntity->m_fDrawDistance; }
				void	set(float value)	{ m_cEntity->m_fDrawDistance = value; }
		}

		property uint8_t Alpha {
			public:
				uint8_t	get()				{ return m_cEntity->m_nAlpha; }
				void	set(uint8_t value)	{ m_cEntity->m_nAlpha = value; }
		}

	private:
		Native_CEntity* m_cEntity;
	};

}