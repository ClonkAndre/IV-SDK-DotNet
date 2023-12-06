#include "pch.h"
#include "IVStoredCar.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVStoredCar::IVStoredCar(CStoredCar* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeStoredCar = nativePtr;
	}

	// - - - Methods / Functions - - -
	void IVStoredCar::StoreCar(UIntPtr pCar)
	{
		NULLPTR_CHECK(NativeStoredCar);
		UINTPTR_ZERO_CHECK(pCar);
		NativeStoredCar->StoreCar((CVehicle*)pCar.ToPointer());
	}
	void IVStoredCar::RestoreCar()
	{
		NULLPTR_CHECK(NativeStoredCar);
		NativeStoredCar->RestoreCar();
	}

}