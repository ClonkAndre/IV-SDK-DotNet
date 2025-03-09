#include "eRadarSprite.h"

class CSprite2d;

struct sRadarTraceProperties
{
	uint8_t pad[0x4];									// 00-04
	uint32_t m_nSprite;									// 04-08
};

struct sRadarTrace
{
	uint16_t ReferenceIndex;							// 00-02
	uint8_t pad[0x6];									// 02-08
	uint8_t m_bNotSimple;								// 08-09 usually 1, if not then it reads everything from ms_RadarTrace[m_nSimpleBlipIndex]
	uint8_t pad2[0x3];									// 09-0C
	uint32_t m_nDisplay;								// 0C-10
	uint8_t pad3[0x8];									// 10-18
	float m_fScaleActual;								// 18-1C
	uint8_t pad4[0x4];									// 1C-20
	uint8_t m_nFlags;									// 20-24
	uint8_t pad5[0xF];									// 09-20
	CVector m_vPos;										// 30-3C
	uint8_t pad6[0x4];									// 3C-40
	float m_fRotation;									// 40-44
	uint8_t pad7[0xC];									// 44-50
	float m_fScale;										// 50-54
	uint32_t m_nColour;									// 54-58 
	uint8_t m_nAlpha;									// 58-59
	uint8_t pad8[0x3];									// 59-5C
	sRadarTraceProperties* m_pProperties;				// 5C-60
};
VALIDATE_OFFSET(sRadarTrace, ReferenceIndex, 0x0);
VALIDATE_OFFSET(sRadarTrace, m_bNotSimple, 0x8);
VALIDATE_OFFSET(sRadarTrace, m_nDisplay, 0xC);
VALIDATE_OFFSET(sRadarTrace, m_fScaleActual, 0x18);
VALIDATE_OFFSET(sRadarTrace, m_nFlags, 0x20);
VALIDATE_OFFSET(sRadarTrace, m_vPos, 0x30);
VALIDATE_OFFSET(sRadarTrace, m_fRotation, 0x40);
VALIDATE_OFFSET(sRadarTrace, m_fScale, 0x50);
VALIDATE_OFFSET(sRadarTrace, m_nAlpha, 0x58);
VALIDATE_OFFSET(sRadarTrace, m_pProperties, 0x5C);

class CRadar
{
public:
	static inline auto RadarTrace = (sRadarTrace**)AddressSetter::Get("CRadar", "RadarTrace"); // RadarTrace[1500]
	static inline auto& m_pRadarRingBack = AddressSetter::GetRef<CSprite2d>("CRadar", "m_pRadarRingBack");
	static inline auto& m_pRadarRingFront = AddressSetter::GetRef<CSprite2d>("CRadar", "m_pRadarRingFront");
	static inline auto RadarBlipSprites = (CSprite2d**)AddressSetter::Get("CRadar", "RadarBlipSprites"); // RadarBlipSprites[128]
	static inline auto& iNumCreatedBlipSprites = AddressSetter::GetRef<int>("CRadar", "iNumCreatedBlipSprites");
	static inline auto& fRange = AddressSetter::GetRef<float>("CRadar", "fRange");
	static inline auto& vec2DRadarOrigin = AddressSetter::GetRef<CVector2D>("CRadar", "vec2DRadarOrigin");

	static inline auto& iCentreBlip = AddressSetter::GetRef<int32_t>("CRadar", "iCentreBlip");
	static inline auto& iNorthBlip = AddressSetter::GetRef<int32_t>("CRadar", "iNorthBlip");
	static inline auto& iSimpleBlip = AddressSetter::GetRef<int32_t>("CRadar", "iSimpleBlip");
	static inline auto& iBlipHovering = AddressSetter::GetRef<int32_t>("CRadar", "iBlipHovering");

	static void DrawBlips()
	{
		((void(__cdecl*)())(AddressSetter::Get("CRadar", "DrawBlips")))();
	}
	static void DrawBlipNames()
	{
		((void(__cdecl*)())(AddressSetter::Get("CRadar", "DrawBlipNames")))();
	}
	static void DrawFrameFront()
	{
		((void(__cdecl*)())(AddressSetter::Get("CRadar", "DrawFrameFront")))();
	}
	static void DrawFrameBack()
	{
		((void(__cdecl*)())(AddressSetter::Get("CRadar", "DrawFrameBack")))();
	}
	static void DrawRoute(bool bMenu)
	{
		((void(__cdecl*)(bool))(AddressSetter::Get("CRadar", "DrawRoute")))(bMenu);
	}
	static int32_t ConvertUniqueBlipToActualBlip(int32_t Index)
	{
		return ((int32_t(__cdecl*)(int32_t))(AddressSetter::Get("CRadar", "ConvertUniqueBlipToActualBlip")))(Index);
	}
	static int32_t CreateBlip(bool unk, int32_t BlpType, CVector* vecPosition, int32_t DispFlag, char* pScriptName)
	{
		return ((int32_t(__cdecl*)(bool, int32_t, CVector*, int32_t, char*))(AddressSetter::Get("CRadar", "CreateBlip")))(unk, BlpType, vecPosition, DispFlag, pScriptName);
	}
	static void SetBlipParameter(int paramId, int32_t Index, int value)
	{
		((void(__cdecl*)(int, int32_t, int))(AddressSetter::Get("CRadar", "SetBlipParameter")))(paramId, Index, value);
	}
	// 0 - scale
	// 16 - rotation
	static void SetBlipParameter(int paramId, int32_t Index, float value)
	{
		((void(__cdecl*)(int, int32_t, float))(AddressSetter::Get("CRadar", "SetBlipParameter_2")))(paramId, Index, value);
	}
	static bool RemoveBlip(int32_t Index, bool isScriptHandle)
	{
		return ((bool(__cdecl*)(int32_t, bool))(AddressSetter::Get("CRadar", "RemoveBlip")))(Index, isScriptHandle);
	}
	static bool IsBlipIdInUse(int32_t Index)
	{
		return ((bool(__cdecl*)(int32_t))(AddressSetter::Get("CRadar", "IsBlipIdInUse")))(Index);
	}
};

auto RadarBlipSpriteFilenames = (const char**)AddressSetter::Get("CRadar", "RadarBlipSpriteFilenames"); // RadarBlipSpriteFilenames[130]