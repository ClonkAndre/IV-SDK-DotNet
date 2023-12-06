#pragma once

namespace IVSDKDotNet
{
	public ref class IVTaskComplexNewGetInVehicle : IVTaskComplex
	{
	public:
		static IVTaskComplexNewGetInVehicle^ Create(UIntPtr veh, int32_t getInType, uint32_t unk27, int32_t unk, float fUnk);

	internal:
		IVTaskComplexNewGetInVehicle(CTaskComplexNewGetInVehicle* nativePtr);

	internal:
		CTaskComplexNewGetInVehicle* NativeTask;
	};
}