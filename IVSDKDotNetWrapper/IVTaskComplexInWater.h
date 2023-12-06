#pragma once

namespace IVSDKDotNet
{
	public ref class IVTaskComplexInWater : IVTaskComplex
	{
	public:
		static IVTaskComplexInWater^ Create(uint32_t unk, uint32_t unk2, bool bUnk);

	internal:
		IVTaskComplexInWater(CTaskComplexInWater* nativePtr);

	internal:
		CTaskComplexInWater* NativeTask;
	};
}