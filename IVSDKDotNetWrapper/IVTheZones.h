#pragma once

namespace IVSDKDotNet
{
	public ref class IVTheZones
	{
	public:
		static property uint32_t TotalNumberOfMapZones
		{
		public:
			uint32_t get()
			{
				return CTheZones::TotalNumberOfMapZones;
			}
			void set(uint32_t value)
			{
				CTheZones::TotalNumberOfMapZones = value;
			}
		}
		static property array<IVZone^>^ MapZoneArray
		{
		public:
			array<IVZone^>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(CTheZones::MapZoneArray, nullptr);

				array<IVZone^>^ arr = gcnew array<IVZone^>(TotalNumberOfMapZones);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = gcnew IVZone(&CTheZones::MapZoneArray[i]);

				return arr;
			}
			void set(array<IVZone^>^ value)
			{
				NULLPTR_CHECK(value);
				NULLPTR_CHECK(CTheZones::MapZoneArray);

				for(int i = 0; i < value->Length; i++)
					CTheZones::MapZoneArray[i] = *value[i]->NativeZone;
			}
		}
		static property uint32_t ZonesRevealed
		{
		public:
			uint32_t get()
			{
				return CTheZones::ZonesRevealed;
			}
			void set(uint32_t value)
			{
				CTheZones::ZonesRevealed = value;
			}
		}
		static property array<bool>^ ZonesVisited
		{
		public:
			array<bool>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(CTheZones::ZonesVisited, nullptr);

				array<bool>^ arr = gcnew array<bool>(100);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = CTheZones::ZonesVisited[i];

				return arr;
			}
			void set(array<bool>^ value)
			{
				NULLPTR_CHECK(value);
				NULLPTR_CHECK(CTheZones::ZonesVisited);

				for(int i = 0; i < value->Length; i++)
					CTheZones::ZonesVisited[i] = value[i];
			}
		}

	public:
		static bool Save();
		static bool Load();
	};
}