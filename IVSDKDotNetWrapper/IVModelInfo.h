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
	};
}