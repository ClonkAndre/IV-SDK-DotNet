#pragma once

namespace IVSDKDotNet
{
	public ref class IVTaskComplexNM : IVTaskComplex
	{
	public:
		static IVTaskComplexNM^ Create(uint32_t nUnk, uint32_t nUnk2, IVTaskSimple^ pSubTask, float fUnk);

	internal:
		IVTaskComplexNM(CTaskComplexNM* nativePtr);

	internal:
		CTaskComplexNM* NativeTask;
	};
}