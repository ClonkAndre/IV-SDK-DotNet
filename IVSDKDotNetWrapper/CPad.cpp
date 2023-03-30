#include "pch.h"
#include "CPad.h"

namespace IVSDKDotNet {

	// =========================================================================
	// ========================== tValueHistoryItem ============================
	// =========================================================================
	tValueHistoryItem::tValueHistoryItem(Native_tValueHistoryItem* nativePtr)
	{
		ValueHistoryItemPointer = nativePtr;
	}


	// =========================================================================
	// ============================ tValueHistory ==============================
	// =========================================================================
	tValueHistory::tValueHistory(Native_tValueHistory* nativePtr)
	{
		m_cNativeValueHistory = nativePtr;
	}


	// =========================================================================
	// ============================== tPadValues ===============================
	// =========================================================================
	tPadValues::tPadValues(Native_tPadValues* nativePtr)
	{
		PadValuePointer = nativePtr;
	}


	// =========================================================================
	// ================================= CPad ==================================
	// =========================================================================
	CPad::CPad(Native_CPad* nativePtr)
	{
		PadPointer = nativePtr;
	}

	CPad^ CPad::FromPointer(UIntPtr ptr)
	{
		if (ptr == UIntPtr::Zero)
			return nullptr;

		return gcnew CPad((Native_CPad*)ptr.ToPointer());
	}
	UIntPtr CPad::GetUIntPtr()
	{
		if (!PadPointer)
			return UIntPtr::Zero;

		return UIntPtr(PadPointer);
	}

	CPad^ CPad::GetPad()
	{
		Native_CPad* ptr = Native_CPad::GetPad();

		if (ptr)
			return gcnew CPad(ptr);

		return nullptr;
	}

}