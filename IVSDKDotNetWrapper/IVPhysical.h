#pragma once

namespace IVSDKDotNet
{
	public ref class IVPhysicalFlags
	{
	public:
		property bool BulletProof
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhysical, false);
				return NativePhysical->m_nPhysicalFlags.bBulletProof;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePhysical);
				NativePhysical->m_nPhysicalFlags.bBulletProof = value;
			}
		}
		property bool FireProof
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhysical, false);
				return NativePhysical->m_nPhysicalFlags.bFireProof;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePhysical);
				NativePhysical->m_nPhysicalFlags.bFireProof = value;
			}
		}
		property bool CollisionProof
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhysical, false);
				return NativePhysical->m_nPhysicalFlags.bCollisionProof;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePhysical);
				NativePhysical->m_nPhysicalFlags.bCollisionProof = value;
			}
		}
		property bool MeleeProof
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhysical, false);
				return NativePhysical->m_nPhysicalFlags.bMeleeProof;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePhysical);
				NativePhysical->m_nPhysicalFlags.bMeleeProof = value;
			}
		}
		property bool Invincible
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhysical, false);
				return NativePhysical->m_nPhysicalFlags.bInvincible;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePhysical);
				NativePhysical->m_nPhysicalFlags.bInvincible = value;
			}
		}
		property bool OnlyDamagedByPlayer
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhysical, false);
				return NativePhysical->m_nPhysicalFlags.bOnlyDamagedByPlayer;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePhysical);
				NativePhysical->m_nPhysicalFlags.bOnlyDamagedByPlayer = value;
			}
		}
		property bool ExplosionProof
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhysical, false);
				return NativePhysical->m_nPhysicalFlags.bExplosionProof;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePhysical);
				NativePhysical->m_nPhysicalFlags.bExplosionProof = value;
			}
		}
		property bool Destroyed
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhysical, false);
				return NativePhysical->m_nPhysicalFlags.bDestroyed;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePhysical);
				NativePhysical->m_nPhysicalFlags.bDestroyed = value;
			}
		}

	internal:
		IVPhysicalFlags(CPhysical* nativePtr);

	internal:
		CPhysical* NativePhysical;
	};

	public ref class IVPhysical : IVDynamicEntity
	{
	public:
		property IVPhysicalFlags^ PhysicalFlags
		{
		public:
			IVPhysicalFlags^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhysical, nullptr);
				return gcnew IVPhysicalFlags(NativePhysical);
			}
		}
		property float PercentSubmerged
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhysical, 0.0F);
				return NativePhysical->m_fPercentSubmerged;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativePhysical);
				NativePhysical->m_fPercentSubmerged = value;
			}
		}
		property uint32_t SubmergedState
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhysical, 0);
				return NativePhysical->m_nSubmergedState;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePhysical);
				NativePhysical->m_nSubmergedState = value;
			}
		}
		property IVEntity^ AttachedToEntity
		{
		public:
			IVEntity^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhysical, nullptr);
				return gcnew IVEntity(NativePhysical->m_pAttachedToEntity);
			}
			void set(IVEntity^ value)
			{
				NULLPTR_CHECK(NativePhysical);
				NULLPTR_CHECK(value);
				NativePhysical->m_pAttachedToEntity = value->NativeEntity;
			}
		}
		property Vector3 AttachOffsetVec3
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhysical, Vector3::Zero);
				CVector v = NativePhysical->m_vAttachOffset;
				return Vector3(v.x, v.y, v.z);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativePhysical);

				CVector v;
				v.x = value.X;
				v.y = value.Y;
				v.z = value.Z;

				NativePhysical->m_vAttachOffset = v;
			}
		}
		property Quaternion AttachOffsetQuat
		{
		public:
			Quaternion get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhysical, Quaternion());
				CQuaternion v = NativePhysical->m_qAttachOffset;
				return Quaternion(v.x, v.y, v.z, v.w);
			}
			void set(Quaternion value)
			{
				NULLPTR_CHECK(NativePhysical);

				CQuaternion v;
				v.x = value.X;
				v.y = value.Y;
				v.z = value.Z;
				v.w = value.W;

				NativePhysical->m_qAttachOffset = v;
			}
		}
		property IVEntity^ LastDamageEntity
		{
		public:
			IVEntity^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhysical, nullptr);
				return gcnew IVEntity(NativePhysical->m_pLastDamageEntity);
			}
			void set(IVEntity^ value)
			{
				NULLPTR_CHECK(NativePhysical);
				NULLPTR_CHECK(value);
				NativePhysical->m_pLastDamageEntity = value->NativeEntity;
			}
		}
		property int32_t LastDamageWeapon
		{
		public:
			int32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhysical, 0);
				return NativePhysical->m_nLastDamageWeapon;
			}
			void set(int32_t value)
			{
				NULLPTR_CHECK(NativePhysical);
				NativePhysical->m_nLastDamageWeapon = value;
			}
		}
		property float Health
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhysical, 0.0F);
				return NativePhysical->m_fHealth;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativePhysical);
				NativePhysical->m_fHealth = value;
			}
		}
		property IVEntity^ EntityIgnoredCollision
		{
		public:
			IVEntity^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhysical, nullptr);
				return gcnew IVEntity(NativePhysical->m_pEntityIgnoredCollision);
			}
			void set(IVEntity^ value)
			{
				NULLPTR_CHECK(NativePhysical);
				NULLPTR_CHECK(value);
				NativePhysical->m_pEntityIgnoredCollision = value->NativeEntity;
			}
		}

	public:
		/// <summary>
		/// Use with: IVPhConstrainedCollider.FromUIntPtr(...);
		/// </summary>
		/// <returns></returns>
		UIntPtr GetConstrainedCollider();
		Vector3 GetVelocity(Vector3 v);
		bool _ProcessWater();
		bool ProcessWater();
		float GetHealth();

	internal:
		IVPhysical(CPhysical* nativePtr);

	internal:
		CPhysical* NativePhysical;
	};
}