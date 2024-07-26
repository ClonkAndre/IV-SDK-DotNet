#pragma once

namespace IVSDKDotNet
{
	public ref class IVPhConstrainedCollider
	{
	public:
		property IVPhSleep^ Sleep
		{
		public:
			IVPhSleep^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeConstrainedCollider, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativeConstrainedCollider->m_pSleep, nullptr);
				return gcnew IVPhSleep(NativeConstrainedCollider->m_pSleep);
			}
			void set(IVPhSleep^ value)
			{
				NULLPTR_CHECK(NativeConstrainedCollider);
				NULLPTR_CHECK(value);
				NativeConstrainedCollider->m_pSleep = value->NativeSleep;
			}
		}
		property Vector3 Pos2
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeConstrainedCollider, Vector3::Zero);
				return CVectorPadToVector3(NativeConstrainedCollider->m_vPos2);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeConstrainedCollider);
				NativeConstrainedCollider->m_vPos2 = Vector3ToCVectorPad(value);
			}
		}
		property float UnkScale
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeConstrainedCollider, 0.0F);
				return NativeConstrainedCollider->m_fUnkScale;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeConstrainedCollider);
				NativeConstrainedCollider->m_fUnkScale = value;
			}
		}
		property float UnkScale2
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeConstrainedCollider, 0.0F);
				return NativeConstrainedCollider->m_fUnkScale2;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeConstrainedCollider);
				NativeConstrainedCollider->m_fUnkScale2 = value;
			}
		}
		property float MaxSpeed
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeConstrainedCollider, 0.0F);
				return NativeConstrainedCollider->m_fMaxSpeed;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeConstrainedCollider);
				NativeConstrainedCollider->m_fMaxSpeed = value;
			}
		}
		property float MaxTurnSpeed
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeConstrainedCollider, 0.0F);
				return NativeConstrainedCollider->m_fMaxTurnSpeed;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeConstrainedCollider);
				NativeConstrainedCollider->m_fMaxTurnSpeed = value;
			}
		}
		property Vector3 Unk1
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeConstrainedCollider, Vector3::Zero);
				return CVectorPadToVector3(NativeConstrainedCollider->m_vUnk1);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeConstrainedCollider);
				NativeConstrainedCollider->m_vUnk1 = Vector3ToCVectorPad(value);
			}
		}
		property Vector3 Unk2
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeConstrainedCollider, Vector3::Zero);
				return CVectorPadToVector3(NativeConstrainedCollider->m_vUnk2);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeConstrainedCollider);
				NativeConstrainedCollider->m_vUnk2 = Vector3ToCVectorPad(value);
			}
		}
		property Vector3 Unk3
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeConstrainedCollider, Vector3::Zero);
				return CVectorPadToVector3(NativeConstrainedCollider->m_vUnk3);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeConstrainedCollider);
				NativeConstrainedCollider->m_vUnk3 = Vector3ToCVectorPad(value);
			}
		}
		property Vector3 Pos
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeConstrainedCollider, Vector3::Zero);
				return CVectorPadToVector3(NativeConstrainedCollider->m_vPos);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeConstrainedCollider);
				NativeConstrainedCollider->m_vPos = Vector3ToCVectorPad(value);
			}
		}
		property Vector3 PedVelocity
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeConstrainedCollider, Vector3::Zero);
				return CVectorPadToVector3(NativeConstrainedCollider->m_vPedVelocity);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeConstrainedCollider);
				NativeConstrainedCollider->m_vPedVelocity = Vector3ToCVectorPad(value);
			}
		}
		property Vector3 Unk4
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeConstrainedCollider, Vector3::Zero);
				return CVectorPadToVector3(NativeConstrainedCollider->m_vUnk4);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeConstrainedCollider);
				NativeConstrainedCollider->m_vUnk4 = Vector3ToCVectorPad(value);
			}
		}
		property IVUnkColliderParams UnkParameters
		{
		public:
			IVUnkColliderParams get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeConstrainedCollider, IVUnkColliderParams());
				NULLPTR_CHECK_WITH_RETURN(NativeConstrainedCollider->m_pUnkParameters, IVUnkColliderParams());
				return IVUnkColliderParams(NativeConstrainedCollider->m_pUnkParameters);
			}
			void set(IVUnkColliderParams value)
			{
				NULLPTR_CHECK(NativeConstrainedCollider);
				NativeConstrainedCollider->m_pUnkParameters = value.NativeColliderParams;
			}
		}

	public:
		static IVPhConstrainedCollider^ FromUIntPtr(UIntPtr ptr);
		UIntPtr GetUIntPtr();

		void SetVelocity(Vector3 v);

	internal:
		IVPhConstrainedCollider(rage::phConstrainedCollider* nativePtr);

	internal:
		rage::phConstrainedCollider* NativeConstrainedCollider;
	};
}