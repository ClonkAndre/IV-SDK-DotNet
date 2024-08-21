#pragma once

namespace IVSDKDotNet
{
	public ref class IVStore
	{
	public:
		static property IVStore^ VehicleModelStore
		{
		public:
			IVStore^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(&ms_vehicleModelStore, nullptr);
				return gcnew IVStore((uint32_t*)&ms_vehicleModelStore, eStoreType::VehicleModelStore);
			}
		}
		static property IVStore^ PedModelStore
		{
		public:
			IVStore^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(&ms_pedModelStore, nullptr);
				return gcnew IVStore((uint32_t*)&ms_pedModelStore, eStoreType::PedModelStore);
			}
		}

	public:
		property eStoreType Type
		{
		public:
			eStoreType get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeStore, eStoreType::Invalid);
				return StoreType;
			}
		}

		property uint32_t MaxItems
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeStore, 0);
				return GetNativeStore<uint32_t>()->m_maxItems;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeStore);
				GetNativeStore<uint32_t>()->m_maxItems = value;
			}
		}
		property uint32_t NextItem
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeStore, 0);
				return GetNativeStore<uint32_t>()->m_nextItem;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeStore);
				GetNativeStore<uint32_t>()->m_nextItem = value;
			}
		}

		property array<UIntPtr>^ StoreArray
		{
		public:
			array<UIntPtr>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeStore, nullptr);

				array<UIntPtr>^ arr = gcnew array<UIntPtr>(MaxItems);

				for (int i = 0; i < arr->Length; i++)
					arr[i] = UIntPtr(GetNativeStore<uint32_t>()->m_storeArray[i]);

				return arr;
			}
			void set(array<UIntPtr>^ value)
			{
				NULLPTR_CHECK(NativeStore);
				NULLPTR_CHECK(value);

				for (int i = 0; i < value->Length; i++)
					GetNativeStore<uint32_t>()->m_storeArray[i] = *(uint32_t*)value[i].ToPointer();
			}
		}

	public:


	internal:
		IVStore(uint32_t* nativePtr, eStoreType storeType);

		template<typename T>
		CStore<T>* GetNativeStore();

	internal:
		uint32_t* NativeStore;
		eStoreType StoreType;
	};
}
