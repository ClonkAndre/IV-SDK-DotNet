#pragma once

namespace IVSDKDotNet
{
	public value class IVPickup
	{
	public:
		/// <summary>
		/// Something timer related. But doesn't get used that often.
		/// </summary>
		property uint32_t field_0
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, 0);
				return NativePickup->field_0;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->field_0 = value;
			}
		}
		/// <summary>
		/// Pointer to the IVObject which is created for the pickup.
		/// </summary>
		property UIntPtr WorldObject
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, UIntPtr::Zero);
				return UIntPtr(NativePickup->m_pWorldObject);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->m_pWorldObject = value.ToUInt32();
			}
		}
		/// <summary>
		/// Seems to be related to interiors.
		/// </summary>
		property uint32_t field_8
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, 0);
				return NativePickup->field_8;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->field_8 = value;
			}
		}
		/// <summary>
		/// The key of the room this pickup is in.
		/// </summary>
		property uint32_t RoomKey
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, 0);
				return NativePickup->m_nRoomKey;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->m_nRoomKey = value;
			}
		}
		/// <summary>
		/// The handle of the blip attached to this pickup.
		/// </summary>
		property int32_t Blip
		{
		public:
			int32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, 0);
				return NativePickup->m_nBlip;
			}
			void set(int32_t value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->m_nBlip = value;
			}
		}
		/// <summary>
		/// The total game time in milliseconds when the pickup was last picked up.
		/// </summary>
		property int32_t LastPickedUpTime
		{
		public:
			int32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, 0);
				return NativePickup->m_nLastPickedUpTime;
			}
			void set(int32_t value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->m_nLastPickedUpTime = value;
			}
		}
		/// <summary>
		/// The pickup position.
		/// </summary>
		property Vector3 Position
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, Vector3::Zero);
				return CVectorToVector3(NativePickup->m_vPosition);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->m_vPosition = Vector3ToCVector(value);
			}
		}
		/// <summary>
		/// The index of the model of this pickup.
		/// </summary>
		property int16_t ModelIndex
		{
			int16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, 0);
				return NativePickup->m_nModelIndex;
			}
			void set(int16_t value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->m_nModelIndex = value;
			}
		}
		/// <summary>
		/// Some important index.
		/// </summary>
		property uint16_t field_42
		{
			uint16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, 0);
				return NativePickup->field_42;
			}
			void set(uint16_t value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->field_42 = value;
			}
		}
		/// <summary>
		/// The pickup type.
		/// </summary>
		property uint8_t Type
		{
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, 0);
				return NativePickup->m_nType;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->m_nType = value;
			}
		}

	public:
		static IVPickup^ FromUIntPtr(UIntPtr ptr);
		UIntPtr GetUIntPtr();

		/// <summary>
		/// Gets rid of this pickup and also of the attached blip if it has one.
		/// </summary>
		/// <returns>Something.</returns>
		int Destroy();

	internal:
		IVPickup(CPickup* nativePtr);

	internal:
		CPickup* NativePickup;
	};

	public ref class IVPickups
	{
	public:
		/// <summary>
		/// Contains all registered pickups.
		/// </summary>
		static property array<IVPickup>^ Pickups
		{
		public:
			array<IVPickup>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(CPickups::Pickups, nullptr);

				array<IVPickup>^ arr = gcnew array<IVPickup>(1500);

				for (int i = 0; i < arr->Length; i++)
				{
					CPickup* ptr = &CPickups::Pickups[i];

					if (!ptr)
						continue;

					arr[i] = IVPickup(ptr);
				}

				return arr;
			}
			void set(array<IVPickup>^ value)
			{
				NULLPTR_CHECK(value);
				NULLPTR_CHECK(CPickups::Pickups);

				for (int i = 0; i < value->Length; i++)
				{
					CPickups::Pickups[i] = *value[i].NativePickup;
				}
			}
		}
		/// <summary>
		/// Seemingly only contains the pickup types.
		/// You should use the "GetTypeOfPickup" function if you want to get the type of a pickup.
		/// </summary>
		static property array<char>^ PickupTypes
		{
		public:
			array<char>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(CPickups::PickupTypes, nullptr);

				array<char>^ arr = gcnew array<char>(1500);

				for (int i = 0; i < arr->Length; i++)
					arr[i] = CPickups::PickupTypes[i];

				return arr;
			}
			void set(array<char>^ value)
			{
				//NULLPTR_CHECK(value);
				//NULLPTR_CHECK(CPickups::Pickups);

				//for (int i = 0; i < value->Length; i++)
				//{
				//	IVPickup^ obj = value[i];

				//	if (!obj)
				//	{
				//		continue;
				//	}

				//	CPickups::Pickups[i] = obj->NativePickup;
				//}
			}
		}

	public:
		/// <summary>
		/// Destroys all pickups.
		/// </summary>
		/// <returns>Something.</returns>
		static int Shutdown();
		/// <summary>
		/// Removes and resets all pickups (not the actual pickup object).
		/// It also resets all the settings related with pickups to their default value.
		/// </summary>
		/// <returns>Always 0</returns>
		static int Reset();
		
		/// <summary>
		/// Converts the pickup index to an actual handle so it can be used with native functions.
		/// </summary>
		/// <param name="index">The index of the pickup in the array of pickups.</param>
		/// <returns>If successful, the handle is returned. Otherwise, -1.</returns>
		static int ConvertIndexToHandle(int32_t index);

		/// <summary>
		/// Creates a new pickup.
		/// </summary>
		/// <param name="position">The position where to create the pickup.</param>
		/// <param name="rotation">The rotation of the pickup.</param>
		/// <param name="modelIndex">The model index (not the hash) of the object to create for this pickup. You also dont need to request the model first as GTA will handle it for you.</param>
		/// <param name="type">The pickup type.</param>
		/// <param name="a5">Unknown.</param>
		/// <param name="a6">Unknown.</param>
		/// <param name="a7_maybeBlipRelated"></param>
		/// <param name="objPointerMaybe"></param>
		/// <param name="a12">Unknown.</param>
		/// <param name="a13">Unknown.</param>
		/// <returns>The handle of the pickup created. Returns -1 if the pickup could not be created.</returns>
		static int CreatePickup(Vector3 position, Vector3 rotation, int modelIndex, int type, bool a5, bool a6, bool a7_maybeBlipRelated, uint32_t objPointerMaybe, char a12, char a13);
		/// <summary>
		/// Removes a pickup with the given handle.
		/// </summary>
		/// <param name="handle">The handle of the pickup to remove.</param>
		/// <returns>The index of the removed pickup, or -1 if the pickup couldn't get removed.</returns>
		static int RemovePickup(int handle);
		
		/// <summary>
		/// Creates a temporary radar blip for each pickup within the range around the given position.
		/// </summary>
		/// <param name="position">The position of where to check for pickups.</param>
		/// <param name="range">The range to check for pickups around the given position.</param>
		/// <param name="type">The pickup type to look for.</param>
		static void CreateTemporaryRadarBlipsForPickupsInArea(Vector3 position, float range, int type);

		/// <summary>
		/// Creates a temporary radar blip for the given pickup only.
		/// </summary>
		/// <param name="position">The position of where the blip should be created.</param>
		/// <param name="pickupIndex">The index of the pickup to assign this blip to.</param>
		/// <returns>The index of the created blip, or -1 if the blip couldn't get created.</returns>
		static int CreateTemporaryRadarBlipForPickup(Vector3 position, int pickupIndex);

		/// <summary>
		/// Removes all temporary radar blip.
		/// </summary>
		static void RemoveTemporaryRadarBlipsForPickups();

		/// <summary>
		/// Does the pickup glow thing.
		/// </summary>
		static void DoPickUpEffects();

		// Helper functions
		/// <summary>
		/// Retrieves the type of the pickup at the given index from the "PickupTypes" array.
		/// </summary>
		/// <param name="index">The index of where the pickup is placed at in the "Pickups" array to get the type from.</param>
		/// <returns>The type of the pickup at the given index.</returns>
		static uint8_t GetTypeOfPickup(int index);

	};
}