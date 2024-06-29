#include "pch.h"
#include "IVPedWeapons.h"

namespace IVSDKDotNet
{

    // - - - Constructor - - -
    IVPedWeapons::IVPedWeapons(PedWeapons* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativePedWeapons = nativePtr;
    }

    // - - - Methods / Functions - - -
    IVPedWeapons^ IVPedWeapons::FromUIntPtr(UIntPtr ptr)
    {
        UINTPTR_ZERO_CHECK_WITH_RETURN(ptr, nullptr);
        return gcnew IVPedWeapons((PedWeapons*)ptr.ToPointer());
    }
    UIntPtr IVPedWeapons::GetUIntPtr()
    {
        NULLPTR_CHECK_WITH_RETURN(NativePedWeapons, UIntPtr::Zero);
        return UIntPtr(NativePedWeapons);
    }

    void IVPedWeapons::GiveWeapon(int weaponType, uint32_t ammoQuantity, bool unk1, bool unk2, bool unk3)
    {
        NULLPTR_CHECK(NativePedWeapons);
        NativePedWeapons->GiveWeapon(weaponType, ammoQuantity, unk1, unk2, unk3);
    }

}