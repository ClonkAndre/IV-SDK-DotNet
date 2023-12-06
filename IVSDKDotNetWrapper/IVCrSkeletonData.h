#pragma once

namespace IVSDKDotNet
{
	public value struct IVCrSkeletonData
	{
	public:
		property String^ Name
		{
		public:
			String^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCrSkeletonData, String::Empty);
				return gcnew String(NativeCrSkeletonData->m_sName);
			}
		}
		property uint16_t BoneID
		{
		public:
			uint16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCrSkeletonData, 0);
				return NativeCrSkeletonData->m_nBoneID;
			}
			void set(uint16_t value)
			{
				NULLPTR_CHECK(NativeCrSkeletonData);
				NativeCrSkeletonData->m_nBoneID = value;
			}
		}

	internal:
		IVCrSkeletonData(rage::crSkeletonData* nativePtr);

	internal:
		rage::crSkeletonData* NativeCrSkeletonData;
	};
}