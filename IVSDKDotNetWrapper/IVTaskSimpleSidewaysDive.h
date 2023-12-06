#pragma once

namespace IVSDKDotNet
{
	public ref class IVTaskSimpleSidewaysDive : IVTaskSimple
	{
	public:
		static IVTaskSimpleSidewaysDive^ Create(bool bDirection);

	internal:
		IVTaskSimpleSidewaysDive(CTaskSimpleSidewaysDive* nativePtr);

	internal:
		CTaskSimpleSidewaysDive* NativeTask;
	};
}