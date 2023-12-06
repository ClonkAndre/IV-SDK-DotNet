#pragma once

namespace IVSDKDotNet
{
	public ref class IVCamera
	{
	public:
		static property IVCamera^ TheIVCamera
		{
		public:
			IVCamera^ get()
			{
				CCamera* c = &TheCamera;
				NULLPTR_CHECK_WITH_RETURN(c, nullptr);
				return gcnew IVCamera(c);
			}
			void set(IVCamera^ value)
			{
				NULLPTR_CHECK(value);

				CCamera* c = &TheCamera;
				NULLPTR_CHECK(c);

				NULLPTR_CHECK(value->NativeCamera);
				c = value->NativeCamera;
			}
		}
		static property IVCam^ TheFinalCam
		{
		public:
			IVCam^ get()
			{
				CCam* c = CCamera::g_pFinalCam;
				NULLPTR_CHECK_WITH_RETURN(c, nullptr);
				return gcnew IVCam(c);
			}
			void set(IVCam^ value)
			{
				NULLPTR_CHECK(value);

				CCam* c = CCamera::g_pFinalCam;
				NULLPTR_CHECK(c);

				NULLPTR_CHECK(value->NativeCam);
				c = value->NativeCam;
			}
		}

	public:
		property IVCam^ FinalCam
		{
		public:
			IVCam^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCamera, nullptr);
				return gcnew IVCam(NativeCamera->m_pFinalCam);
			}
			void set(IVCam^ value)
			{
				NULLPTR_CHECK(NativeCamera);
				NULLPTR_CHECK(value);
				NULLPTR_CHECK(value->NativeCam);

				NativeCamera->m_pFinalCam = value->NativeCam;
			}
		}
		property IVCam^ GameCam
		{
		public:
			IVCam^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCamera, nullptr);
				return gcnew IVCam(NativeCamera->m_pGameCam);
			}
			void set(IVCam^ value)
			{
				NULLPTR_CHECK(NativeCamera);
				NULLPTR_CHECK(value);
				NULLPTR_CHECK(value->NativeCam);

				NativeCamera->m_pGameCam = value->NativeCam;
			}
		}
		property IVCamFollowVehicle^ VehicleCam
		{
		public:
			IVCamFollowVehicle^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCamera, nullptr);
				return gcnew IVCamFollowVehicle(NativeCamera->m_pVehicleCam);
			}
			void set(IVCamFollowVehicle^ value)
			{
				NULLPTR_CHECK(NativeCamera);
				NULLPTR_CHECK(value);
				NULLPTR_CHECK(value->NativeCam);

				NativeCamera->m_pVehicleCam = value->NativeCam;
			}
		}
		property IVCam^ OnFootCam
		{
		public:
			IVCam^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCamera, nullptr);
				return gcnew IVCam(NativeCamera->m_pOnFootCam);
			}
			void set(IVCam^ value)
			{
				NULLPTR_CHECK(NativeCamera);
				NULLPTR_CHECK(value);
				NULLPTR_CHECK(value->NativeCam);

				NativeCamera->m_pOnFootCam = value->NativeCam;
			}
		}

	public:
		IVCam^ CreateCam(int type, IVCam^ unk, IVCam^ unk2);

	internal:
		IVCamera(CCamera* nativePtr);

	internal:
		CCamera* NativeCamera;
	};
}