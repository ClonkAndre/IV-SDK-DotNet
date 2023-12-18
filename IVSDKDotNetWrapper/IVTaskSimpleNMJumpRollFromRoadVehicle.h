#pragma once

namespace IVSDKDotNet
{
	public ref class IVTaskSimpleNMJumpRollFromRoadVehicle : IVTaskSimple
	{
	public:
		static IVTaskSimpleNMJumpRollFromRoadVehicle^ Create(uint32_t time, uint32_t time2);

	internal:
		IVTaskSimpleNMJumpRollFromRoadVehicle(CTaskSimpleNMJumpRollFromRoadVehicle* nativePtr);

	internal:
		CTaskSimpleNMJumpRollFromRoadVehicle* NativeTask;
	};
}