#include "pch.h"
#include "IVPedWeaponSlot.h"

namespace IVSDKDotNet
{
	// - - - Constructor - - -
	IVPedWeaponSlot::IVPedWeaponSlot(PedWeaponSlot* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativePedWeaponSlot = nativePtr;
	}
}