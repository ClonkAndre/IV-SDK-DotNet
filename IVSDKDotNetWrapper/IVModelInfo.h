#pragma once

namespace IVSDKDotNet
{
	public ref class IVModelInfo
	{
	public:
		static property array<IVBaseModelInfo^>^ ModelInfos
		{
		public:
			array<IVBaseModelInfo^>^ get()
			{
				CBaseModelInfo** ptr = CModelInfo::ms_modelInfoPtrs;
				NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);

				array<IVBaseModelInfo^>^ arr = gcnew array<IVBaseModelInfo^>(31000);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = gcnew IVBaseModelInfo(ptr[i]);

				return arr;
			}
			void set(array<IVBaseModelInfo^>^ value)
			{
				NULLPTR_CHECK(value);

				CBaseModelInfo** ptr = CModelInfo::ms_modelInfoPtrs;
				NULLPTR_CHECK(ptr);

				for(int i = 0; i < value->Length; i++)
					ptr[i] = value[i]->NativeModelInfo;
			}
		}

	public:
		static IVBaseModelInfo^ GetModelInfo(uint32_t hashKey, [OutAttribute] int% index);
		static IVPedModelInfo^ AddPedModel(String^ modelName);
		static IVVehicleModelInfo^ AddVehicleModel(String^ modelName);
		static IVBaseModelInfo^ AddAtomicModel(String^ modelName);
		static void Initialise();

		/// <summary>
		/// Returns the same as the "index" out-parameter of the "GetModelInfo" function would, but this creates no garbage collection allocations.
		/// </summary>
		/// <param name="hashKey">The hash key to get the index from.</param>
		/// <returns>The index from the given hask key. Returns -1 if the index could not be found or if the given hash key is invalid.</returns>
		static int GetIndexFromHashKey(uint32_t hashKey);

		/// <summary>
		/// If you have the index from the model info that you want to get, you can use this function here to get the "IVBaseModelInfo" instance instead of using the "ModelInfos" array (Which would be slower as its creating garbage collections).
		/// </summary>
		/// <param name="index">The index between 0 and 31000.</param>
		/// <returns>If found, the "IVBaseModelInfo" instance is returned.</returns>
		static IVBaseModelInfo^ GetModelInfoFromIndex(int index);

	};
}