#pragma once

struct Native_tViewportData
{
	uint8_t pad[0x180];						// 000-180
	Native_CMatrix m_mProjectionMatrix;		// 180-1C0
	uint8_t pad2[0xC0];						// 1C0-280
	float m_fLeft;							// 280-284
	float m_fTop;							// 284-288
	float m_fRight;							// 288-28C
	float m_fBottom;						// 28C-290
	uint8_t pad3[0x20];						// 290-2B0
	uint32_t m_nResX;						// 2B0-2B4
	uint32_t m_nResY;						// 2B4-2B8
	float m_fFOV;							// 2B8-2BC
	float m_fAspect;						// 2BC-2C0
	float m_fNearClip;						// 2C0-2C4
	float m_fFarClip;						// 2C4-2C8
	uint8_t pad4[0x8];						// 2C8-2D0
	float m_fScaleX;						// 2D0-2D4
	float m_fScaleY;						// 2D4-2D8
};
VALIDATE_OFFSET(Native_tViewportData, m_mProjectionMatrix, 0x180);
VALIDATE_OFFSET(Native_tViewportData, m_fLeft, 0x280);
VALIDATE_OFFSET(Native_tViewportData, m_fTop, 0x284);
VALIDATE_OFFSET(Native_tViewportData, m_fRight, 0x288);
VALIDATE_OFFSET(Native_tViewportData, m_fBottom, 0x28C);
VALIDATE_OFFSET(Native_tViewportData, m_nResX, 0x2B0);
VALIDATE_OFFSET(Native_tViewportData, m_nResY, 0x2B4);
VALIDATE_OFFSET(Native_tViewportData, m_fFOV, 0x2B8);
VALIDATE_OFFSET(Native_tViewportData, m_fAspect, 0x2BC);
VALIDATE_OFFSET(Native_tViewportData, m_fNearClip, 0x2C0);
VALIDATE_OFFSET(Native_tViewportData, m_fFarClip, 0x2C4);
VALIDATE_OFFSET(Native_tViewportData, m_fScaleX, 0x2D0);
VALIDATE_OFFSET(Native_tViewportData, m_fScaleY, 0x2D4);

class Native_CViewport
{
public:
	uint8_t pad[0x10];						// 000-010
	Native_tViewportData m_pData;			// 010-??
};

class Native_CViewportPrimaryOrtho : public Native_CViewport {};
class Native_CViewportGame : public Native_CViewport {};
class Native_CViewportRadar : public Native_CViewport {};
class Native_CViewportMobilePhone : public Native_CViewport {};

struct Native_tGlobalScene
{
	Native_CViewportPrimaryOrtho* m_pPrimaryViewport;					// 000-004
	Native_CViewportGame* m_pGameViewport;								// 004-008
	Native_CViewportRadar* m_pRadarViewport;							// 008-00C
	Native_CViewportMobilePhone* m_pPhoneViewport;						// 00C-010
	uint8_t pad[0x70];													// 010-080
	//rage::ProceduralTextureRenderTargetDef* m_pRenderTargetTexture;	// 080-084
	uint8_t pad2[0x7C];													// 084-100
	//rage::grcRenderTargetPC* m_pRenderTarget;							// 100-104
	uint8_t pad3[0x7C];													// 104-180
	//rage::grmShaderFx* m_pUnkShaderFx[2];								// 180-188
	uint8_t pad4[0x78];													// 188-200
	//rage::SkyhatPerlinNoise m_sSkyhatNoise;							// 200-230
	uint8_t pad5[0x10];													// 230-240
	//rage::grcVertexBufferD3D m_sVertexBuffer[2];						// 240-2C0
};
//VALIDATE_OFFSET(tGlobalScene, m_pPrimaryViewport, 0x0);
//VALIDATE_OFFSET(tGlobalScene, m_pGameViewport, 0x4);
//VALIDATE_OFFSET(tGlobalScene, m_pRadarViewport, 0x8);
//VALIDATE_OFFSET(tGlobalScene, m_pPhoneViewport, 0xC);
//VALIDATE_OFFSET(tGlobalScene, m_pRenderTargetTexture, 0x80);
//VALIDATE_OFFSET(tGlobalScene, m_pRenderTarget, 0x100);
//VALIDATE_OFFSET(tGlobalScene, m_pUnkShaderFx, 0x180);
//VALIDATE_OFFSET(tGlobalScene, m_sSkyhatNoise, 0x200);

class Native_CDraw
{
public:
	Native_tGlobalScene* m_pGlobalScene;							// 000-004
	uint8_t pad[0x34];												// 004-038
	//tRenderPhases* m_pRenderPhases;								// 038-03C
	uint16_t m_nNumRenderPhases;									// 03C-03E
	uint8_t pad2[0x415];											// 03E-453
	uint8_t m_bForceHudWidescreen;									// 453-454 m_bWidescreenBorders?

	float CalculateAspectRatio(bool bUnk) // bUnk = 1 forces it to 1.777... if m_bForceHudWidescreen byte is non-zero
	{
		return ((float(__thiscall*)(Native_CDraw*, bool))(AddressSetter::Get(0x3B4110, 0x49BA00)))(this, bUnk);
	}
};
//VALIDATE_OFFSET(CDraw, m_pRenderPhases, 0x38);
//VALIDATE_OFFSET(CDraw, m_bForceHudWidescreen, 0x453);

namespace IVSDKDotNet {

