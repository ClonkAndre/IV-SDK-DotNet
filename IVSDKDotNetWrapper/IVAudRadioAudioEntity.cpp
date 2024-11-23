#include "pch.h"
#include "IVAudRadioAudioEntity.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVAudRadioAudioEntity::IVAudRadioAudioEntity(audRadioAudioEntity* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeRadioAudioEntity = nativePtr;
	}

	// - - - Methods / Functions - - -
	IVAudRadioAudioEntity^ IVAudRadioAudioEntity::FromUIntPtr(UIntPtr ptr)
	{
		UINTPTR_ZERO_CHECK_WITH_RETURN(ptr, nullptr);
		return gcnew IVAudRadioAudioEntity((audRadioAudioEntity*)ptr.ToPointer());
	}
	UIntPtr IVAudRadioAudioEntity::GetUIntPtr()
	{
		NULLPTR_CHECK_WITH_RETURN(NativeRadioAudioEntity, UIntPtr::Zero);
		return UIntPtr(NativeRadioAudioEntity);
	}

}