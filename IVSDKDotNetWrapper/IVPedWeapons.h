#pragma once

namespace IVSDKDotNet
{
	public ref class IVPedWeapons
	{
	public:
		property uint32_t ActiveWeaponSlot
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedWeapons, 0);
				return NativePedWeapons->m_nActiveWeaponSlot;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePedWeapons);
				NativePedWeapons->m_nActiveWeaponSlot = value;
			}
		}
		property IVObject^ WeaponObject
		{
		public:
			IVObject^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedWeapons, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativePedWeapons->m_pWeaponObject, nullptr);
				return gcnew IVObject(NativePedWeapons->m_pWeaponObject);
			}
			void set(IVObject^ value)
			{
				NULLPTR_CHECK(NativePedWeapons);
				NULLPTR_CHECK(value);
				NativePedWeapons->m_pWeaponObject = value->NativeObject;
			}
		}
		property array<IVPedWeaponSlot^>^ Weapons
		{
		public:
			array<IVPedWeaponSlot^>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePedWeapons, nullptr);

				PedWeaponSlot* ptr = NativePedWeapons->m_aWeapons;
				NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);

				array<IVPedWeaponSlot^>^ arr = gcnew array<IVPedWeaponSlot^>(12);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = gcnew IVPedWeaponSlot(&ptr[i]);

				return arr;
			}
			void set(array<IVPedWeaponSlot^>^ value)
			{
				NULLPTR_CHECK(NativePedWeapons);
				NULLPTR_CHECK(value);

				PedWeaponSlot* ptr = NativePedWeapons->m_aWeapons;
				NULLPTR_CHECK(ptr);

				for(int i = 0; i < value->Length; i++)
					ptr[i] = *value[i]->NativePedWeaponSlot;
			}
		}

	public:
		void GiveWeapon(int weaponType, uint32_t ammoQuantity, bool unk1, bool unk2, bool unk3);

	internal:
		IVPedWeapons(PedWeapons* nativePtr);

	internal:
		PedWeapons* NativePedWeapons;
	};
}