#pragma once

namespace IVSDKDotNet
{
	public ref class IVTaskComplexMobileMakeCall : IVTaskComplex
	{
	public:
		static IVTaskComplexMobileMakeCall^ Create(String^ speechLine, bool bUnk1, bool bUnk2);

	internal:
		IVTaskComplexMobileMakeCall(CTaskComplexMobileMakeCall* nativePtr);

	internal:
		CTaskComplexMobileMakeCall* NativeTask;
	};
}