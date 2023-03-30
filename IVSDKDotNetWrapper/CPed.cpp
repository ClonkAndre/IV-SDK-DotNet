#include "pch.h"
#include "CPed.h"

namespace IVSDKDotNet {

	// =========================================================================
	// ============================ PedWeaponSlot ==============================
	// =========================================================================
	PedWeaponSlot::PedWeaponSlot(Native_PedWeaponSlot* nativePtr)
	{
		PedWeaponSlotPointer = nativePtr;
	}

	// =========================================================================
	// ============================== PedWeapons ===============================
	// =========================================================================
	PedWeapons::PedWeapons(Native_PedWeapons* nativePtr)
	{
		PedWeaponsPointer = nativePtr;
	}

	// =========================================================================
	// ========================= CPedMoveBlendOnFoot ===========================
	// =========================================================================
	CPedMoveBlendOnFoot::CPedMoveBlendOnFoot(Native_CPedMoveBlendOnFoot* nativePtr)
	{
		Pointer = nativePtr;
	}

	// =========================================================================
	// ================================= CPed ==================================
	// =========================================================================
	CPed::CPed(Native_CPed* nativePtr) : CPhysical(nativePtr)
	{
		PedPointer = nativePtr;
	}

	CPed^ CPed::FromPointer(UIntPtr ptr)
	{
		if (ptr == UIntPtr::Zero)
			return nullptr;

		return gcnew CPed((Native_CPed*)ptr.ToPointer());
	}
	UIntPtr CPed::GetUIntPtr()
	{
		if (!PedPointer)
			return UIntPtr::Zero;

		return UIntPtr(PedPointer);
	}

	CVehicle^ CPed::GetVehicle()
	{
		Native_CVehicle* vehPtr = PedPointer->GetVehicle();

		if (!vehPtr)
			return nullptr;

		return gcnew CVehicle(vehPtr);
	}

	void CPed::ProcessWeaponSwitch()
	{
		m_cNativePed->ProcessWeaponSwitch();
	}
	UIntPtr CPed::GetPadFromPlayer()
	{
		Native_CPad* ptr = PedPointer->GetPadFromPlayer();

		if (!ptr)
			return UIntPtr::Zero;

		return UIntPtr(ptr);
	}
	void CPed::SetHealth(float health, int unk)
	{
		m_cNativePed->SetHealth(health, unk);
	}
	void CPed::AddHealth(float health)
	{
		m_cNativePed->AddHealth(health);
	}
	void CPed::ProcessHeading()
	{
		m_cNativePed->ProcessHeading();
	}

}