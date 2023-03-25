#include "pch.h"
#include "CDraw.h"

namespace IVSDKDotNet {

	// =========================================================================
	// ============================= tViewportData =============================
	// =========================================================================
	tViewportData::tViewportData(Native_tViewportData* nativePtr)
	{
		m_cNativeViewportData = nativePtr;
	}


	// =========================================================================
	// ============================== CViewport ================================
	// =========================================================================
	CViewport::CViewport(Native_CViewport* nativePtr)
	{
		m_cNativeViewport = nativePtr;
	}


	// =========================================================================
	// ======================== CViewportPrimaryOrtho ==========================
	// =========================================================================
	CViewportPrimaryOrtho::CViewportPrimaryOrtho(Native_CViewportPrimaryOrtho* nativePtr) : CViewport(nativePtr)
	{

	}


	// =========================================================================
	// ============================ CViewportGame ==============================
	// =========================================================================
	CViewportGame::CViewportGame(Native_CViewportGame* nativePtr) : CViewport(nativePtr)
	{

	}


	// =========================================================================
	// =========================== CViewportRadar ==============================
	// =========================================================================
	CViewportRadar::CViewportRadar(Native_CViewportRadar* nativePtr) : CViewport(nativePtr)
	{

	}


	// =========================================================================
	// ========================= CViewportMobilePhone ==========================
	// =========================================================================
	CViewportMobilePhone::CViewportMobilePhone(Native_CViewportMobilePhone* nativePtr) : CViewport(nativePtr)
	{

	}


	// =========================================================================
	// ============================= tGlobalScene ==============================
	// =========================================================================
	tGlobalScene::tGlobalScene(Native_tGlobalScene* nativePtr)
	{
		m_cGlobalScene = nativePtr;
	}


	// =========================================================================
	// ================================= CDraw =================================
	// =========================================================================
	CDraw::CDraw(Native_CDraw* nativePtr)
	{
		m_cNativeCDraw = nativePtr;
	}

	CDraw^ CDraw::Get()
	{
		Native_CDraw* ptr = &AddressSetter::GetRef<Native_CDraw>(0xCF47E0, 0xDF8280);;

		if (ptr)
			return gcnew CDraw(ptr);

		return nullptr;
	}

	float CDraw::CalculateAspectRatio(bool bUnk)
	{
		return m_cNativeCDraw->CalculateAspectRatio(bUnk);
	}

}