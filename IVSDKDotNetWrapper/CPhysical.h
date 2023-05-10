#pragma once

namespace rage { class phConstrainedCollider; }

class Native_CPhysical : public Native_CDynamicEntity
{
public:
	uint8_t pad7[0x8];													// 110-118
	struct
	{
		unsigned int flag1 : 6;
		unsigned int bBulletProof : 1;
		unsigned int bFireProof : 1;
		unsigned int bCollisionProof : 1;
		unsigned int bMeleeProof : 1;
		unsigned int bInvincible : 1;
		unsigned int bOnlyDamagedByPlayer : 1;
		unsigned int bExplosionProof : 1;
		unsigned int flag14 : 3;
		unsigned int bDestroyed : 1;
		unsigned int flag18 : 15;
	} m_nPhysicalFlags;													// 118-11C
	uint8_t pad9[0x4];													// 11C-120
	float m_fPercentSubmerged;											// 120-124
	uint8_t pad124[0x20];												// 124-144
	uint32_t m_nSubmergedState;											// 144-148 0 - not submerged, 1 - on water surface? (swimming for peds) 2 - below water surface?
	uint8_t pad148[0x74];												// 148-1BC
	Native_CEntity* m_pAttachedToEntity;								// 1BC-1C0
	Native_CVector m_vAttachOffset;										// 1C0-1CC
	uint8_t pad10[0x4];													// 1CC-1D0
	Native_CQuaternion m_qAttachOffset;									// 1D0-1E0
	uint8_t pad11[0x4];													// 1E0-1E4
	Native_CEntity* m_pLastDamageEntity;								// 1E4-1E8
	uint8_t pad12[0x4];													// 1E8-1EC
	int32_t m_nLastDamageWeapon;										// 1EC-1F0
	float m_fHealth;													// 1F0-1F4
	uint8_t pad13[0x4];													// 1F4-1F8
	Native_CEntity* m_pEntityIgnoredCollision;							// 1F8-1FC
	uint8_t pad14[0x14];												// 1FC-210

	rage::phConstrainedCollider* GetConstrainedCollider()
	{
		return ((rage::phConstrainedCollider * (__thiscall*)(Native_CPhysical*))(AddressSetter::Get(0x5E7080, 0x505110)))(this);
	}

	Native_CVector* GetVelocity(Native_CVector* v)
	{
		return ((Native_CVector * (__thiscall*)(Native_CPhysical*, Native_CVector*))(*(void***)this)[59])(this, v);
	}

	// static
	bool _ProcessWater()
	{
		return ((char(__thiscall*)(Native_CPhysical*))(AddressSetter::Get(0x64AF20, 0x4E82E0)))(this);
	}

	// vftable
	bool ProcessWater()
	{
		return ((char(__thiscall*)(Native_CPhysical*))(*(void***)this)[71])(this);
	}

	float GetHealth()
	{
		return ((float(__thiscall*)(Native_CPhysical*))(*(void***)this)[63])(this);
	}
};
VALIDATE_SIZE(Native_CPhysical, 0x210);
VALIDATE_OFFSET(Native_CPhysical, m_pLastDamageEntity, 0x1E4);
VALIDATE_OFFSET(Native_CPhysical, m_nLastDamageWeapon, 0x1EC);
VALIDATE_OFFSET(Native_CPhysical, m_fHealth, 0x1F0);
VALIDATE_OFFSET(Native_CPhysical, m_nPhysicalFlags, 0x118);
VALIDATE_OFFSET(Native_CPhysical, m_pAttachedToEntity, 0x1BC);
VALIDATE_OFFSET(Native_CPhysical, m_vAttachOffset, 0x1C0);
VALIDATE_OFFSET(Native_CPhysical, m_qAttachOffset, 0x1D0);
VALIDATE_OFFSET(Native_CPhysical, m_pEntityIgnoredCollision, 0x1F8);
VALIDATE_OFFSET(Native_CPhysical, m_fPercentSubmerged, 0x120);
VALIDATE_OFFSET(Native_CPhysical, m_nSubmergedState, 0x144);

namespace IVSDKDotNet {

