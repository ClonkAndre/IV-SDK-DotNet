#pragma once

namespace IVSDKDotNet
{
	public ref class IVMenuManager
	{
	public:
		/// <summary>
		/// Gets or sets if the X-Axis of the Mouse should be inverted.
		/// </summary>
		static property bool InvertMouseX
		{
		public:
			bool get()
			{
				return CMenuManager::m_bInvertMouseX;
			}
			void set(bool value)
			{
				CMenuManager::m_bInvertMouseX = value;
			}
		}
		/// <summary>
		/// Gets or sets if the X-Axis of the Right Stick should be inverted.
		/// </summary>
		static property bool InvertRightStickX
		{
		public:
			bool get()
			{
				return CMenuManager::m_bInvertRightStickX;
			}
			void set(bool value)
			{
				CMenuManager::m_bInvertRightStickX = value;
			}
		}
		/// <summary>
		/// Gets or sets if the Auto Save option is active.
		/// </summary>
		static property bool AutoSave
		{
		public:
			bool get()
			{
				return CMenuManager::m_bAutoSave;
			}
			void set(bool value)
			{
				CMenuManager::m_bAutoSave = value;
			}
		}
		/// <summary>
		/// Gets or sets if the Clip Capture option is active.
		/// </summary>
		static property bool ClipCapture
		{
		public:
			bool get()
			{
				return CMenuManager::m_bClipCapture;
			}
			void set(bool value)
			{
				CMenuManager::m_bClipCapture = value;
			}
		}
		/// <summary>
		/// Gets or sets if the Heli Mouse Controls option is active.
		/// </summary>
		static property bool HeliMouseControls
		{
		public:
			bool get()
			{
				return CMenuManager::m_bHeliMouseControls;
			}
			void set(bool value)
			{
				CMenuManager::m_bHeliMouseControls = value;
			}
		}
		/// <summary>
		/// Gets or sets if the Hud should be visible or not.
		/// </summary>
		static property bool HudOn
		{
		public:
			bool get()
			{
				return CMenuManager::m_bHudOn;
			}
			void set(bool value)
			{
				CMenuManager::m_bHudOn = value;
			}
		}
		/// <summary>
		/// Gets or sets the current radar mode.
		/// O = Off, 1 = On, 2 = Blips only.
		/// </summary>
		static property uint32_t RadarMode
		{
		public:
			uint32_t get()
			{
				return CMenuManager::m_nRadarMode;
			}
			void set(uint32_t value)
			{
				CMenuManager::m_nRadarMode = value;
			}
		}

		/// <summary>
		/// Gets or sets the Mouse Sensitivity.
		/// </summary>
		static property uint32_t MouseSensitivity
		{
		public:
			uint32_t get()
			{
				return CMenuManager::m_nMouseSensitivity;
			}
			void set(uint32_t value)
			{
				CMenuManager::m_nMouseSensitivity = value;
			}
		}

		/// <summary>
		/// Gets or sets the brightness of the game.
		/// This value is written to 'BrightnessFloat' when changed in menu.
		/// </summary>
		static property uint32_t Brightness
		{
		public:
			uint32_t get()
			{
				return CMenuManager::m_nBrightness;
			}
			void set(uint32_t value)
			{
				CMenuManager::m_nBrightness = value;
			}
		}
		/// <summary>
		/// Gets or sets the contrast of the game.
		/// This value is written to 'ContrastFloat' when changed in menu.
		/// </summary>
		static property uint32_t Contrast
		{
		public:
			uint32_t get()
			{
				return CMenuManager::m_nContrast;
			}
			void set(uint32_t value)
			{
				CMenuManager::m_nContrast = value;
			}
		}
		/// <summary>
		/// Gets or sets the saturation of the game.
		/// This value is written to 'SaturationFloat' when changed in menu.
		/// </summary>
		static property uint32_t Saturation
		{
		public:
			uint32_t get()
			{
				return CMenuManager::m_nSaturation;
			}
			void set(uint32_t value)
			{
				CMenuManager::m_nSaturation = value;
			}
		}

		/// <summary>
		/// Gets or sets the brightness of the game.
		/// </summary>
		static property float FloatBrightness
		{
		public:
			float get()
			{
				return CMenuManager::m_fBrightness;
			}
			void set(float value)
			{
				CMenuManager::m_fBrightness = value;
			}
		}
		/// <summary>
		/// Gets or sets the contrast of the game.
		/// </summary>
		static property float FloatContrast
		{
		public:
			float get()
			{
				return CMenuManager::m_fContrast;
			}
			void set(float value)
			{
				CMenuManager::m_fContrast = value;
			}
		}
		/// <summary>
		/// Gets or sets the saturation of the game.
		/// </summary>
		static property float FloatSaturation
		{
		public:
			float get()
			{
				return CMenuManager::m_fSaturation;
			}
			void set(float value)
			{
				CMenuManager::m_fSaturation = value;
			}
		}

		/// <summary>
		/// Gets or sets the Vehicle Density.
		/// </summary>
		static property uint32_t VehicleDensity
		{
		public:
			uint32_t get()
			{
				return CMenuManager::m_nVehicleDensity;
			}
			void set(uint32_t value)
			{
				CMenuManager::m_nVehicleDensity = value;
			}
		}


		static property array<IVControlRemapInfo>^ RemapOptions
		{
		public:
			array<IVControlRemapInfo>^ get()
			{
				tControlRemapInfo* ptr = CMenuManager::m_aRemapOptions;
				NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);

				array<IVControlRemapInfo>^ arr = gcnew array<IVControlRemapInfo>(66); // TODO: Check if size is correct

				for (int i = 0; i < arr->Length; i++)
					arr[i] = IVControlRemapInfo(&ptr[i]);

				return arr;
			}
			void set(array<IVControlRemapInfo>^ value)
			{
				NULLPTR_CHECK(value);
				
				for (int i = 0; i < value->Length; i++)
					CMenuManager::m_aRemapOptions[i] = *value[i].NativeControlRemapInfo;
			}
		}

	public:
		/// <summary>
		/// Gets the value of the given setting.
		/// </summary>
		/// <param name="setting">The setting you want to get the value of.</param>
		/// <returns>The value of the setting.</returns>
		static uint32_t GetSetting(eSettings setting);
		/// <summary>
		/// Sets the value of the given setting.
		/// </summary>
		/// <param name="setting">The setting you want to change the value of.</param>
		/// <param name="value">The new value you want to set the setting with.</param>
		static void	SetSetting(eSettings setting, uint32_t value);

	};
}