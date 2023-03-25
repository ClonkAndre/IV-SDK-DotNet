#pragma once

struct Native_tControlRemapInfo
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
VALIDATE_SIZE(Native_tControlRemapInfo, 0xE2);
VALIDATE_OFFSET(Native_tControlRemapInfo, m_nControlId, 0x0);
VALIDATE_OFFSET(Native_tControlRemapInfo, m_sControlName, 0x8);
VALIDATE_OFFSET(Native_tControlRemapInfo, m_sAltControlName, 0x74);

class Native_CMenuManager
{
public:

	// Game
	static uint32_t GetAutoSave()							{ return AddressSetter::GetRef<uint32_t>(0xCC79F0, 0xCFC0C0); }
	static void		SetAutoSave(uint32_t value)				{ AddressSetter::GetRef<uint32_t>(0xCC79F0, 0xCFC0C0) = value; }

	static uint32_t GetClipCapture()						{ return AddressSetter::GetRef<uint32_t>(0xCC7C58, 0xCFC328); }
	static void		SetClipCapture(uint32_t value)			{ AddressSetter::GetRef<uint32_t>(0xCC7C58, 0xCFC328) = value; }

	// Controls
	static uint32_t GetInvertMouseX()						{ return AddressSetter::GetRef<uint32_t>(0xCC7A00, 0xCFC0D0); }
	static void		SetInvertMouseX(uint32_t value)			{ AddressSetter::GetRef<uint32_t>(0xCC7A00, 0xCFC0D0) = value; }

	static uint32_t GetInvertRightStickX()					{ return AddressSetter::GetRef<uint32_t>(0xCC7A04, 0xCFC0D4); }
	static void		SetInvertRightStickX(uint32_t value)	{ AddressSetter::GetRef<uint32_t>(0xCC7A04, 0xCFC0D4) = value; }

	static uint32_t GetHeliMouseControls()					{ return AddressSetter::GetRef<uint32_t>(0xCC7C78, 0xCFC348); }
	static void		SetHeliMouseControls(uint32_t value)	{ AddressSetter::GetRef<uint32_t>(0xCC7C78, 0xCFC348) = value; }

	static uint32_t GetMouseSensitivity()					{ return AddressSetter::GetRef<uint32_t>(0xCC7C10, 0xCFC2E0); }
	static void		SetMouseSensitivity(uint32_t value)		{ AddressSetter::GetRef<uint32_t>(0xCC7C10, 0xCFC2E0) = value; }

	// - - - Graphics - - -
	static uint32_t GetVehicleDensity()						{ return AddressSetter::GetRef<uint32_t>(0xCC7C3C, 0xCFC30C); }
	static void		SetVehicleDensity(uint32_t value)		{ AddressSetter::GetRef<uint32_t>(0xCC7C3C, 0xCFC30C) = value; }

	// - - - Display - - -
	static uint32_t GetHudOn()								{ return AddressSetter::GetRef<uint32_t>(0xCC7A2C, 0xCFC0FC); }
	static void		SetHudOn(uint32_t value)				{ AddressSetter::GetRef<uint32_t>(0xCC7A2C, 0xCFC0FC) = value; }

	static uint32_t GetRadarMode()							{ return AddressSetter::GetRef<uint32_t>(0xCC7A3C, 0xCFC10C); }
	static void		SetRadarMode(uint32_t value)			{ AddressSetter::GetRef<uint32_t>(0xCC7A3C, 0xCFC10C) = value; }

	// Written to float values when changed in menu
	static uint32_t GetBrightness()							{ return AddressSetter::GetRef<uint32_t>(0xCC7A18, 0xCFC0E8); }
	static void		SetBrightness(uint32_t value)			{ AddressSetter::GetRef<uint32_t>(0xCC7A18, 0xCFC0E8) = value; }

	static uint32_t GetContrast()							{ return AddressSetter::GetRef<uint32_t>(0xCC7A1C, 0xCFC0EC); }
	static void		SetContrast(uint32_t value)				{ AddressSetter::GetRef<uint32_t>(0xCC7A1C, 0xCFC0EC) = value; }

