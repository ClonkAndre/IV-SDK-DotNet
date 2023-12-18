#include "pch.h"
#include "IVGarage.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVGarage::IVGarage(CGarage* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeGarage = nativePtr;
	}

	// - - - Method / Functions - - -
	bool IVGarage::IsPointInsideGarage(Vector3 point)
	{
		NULLPTR_CHECK_WITH_RETURN(NativeGarage, false);

		CVector vec;
		vec.x = point.X;
		vec.y = point.Y;
		vec.z = point.Z;

		return NativeGarage->IsPointInsideGarage(vec);
	}
	void IVGarage::PlayerArrestedOrDied()
	{
		NULLPTR_CHECK(NativeGarage);
		NativeGarage->PlayerArrestedOrDied();
	}
	void IVGarage::StoreAndRemoveCarsForThisHideOut(IVStoredCar^ aStoredCars, bool unk)
	{
		NULLPTR_CHECK(NativeGarage);
		// TODO
	}
	void IVGarage::TidyUpGarageClose()
	{
		NULLPTR_CHECK(NativeGarage);
		NativeGarage->TidyUpGarageClose();
	}
	void IVGarage::Update()
	{
		NULLPTR_CHECK(NativeGarage);
		NativeGarage->Update();
	}

}