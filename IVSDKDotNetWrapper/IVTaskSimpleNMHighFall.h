#pragma once

namespace IVSDKDotNet
{
	public ref class IVTaskSimpleNMHighFall : IVTaskSimple
	{
	public:
		static IVTaskSimpleNMHighFall^ Create(uint32_t nUnk, uint32_t nUnk2, uint32_t nUnk3, uint32_t nUnk4);

	internal:
		IVTaskSimpleNMHighFall(CTaskSimpleNMHighFall* nativePtr);

	internal:
		CTaskSimpleNMHighFall* NativeTask;
	};
}