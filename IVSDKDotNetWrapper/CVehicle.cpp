#include "pch.h"
#include "CVehicle.h"

namespace IVSDKDotNet {

	// =========================================================================
	// ============================= CVehicleDoor ==============================
	// =========================================================================
	CVehicleDoor::CVehicleDoor(Native_CVehicleDoor* native)
	{
		m_cVehicleDoor = native;
	}

	// =========================================================================
	// ============================ CVehicleWheel ==============================
	// =========================================================================
	CVehicleWheel::CVehicleWheel(Native_CVehicleWheel* native)
	{
		m_cVehicleWheel = native;
	}

	// =========================================================================
	// =============================== CVehicle ================================
	// =========================================================================
	CVehicle::CVehicle(uint32_t handle, Native_CVehicle* native) : CPhysical(native)
	{
		Handle = handle;
		m_cNativeVehicle = native;
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