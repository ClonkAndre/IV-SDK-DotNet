#pragma once

namespace IVSDKDotNet
{
	public value struct IVControlRemapInfo
	{
	public:
		property uint8_t ControlId
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeControlRemapInfo, 0);
				return NativeControlRemapInfo->m_nControlId;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeControlRemapInfo);
				NativeControlRemapInfo->m_nControlId = value;
			}
		}
		property bool DontShowInMenu
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeControlRemapInfo, 0);
				return NativeControlRemapInfo->m_bDontShowInMenu;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeControlRemapInfo);
				NativeControlRemapInfo->m_bDontShowInMenu = value;
			}
		}
		property uint16_t BoundKey
		{
		public:
			uint16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeControlRemapInfo, 0);
				return NativeControlRemapInfo->m_nBoundKey;
			}
			void set(uint16_t value)
			{
				NULLPTR_CHECK(NativeControlRemapInfo);
				NativeControlRemapInfo->m_nBoundKey = value;
			}
		}
		property String^ ControlName
		{
		public:
			String^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeControlRemapInfo, String::Empty);
				return gcnew String(NativeControlRemapInfo->m_sControlName);
			}
		}
		property String^ AltControlName
		{
		public:
			String^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeControlRemapInfo, String::Empty);
				return gcnew String(NativeControlRemapInfo->m_sAltControlName);
			}
		}

	internal:
		IVControlRemapInfo(tControlRemapInfo* nativePtr);

	internal:
		tControlRemapInfo* NativeControlRemapInfo;
	};
}