#pragma once

namespace IVSDKDotNet
{
	public ref class IVRmcDrawable
	{
	public:
		property UIntPtr ShaderGroup
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeRmcDrawable, UIntPtr::Zero);
				NULLPTR_CHECK_WITH_RETURN(NativeRmcDrawable->m_pShaderGroup, UIntPtr::Zero);
				return UIntPtr(NativeRmcDrawable->m_pShaderGroup);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativeRmcDrawable);
				UINTPTR_ZERO_CHECK(value);
				NativeRmcDrawable->m_pShaderGroup = (rage::grmShaderGroup*)value.ToPointer();
			}
		}
		property IVCrSkeleton^ Skeleton
		{
		public:
			IVCrSkeleton^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeRmcDrawable, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativeRmcDrawable->m_pSkeleton, nullptr);
				return gcnew IVCrSkeleton(NativeRmcDrawable->m_pSkeleton);
			}
			void set(IVCrSkeleton^ value)
			{
				NULLPTR_CHECK(NativeRmcDrawable);
				NULLPTR_CHECK(value);
				NativeRmcDrawable->m_pSkeleton = value->NativeCrSkeleton;
			}
		}

		property float LodDistanceHigh
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeRmcDrawable, 0.0F);
				return NativeRmcDrawable->m_fLodDistanceHigh;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeRmcDrawable);
				NativeRmcDrawable->m_fLodDistanceHigh = value;
			}
		}
		property float LodDistanceLow
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeRmcDrawable, 0.0F);
				return NativeRmcDrawable->m_fLodDistanceLow;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeRmcDrawable);
				NativeRmcDrawable->m_fLodDistanceLow = value;
			}
		}
		property float LodDistanceVLow
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeRmcDrawable, 0.0F);
				return NativeRmcDrawable->m_fLodDistanceVLow;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeRmcDrawable);
				NativeRmcDrawable->m_fLodDistanceVLow = value;
			}
		}
		property float LodDistanceVLow2
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeRmcDrawable, 0.0F);
				return NativeRmcDrawable->m_fLodDistanceVLow2;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeRmcDrawable);
				NativeRmcDrawable->m_fLodDistanceVLow2 = value;
			}
		}

	internal:
		IVRmcDrawable(rage::rmcDrawable* nativePtr);

	internal:
		rage::rmcDrawable* NativeRmcDrawable;
	};

}