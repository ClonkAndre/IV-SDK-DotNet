#pragma once

namespace IVSDKDotNet
{
	public ref class IVPickup
	{
	public:
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
		property uint32_t field_4
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, 0);
				return NativePickup->field_4;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->field_4 = value;
			}
		}
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
		property uint32_t roomHash
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, 0);
				return NativePickup->roomHash;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->roomHash = value;
			}
		}
		property uint16_t blip
		{
		public:
			uint16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, 0);
				return NativePickup->blip;
			}
			void set(uint16_t value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->blip = value;
			}
		}
		property uint32_t field_14
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, 0);
				return NativePickup->field_14;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->field_14 = value;
			}
		}
		property Vector3 pos
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, Vector3::Zero);
				return CVectorToVector3(NativePickup->pos);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->pos = Vector3ToCVector(value);
			}
		}
		property uint32_t field_24
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, 0);
				return NativePickup->field_24;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->field_24 = value;
			}
		}
		property uint32_t field_28
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, 0);
				return NativePickup->field_28;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->field_28 = value;
			}
		}
		property uint32_t field_2C
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, 0);
				return NativePickup->field_2C;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->field_2C = value;
			}
		}
		property uint32_t field_30
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, 0);
				return NativePickup->field_30;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->field_30 = value;
			}
		}
		property uint32_t field_34
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, 0);
				return NativePickup->field_34;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->field_34 = value;
			}
		}
		property uint32_t field_38
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, 0);
				return NativePickup->field_38;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->field_38 = value;
			}
		}
		property uint16_t field_3C
		{
		public:
			uint16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, 0);
				return NativePickup->field_3C;
			}
			void set(uint16_t value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->field_3C = value;
			}
		}
		property uint32_t field_40
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, 0);
				return NativePickup->field_40;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->field_40 = value;
			}
		}
		property uint16_t field_42
		{
		public:
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
		property uint16_t type
		{
		public:
			uint16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, 0);
				return NativePickup->type;
			}
			void set(uint16_t value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->type = value;
			}
		}
		property uint8_t field_45
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, 0);
				return NativePickup->field_45;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->field_45 = value;
			}
		}
		property uint8_t field_46
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, 0);
				return NativePickup->field_46;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->field_46 = value;
			}
		}
		property uint8_t field_47
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, 0);
				return NativePickup->field_47;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->field_47 = value;
			}
		}
		property uint8_t field_48
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, 0);
				return NativePickup->field_48;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->field_48 = value;
			}
		}
		property uint8_t field_49
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, 0);
				return NativePickup->field_49;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->field_49 = value;
			}
		}
		property uint8_t field_4A
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, 0);
				return NativePickup->field_4A;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->field_4A = value;
			}
		}
		property uint8_t field_4B
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, 0);
				return NativePickup->field_4B;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->field_4B = value;
			}
		}
		property uint8_t field_4C
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativePickup, 0);
				return NativePickup->field_4C;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativePickup);
				NativePickup->field_4C = value;
			}
		}

	public:
		static IVPickup^ FromUIntPtr(UIntPtr ptr);
		UIntPtr GetUIntPtr();

		int Destroy();

	internal:
		IVPickup(CPickup* nativePtr);

	internal:
		CPickup* NativePickup;
	};

	public ref class IVPickups
	{
	public:
		static property array<IVPickup^>^ Pickups
		{
		public:
			array<IVPickup^>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(CPickups::Pickups, nullptr);

				array<IVPickup^>^ arr = gcnew array<IVPickup^>(1500);

				for (int i = 0; i < arr->Length; i++)
				{
					CPickup* ptr = &CPickups::Pickups[i];

					if (!ptr)
						continue;

					arr[i] = gcnew IVPickup(ptr);
				}

				return arr;
			}
			void set(array<IVPickup^>^ value)
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
		/// <returns></returns>
		static int Shutdown();
		/// <summary>
		/// Removes and resets all pickups (not the actual pickup object).
		/// It also resets all the settings related with pickups to their default value.
		/// </summary>
		/// <returns>Always 0</returns>
		static int Reset();
		
		/// <summary>
		/// Creates a new pickup.
		/// </summary>
		/// <param name="position">The position where to create the pickup.</param>
		/// <param name="rotation">The rotation of the pickup.</param>
		/// <param name="modelIndex">The model index (not the hash) of the object to create for this pickup. You also dont need to request the model first as GTA will handle it for you.</param>
		/// <param name="type">The pickup type.</param>
		/// <param name="a5"></param>
		/// <param name="a6"></param>
		/// <param name="a7_maybeBlipRelated"></param>
		/// <param name="objPointerMaybe"></param>
		/// <param name="a12"></param>
		/// <param name="a13"></param>
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
		/// <param name="pos">The position of where to check for pickups.</param>
		/// <param name="range">The range to check for pickups around the given position.</param>
		/// <param name="type">The pickup type to look for.</param>
		static void CreateTemporaryRadarBlipsForPickupsInArea(Vector3 pos, float range, int type);
		/// <summary>
		/// Removes all temporary radar blip.
		/// </summary>
		static void RemoveTemporaryRadarBlipsForPickups();

		/// <summary>
		/// Does the pickup glow thing.
		/// </summary>
		static void DoPickUpEffects();

		static uint8_t GetTypeOfPickup(int index)
		{
			return CPickups::PickupTypes[0x50 * index];
		}

	};
}