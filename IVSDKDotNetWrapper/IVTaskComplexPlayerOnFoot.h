#pragma once

namespace IVSDKDotNet
{
	public ref class IVTaskComplexPlayerOnFoot : IVTaskComplex
	{
	public:
		static IVTaskComplexPlayerOnFoot^ Create();

	internal:
		IVTaskComplexPlayerOnFoot(CTaskComplexPlayerOnFoot* nativePtr);

	internal:
		CTaskComplexPlayerOnFoot* NativeTask;
	};
}