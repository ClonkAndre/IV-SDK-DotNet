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

	public:
		static int Shutdown();
		/// <summary>
		/// Removes and resets all pickups (not the actual pickup object).
		/// It also resets all the settings related with pickups to their default value.
		/// </summary>
		/// <returns>Always 0</returns>
		static int Reset();
		static void DoPickUpEffects();
		static void CreateTemporaryRadarBlipsForPickupsInArea(Vector3 pos, float range, int type);
		static void RemoveTemporaryRadarBlipsForPickups();
	};
}