#include "pch.h"
#include "phInstGta.h"

namespace IVSDKDotNet {

	// =========================================================================
	// ============================= phArchetypeGta ============================
	// =========================================================================
	phArchetypeGta::phArchetypeGta(Native_phArchetypeGta* nativePtr)
	{
		m_cNativeArchetypeGta = nativePtr;
	}


	// =========================================================================
	// ================================= phInst ================================
	// =========================================================================
	phInst::phInst(rage::Native_phInst* nativePtr)
	{
		m_cNativeInst = nativePtr;
	}


	// =========================================================================
	// =============================== gtaFragType ===============================
	// =========================================================================
	gtaFragType::gtaFragType(Native_gtaFragType* nativePtr)
	{
		m_cNativeGtaFragType = nativePtr;
	}


	// =========================================================================
	// =============================== phInstGta ===============================
	// =========================================================================
	phInstGta::phInstGta(Native_phInstGta* nativePtr) : phInst(nativePtr)
	{
		InstGtaPointer = nativePtr;
	}

	phInstGta^ phInstGta::FromPointer(UIntPtr ptr)
	{
		if (ptr == UIntPtr::Zero)
			return nullptr;

		return gcnew phInstGta((Native_phInstGta*)ptr.ToPointer());
	}
	UIntPtr phInstGta::GetUIntPtr()
	{
		if (!InstGtaPointer)
			return UIntPtr::Zero;

		return UIntPtr(InstGtaPointer);
	}

	phInstGta^ phInstGta::DetachFragmentGroup(uint32_t groupId)
	{
		Native_phInstGta* ptr = m_cNativeInstGta->DetachFragmentGroup(groupId);

		if (ptr)
			return gcnew phInstGta(ptr);

		return nullptr;
	}


}