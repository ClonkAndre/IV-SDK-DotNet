#pragma once

namespace IVSDKDotNet
{
	public ref class IVTaskComplexWanderStandard
	{
	public:
		static IVTaskComplexWanderStandard^ Create(uint32_t moveState, float initialDir, bool bSensibly, float targetRadius, uint32_t unk1);

	internal:
		IVTaskComplexWanderStandard(CTaskComplexWanderStandard* nativePtr);

	internal:
		CTaskComplexWanderStandard* NativeTask;
	};
}