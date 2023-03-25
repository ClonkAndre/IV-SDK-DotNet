#include "pch.h"
#include "CHandlingDataMgr.h"

namespace IVSDKDotNet {

	// =========================================================================
	// ============================ tHandlingData ==============================
	// =========================================================================
	tHandlingData::tHandlingData(Native_tHandlingData* nativePtr)
	{
		HandlingDataPointer = nativePtr;
		TheModelFlags = gcnew ModelFlags(this);
		TheHandlingFlags = gcnew HandlingFlags(this);
	}

	tHandlingData^ tHandlingData::FromPointer(UIntPtr ptr)
	{
		if (ptr == UIntPtr::Zero)
			return nullptr;

		return gcnew tHandlingData((Native_tHandlingData*)ptr.ToPointer());
	}
	UIntPtr tHandlingData::GetUIntPtr()
	{
		if (!HandlingDataPointer)
			return UIntPtr::Zero;

		return UIntPtr(HandlingDataPointer);
	}

	// =========================================================================
	// ====================== tHandlingData.ModelFlags =========================
	// =========================================================================
	tHandlingData::ModelFlags::ModelFlags(tHandlingData^ parent)
	{
		m_cParent = parent;
	}


	// =========================================================================
	// ===================== tHandlingData.HandlingFlags =======================
	// =========================================================================
	tHandlingData::HandlingFlags::HandlingFlags(tHandlingData^ parent)
	{
		m_cParent = parent;
	}


	// =========================================================================
	// =========================== CHandlingDataMgr ============================
	// =========================================================================
	void CHandlingDataMgr::Initialise()
	{
		Native_CHandlingDataMgr::Initialise();
	}
	void CHandlingDataMgr::LoadHandlingData(String^ sPath)
	{
		msclr::interop::marshal_context ctx;
		Native_CHandlingDataMgr::LoadHandlingData((char*)ctx.marshal_as<const char*>(sPath));
	}
	tHandlingData^ CHandlingDataMgr::GetHandlingData(int id)
	{
		Native_tHandlingData* ptr = Native_CHandlingDataMgr::GetHandlingData(id);

		if (ptr)
			return gcnew tHandlingData(ptr);

		return nullptr;
	}
	int CHandlingDataMgr::GetHandlingId(String^ handlingName)
	{
		msclr::interop::marshal_context ctx;
		return Native_CHandlingDataMgr::GetHandlingId((char*)ctx.marshal_as<const char*>(handlingName));
	}


}