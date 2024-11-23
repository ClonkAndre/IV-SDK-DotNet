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
		property uint32_t RadioState
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeRadioAudioEntity, 0);
				return NativeRadioAudioEntity->m_nRadioState;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeRadioAudioEntity);
				NativeRadioAudioEntity->m_nRadioState = value;
			}
		}
		property uint32_t RadioState2
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeRadioAudioEntity, 0);
				return NativeRadioAudioEntity->m_nRadioState2;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeRadioAudioEntity);
				NativeRadioAudioEntity->m_nRadioState2 = value;
			}
		}

		property uint32_t CurrentRadioStationIndexPriority
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeRadioAudioEntity, 0);
				return NativeRadioAudioEntity->m_nCurrentRadioStationPriority;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeRadioAudioEntity);
				NativeRadioAudioEntity->m_nCurrentRadioStationPriority = value;
			}
		}

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

		property uint32_t StationIndex
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeRadioAudioEntity, 0);
				return NativeRadioAudioEntity->m_nStationIndex;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeRadioAudioEntity);
				NativeRadioAudioEntity->m_nStationIndex = value;
			}
		}

	public:
		static IVAudRadioAudioEntity^ FromUIntPtr(UIntPtr ptr);
		UIntPtr GetUIntPtr();

	internal:
		IVAudRadioAudioEntity(audRadioAudioEntity* nativePtr);

	internal:
		audRadioAudioEntity* NativeRadioAudioEntity;
	};
}