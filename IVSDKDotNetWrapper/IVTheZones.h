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

		/// <summary>
		/// Resets all the zones in the array leaving only the LIBERTY zone.
		/// </summary>
		/// <returns>A UIntPtr holding the pointer to the zones array.</returns>
		static UIntPtr Reset()
		{
			return UIntPtr(CTheZones::Reset());
		}

		/// <summary>
		/// Adds a new zone defined by its name, minimum and maximum coordinates, and an additional string parameter.
		/// </summary>
		/// <param name="infoLabel">The name of the zone.</param>
		/// <param name="textLabel">The display name GXT label of the zone.</param>
		/// <param name="min">The minimum coordinates (Vector3) of the zone.</param>
		/// <param name="max">The maximum coordinates (Vector3) of the zone.</param>
		/// <returns>Probably the index of the next slot in the zones array.</returns>
		static int Add(String^ infoLabel, String^ textLabel, Vector3 min, Vector3 max)
		{
			if (String::IsNullOrWhiteSpace(infoLabel))
				return -1;
			if (String::IsNullOrWhiteSpace(textLabel))
				return -1;

			msclr::interop::marshal_context ctx;
			return CTheZones::Add(ctx.marshal_as<const char*>(infoLabel), min.X, min.Y, min.Z, max.X, max.Y, max.Z, ctx.marshal_as<const char*>(textLabel));
		}
		/// <summary>
		/// Adds a new zone defined by its name, minimum and maximum coordinates, and an additional string parameter.
		/// </summary>
		/// <param name="infoLabel">The name of the zone.</param>
		/// <param name="textLabel">The display name GXT label of the zone.</param>
		/// <param name="minX">The minimum X coordinate of the zone.</param>
		/// <param name="minY">The minimum Y coordinate of the zone.</param>
		/// <param name="minZ">The minimum Z coordinate of the zone.</param>
		/// <param name="maxX">The maximum X coordinate of the zone.</param>
		/// <param name="maxY">The maximum Y coordinate of the zone.</param>
		/// <param name="maxZ">The maximum Z coordinate of the zone.</param>
		/// <returns>Probably the index of the next slot in the zones array.</returns>
		static int Add(String^ infoLabel, String^ textLabel, float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
		{
			return Add(infoLabel, textLabel, Vector3(minX, minY, minZ), Vector3(maxX, maxY, maxZ));
		}

		/// <summary>
		/// Retrieves the name of the zone corresponding to the given 3D coordinates.
		/// </summary>
		/// <param name="vec">A Vector3 representing the coordinates for which to find the zone name.</param>
		/// <returns>The name of the zone at the specified coordinates.</returns>
		static String^ GetZoneNameByCoords(Vector3 vec)
		{
			const char* name = CTheZones::GetZoneNameByCoords(&Vector3ToCVector(vec));

			if (!name)
				return String::Empty;

			return gcnew String(name);
		}

		/// <summary>
		/// Retrieves the zone name corresponding to the specified index.
		/// </summary>
		/// <param name="index">The index of the zone whose name is to be retrieved.</param>
		/// <returns>The name of the zone.</returns>
		static String^ GetZoneNameByIndex(int index)
		{
			const char* name = CTheZones::GetZoneNameByIndex(index);
			
			if (!name)
				return String::Empty;

			return gcnew String(name);
		}

		/// <summary>
		/// Gets the index in the zones array which corresponds to the specified zone name.
		/// </summary>
		/// <param name="name">The name of the zone to get the array index from.</param>
		/// <returns>The index of the zone in the array associated with the given name, or -1 if the zone could not be found, the name is null, empty, or consists only of whitespace.</returns>
		static int GetZoneNumberByName(String^ name)
		{
			if (String::IsNullOrWhiteSpace(name))
				return -1;

			msclr::interop::marshal_context ctx;
			return CTheZones::GetZoneNumberByName(ctx.marshal_as<const char*>(name));
		}

		/// <summary>
		/// Determines whether a given 3D point is inside a specified zone.
		/// </summary>
		/// <param name="vec">The 3D point to test.</param>
		/// <param name="zone">A pointer or reference to the zone in which to check for the point.</param>
		/// <returns>true if the point is inside the specified zone; otherwise, false.</returns>
		static bool IsPointInZone(Vector3 vec, IVZone^ zone)
		{
			if (!zone)
				return false;

			return CTheZones::IsPointInZone(&Vector3ToCVector(vec), zone->NativeZone);
		}

	};
}