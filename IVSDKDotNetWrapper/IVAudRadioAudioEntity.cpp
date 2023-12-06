#include "pch.h"
#include "IVAudRadioAudioEntity.h"

namespace IVSDKDotNet
{
	IVAudRadioAudioEntity::IVAudRadioAudioEntity(audRadioAudioEntity* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeRadioAudioEntity = nativePtr;
	}
}