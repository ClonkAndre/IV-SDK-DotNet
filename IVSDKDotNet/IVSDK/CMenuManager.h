struct tControlRemapInfo
{
	uint8_t m_nControlId;					// 00-01 see ePadControls
	bool m_bDontShowInMenu;					// 01-02
	uint16_t m_nBoundKey;					// 02-04 display only?
	uint8_t pad[0x4];						// 04-08
	wchar_t m_sControlName[24];				// 08-38
	uint8_t pad2[0x3C];						// 38-74
	wchar_t m_sAltControlName[24];			// 74-A4
	uint8_t pad3[0x3E];						// A4-E2
};
VALIDATE_SIZE(tControlRemapInfo, 0xE2);
VALIDATE_OFFSET(tControlRemapInfo, m_nControlId, 0x0);
VALIDATE_OFFSET(tControlRemapInfo, m_sControlName, 0x8);
VALIDATE_OFFSET(tControlRemapInfo, m_sAltControlName, 0x74);

class CMenuManager
{
public:
	static inline uint32_t& m_bInvertMouseX = AddressSetter::GetRef<uint32_t>("CMenuManager", "m_bInvertMouseX");
	static inline uint32_t& m_bInvertRightStickX = AddressSetter::GetRef<uint32_t>("CMenuManager", "m_bInvertRightStickX");
	static inline uint32_t& m_bAutoSave = AddressSetter::GetRef<uint32_t>("CMenuManager", "m_bAutoSave");
	static inline uint32_t& m_bClipCapture = AddressSetter::GetRef<uint32_t>("CMenuManager", "m_bClipCapture");
	static inline uint32_t& m_bHeliMouseControls = AddressSetter::GetRef<uint32_t>("CMenuManager", "m_bHeliMouseControls");
	static inline uint32_t& m_bHudOn = AddressSetter::GetRef<uint32_t>("CMenuManager", "m_bHudOn");
	static inline uint32_t& m_nRadarMode = AddressSetter::GetRef<uint32_t>("CMenuManager", "m_nRadarMode");

	static inline uint32_t& m_nMouseSensitivity = AddressSetter::GetRef<uint32_t>("CMenuManager", "m_nMouseSensitivity");

	// written to float values when changed in menu
	static inline uint32_t& m_nBrightness = AddressSetter::GetRef<uint32_t>("CMenuManager", "m_nBrightness");
	static inline uint32_t& m_nContrast = AddressSetter::GetRef<uint32_t>("CMenuManager", "m_nContrast");
	static inline uint32_t& m_nSaturation = AddressSetter::GetRef<uint32_t>("CMenuManager", "m_nSaturation");

	static inline uint32_t& m_nVehicleDensity = AddressSetter::GetRef<uint32_t>("CMenuManager", "m_nVehicleDensity");

	static inline float& m_fBrightness = AddressSetter::GetRef<float>("CMenuManager", "m_fBrightness");
	static inline float& m_fContrast = AddressSetter::GetRef<float>("CMenuManager", "m_fContrast");
	static inline float& m_fSaturation = AddressSetter::GetRef<float>("CMenuManager", "m_fSaturation");

	static inline tControlRemapInfo* m_aRemapOptions = (tControlRemapInfo*)AddressSetter::Get("CMenuManager", "m_aRemapOptions");
};