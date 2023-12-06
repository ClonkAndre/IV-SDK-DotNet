#pragma once

namespace IVSDKDotNet
{
	public value struct IVObjectDrawable
	{
	public:
		property UIntPtr ShaderEffect
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeObjDrawable, UIntPtr::Zero);
				return UIntPtr(NativeObjDrawable->m_pShaderEffect);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativeObjDrawable);
				NativeObjDrawable->m_pShaderEffect = (uint32_t*)value.ToPointer();
			}
		}
		property UIntPtr EntityPtr
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeObjDrawable, UIntPtr::Zero);
				return UIntPtr(NativeObjDrawable->m_pEntityPtr);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativeObjDrawable);
				UINTPTR_ZERO_CHECK(value);
				NativeObjDrawable->m_pEntityPtr = (CEntity*)value.ToPointer();
			}
		}

	internal:
		IVObjectDrawable(tObjectDrawable* nativePtr);

	internal:
		tObjectDrawable* NativeObjDrawable;
	};

	public ref class IVEntity
	{
	public:
		property Vector4 Placement
		{
		public:
			Vector4 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeEntity, Vector4::Zero);
				CSimpleTransform v = NativeEntity->m_placement;
				return Vector4(v.m_vPosition.x, v.m_vPosition.y, v.m_vPosition.z, v.m_fHeading);
			}
			void set(Vector4 value)
			{
				NULLPTR_CHECK(NativeEntity);

				CSimpleTransform v;
				v.m_vPosition.x = value.X;
				v.m_vPosition.y = value.Y;
				v.m_vPosition.z = value.Z;
				v.m_fHeading = value.W;
				NativeEntity->m_placement = v;
			}
		}
		property IVMatrix Matrix
		{
		public:
			IVMatrix get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeEntity, IVMatrix::Empty());
				return IVMatrix(NativeEntity->m_pMatrix);
			}
			void set(IVMatrix value)
			{
				NULLPTR_CHECK(NativeEntity);
				NativeEntity->m_pMatrix = &value.ToCMatrix();
			}
		}
		property uint32_t EntityFlags2
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeEntity, 0);
				return NativeEntity->m_nEntityFlags2;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeEntity);
				NativeEntity->m_nEntityFlags2 = value;
			}
		}
		property int16_t ModelIndex
		{
		public:
			int16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeEntity, 0);
				return NativeEntity->m_nModelIndex;
			}
			void set(int16_t value)
			{
				NULLPTR_CHECK(NativeEntity);
				NativeEntity->m_nModelIndex = value;
			}
		}
		property IVObjectDrawable DrawablePtr
		{
		public:
			IVObjectDrawable get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeEntity, IVObjectDrawable());
				return IVObjectDrawable(NativeEntity->m_pDrawablePtr);
			}
			void set(IVObjectDrawable value)
			{
				NULLPTR_CHECK(NativeEntity);
				NativeEntity->m_pDrawablePtr = value.NativeObjDrawable;
			}
		}
		/// <summary>
		/// Use with: IVPhInstGta.FromPointer(...);
		/// </summary>
		property UIntPtr InstGta
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeEntity, UIntPtr::Zero);
				NULLPTR_CHECK_WITH_RETURN(NativeEntity->m_pInstGta, UIntPtr::Zero);
				return UIntPtr(NativeEntity->m_pInstGta);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativeEntity);
				UINTPTR_ZERO_CHECK(value);
				NativeEntity->m_pInstGta = (phInstGta*)value.ToPointer();
			}
		}
		property UIntPtr DeletePtr
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeEntity, UIntPtr::Zero);
				return UIntPtr(NativeEntity->m_unkDeletePtr);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativeEntity);
				NativeEntity->m_unkDeletePtr = (uint32_t)value.ToPointer();
			}
		}
		property float DrawDistance
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeEntity, 0.0F);
				return NativeEntity->m_fDrawDistance;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeEntity);
				NativeEntity->m_fDrawDistance = value;
			}
		}
		property uint8_t Alpha
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeEntity, 0);
				return NativeEntity->m_nAlpha;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeEntity);
				NativeEntity->m_nAlpha = value;
			}
		}
		property UIntPtr NetworkObject
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeEntity, UIntPtr::Zero);
				return UIntPtr(NativeEntity->m_pNetworkObject);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativeEntity);
				NativeEntity->m_pNetworkObject = (CNetworkObject*)value.ToPointer();
			}
		}

	public:
		static IVEntity^ FromUIntPtr(UIntPtr ptr);
		UIntPtr GetUIntPtr();

		void Teleport(IVMatrix mat, bool bDontUpdatePhysicsMatrix, bool bImmediately);
		void Teleport(Vector3 v, bool bDontUpdatePhysicsMatrix, bool bImmediately);

		void PreRender(int nUnk, int nUnk2, char alpha, int nUnkNeg1);

	internal:
		IVEntity(CEntity* nativePtr);

	internal:
		CEntity* NativeEntity;
	};
}