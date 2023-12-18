#pragma once

namespace IVSDKDotNet
{
	public ref class IVHandlingDataMgr
	{
	public:
		static property array<IVHandlingData^>^ HandlingData
		{
		public:
			array<IVHandlingData^>^ get()
			{
				tHandlingData* ptr = cHandlingDataMgr::HandlingData;
				NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);
				
				array<IVHandlingData^>^ arr = gcnew array<IVHandlingData^>(160);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = gcnew IVHandlingData(&ptr[i]);

				return arr;
			}
			void set(array<IVHandlingData^>^ value)
			{
				NULLPTR_CHECK(value);

				tHandlingData* ptr = cHandlingDataMgr::HandlingData;
				NULLPTR_CHECK(ptr);

				for(int i = 0; i < value->Length; i++)
					ptr[i] = *value[i]->NativeHandlingData;
			}
		}
		static property array<IVHandlingData^>^ BikeHandlingData
		{
		public:
			array<IVHandlingData^>^ get()
			{
				tHandlingData* ptr = cHandlingDataMgr::BikeHandlingData;
				NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);

				array<IVHandlingData^>^ arr = gcnew array<IVHandlingData^>(40);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = gcnew IVHandlingData(&ptr[i]);

				return arr;
			}
			void set(array<IVHandlingData^>^ value)
			{
				NULLPTR_CHECK(value);

				tHandlingData* ptr = cHandlingDataMgr::BikeHandlingData;
				NULLPTR_CHECK(ptr);

				for(int i = 0; i < value->Length; i++)
					ptr[i] = *value[i]->NativeHandlingData;
			}
		}
		static property array<IVHandlingData^>^ FlyingHandlingData
		{
		public:
			array<IVHandlingData^>^ get()
			{
				tHandlingData* ptr = cHandlingDataMgr::FlyingHandlingData;
				NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);

				array<IVHandlingData^>^ arr = gcnew array<IVHandlingData^>(40);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = gcnew IVHandlingData(&ptr[i]);

				return arr;
			}
			void set(array<IVHandlingData^>^ value)
			{
				NULLPTR_CHECK(value);

				tHandlingData* ptr = cHandlingDataMgr::FlyingHandlingData;
				NULLPTR_CHECK(ptr);

				for(int i = 0; i < value->Length; i++)
					ptr[i] = *value[i]->NativeHandlingData;
			}
		}
		static property array<IVHandlingData^>^ BoatHandlingData
		{
		public:
			array<IVHandlingData^>^ get()
			{
				tHandlingData* ptr = cHandlingDataMgr::BoatHandlingData;
				NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);

				array<IVHandlingData^>^ arr = gcnew array<IVHandlingData^>(40);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = gcnew IVHandlingData(&ptr[i]);

				return arr;
			}
			void set(array<IVHandlingData^>^ value)
			{
				NULLPTR_CHECK(value);

				tHandlingData* ptr = cHandlingDataMgr::BoatHandlingData;
				NULLPTR_CHECK(ptr);

				for(int i = 0; i < value->Length; i++)
					ptr[i] = *value[i]->NativeHandlingData;
			}
		}

	public:
		static void Initialise();
		static void LoadHandlingData(String^ sPath);
		static IVHandlingData^ GetHandlingData(int id);
		static int GetHandlingId(String^ handlingName);
	};
}