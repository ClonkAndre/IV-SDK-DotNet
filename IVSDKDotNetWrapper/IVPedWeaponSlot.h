#pragma once

namespace IVSDKDotNet
{
	public ref class IVPedWeaponSlot
	{
	public:
		property uint32_t Type
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedWeaponSlot, 0);
				return NativePedWeaponSlot->m_nType;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePedWeaponSlot);
				NativePedWeaponSlot->m_nType = value;
			}
		}
		property uint32_t Ammo
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedWeaponSlot, 0);
				return *NativePedWeaponSlot->m_pAmmo;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePedWeaponSlot);
				NativePedWeaponSlot->m_pAmmo = &value;
			}
		}
		property bool HasModelLoaded
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedWeaponSlot, false);
				return NativePedWeaponSlot->m_nHasModelLoaded;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativePedWeaponSlot);
				NativePedWeaponSlot->m_nHasModelLoaded = value;
			}
		}

	internal:
		IVPedWeaponSlot(PedWeaponSlot* nativePtr);

	internal:
		PedWeaponSlot* NativePedWeaponSlot;
	};
}