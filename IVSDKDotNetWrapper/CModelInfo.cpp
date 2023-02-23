#include "pch.h"
#include "CModelInfo.h"

namespace IVSDKDotNet {

	// =========================================================================
	// =========================== CBaseModelInfo ==============================
	// =========================================================================
	CBaseModelInfo::CBaseModelInfo(Native_CBaseModelInfo* nativePtr)
	{
		NativePointer = nativePtr;
	}

	uint8_t CBaseModelInfo::GetModelType()
	{
		return NativePointer->GetModelType();
	}
	void CBaseModelInfo::SetAnimGroup(String^ group)
	{
		msclr::interop::marshal_context ctx;
		NativePointer->SetAnimGroup((char*)ctx.marshal_as<const char*>(group));
	}
	void CBaseModelInfo::SetTexDictionary(String^ txd)
	{
		msclr::interop::marshal_context ctx;
		NativePointer->SetTexDictionary((char*)ctx.marshal_as<const char*>(txd));
	}



	// =========================================================================
	// ============================ CPedModelInfo ==============================
	// =========================================================================
	CPedModelInfo::CPedModelInfo(Native_CPedModelInfo* nativePtr) : CBaseModelInfo(nativePtr)
	{
		NativePointer = nativePtr;
	}



	// =========================================================================
	// ========================== CVehicleStructure ============================
	// =========================================================================
	CVehicleStructure::CVehicleStructure(Native_CVehicleStructure* nativePtr)
	{
		NativePointer = nativePtr;
	}



	// =========================================================================
	// ========================== CVehicleModelInfo ============================
	// =========================================================================
	CVehicleModelInfo::CVehicleModelInfo(Native_CVehicleModelInfo* nativePtr) : CBaseModelInfo(nativePtr)
	{
		NativePointer = nativePtr;
	}

	int CVehicleModelInfo::GetNumberOfSeats(int modelIndex)
	{
		return Native_CVehicleModelInfo::GetNumberOfSeats(modelIndex);
	}

	void CVehicleModelInfo::SetSecondaryAnimGroup(String^ group)
	{
		msclr::interop::marshal_context ctx;
		NativePointer->SetSecondaryAnimGroup((char*)ctx.marshal_as<const char*>(group));
	}



	// =========================================================================
	// ============================== CModelInfo ===============================
	// =========================================================================
	CBaseModelInfo^ CModelInfo::GetModelInfo(uint32_t hashKey, [OutAttribute] int% index)
	{
		int nIndex;
		Native_CBaseModelInfo* ptr = Native_CModelInfo::GetModelInfo(hashKey, &nIndex);

		if (!ptr)
			return nullptr;

		index = nIndex;
		return gcnew CBaseModelInfo(ptr);
	}
	CPedModelInfo^ CModelInfo::AddPedModel(String^ modelName)
	{
		msclr::interop::marshal_context ctx;
		Native_CPedModelInfo* ptr = Native_CModelInfo::AddPedModel((char*)ctx.marshal_as<const char*>(modelName));

		if (!ptr)
			return nullptr;
		
		return gcnew CPedModelInfo(ptr);
	}
	CVehicleModelInfo^ CModelInfo::AddVehicleModel(String^ modelName)
	{
		msclr::interop::marshal_context ctx;
		Native_CVehicleModelInfo* ptr = Native_CModelInfo::AddVehicleModel((char*)ctx.marshal_as<const char*>(modelName));

		if (!ptr)
			return nullptr;

		return gcnew CVehicleModelInfo(ptr);
	}



}