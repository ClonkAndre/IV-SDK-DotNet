#pragma once

class Native_CCamera
{
public:
	//static inline Native_CCam*& g_pFinalCam = AddressSetter::GetRef<Native_CCam*>(0xB21A70, 0xB488EC); // CCamFinal

	uint8_t pad[0x4];							// 00-04
	Native_CCam* m_pFinalCam;					// 04-08
	uint8_t pad2[0x4];							// 08-0C
	Native_CCam* m_pGameCam;					// 0C-10
	Native_CCamFollowVehicle* m_pVehicleCam;	// 10-14
	Native_CCam* m_pOnFootCam;					// 14-18

	Native_CCam* CreateCam(int type, Native_CCam* unk, Native_CCam* unk2)
	{
		return ((Native_CCam*(__thiscall*)(Native_CCamera*, int, Native_CCam*, Native_CCam*))(AddressSetter::Get(0x51F510, 0x5DF770)))(this, type, unk, unk2);
	}
};
VALIDATE_OFFSET(Native_CCamera, m_pFinalCam, 0x4);
VALIDATE_OFFSET(Native_CCamera, m_pGameCam, 0xC);

namespace IVSDKDotNet {

	public ref class CCamera
	{
	public:
		CCamera(Native_CCamera* nativePtr);

		static CCamera^ GetTheCamera();
		static CCam^	GetFinalCam();

		CCam^ CreateCam(int type, CCam^ unk, CCam^ unk2);

		property CCam^ FinalCam {
			public:
				CCam^ get()
				{
					Native_CCam* cam = m_cNativeCamera->m_pFinalCam;

					if (!cam)
						return nullptr;

					return gcnew CCam(cam);
				}
				void set(CCam^ value)	{ m_cNativeCamera->m_pFinalCam = value->CamPointer; }
		}
		property CCam^ GameCam {
			public:
				CCam^	get()
				{
					Native_CCam* cam = m_cNativeCamera->m_pGameCam;

					if (!cam)
						return nullptr;

					return gcnew CCam(cam);
				}
				void set(CCam^ value)	{ m_cNativeCamera->m_pGameCam = value->CamPointer; }
		}
		property CCamFollowVehicle^ VehicleCam {
			public:
				CCamFollowVehicle^	get() 
				{
					Native_CCamFollowVehicle* cam = m_cNativeCamera->m_pVehicleCam;

					if (!cam)
						return nullptr;

					return gcnew CCamFollowVehicle(cam);
				}
				void set(CCamFollowVehicle^ value)	{ m_cNativeCamera->m_pVehicleCam = value->VehCameraPointer; }
		}
		property CCam^ OnFootCam {
			public:
				CCam^	get() 
				{
					Native_CCam* cam = m_cNativeCamera->m_pOnFootCam;

					if (!cam)
						return nullptr;

					return gcnew CCam(cam);
				}
				void	set(CCam^ value)	{ m_cNativeCamera->m_pOnFootCam = value->CamPointer; }
		}

		property Native_CCamera* CameraPointer {
			public:
				Native_CCamera* get()						{ return m_cNativeCamera; }
				void			set(Native_CCamera* value)	{ m_cNativeCamera = value; }
		}

	private:
		Native_CCamera* m_cNativeCamera;
	};

}