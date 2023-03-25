#pragma once

class Native_CCam
{
public:
	uint8_t pad[0x10];													// 000-010
	Native_CMatrix m_mMatrix;											// 010-050
	uint8_t pad2[0x10];													// 050-060
	float m_fFOV;														// 060-064
	float m_fNearZ;														// 064-068
	float m_fFarZ;														// 068-06C
	float m_fNearDOF;													// 06C-06C
	float m_fFarDOF;													// 070-074
	uint8_t pad3[0xCC];													// 074-140

	Native_CCam* GetCamOfType(int type, int unk)
	{
		return ((Native_CCam*(__thiscall*)(Native_CCam*, int, int))(AddressSetter::Get(0x5AD2D0, 0x5DEEB0)))(this, type, unk);
	}
	Native_CCam* Activate()
	{
		return ((Native_CCam*(__thiscall*)(Native_CCam*))(AddressSetter::Get(0x5ACC00, 0x5DE7E0)))(this);
	}
	bool Process()
	{
		return ((bool(__thiscall*)(Native_CCam*))(*(void***)this)[4])(this);
	}
};
VALIDATE_SIZE(Native_CCam, 0x140); // probably?
VALIDATE_OFFSET(Native_CCam, m_mMatrix, 0x10);
VALIDATE_OFFSET(Native_CCam, m_fFOV, 0x60);
VALIDATE_OFFSET(Native_CCam, m_fNearZ, 0x64);
VALIDATE_OFFSET(Native_CCam, m_fFarZ, 0x68);
VALIDATE_OFFSET(Native_CCam, m_fNearDOF, 0x6C);
VALIDATE_OFFSET(Native_CCam, m_fFarDOF, 0x70);

class Native_CCamFollowVehicle : public Native_CCam
{
public:
	// 000-140
	uint8_t pad[0x40];													// 140-180
	float m_fTargetFOV;													// 180-184
};
VALIDATE_OFFSET(Native_CCamFollowVehicle, m_fTargetFOV, 0x180);

namespace IVSDKDotNet {

	public ref class CCam
	{
	public:
		CCam(Native_CCam* nativePtr);

		/// <summary>
		/// Gets a cam of a specific type.
		/// </summary>
		/// <param name="type">See eCamType enum for cam types.</param>
		/// <param name="unk">Unknown.</param>
		/// <returns>The cam of the specific type if found.</returns>
		CCam^ GetCamOfType(int type, int unk);

		UIntPtr GetUIntPtr();

		CCam^ Activate();

		bool Process();

		property GTAMatrix Matrix {
			public:
				GTAMatrix	get()					{ return GTAMatrix(m_cNativeCam->m_mMatrix); }
				void		set(GTAMatrix value)	{ m_cNativeCam->m_mMatrix = Native_CMatrix(value.right, value.up, value.at, value.pos); }
		}

		property float FOV {
			public:
				float	get()				{ return m_cNativeCam->m_fFOV; }
				void	set(float value)	{ m_cNativeCam->m_fFOV = value; }
		}
		property float NearZ {
			public:
				float	get()				{ return m_cNativeCam->m_fNearZ; }
				void	set(float value)	{ m_cNativeCam->m_fNearZ = value; }
		}
		property float FarZ {
			public:
				float	get()				{ return m_cNativeCam->m_fFarZ; }
				void	set(float value)	{ m_cNativeCam->m_fFarZ = value; }
		}
		property float NearDOF {
			public:
				float	get()				{ return m_cNativeCam->m_fNearDOF; }
				void	set(float value)	{ m_cNativeCam->m_fNearDOF = value; }
		}
		property float FarDOF {
			public:
				float	get()				{ return m_cNativeCam->m_fFarDOF; }
				void	set(float value)	{ m_cNativeCam->m_fFarDOF = value; }
		}

		property Native_CCam* CamPointer {
			public:
				Native_CCam*	get()					{ return m_cNativeCam; }
				void			set(Native_CCam* value) { m_cNativeCam = value; }
		}

	private:
		uint32_t m_iHandle;
		Native_CCam* m_cNativeCam;
	};

	public ref class CCamFollowVehicle : CCam
	{
	public:
		CCamFollowVehicle(Native_CCamFollowVehicle* nativePtr);

		property float TargetFOV {
			public:
				float	get()				{ return VehCameraPointer->m_fTargetFOV; }
				void	set(float value)	{ VehCameraPointer->m_fTargetFOV = value; }
		}

		property Native_CCamFollowVehicle* VehCameraPointer {
			public:
				Native_CCamFollowVehicle*	get()									{ return m_cNativeFollowVehicleCam; }
				void						set(Native_CCamFollowVehicle* value)	{ m_cNativeFollowVehicleCam = value; }
		}

	private:
		Native_CCamFollowVehicle* m_cNativeFollowVehicleCam;
	};

}