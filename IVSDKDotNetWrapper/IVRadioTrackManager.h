#pragma once

namespace IVSDKDotNet
{
	public ref class IVRadioTrackManager
	{
	public:
		/// <summary>
		/// Gets or sets if the lazlow station is locked.
		/// </summary>
		static property bool LazlowStationLocked
		{
		public:
			bool get()
			{
				return CAERadioTrackManager::m_bLazlowStationLocked;
			}
			void set(bool value)
			{
				CAERadioTrackManager::m_bLazlowStationLocked = value;
			}
		}
		/// <summary>
		/// Undocumented.
		/// </summary>
		static property bool TaxiGarageRadioState
		{
		public:
			bool get()
			{
				return CAERadioTrackManager::m_bTaxiGarageRadioState;
			}
			void set(bool value)
			{
				CAERadioTrackManager::m_bTaxiGarageRadioState = value;
			}
		}
		/// <summary>
		/// Gets or sets the number of radio stations.
		/// </summary>
		static property uint32_t NumRadioStations
		{
		public:
			uint32_t get()
			{
				return CAERadioTrackManager::m_nNumRadioStations;
			}
			void set(uint32_t value)
			{
				CAERadioTrackManager::m_nNumRadioStations = value;
			}
		}
		/// <summary>
		/// Gets or sets the array of every radio station there is in the game. Length of this array: 30.
		/// </summary>
		static property array<IVRadioStation^>^ RadioStations
		{
		public:
			array<IVRadioStation^>^ get()
			{
				CRadioStation** allStations = CAERadioTrackManager::m_aRadioStations;
				NULLPTR_CHECK_WITH_RETURN(allStations, nullptr);

				// Create and populate array
				array<IVRadioStation^>^ arr = gcnew array<IVRadioStation^>(30);

				for (int32_t i = 0; i < arr->Length; i++)
				{
					CRadioStation* station = allStations[i];
					
					if (!station)
						continue;

					arr[i] = gcnew IVRadioStation(station);
				}

				return arr;
			}
			void set(array<IVRadioStation^>^ value)
			{
				NULLPTR_CHECK(value);

				CRadioStation** allStations = CAERadioTrackManager::m_aRadioStations;
				NULLPTR_CHECK(allStations);

				// Set array
				for (int32_t i = 0; i < value->Length; i++)
				{
					IVRadioStation^ station = value[i];

					if (!station)
						continue;

					allStations[i] = station->NativeRadioStation;
				}
			}
		}

	public:
		static IVRadioStation^ GetRadioStation(int32_t id);
		static IVRadioStation^ GetRadioStationByName(String^ name);
		static IVRadioStation^ GetRadioStationByHash(uint32_t hash);
	};
}