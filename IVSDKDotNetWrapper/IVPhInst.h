#pragma once

namespace IVSDKDotNet
{
	public ref class IVPhInst
	{
	public:
		property IVPhArchetypeGta^ Archetype
		{
		public:
			IVPhArchetypeGta^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhInst, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativePhInst->m_pArchetype, nullptr);
				return gcnew IVPhArchetypeGta(NativePhInst->m_pArchetype);
			}
			void set(IVPhArchetypeGta^ value)
			{
				NULLPTR_CHECK(NativePhInst);
				NULLPTR_CHECK(value);
				NativePhInst->m_pArchetype = value->NativePhArchetypeGta;
			}
		}
		property int16_t RigidBodyIndex
		{
		public:
			int16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhInst, 0);
				return NativePhInst->m_nRigidBodyIndex;
			}
			void set(int16_t value)
			{
				NULLPTR_CHECK(NativePhInst);
				NativePhInst->m_nRigidBodyIndex = value;
			}
		}
		property IVEntity^ Entity
		{
		public:
			IVEntity^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhInst, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativePhInst->m_pEntity, nullptr);
				return gcnew IVEntity(NativePhInst->m_pEntity);
			}
			void set(IVEntity^ value)
			{
				NULLPTR_CHECK(NativePhInst);
				NULLPTR_CHECK(value);
				NativePhInst->m_pEntity = value->NativeEntity;
			}
		}
		property Vector3 Pos
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePhInst, Vector3::Zero);
				return CVectorToVector3(NativePhInst->m_vPos);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativePhInst);
				NativePhInst->m_vPos = Vector3ToCVector(value);
			}
		}

	internal:
		IVPhInst(rage::phInst* nativePtr);

	internal:
		rage::phInst* NativePhInst;
	};
}