	static uint32_t GetSaturation()							{ return AddressSetter::GetRef<uint32_t>(0xCC7A20, 0xCFC0F0); }
	static void		SetSaturation(uint32_t value)			{ AddressSetter::GetRef<uint32_t>(0xCC7A20, 0xCFC0F0) = value; }

	// Floats
	static float	GetFloatBrightness()					{ return AddressSetter::GetRef<float>(0xB21704, 0xB38208); }
	static void		SetFloatBrightness(float value)			{ AddressSetter::GetRef<float>(0xB21704, 0xB38208) = value; }

	static float	GetFloatContrast()						{ return AddressSetter::GetRef<float>(0xB21708, 0xB3820C); }
	static void		SetFloatContrast(float value)			{ AddressSetter::GetRef<float>(0xB21708, 0xB3820C) = value; }

	static float	GetFloatSaturation()					{ return AddressSetter::GetRef<float>(0xB2170C, 0xB38210); }
	static void		SetFloatSaturation(float value)			{ AddressSetter::GetRef<float>(0xB2170C, 0xB38210) = value; }


	static Native_tControlRemapInfo* GetRemapOptions()
	{
		return (Native_tControlRemapInfo*)AddressSetter::Get(0xB1547A, 0xB4DF8A);
	}
};

namespace IVSDKDotNet {

	public ref struct tControlRemapInfo
	{
	public:
		static tControlRemapInfo^ GetRemapInfo()
		{
			Native_tControlRemapInfo* r = Native_CMenuManager::GetRemapOptions();

			if (r)
				return gcnew tControlRemapInfo(r);

			return nullptr;
		}

		property uint8_t ControlID {
			public:		uint8_t get()			{ return m_nControlId; }
			private:	void set(uint8_t value) { m_nControlId = value; }
		}

		property bool DontShowInMenu {
			public:		bool get()				{ return m_bDontShowInMenu; }
			private:	void set(bool value)	{ m_bDontShowInMenu = value; }
		}

		property uint16_t BoundKey {
			public:		uint16_t get()			{ return m_nBoundKey; }
			private:	void set(uint16_t value) { m_nBoundKey = value; }
		}

		property String^ ControlName {
			public:		String^ get()			{ return m_sControlName; }
			private:	void set(String^ value) { m_sControlName = value; }
		}

		property String^ AltControlName {
			public:		String^ get()			{ return m_sAltControlName; }
			private:	void set(String^ value) { m_sAltControlName = value; }
		}

	private:
		tControlRemapInfo(Native_tControlRemapInfo* unmanagedtControlRemapInfo);

		uint8_t m_nControlId;
		bool m_bDontShowInMenu;
		uint16_t m_nBoundKey;
		String^ m_sControlName;
		String^ m_sAltControlName;
	};

