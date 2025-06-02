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

	//public ref class IVEntityFlags2
	//{
	//public:
	//	property bool _f0
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._f0;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._f0 = value;
	//		}
	//	}
	//	property bool _f1
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._f1;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._f1 = value;
	//		}
	//	}
	//	property bool _f2
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._f2;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._f2 = value;
	//		}
	//	}
	//	property bool _f3
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._f3;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._f3 = value;
	//		}
	//	}
	//	property bool _f4
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._f4;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._f4 = value;
	//		}
	//	}
	//	property bool _f5
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._f5;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._f5 = value;
	//		}
	//	}
	//	property bool _f6
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._f6;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._f6 = value;
	//		}
	//	}
	//	property bool _f7
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._f7;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._f7 = value;
	//		}
	//	}
	//	property bool _f8
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._f8;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._f8 = value;
	//		}
	//	}
	//	property bool _f9
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._f9;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._f9 = value;
	//		}
	//	}
	//	property bool _fa
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._fa;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._fa = value;
	//		}
	//	}
	//	property bool _fb
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._fb;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._fb = value;
	//		}
	//	}
	//	property bool _fc
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._fc;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._fc = value;
	//		}
	//	}
	//	property bool _fd
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._fd;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._fd = value;
	//		}
	//	}
	//	property bool _fe
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._fe;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._fe = value;
	//		}
	//	}
	//	property bool _ff
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._ff;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._ff = value;
	//		}
	//	}
	//	property bool _f10
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._f10;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._f10 = value;
	//		}
	//	}
	//	property bool _f11
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._f11;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._f11 = value;
	//		}
	//	}
	//	property bool _f12
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._f12;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._f12 = value;
	//		}
	//	}
	//	property bool _f13
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._f13;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._f13 = value;
	//		}
	//	}
	//	property bool _f14
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._f14;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._f14 = value;
	//		}
	//	}
	//	property bool _f15
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._f15;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._f15 = value;
	//		}
	//	}
	//	property bool _f16
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._f16;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._f16 = value;
	//		}
	//	}
	//	property bool _f17
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._f17;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._f17 = value;
	//		}
	//	}
	//	property bool _f18
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._f18;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._f18 = value;
	//		}
	//	}
	//	property bool _f19
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._f19;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._f19 = value;
	//		}
	//	}
	//	property bool _f1a
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._f1a;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._f1a = value;
	//		}
	//	}
	//	property bool _f1b
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._f1b;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._f1b = value;
	//		}
	//	}
	//	property bool _f1c
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._f1c;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._f1c = value;
	//		}
	//	}
	//	property bool _f1d
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._f1d;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._f1d = value;
	//		}
	//	}
	//	property bool _f1e
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._f1e;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._f1e = value;
	//		}
	//	}
	//	property bool _f1f
	//	{
	//	public:
	//		bool get()
	//		{
	//			NULLPTR_CHECK_WITH_RETURN(NativeEntity, false);
	//			return NativeEntity->m_nEntityFlags2._f1f;
	//		}
	//		void set(bool value)
	//		{
	//			NULLPTR_CHECK(NativeEntity);
	//			NativeEntity->m_nEntityFlags2._f1f = value;
	//		}
	//	}

	//internal:
	//	IVEntityFlags2(CEntity* nativePtr)
	//	{
	//		NativeEntity = nativePtr;
	//	}

	//internal:
	//	CEntity* NativeEntity;
	//};

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
				NULLPTR_CHECK_WITH_RETURN(NativeEntity, IVMatrix::Zero);
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
		/// Use with: IVPhInstGta.FromUIntPtr(...);
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