#pragma once

namespace IVSDKDotNet
{
	public ref class IVTaskComplexClimbLadder : IVTaskComplex
	{
	public:
		static IVTaskComplexClimbLadder^ Create(IVObject^ ladder, int32_t type, uint32_t unk0);

	internal:
		IVTaskComplexClimbLadder(CTaskComplexClimbLadder* nativePtr);

	internal:
		CTaskComplexClimbLadder* NativeTask;
	};
}