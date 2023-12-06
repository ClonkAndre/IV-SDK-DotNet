#pragma once

namespace IVSDKDotNet
{
	public ref class IVTaskComplexPlayerSettingsTask : IVTaskComplex
	{
	public:
		property uint32_t Unk0
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTask, 0);
				return NativeTask->m_nUnk0;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeTask);
				NativeTask->m_nUnk0 = value;
			}
		}
		property int32_t UnkNeg1
		{
		public:
			int32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTask, 0);
				return NativeTask->m_nUnkNeg1;
			}
			void set(int32_t value)
			{
				NULLPTR_CHECK(NativeTask);
				NativeTask->m_nUnkNeg1 = value;
			}
		}
		property int32_t UnkNeg1_2
		{
		public:
			int32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTask, 0);
				return NativeTask->m_nUnkNeg1_2;
			}
			void set(int32_t value)
			{
				NULLPTR_CHECK(NativeTask);
				NativeTask->m_nUnkNeg1_2 = value;
			}
		}
		property uint32_t UnkFromPed
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTask, 0);
				return NativeTask->m_nUnkFromPed;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeTask);
				NativeTask->m_nUnkFromPed = value;
			}
		}

	public:
		static IVTaskComplexPlayerSettingsTask^ Create(uint32_t unkFromPed);

	internal:
		IVTaskComplexPlayerSettingsTask(CTaskComplexPlayerSettingsTask* nativePtr);

	internal:
		CTaskComplexPlayerSettingsTask* NativeTask;
	};
}