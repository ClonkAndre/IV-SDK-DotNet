#include "pch.h"
#include "IVPed.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVPedFlags::IVPedFlags(CPed* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativePed = nativePtr;
	}
	IVPedFlags2::IVPedFlags2(CPed* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativePed = nativePtr;
	}
	IVPed::IVPed(CPed* nativePtr) : IVPhysical(nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativePed = nativePtr;
	}

	// - - - Methods / Functions - - -
	IVPed^ IVPed::FromUIntPtr(UIntPtr ptr)
	{
		UINTPTR_ZERO_CHECK_WITH_RETURN(ptr, nullptr);
		return gcnew IVPed((CPed*)ptr.ToPointer());
	}
	UIntPtr IVPed::GetUIntPtr()
	{
		NULLPTR_CHECK_WITH_RETURN(NativePed, UIntPtr::Zero);
		return UIntPtr(NativePed);
	}

	void IVPed::ProcessWeaponSwitch()
	{
		NULLPTR_CHECK(NativePed);
		NativePed->ProcessWeaponSwitch();
	}
	IVPad^ IVPed::GetPadFromPlayer()
	{
		NULLPTR_CHECK_WITH_RETURN(NativePed, nullptr);

		CPad* ptr = NativePed->GetPadFromPlayer();
		NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);

		return gcnew IVPad(ptr);
	}
	UIntPtr IVPed::GetVehicle()
	{
		NULLPTR_CHECK_WITH_RETURN(NativePed, UIntPtr::Zero);

		CVehicle* ptr = NativePed->GetVehicle();
		NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);

		return UIntPtr(ptr);
	}
	void IVPed::SetHealth(float health, int unk)
	{
		NULLPTR_CHECK(NativePed);
		NativePed->SetHealth(health, unk);
	}
	void IVPed::AddHealth(float health)
	{
		NULLPTR_CHECK(NativePed);
		NativePed->AddHealth(health);
	}
	void IVPed::ProcessHeading()
	{
		NULLPTR_CHECK(NativePed);
		NativePed->ProcessHeading();
	}

}