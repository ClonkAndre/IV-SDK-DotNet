#pragma once

namespace IVSDKDotNet
{
	public value struct IVLineOfSightResults
	{
	public:
		/// <summary>
		/// IVPhInstGta pointer of hit entity.
		/// Use with: IVPhInstGta.FromPointer(...);
		/// </summary>
		property UIntPtr Inst
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeLineOfSightResults, UIntPtr::Zero);
				NULLPTR_CHECK_WITH_RETURN(NativeLineOfSightResults->m_pInst, UIntPtr::Zero);
				return UIntPtr(NativeLineOfSightResults->m_pInst);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativeLineOfSightResults);
				UINTPTR_ZERO_CHECK(value);
				NativeLineOfSightResults->m_pInst = (phInstGta*)value.ToPointer();
			}
		}
		/// <summary>
		/// Where the line of sight hit point ended up.
		/// </summary>
		property Vector3 EndPosition
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeLineOfSightResults, Vector3::Zero);
				return CVectorToVector(NativeLineOfSightResults->m_vEndPosition);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeLineOfSightResults);
				NativeLineOfSightResults->m_vEndPosition = VectorToCVector(value);
			}
		}
		property uint32_t UnkFlags
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeLineOfSightResults, 0);
				return NativeLineOfSightResults->m_nUnkFlags;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeLineOfSightResults);
				NativeLineOfSightResults->m_nUnkFlags = value;
			}
		}
		property Vector3 Unk
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeLineOfSightResults, Vector3::Zero);
				return CVectorToVector(NativeLineOfSightResults->m_vUnk);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeLineOfSightResults);
				NativeLineOfSightResults->m_vUnk = VectorToCVector(value);
			}
		}
		property uint32_t UnkFlags2
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeLineOfSightResults, 0);
				return NativeLineOfSightResults->m_nUnkFlags2;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeLineOfSightResults);
				NativeLineOfSightResults->m_nUnkFlags2 = value;
			}
		}
		property Vector3 Unk2
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeLineOfSightResults, Vector3::Zero);
				return CVectorToVector(NativeLineOfSightResults->m_vUnk2);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeLineOfSightResults);
				NativeLineOfSightResults->m_vUnk2 = VectorToCVector(value);
			}
		}
		property uint32_t UnkFlags3
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeLineOfSightResults, 0);
				return NativeLineOfSightResults->m_nUnkFlags3;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeLineOfSightResults);
				NativeLineOfSightResults->m_nUnkFlags3 = value;
			}
		}
		property float UnkFloat1
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeLineOfSightResults, 0.0F);
				return NativeLineOfSightResults->m_fUnk1;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeLineOfSightResults);
				NativeLineOfSightResults->m_fUnk1 = value;
			}
		}
		property float UnkFloat2
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeLineOfSightResults, 0.0F);
				return NativeLineOfSightResults->m_fUnk2;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeLineOfSightResults);
				NativeLineOfSightResults->m_fUnk2 = value;
			}
		}
		property uint32_t UnkFlags4
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeLineOfSightResults, 0);
				return NativeLineOfSightResults->m_nUnkFlags4;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeLineOfSightResults);
				NativeLineOfSightResults->m_nUnkFlags4 = value;
			}
		}
		property uint32_t UnkFlags5
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeLineOfSightResults, 0);
				return NativeLineOfSightResults->m_nUnkFlags5;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeLineOfSightResults);
				NativeLineOfSightResults->m_nUnkFlags5 = value;
			}
		}
		property uint32_t UnkFlags6
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeLineOfSightResults, 0);
				return NativeLineOfSightResults->m_nUnkFlags6;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeLineOfSightResults);
				NativeLineOfSightResults->m_nUnkFlags6 = value;
			}
		}

	internal:
		IVLineOfSightResults(tLineOfSightResults* nativePtr);

	internal:
		tLineOfSightResults* NativeLineOfSightResults;
	};
}