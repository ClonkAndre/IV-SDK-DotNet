#pragma once

namespace IVSDKDotNet
{
	public ref class IVMenuManager
	{
	public:
		static property uint32_t m_bInvertMouseX
		{
		public:
			uint32_t get()
			{
				return CMenuManager::m_bInvertMouseX;
			}
			void set(uint32_t value)
			{
				CMenuManager::m_bInvertMouseX = value;
			}
		}
		static property uint32_t m_bInvertRightStickX
		{
		public:
			uint32_t get()
			{
				return CMenuManager::m_bInvertRightStickX;
			}
			void set(uint32_t value)
			{
				CMenuManager::m_bInvertRightStickX = value;
			}
		}
		static property uint32_t m_bAutoSave
		{
		public:
			uint32_t get()
			{
				return CMenuManager::m_bAutoSave;
			}
			void set(uint32_t value)
			{
				CMenuManager::m_bAutoSave = value;
			}
		}
		static property uint32_t m_bClipCapture
		{
		public:
			uint32_t get()
			{
				return CMenuManager::m_bClipCapture;
			}
			void set(uint32_t value)
			{
				CMenuManager::m_bClipCapture = value;
			}
		}
		static property uint32_t m_bHeliMouseControls
		{
		public:
			uint32_t get()
			{
				return CMenuManager::m_bHeliMouseControls;
			}
			void set(uint32_t value)
			{
				CMenuManager::m_bHeliMouseControls = value;
			}
		}
		static property uint32_t m_bHudOn
		{
		public:
			uint32_t get()
			{
				return CMenuManager::m_bHudOn;
			}
			void set(uint32_t value)
			{
				CMenuManager::m_bHudOn = value;
			}
		}
		static property uint32_t m_nRadarMode
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

		static property uint32_t m_nMouseSensitivity
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

		static property uint32_t m_nBrightness
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
		static property uint32_t m_nContrast
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
		static property uint32_t m_nSaturation
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
		static property float m_fBrightness
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
		static property float m_fContrast
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
		static property float m_fSaturation
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

		static property uint32_t m_nVehicleDensity
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

		// TODO: Might be an array
		static property IVControlRemapInfo^ m_aRemapOptions
		{
		public:
			IVControlRemapInfo^ get()
			{
				tControlRemapInfo* ptr = CMenuManager::m_aRemapOptions;
				NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);
				return gcnew IVControlRemapInfo(ptr);
			}
			void set(IVControlRemapInfo^ value)
			{
				NULLPTR_CHECK(value);
				NULLPTR_CHECK(value->NativeControlRemapInfo);
				CMenuManager::m_aRemapOptions = value->NativeControlRemapInfo;
			}
		}

	public:
		static uint32_t GetSetting(eSettings setting);
		static void	SetSetting(eSettings setting, uint32_t value);

	};
}