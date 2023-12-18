#pragma once

namespace IVSDKDotNet
{
	public ref class IVCrSkeleton
	{
	public:
		property array<IVCrSkeletonData>^ Data
		{
		public:
			array<IVCrSkeletonData>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCrSkeleton, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativeCrSkeleton->m_aData, nullptr);

				// TODO: Validate if the array is actually of size BoneCount!
				array<IVCrSkeletonData>^ arr = gcnew array<IVCrSkeletonData>(BoneCount);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = IVCrSkeletonData(&NativeCrSkeleton->m_aData[i]);

				return arr;
			}
			void set(array<IVCrSkeletonData>^ value)
			{
				NULLPTR_CHECK(NativeCrSkeleton);
				NULLPTR_CHECK(value);

				for(int i = 0; i < value->Length; i++)
					NativeCrSkeleton->m_aData[i] = *value[i].NativeCrSkeletonData;
			}
		}
		property uint16_t BoneCount
		{
		public:
			uint16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCrSkeleton, 0);
				return NativeCrSkeleton->m_nBoneCount;
			}
			void set(uint16_t value)
			{
				NULLPTR_CHECK(NativeCrSkeleton);
				NativeCrSkeleton->m_nBoneCount = value;
			}
		}

	public:
		IVCrSkeletonData GetBoneDataByName(String^ sName);

	internal:
		IVCrSkeleton(rage::crSkeleton* nativePtr);

	internal:
		rage::crSkeleton* NativeCrSkeleton;
	};
}