	public ref class CPhysical : CDynamicEntity
	{
	public:
		ref class PhysicalFlags
		{
		public:
			PhysicalFlags(CPhysical^ parent);

			property bool BulletProof {
				public:
					bool get() { return m_cParent->PhysicalPointer->m_nPhysicalFlags.bBulletProof; }
					void set(bool value) { m_cParent->PhysicalPointer->m_nPhysicalFlags.bBulletProof = value; }
			}

			property bool FireProof {
				public:
					bool get() { return m_cParent->PhysicalPointer->m_nPhysicalFlags.bFireProof; }
					void set(bool value) { m_cParent->PhysicalPointer->m_nPhysicalFlags.bFireProof = value; }
			}

			property bool CollisionProof {
				public:
					bool get() { return m_cParent->PhysicalPointer->m_nPhysicalFlags.bCollisionProof; }
					void set(bool value) { m_cParent->PhysicalPointer->m_nPhysicalFlags.bCollisionProof = value; }
			}

			property bool MeleeProof {
				public:
					bool get() { return m_cParent->PhysicalPointer->m_nPhysicalFlags.bMeleeProof; }
					void set(bool value) { m_cParent->PhysicalPointer->m_nPhysicalFlags.bMeleeProof = value; }
			}

			property bool Invincible {
				public:
					bool get() { return m_cParent->PhysicalPointer->m_nPhysicalFlags.bInvincible; }
					void set(bool value) { m_cParent->PhysicalPointer->m_nPhysicalFlags.bInvincible = value; }
			}

			property bool OnlyDamagedByPlayer {
				public:
					bool get() { return m_cParent->PhysicalPointer->m_nPhysicalFlags.bOnlyDamagedByPlayer; }
					void set(bool value) { m_cParent->PhysicalPointer->m_nPhysicalFlags.bOnlyDamagedByPlayer = value; }
			}

			property bool ExplosionProof {
				public:
					bool get() { return m_cParent->PhysicalPointer->m_nPhysicalFlags.bExplosionProof; }
					void set(bool value) { m_cParent->PhysicalPointer->m_nPhysicalFlags.bExplosionProof = value; }
			}

			property bool Destroyed {
				public:
					bool get() { return m_cParent->PhysicalPointer->m_nPhysicalFlags.bDestroyed; }
					void set(bool value) { m_cParent->PhysicalPointer->m_nPhysicalFlags.bDestroyed = value; }
			}

		private:
			CPhysical^ m_cParent;
		};

	public:
		CPhysical(Native_CPhysical* native);

		property PhysicalFlags^ ThePhysicalFlags {
			public: PhysicalFlags^ get() { return m_cPhysicalFlags; }
		}

		property float PercentSubmerged {
			public:
				float	get()				{ return PhysicalPointer->m_fPercentSubmerged; }
				void	set(float value)	{ PhysicalPointer->m_fPercentSubmerged = value; }
		}

		/// <summary>
		/// 0 - not submerged, 1 - on water surface? (swimming for peds) 2 - below water surface?
		/// </summary>
		property uint32_t SubmergedState {
			public:
				uint32_t	get()				{ return PhysicalPointer->m_nSubmergedState; }
				void		set(uint32_t value) { PhysicalPointer->m_nSubmergedState = value; }
		}

		property CEntity^ AttachedToEntity {
			public:
				CEntity^ get()
				{
					Native_CEntity* ptr = PhysicalPointer->m_pAttachedToEntity;

					if (ptr)
						return gcnew CEntity(ptr);

					return nullptr;
				}
				void set(CEntity^ value)
				{
					if (value)
					{
						PhysicalPointer->m_pAttachedToEntity = value->EntityPointer;
					}
				}
		}

		property Vector3 AttachPositionOffset {
			public:
				Vector3 get()				{ return Vector3(PhysicalPointer->m_vAttachOffset.x, PhysicalPointer->m_vAttachOffset.y, PhysicalPointer->m_vAttachOffset.z); }
				void	set(Vector3 value)	{ PhysicalPointer->m_vAttachOffset = Native_CVector(value.X, value.Y, value.Z); }
		}

		property Quaternion AttachRotationOffset {
			public:
				Quaternion	get()					{ return Quaternion(PhysicalPointer->m_qAttachOffset.x, PhysicalPointer->m_qAttachOffset.y, PhysicalPointer->m_qAttachOffset.z, m_cNativePhysical->m_qAttachOffset.w); }
				void		set(Quaternion value)	{ PhysicalPointer->m_qAttachOffset = Native_CQuaternion(value.X, value.Y, value.Z, value.W); }
		}

		property CEntity^ LastDamageEntity {
			public:
				CEntity^ get()
				{
					Native_CEntity* ptr = PhysicalPointer->m_pLastDamageEntity;

					if (ptr)
						return gcnew CEntity(ptr);

					return nullptr;
				}
				void set(CEntity^ value)
				{
					if (value)
					{
						PhysicalPointer->m_pLastDamageEntity = value->EntityPointer;
					}
				}
		}

		property int32_t LastDamageWeapon {
			public:
				int32_t	get()				{ return PhysicalPointer->m_nLastDamageWeapon; }
				void	set(int32_t value)	{ PhysicalPointer->m_nLastDamageWeapon = value; }
		}

		property float Health {
			public:
				float	get()				{ return PhysicalPointer->m_fHealth; }
				void	set(float value)	{ PhysicalPointer->m_fHealth = value; }
		}

		property CEntity^ EntityIgnoredCollision {
			public:
				CEntity^ get()
				{
					Native_CEntity* ptr = PhysicalPointer->m_pEntityIgnoredCollision;

					if (ptr)
						return gcnew CEntity(ptr);

					return nullptr;
				}
				void set(CEntity^ value)
				{
					if (value)
					{
						PhysicalPointer->m_pEntityIgnoredCollision = value->EntityPointer;
					}
				}
		}

		property Native_CPhysical* PhysicalPointer {
			public:
				Native_CPhysical*	get() { return m_cNativePhysical; }
				void				set(Native_CPhysical* value) { m_cNativePhysical = value; }
		}

		bool ProcessWater();
		float GetHealth();

	private:
		Native_CPhysical* m_cNativePhysical;
		PhysicalFlags^ m_cPhysicalFlags;
	};

}