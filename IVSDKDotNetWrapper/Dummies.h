#pragma once

class Native_CDummyTask;
class Native_CDummyPed;

namespace IVSDKDotNet {

	public ref class CDummyTask
	{
	public:
		CDummyTask(Native_CDummyTask* nativePtr)
		{
			m_cNativeDummyTask = nativePtr;
		}

	private:
		Native_CDummyTask* m_cNativeDummyTask;
	};

	public ref class CDummyPed
	{
	public:
		CDummyPed(Native_CDummyPed* nativePtr)
		{
			m_cNativeDummyPed = nativePtr;
		}

	private:
		Native_CDummyPed* m_cNativeDummyPed;
	};

}