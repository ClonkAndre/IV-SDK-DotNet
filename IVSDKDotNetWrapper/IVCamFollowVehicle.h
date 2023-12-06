#pragma once

namespace IVSDKDotNet
{
	public ref class IVCamFollowVehicle : public IVCam
	{
	public:
		property float TargetFOV
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCam, 0.0F);
				return NativeCam->m_fTargetFOV;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeCam);
				NativeCam->m_fTargetFOV = value;
			}
		}

	internal:
		IVCamFollowVehicle(CCamFollowVehicle* nativePtr);

	internal:
		CCamFollowVehicle* NativeCam;
	};
}