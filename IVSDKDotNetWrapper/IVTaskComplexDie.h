#pragma once

namespace IVSDKDotNet
{
	public ref class IVTaskComplexDie : IVTaskComplex
	{
	public:
		static IVTaskComplexDie^ Create(uint32_t unk, uint32_t unk2, uint32_t unk3_44, uint32_t unk4_190, float fBlendDelta, float fAnimSpeed, uint32_t unk5_1);

	internal:
		IVTaskComplexDie(CTaskComplexDie* nativePtr);

	internal:
		CTaskComplexDie* NativeTask;
	};
}