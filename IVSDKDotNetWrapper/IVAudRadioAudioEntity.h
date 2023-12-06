#pragma once

namespace IVSDKDotNet
{
	public ref class IVAudRadioAudioEntity
	{
	public:
		static property IVAudRadioAudioEntity^ TheRadioAudioEntity
		{
		public:
			IVAudRadioAudioEntity^ get()
			{
				audRadioAudioEntity* c = &RadioAudioEntity;
				NULLPTR_CHECK_WITH_RETURN(c, nullptr);

				return gcnew IVAudRadioAudioEntity(c);
			}
			void set(IVAudRadioAudioEntity^ value)
			{
				NULLPTR_CHECK(value);

				audRadioAudioEntity* c = &RadioAudioEntity;
				NULLPTR_CHECK(c);

				NULLPTR_CHECK(value->NativeRadioAudioEntity);
				c = value->NativeRadioAudioEntity;
			}
		}

	public:
		/// <summary>
		/// Gets or sets the index of the current radio station.
		/// </summary>
		property uint32_t CurrentRadioStationIndex
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeRadioAudioEntity, 0);
				return NativeRadioAudioEntity->m_nCurrentRadioStation;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeRadioAudioEntity);
				NativeRadioAudioEntity->m_nCurrentRadioStation = value;
			}
		}

	internal:
		IVAudRadioAudioEntity(audRadioAudioEntity* nativePtr);

	internal:
		audRadioAudioEntity* NativeRadioAudioEntity;
	};
}