	public ref class tViewportData
	{
	public:
		tViewportData(Native_tViewportData* nativePtr);

		property GTAMatrix ProjectionMatrix {
			public: GTAMatrix get() { return GTAMatrix(m_cNativeViewportData->m_mProjectionMatrix); }
		}

		property Drawing::RectangleF Rect {
			public: Drawing::RectangleF get() { return Drawing::RectangleF(m_cNativeViewportData->m_fLeft, m_cNativeViewportData->m_fTop, m_cNativeViewportData->m_fRight, m_cNativeViewportData->m_fBottom); }
		}

		property Size Resolution {
			public: Size get() { return Size((int)m_cNativeViewportData->m_nResX, (int)m_cNativeViewportData->m_nResY); }
		}

		property float FOV {
			public: float get() { return m_cNativeViewportData->m_fFOV; }
		}

		property float Aspect {
			public: float get() { return m_cNativeViewportData->m_fAspect; }
		}

		property float NearClip {
			public: float get() { return m_cNativeViewportData->m_fNearClip; }
		}

		property float FarClip {
			public: float get() { return m_cNativeViewportData->m_fFarClip; }
		}

		property SizeF Scale {
			public: SizeF get() { return SizeF(m_cNativeViewportData->m_fScaleX, m_cNativeViewportData->m_fScaleY); }
		}

	private:
		Native_tViewportData* m_cNativeViewportData;
	};

	public ref class CViewport
	{
	public:
		CViewport(Native_CViewport* nativePtr);

		property tViewportData^ Data {
			public:
				tViewportData^ get() { return gcnew tViewportData(&m_cNativeViewport->m_pData); }
				//void		set(uint16_t value) { m_cNativeCDraw->m_nNumRenderPhases = value; }
		}

	private:
		Native_CViewport* m_cNativeViewport;
	};

	public ref class CViewportPrimaryOrtho : CViewport
	{
	public:
		CViewportPrimaryOrtho(Native_CViewportPrimaryOrtho* nativePtr);

	private:
		Native_CViewportPrimaryOrtho* m_cNativeViewportPrimaryOrtho;
	};

	public ref class CViewportGame : CViewport
	{
	public:
		CViewportGame(Native_CViewportGame* nativePtr);

	private:
		Native_CViewportGame* m_cNativeViewportGame;
	};

	public ref class CViewportRadar : CViewport
	{
	public:
		CViewportRadar(Native_CViewportRadar* nativePtr);

	private:
		Native_CViewportRadar* m_cNativeViewportRadar;
	};

	public ref class CViewportMobilePhone : CViewport
	{
	public:
		CViewportMobilePhone(Native_CViewportMobilePhone* nativePtr);

	private:
		Native_CViewportMobilePhone* m_cNativeViewportMobilePhone;
	};

	public ref class tGlobalScene
	{
	public:
		tGlobalScene(Native_tGlobalScene* nativePtr);
		
		/// <summary>
		/// Gets the orthographic viewport.
		/// </summary>
		property CViewportPrimaryOrtho^ ViewportPrimaryOrtho {
			public:
				CViewportPrimaryOrtho^	get() { return gcnew CViewportPrimaryOrtho(m_cGlobalScene->m_pPrimaryViewport); }
				//void		set(CViewportPrimaryOrtho^ value) { m_cNativeCDraw->m_nNumRenderPhases = value; }
		}

		/// <summary>
		/// Gets the viewport of the game.
		/// </summary>
		property CViewportGame^ ViewportGame {
			public:
				CViewportGame^	get() { return gcnew CViewportGame(m_cGlobalScene->m_pGameViewport); }
				//void		set(CViewportGame^ value) { m_cNativeCDraw->m_nNumRenderPhases = value; }
		}

		/// <summary>
		/// Gets the viewport of the radar.
		/// </summary>
		property CViewportRadar^ ViewportRadar {
			public:
				CViewportRadar^	get() { return gcnew CViewportRadar(m_cGlobalScene->m_pRadarViewport); }
				//void		set(CViewportRadar^ value) { m_cNativeCDraw->m_nNumRenderPhases = value; }
		}

		/// <summary>
		/// Gets the viewport of the mobile phone.
		/// </summary>
		property CViewportMobilePhone^ ViewportMobilePhone {
			public:
				CViewportMobilePhone^	get() { return gcnew CViewportMobilePhone(m_cGlobalScene->m_pPhoneViewport); }
				//void		set(CViewportMobilePhone^ value) { m_cNativeCDraw->m_nNumRenderPhases = value; }
		}

	private:
		Native_tGlobalScene* m_cGlobalScene;
	};

	public ref class CDraw
	{
	public:
		CDraw(Native_CDraw* nativePtr);

		/// <summary>
		/// Gets the main CDraw instance.
		/// </summary>
		/// <returns>The CDraw instance.</returns>
		static CDraw^ Get();

		/// <summary>
		/// Calculates the aspect ratio.
		/// </summary>
		/// <param name="bUnk">True forces it to 1.777... if ForceHudWidescreen byte is non-zero.</param>
		/// <returns>The calculated aspect ratio.</returns>
		float CalculateAspectRatio(bool bUnk);

		property tGlobalScene^ GlobalScene {
			public:
				tGlobalScene^	get() { return gcnew tGlobalScene(m_cNativeCDraw->m_pGlobalScene); }
				//void		set(uint16_t value) { m_cNativeCDraw->m_nNumRenderPhases = value; }
		}

		property uint16_t NumRenderPhases {
			public:
				uint16_t	get()				{ return m_cNativeCDraw->m_nNumRenderPhases; }
				void		set(uint16_t value) { m_cNativeCDraw->m_nNumRenderPhases = value; }
		}

		/// <summary>
		///	m_bWidescreenBorders?
		/// </summary>
		property uint8_t ForceHudWidescreen {
			public:
				uint8_t get()				{ return m_cNativeCDraw->m_bForceHudWidescreen; }
				void	set(uint8_t value)	{ m_cNativeCDraw->m_bForceHudWidescreen = value; }
		}

	private:
		Native_CDraw* m_cNativeCDraw;
	};

}