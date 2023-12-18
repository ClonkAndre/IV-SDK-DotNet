#pragma once

namespace IVSDKDotNet
{
	public ref class IVTaskComplexWander : IVTaskComplex
	{
	public:
		property float Unk
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTask, 0.0F);
				return NativeTask->m_fUnk;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTask);
				NativeTask->m_fUnk = value;
			}
		}

	public:
		static IVTaskComplexWander^ Create(uint32_t moveState, float initialDir, bool bSensibly, float targetRadius, uint32_t unk1);

	internal:
		IVTaskComplexWander(CTaskComplexWander* nativePtr);

	internal:
		CTaskComplexWander* NativeTask;
	};
}