	public ref class CMenuManager
	{
	public:

		ref class Controls
		{
		public:

			/// <summary>
			/// Gets or sets the Invert Mouse value set in the "Controls" settings menu.
			/// </summary>
			static property uint32_t InvertMouseX {
				public:
					uint32_t	get()				{ return Native_CMenuManager::GetInvertMouseX(); }
					void		set(uint32_t value) { Native_CMenuManager::SetInvertMouseX(value); }
			}

			/// <summary>
			/// Gets or sets the Invert Right Stick value set in the "Controls" settings menu.
			/// </summary>
			static property uint32_t InvertRightStickX {
				public:
					uint32_t	get()				{ return Native_CMenuManager::GetInvertRightStickX(); }
					void		set(uint32_t value) { Native_CMenuManager::SetInvertRightStickX(value); }
			}

			/// <summary>
			/// Gets or sets the Helicopter Mouse Controls value set in the "Controls" settings menu.
			/// </summary>
			static property uint32_t HeliMouseControls {
				public:
					uint32_t	get()				{ return Native_CMenuManager::GetHeliMouseControls(); }
					void		set(uint32_t value) { Native_CMenuManager::SetHeliMouseControls(value); }
			}

			/// <summary>
			/// Gets or sets the Mouse Sensitivity value set in the "Controls" settings menu.
			/// </summary>
			static property uint32_t MouseSensitivity {
				public:
					uint32_t	get()				{ return Native_CMenuManager::GetMouseSensitivity(); }
					void		set(uint32_t value) { Native_CMenuManager::SetMouseSensitivity(value); }
			}

		};

		ref class Display
		{
		public:

			/// <summary>
			/// Gets or sets the Brightness value set in the "Display" settings menu.
			/// </summary>
			static property uint32_t Brightness {
				public:
					uint32_t	get()				{ return Native_CMenuManager::GetBrightness(); }
					void		set(uint32_t value) { Native_CMenuManager::SetBrightness(value); }
			}
			/// <summary>
			/// Gets or sets the float Brightness value set in the "Display" settings menu.
			/// </summary>
			static property float FloatBrightness {
				public:
					float		get()				{ return Native_CMenuManager::GetFloatBrightness(); }
					void		set(float value)	{ Native_CMenuManager::SetFloatBrightness(value); }
			}

			/// <summary>
			/// Gets or sets the Contrast value set in the "Display" settings menu.
			/// </summary>
			static property uint32_t Contrast {
				public:
					uint32_t	get()				{ return Native_CMenuManager::GetContrast(); }
					void		set(uint32_t value) { Native_CMenuManager::SetContrast(value); }
			}
			/// <summary>
			/// Gets or sets the float Contrast value set in the "Display" settings menu.
			/// </summary>
			static property float FloatContrast {
				public:
					float		get()				{ return Native_CMenuManager::GetFloatContrast(); }
					void		set(float value)	{ Native_CMenuManager::SetFloatContrast(value); }
			}

			/// <summary>
			/// Gets or sets the Saturation value set in the "Display" settings menu.
			/// </summary>
			static property uint32_t Saturation {
				public:
					uint32_t	get()				{ return Native_CMenuManager::GetSaturation(); }
					void		set(uint32_t value) { Native_CMenuManager::SetSaturation(value); }
			}
			/// <summary>
			/// Gets or sets the float Saturation value set in the "Display" settings menu.
			/// </summary>
			static property float FloatSaturation {
				public:
					float		get()				{ return Native_CMenuManager::GetFloatSaturation(); }
					void		set(float value)	{ Native_CMenuManager::SetFloatSaturation(value); }
			}

			/// <summary>
			/// Gets or sets the Radar value set in the "Display" settings menu.
			/// O = Off, 1 = On, 2 = Blips only.
			/// </summary>
			static property uint32_t RadarMode {
				public:
					uint32_t	get()				{ return Native_CMenuManager::GetRadarMode(); }
					void		set(uint32_t value) { Native_CMenuManager::SetRadarMode(value); }
			}

			/// <summary>
			/// Gets or sets the HUD value set in the "Display" settings menu.
			/// </summary>
			static property uint32_t HudOn {
				public:
					uint32_t	get()				{ return Native_CMenuManager::GetHudOn(); }
					void		set(uint32_t value) { Native_CMenuManager::SetHudOn(value); }
			}

		};

		ref class Graphics
		{
		public:

			/// <summary>
			/// Gets or sets the Vehicle Density value set in the "Graphics" settings menu.
			/// </summary>
			static property uint32_t VehicleDensity {
				public:
					uint32_t	get()				{ return Native_CMenuManager::GetVehicleDensity(); }
					void		set(uint32_t value) { Native_CMenuManager::SetVehicleDensity(value); }
			}

		};

		ref class Game
		{
		public:

			/// <summary>
			/// Gets or sets the Autosave value set in the "Game" settings menu.
			/// </summary>
			static property uint32_t AutoSave {
				public:
					uint32_t	get()				{ return Native_CMenuManager::GetAutoSave(); }
					void		set(uint32_t value) { Native_CMenuManager::SetAutoSave(value); }
			}

			/// <summary>
			/// Gets or sets the Clip Capture value set in the "Game" settings menu.
			/// </summary>
			static property uint32_t ClipCapture {
				public:
					uint32_t	get()				{ return Native_CMenuManager::GetClipCapture(); }
					void		set(uint32_t value) { Native_CMenuManager::SetClipCapture(value); }
			}

		};

		static uint32_t GetSetting(eSettings setting);
		static void		SetSetting(eSettings setting, uint32_t value);

	};

}