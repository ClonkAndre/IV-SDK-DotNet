#include "pch.h"
#include "CVehicle.h"

namespace IVSDKDotNet {

	// =========================================================================
	// ============================= CVehicleDoor ==============================
	// =========================================================================
	CVehicleDoor::CVehicleDoor(Native_CVehicleDoor* nativePtr)
	{
		m_cVehicleDoor = nativePtr;
	}

	// =========================================================================
	// ============================ CVehicleWheel ==============================
	// =========================================================================
	CVehicleWheel::CVehicleWheel(Native_CVehicleWheel* nativePtr)
	{
		m_cVehicleWheel = nativePtr;
	}

	// =========================================================================
	// =============================== CVehicle ================================
	// =========================================================================
	CVehicle::CVehicle(Native_CVehicle* nativePtr) : CPhysical(nativePtr)
	{
		VehiclePointer = nativePtr;
	}

	CVehicle^ CVehicle::FromPointer(UIntPtr ptr)
	{
		if (ptr == UIntPtr::Zero)
			return nullptr;

		return gcnew CVehicle((Native_CVehicle*)ptr.ToPointer());
	}
	UIntPtr CVehicle::GetUIntPtr()
	{
		if (!VehiclePointer)
			return UIntPtr::Zero;

		return UIntPtr(VehiclePointer);
	}

	// Statics
	float CVehicle::HeightAboveCeiling(float height, int flightModel)
	{
		return Native_CVehicle::HeightAboveCeiling(height, flightModel);
	}
	bool CVehicle::UsesSiren(int32_t id)
	{
		return Native_CVehicle::UsesSiren(id);
	}

	// Non-statics
	void CVehicle::Fix()
	{
		m_cNativeVehicle->Fix();
	}
	void CVehicle::MakeDirty()
	{
		m_cNativeVehicle->MakeDirty();
	}
	void CVehicle::GetVehicleLightsStatus()
	{
		m_cNativeVehicle->GetVehicleLightsStatus();
	}
	void CVehicle::ProcessRespot(float delta)
	{
		m_cNativeVehicle->ProcessRespot(delta);
	}
	void CVehicle::ProcessAirControl(IntPtr unk)
	{
		m_cNativeVehicle->ProcessAirControl(unk.ToPointer());
	}

	int CVehicle::GetSeatPartId(int seat)
	{
		return m_cNativeVehicle->GetSeatPartId(seat);
	}
	bool CVehicle::GetCameraType([OutAttribute] eVehicleCameraType% type)
	{
		int iType;
		bool result = m_cNativeVehicle->GetCameraType(&iType);
		type = (eVehicleCameraType)iType;
		return result;
	}


}