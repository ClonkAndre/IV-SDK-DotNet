#include "CTasks.h"
#include "pch.h"

namespace IVSDKDotNet {

	// =========================================================================
	// =========================== CTaskComplexDie =============================
	// =========================================================================
	UIntPtr CTaskComplexDie::Create(uint32_t unk, uint32_t unk2, uint32_t unk3_44, uint32_t unk4_190, float fBlendDelta, float fAnimSpeed, uint32_t unk5_1)
	{
		Native_CTaskComplexDie* task = new Native_CTaskComplexDie(unk, unk2, unk3_44, unk4_190, fBlendDelta, fAnimSpeed, unk5_1);

		if (!task)
			return UIntPtr::Zero;

		return UIntPtr(task);
	}

	// =========================================================================
	// ===================== CTaskComplexMobileMakeCall ========================
	// =========================================================================
	UIntPtr CTaskComplexMobileMakeCall::Create(String^ speechLine, bool bUnk1, bool bUnk2)
	{
		msclr::interop::marshal_context ctx;
		Native_CTaskComplexMobileMakeCall* task = new Native_CTaskComplexMobileMakeCall((char*)ctx.marshal_as<const char*>(speechLine), bUnk1, bUnk2);

		if (!task)
			return UIntPtr::Zero;

		return UIntPtr(task);
	}

	// =========================================================================
	// ==================== CTaskComplexNewGetInVehicle ========================
	// =========================================================================
	UIntPtr CTaskComplexNewGetInVehicle::Create(CVehicle^ veh, eNewGetInVehicleType getInType, uint32_t unk27, int32_t unk, float fUnk)
	{
		if (!veh)
			return UIntPtr::Zero;

		Native_CTaskComplexNewGetInVehicle* task = new Native_CTaskComplexNewGetInVehicle(veh->VehiclePointer, (int32_t)getInType, unk27, unk, fUnk);

		if (!task)
			return UIntPtr::Zero;

		return UIntPtr(task);
	}

	// =========================================================================
	// =========================== CTaskComplexNM ==============================
	// =========================================================================
	UIntPtr CTaskComplexNM::Create(uint32_t nUnk, uint32_t nUnk2, UIntPtr pSubTask, float fUnk)
	{
		if (pSubTask == UIntPtr::Zero)
			return UIntPtr::Zero;

		Native_CTaskComplexNM* task = new Native_CTaskComplexNM(nUnk, nUnk2, (uint32_t*)pSubTask.ToPointer(), fUnk);

		if (!task)
			return UIntPtr::Zero;

		return UIntPtr(task);
	}

	// =========================================================================
	// ===================== CTaskComplexPlayerOnFoot ==========================
	// =========================================================================
	UIntPtr CTaskComplexPlayerOnFoot::Create()
	{
		Native_CTaskComplexPlayerOnFoot* task = new Native_CTaskComplexPlayerOnFoot();

		if (!task)
			return UIntPtr::Zero;

		return UIntPtr(task);
	}

	// =========================================================================
	// ======================= CTaskSimpleNMHighFall ===========================
	// =========================================================================
	UIntPtr CTaskSimpleNMHighFall::Create(uint32_t nUnk, uint32_t nUnk2, uint32_t nUnk3, uint32_t nUnk4)
	{
		Native_CTaskSimpleNMHighFall* task = new Native_CTaskSimpleNMHighFall(nUnk, nUnk2, nUnk3, nUnk4);

		if (!task)
			return UIntPtr::Zero;

		return UIntPtr(task);
	}

	// =========================================================================
	// =============== CTaskSimpleNMJumpRollFromRoadVehicle ====================
	// =========================================================================
	UIntPtr CTaskSimpleNMJumpRollFromRoadVehicle::Create(uint32_t time, uint32_t time2)
	{
		Native_CTaskSimpleNMJumpRollFromRoadVehicle* task = new Native_CTaskSimpleNMJumpRollFromRoadVehicle(time, time2);

		if (!task)
			return UIntPtr::Zero;

		return UIntPtr(task);
	}

	// =========================================================================
	// ======================= CTaskSimpleSidewaysDive =========================
	// =========================================================================
	UIntPtr CTaskSimpleSidewaysDive::Create(bool bDirection)
	{
		Native_CTaskSimpleSidewaysDive* task = new Native_CTaskSimpleSidewaysDive(bDirection);

		if (!task)
			return UIntPtr::Zero;

		return UIntPtr(task);
	}

	// =========================================================================
	// ======================= CTaskComplexClimbLadder =========================
	// =========================================================================
	UIntPtr CTaskComplexClimbLadder::Create(CObject^ ladder, int32_t type, uint32_t unk0)
	{
		Native_CTaskComplexClimbLadder* task = new Native_CTaskComplexClimbLadder(ladder->ObjectPointer, type, unk0);

		if (!task)
			return UIntPtr::Zero;

		return UIntPtr(task);
	}

	// =========================================================================
	// ========================= CTaskComplexInWater ===========================
	// =========================================================================
	UIntPtr CTaskComplexInWater::Create(uint32_t unk, uint32_t unk2, bool bUnk)
	{
		Native_CTaskComplexInWater* task = new Native_CTaskComplexInWater(unk, unk2, bUnk);

		if (!task)
			return UIntPtr::Zero;

		return UIntPtr(task);
	}

	// =========================================================================
	// ========================== CTaskComplexWander ===========================
	// =========================================================================
	UIntPtr CTaskComplexWander::Create(uint32_t moveState, float initialDir, bool bSensibly, float targetRadius, uint32_t unk1)
	{
		Native_CTaskComplexWander* task = new Native_CTaskComplexWander(moveState, initialDir, bSensibly, targetRadius, unk1);

		if (!task)
			return UIntPtr::Zero;

		return UIntPtr(task);
	}

	// =========================================================================
	// ====================== CTaskComplexWanderStandard =======================
	// =========================================================================
	UIntPtr CTaskComplexWanderStandard::Create(uint32_t moveState, float initialDir, bool bSensibly, float targetRadius, uint32_t unk1)
	{
		Native_CTaskComplexWanderStandard* task = new Native_CTaskComplexWanderStandard(moveState, initialDir, bSensibly, targetRadius, unk1);

		if (!task)
			return UIntPtr::Zero;

		return UIntPtr(task);
	}

	// =========================================================================
	// ==================== CTaskComplexPlayerSettingsTask =====================
	// =========================================================================
	UIntPtr CTaskComplexPlayerSettingsTask::Create(uint32_t unkFromPed)
	{
		Native_CTaskComplexPlayerSettingsTask* task = new Native_CTaskComplexPlayerSettingsTask(unkFromPed);

		if (!task)
			return UIntPtr::Zero;

		return UIntPtr(task);
	}

}