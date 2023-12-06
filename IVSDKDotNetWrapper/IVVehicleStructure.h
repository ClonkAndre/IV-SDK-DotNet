#pragma once

namespace IVSDKDotNet
{
	public ref class IVVehicleStructure
	{
	public:
		property array<uint32_t>^ Bones
		{
		public:
			array<uint32_t>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeVehicleStructure, nullptr);

				array<uint32_t>^ arr = gcnew array<uint32_t>(102);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = NativeVehicleStructure->m_nBones[i];

				return arr;
			}
			void set(array<uint32_t>^ value)
			{
				NULLPTR_CHECK(NativeVehicleStructure);
				NULLPTR_CHECK(value);

				for(int i = 0; i < value->Length; i++)
					NativeVehicleStructure->m_nBones[i] = value[i];
			}
		}

	internal:
		IVVehicleStructure(CVehicleStructure* nativePtr);

	internal:
		CVehicleStructure* NativeVehicleStructure;
	};
}