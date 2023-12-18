#pragma once

namespace IVSDKDotNet
{
	public ref class IVGarages
	{
	public:
		static property bool CamShouldBeOutside
		{
		public:
			bool get()
			{
				return CGarages::bCamShouldBeOutside;
			}
			void set(bool value)
			{
				CGarages::bCamShouldBeOutside = value;
			}
		}
		static property bool HasResprayHappened
		{
		public:
			bool get()
			{
				return CGarages::bHasResprayHappened;
			}
			void set(bool value)
			{
				CGarages::bHasResprayHappened = value;
			}
		}
		static property uint32_t MessageStartTime
		{
		public:
			uint32_t get()
			{
				return CGarages::MessageStartTime;
			}
			void set(uint32_t value)
			{
				CGarages::MessageStartTime = value;
			}
		}
		static property uint32_t MessageEndTime
		{
		public:
			uint32_t get()
			{
				return CGarages::MessageEndTime;
			}
			void set(uint32_t value)
			{
				CGarages::MessageEndTime = value;
			}
		}
		static property int32_t LastGaragePlayerWasIn
		{
		public:
			int32_t get()
			{
				return CGarages::LastGaragePlayerWasIn;
			}
			void set(int32_t value)
			{
				CGarages::LastGaragePlayerWasIn = value;
			}
		}
		static property uint32_t LastTimeHelpMessage
		{
		public:
			uint32_t get()
			{
				return CGarages::LastTimeHelpMessage;
			}
			void set(uint32_t value)
			{
				CGarages::LastTimeHelpMessage = value;
			}
		}

		static property bool BombsAreFree
		{
		public:
			bool get()
			{
				return CGarages::BombsAreFree;
			}
			void set(bool value)
			{
				CGarages::BombsAreFree = value;
			}
		}
		static property bool RespraysAreFree
		{
		public:
			bool get()
			{
				return CGarages::RespraysAreFree;
			}
			void set(bool value)
			{
				CGarages::RespraysAreFree = value;
			}
		}
		static property bool NoResprays
		{
		public:
			bool get()
			{
				return CGarages::NoResprays;
			}
			void set(bool value)
			{
				CGarages::NoResprays = value;
			}
		}

		static property uint32_t NumGarages
		{
		public:
			uint32_t get()
			{
				return CGarages::NumGarages;
			}
			void set(uint32_t value)
			{
				CGarages::NumGarages = value;
			}
		}
		static property uint32_t NumSafehouseGarages
		{
		public:
			uint32_t get()
			{
				return CGarages::NumSafehouseGarages;
			}
			void set(uint32_t value)
			{
				CGarages::NumSafehouseGarages = value;
			}
		}

		static property array<IVGarage^>^ Garages
		{
		public:
			array<IVGarage^>^ get()
			{
				CGarage* ptr = CGarages::aGarages;
				NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);

				array<IVGarage^>^ arr = gcnew array<IVGarage^>(40);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = gcnew IVGarage(&ptr[i]);

				return arr;
			}
			void set(array<IVGarage^>^ value)
			{
				NULLPTR_CHECK(value);

				CGarage* ptr = CGarages::aGarages;
				NULLPTR_CHECK(ptr);

				for(int i = 0; i < value->Length; i++)
					ptr[i] = *value[i]->NativeGarage;
			}
		}
		static property array<IVStoredCar^>^ CarsInSafeHouse
		{
		public:
			array<IVStoredCar^>^ get()
			{
				CStoredCar* ptr = CGarages::aCarsInSafeHouse;
				NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);

				array<IVStoredCar^>^ arr = gcnew array<IVStoredCar^>(40);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = gcnew IVStoredCar(&ptr[i]);

				return arr;
			}
			void set(array<IVStoredCar^>^ value)
			{
				NULLPTR_CHECK(value);

				CStoredCar* ptr = CGarages::aCarsInSafeHouse;
				NULLPTR_CHECK(ptr);

				for(int i = 0; i < value->Length; i++)
					ptr[i] = *value[i]->NativeStoredCar;
			}
		}

	public:
		static bool CameraShouldBeOutside();
		static void CloseHideOutGaragesBeforeSave(bool unk);
		static void Init();
		static bool Load();
		static void PlayerArrestedOrDied();
		static bool Save();
		static void Shutdown();
		static void Update();

	};
}