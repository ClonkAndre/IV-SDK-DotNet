#pragma once

namespace IVSDKDotNet
{
	public ref class IVBaseModelInfo
	{
	public:
		/// <summary>
		/// Use with: IVPhArchetypeGta.FromPointer(...);
		/// </summary>
		property UIntPtr Archetype
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeModelInfo, UIntPtr::Zero);
				NULLPTR_CHECK_WITH_RETURN(NativeModelInfo->m_pArchetype, UIntPtr::Zero);
				return UIntPtr(NativeModelInfo->m_pArchetype);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativeModelInfo);
				UINTPTR_ZERO_CHECK(value);

				NativeModelInfo->m_pArchetype = (phArchetypeGta*)value.ToPointer();
			}
		}
		/// <summary>
		/// Use with: IVGtaFragType.FromPointer(...);
		/// </summary>
		property UIntPtr FragType
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeModelInfo, UIntPtr::Zero);
				NULLPTR_CHECK_WITH_RETURN(NativeModelInfo->m_pFragType, UIntPtr::Zero);
				return UIntPtr(NativeModelInfo->m_pFragType);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativeModelInfo);
				UINTPTR_ZERO_CHECK(value);

				NativeModelInfo->m_pFragType = (gtaFragType*)value.ToPointer();
			}
		}
		property UIntPtr DrawableStruct
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeModelInfo, UIntPtr::Zero);
				NULLPTR_CHECK_WITH_RETURN(NativeModelInfo->m_pDrawableStruct, UIntPtr::Zero);
				return UIntPtr(NativeModelInfo->m_pDrawableStruct);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativeModelInfo);
				UINTPTR_ZERO_CHECK(value);

				NativeModelInfo->m_pDrawableStruct = (tDrawableStruct*)value.ToPointer();
			}
		}

		property Vector3 MinBounds
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeModelInfo, Vector3::Zero);
				CVector v = NativeModelInfo->m_vMinBounds;
				return Vector3(v.x, v.y, v.z);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeModelInfo);

				CVector v;
				v.x = value.X;
				v.y = value.Y;
				v.z = value.Z;
				NativeModelInfo->m_vMinBounds = v;
			}
		}
		property float DrawDistance
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeModelInfo, 0.0F);
				return NativeModelInfo->m_fDrawDistance;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeModelInfo);
				NativeModelInfo->m_fDrawDistance = value;
			}
		}
		property Vector3 MaxBounds
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeModelInfo, Vector3::Zero);
				CVector v = NativeModelInfo->m_vMaxBounds;
				return Vector3(v.x, v.y, v.z);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeModelInfo);

				CVector v;
				v.x = value.X;
				v.y = value.Y;
				v.z = value.Z;
				NativeModelInfo->m_vMaxBounds = v;
			}
		}
		property uint32_t Hash
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeModelInfo, 0);
				return NativeModelInfo->m_nHash;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeModelInfo);
				NativeModelInfo->m_nHash = value;
			}
		}
		property uint32_t IDEFlags
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeModelInfo, 0);
				return NativeModelInfo->m_nIDEFlags;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeModelInfo);
				NativeModelInfo->m_nIDEFlags = value;
			}
		}
		property uint32_t ReferencesThisFrame
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeModelInfo, 0);
				return NativeModelInfo->m_nReferencesThisFrame;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeModelInfo);
				NativeModelInfo->m_nReferencesThisFrame = value;
			}
		}
		property int16_t TexDictionary
		{
		public:
			int16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeModelInfo, 0);
				return NativeModelInfo->m_nTexDictionary;
			}
			void set(int16_t value)
			{
				NULLPTR_CHECK(NativeModelInfo);
				NativeModelInfo->m_nTexDictionary = value;
			}
		}
		property int8_t AnimIndex
		{
		public:
			int8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeModelInfo, 0);
				return NativeModelInfo->m_nAnimIndex;
			}
			void set(int8_t value)
			{
				NULLPTR_CHECK(NativeModelInfo);
				NativeModelInfo->m_nAnimIndex = value;
			}
		}

	public:
		uint8_t GetModelType();
		void SetAnimGroup(String^ group);
		void SetTexDictionary(String^ txd);

	internal:
		IVBaseModelInfo(CBaseModelInfo* nativePtr);

	internal:
		CBaseModelInfo* NativeModelInfo;
	};
}