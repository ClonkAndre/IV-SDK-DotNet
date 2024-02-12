#pragma once

namespace IVSDKDotNet
{
	public ref class IVTaskComplexClimbLadder : IVTaskComplex
	{
	public:
		/// <summary>
		/// Creates a new climb ladder task.
		/// </summary>
		/// <param name="ladder">The target ladder to climb.</param>
		/// <param name="type">Not quite sure what this does.</param>
		/// <param name="unk0">0 = Only get on the ladder, 1 = Get on and climb, 2 = Get on and climb fast</param>
		/// <returns></returns>
		static IVTaskComplexClimbLadder^ Create(IVObject^ ladder, int32_t type, uint32_t unk0);

	internal:
		IVTaskComplexClimbLadder(CTaskComplexClimbLadder* nativePtr);

	internal:
		CTaskComplexClimbLadder* NativeTask;
	};
}