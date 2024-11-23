#pragma once

namespace IVSDKDotNet
{
	public value class BuildingSwapStruct
	{
	public:
		property IVBuilding^ Building
		{
		public:
			IVBuilding^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeBuildingSwapStruct, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativeBuildingSwapStruct->pBuilding, nullptr);
				return gcnew IVBuilding(NativeBuildingSwapStruct->pBuilding);
			}
			void set(IVBuilding^ value)
			{
				NULLPTR_CHECK(NativeBuildingSwapStruct);
				NULLPTR_CHECK(value);
				NativeBuildingSwapStruct->pBuilding = value->NativeBuilding;
			}
		}
		property uint32_t NewModelIndex
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeBuildingSwapStruct, 0);
				return NativeBuildingSwapStruct->NewModelIndex;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeBuildingSwapStruct);
				NativeBuildingSwapStruct->NewModelIndex = value;
			}
		}
		property uint32_t OldModelIndex
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeBuildingSwapStruct, 0);
				return NativeBuildingSwapStruct->OldModelIndex;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeBuildingSwapStruct);
				NativeBuildingSwapStruct->OldModelIndex = value;
			}
		}

	internal:
		BuildingSwapStruct(building_swap_struct* nativePtr);

	internal:
		building_swap_struct* NativeBuildingSwapStruct;
	};

	public ref class IVTheScripts
	{
	public:
		static property array<BuildingSwapStruct>^ BuildingSwapArray
		{
		public:
			array<BuildingSwapStruct>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(CTheScripts::BuildingSwapArray, nullptr);

				array<BuildingSwapStruct>^ arr = gcnew array<BuildingSwapStruct>(25);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = BuildingSwapStruct(&CTheScripts::BuildingSwapArray[i]);

				return arr;
			}
			void set(array<BuildingSwapStruct>^ value)
			{
				NULLPTR_CHECK(value);
				NULLPTR_CHECK(CTheScripts::BuildingSwapArray);

				for(int i = 0; i < value->Length; i++)
					CTheScripts::BuildingSwapArray[i] = *value[i].NativeBuildingSwapStruct;
			}
		}
		static property array<uint32_t>^ GlobalVariables
		{
		public:
			array<uint32_t>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(CTheScripts::m_aGlobalVariables, nullptr);

				array<uint32_t>^ arr = gcnew array<uint32_t>(65535);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = CTheScripts::m_aGlobalVariables[i];

				return arr;
			}
		}
		static property uint32_t CurrentThread
		{
		public:
			uint32_t get()
			{
				return CTheScripts::m_pCurrentThread;
			}
			void set(uint32_t value)
			{
				CTheScripts::m_pCurrentThread = value;
			}
		}

	public:
		static uint32_t FindNativeAddress(uint32_t nativeHash);
		static int RegisterNativeNoChecks(uint32_t hash, IntPtr funcPtr);
		static int RegisterNative(uint32_t hash, IntPtr funcPtr);

		/// <summary>
		/// Gets the name of the current calling script.
		/// <para>This does not return the name of the current IV-SDK .NET script! This function only works for sco scripts.</para>
		/// </summary>
		/// <returns>The name of the calling script. Otherwise 'ERROR!!! Unknown script name ERROR!!!' is returned.</returns>
		static String^ GetNameOfCurrentScript()
		{
			return gcnew String(CTheScripts::GetNameOfCurrentScript());
		}

		static bool IsPlayerOnAMission();
		static void GivePedScriptedTask(int handle, IVTask^ task, int unk);
		static void AddToBuildingSwapArray(IVBuilding^ pBildng, int32_t oldModIndx, int32_t newModIndx);
		static void UndoBuildingSwaps();
		static void Save();
		static void Load();

		static void SetDummyThread();
		static void RestorePreviousThread();

		static uint32_t GetGlobalAddress(int index);

		static int GetGlobalInteger(int index);
		static float GetGlobalFloat(int index);
		static String^ GetGlobalString(int index);

		static void SetGlobal(int index, int value);
		static void SetGlobal(int index, float value);
		static bool SetGlobal(int index, String^ value);

	private:
		static uint32_t m_iPreviousThread;

	};
}