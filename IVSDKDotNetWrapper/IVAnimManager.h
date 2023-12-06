#pragma once

namespace IVSDKDotNet
{
	public ref class IVAnimManager
	{
	public:

		ref class IVAnimAssocDefinition
		{
		public:
			property String^ Name
			{
			public:
				String^ get()
				{
					NULLPTR_CHECK_WITH_RETURN(NativeAnimAssocDefPtr, String::Empty);
					return gcnew String(NativeAnimAssocDefPtr->pName);
				}
			}
			property String^ BlockName
			{
			public:
				String^ get()
				{
					NULLPTR_CHECK_WITH_RETURN(NativeAnimAssocDefPtr, String::Empty);
					return gcnew String(NativeAnimAssocDefPtr->pBlockName);
				}
			}
			property UIntPtr Unknown
			{
			public:
				UIntPtr get()
				{
					NULLPTR_CHECK_WITH_RETURN(NativeAnimAssocDefPtr, UIntPtr::Zero);
					return UIntPtr(NativeAnimAssocDefPtr->pUnknown);
				}
				void set(UIntPtr value)
				{
					UINTPTR_ZERO_CHECK(value);
					NULLPTR_CHECK(NativeAnimAssocDefPtr);
					NativeAnimAssocDefPtr->pUnknown = value.ToPointer();
				}
			}
			property UIntPtr AnimDesc
			{
			public:
				UIntPtr get()
				{
					NULLPTR_CHECK_WITH_RETURN(NativeAnimAssocDefPtr, UIntPtr::Zero);
					return UIntPtr(NativeAnimAssocDefPtr->aAnimDesc);
				}
				void set(UIntPtr value)
				{
					UINTPTR_ZERO_CHECK(value);
					NULLPTR_CHECK(NativeAnimAssocDefPtr);
					NativeAnimAssocDefPtr->aAnimDesc = (CAnimManager::AnimDescriptor*)value.ToPointer();
				}
			}

		internal:
			IVAnimAssocDefinition(CAnimManager::AnimAssocDefinition* nativePtr)
			{
				NULLPTR_CHECK(nativePtr);
				NativeAnimAssocDefPtr = nativePtr;
			}

		internal:
			CAnimManager::AnimAssocDefinition* NativeAnimAssocDefPtr;
		};

	public:
		static property array<IVAnimAssocDefinition^>^ AnimAssocDefinitions
		{
		public:
			array<IVAnimAssocDefinition^>^ get()
			{
				CAnimManager::AnimAssocDefinition* allDefinitions = CAnimManager::ms_aAnimAssocDefinitions;
				NULLPTR_CHECK_WITH_RETURN(allDefinitions, nullptr);

				// Create and populate array
				array<IVAnimAssocDefinition^>^ arr = gcnew array<IVAnimAssocDefinition^>(CAnimManager::ms_numAnimAssocDefinitions);

				for (int32_t i = 0; i < arr->Length; i++)
				{
					CAnimManager::AnimAssocDefinition* def = &allDefinitions[i];

					if (!def)
						continue;

					arr[i] = gcnew IVAnimAssocDefinition(def);
				}

				return arr;
			}
			void set(array<IVAnimAssocDefinition^>^ value)
			{
				NULLPTR_CHECK(value);

				CAnimManager::AnimAssocDefinition* allDefinitions = CAnimManager::ms_aAnimAssocDefinitions;
				NULLPTR_CHECK(allDefinitions);

				// Set array
				for (int32_t i = 0; i < value->Length; i++)
				{
					IVAnimAssocDefinition^ def = value[i];

					if (!def)
						continue;

					allDefinitions[i] = *def->NativeAnimAssocDefPtr;
				}
			}
		}
		static property int32_t NumAnimAssocDefinitions
		{
		public:
			int32_t get()
			{
				return CAnimManager::ms_numAnimAssocDefinitions;
			}
			void set(int32_t value)
			{
				CAnimManager::ms_numAnimAssocDefinitions = value;
			}
		}

	public:
		static void Initialise();
		static void AddAnimAssocDefinition(int id, String^ pName, String^ pFile, uint32_t numAnims, array<String^>^ pAnimNames, UIntPtr pAnimDescs, int unk1, int unk2, int unk3, bool unk4);
	};
}