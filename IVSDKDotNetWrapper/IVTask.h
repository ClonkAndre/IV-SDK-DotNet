#pragma once

namespace IVSDKDotNet
{
	public ref class IVTask
	{
	internal:
		IVTask(CTask* nativePtr);

	internal:
		CTask* NativeBaseTask;
	};

	public ref class IVTaskComplex : IVTask
	{
	internal:
		IVTaskComplex(CTaskComplex* nativePtr);

	internal:
		CTaskComplex* NativeComplexTask;
	};

	public ref class IVTaskSimple : IVTask
	{
	internal:
		IVTaskSimple(CTaskSimple* nativePtr);

	internal:
		CTaskSimple* NativeSimpleTask;
	};
}