#pragma once

class Native_CTheScripts
{
public:

	// m_aGlobalVariables[65535]?
	static uint32_t*& GetGlobalVariables()					{ return AddressSetter::GetRef<uint32_t*>(0x1449AEC, 0x1394FC0);  }
	static void		  SetGlobalVariables(uint32_t*& value)	{ AddressSetter::GetRef<uint32_t*>(0x1449AEC, 0x1394FC0) = value; }

	static uint32_t GetCurrentThread()					{ return AddressSetter::GetRef<uint32_t>(0x1449AE0, 0x1394FB4); }
	static void		SetCurrentThread(uint32_t value)	{ AddressSetter::GetRef<uint32_t>(0x1449AE0, 0x1394FB4) = value; }

	static uint32_t FindNativeAddress(uint32_t nativeHash)
	{
		__try {
			uint32_t funcPtr = AddressSetter::Get(0x1A76D0, 0x226AF0);
			uint32_t nativePtr;
			_asm
			{
				push esi
				mov esi, nativeHash
				call funcPtr
				pop esi
				mov nativePtr, eax
			}

			return nativePtr;
		} __except (EXCEPTION_EXECUTE_HANDLER) {
			return 0;
		}
	}

	static bool IsPlayerOnAMission()
	{
		return ((bool(__cdecl*)())(AddressSetter::Get(0x403E00, 0x4AE3E0)))();
	}
	static void GivePedScriptedTask(int handle, uint32_t* task, int unk)
	{
		((void(__cdecl*)(int, uint32_t*, int))(AddressSetter::Get(0x4067A0, 0x4B0DF0)))(handle, task, unk);
	}
};

namespace IVSDKDotNet {

	public ref class CTheScripts
	{
	public:

		static property array<uint32_t>^ GlobalVariables {
			public:
				array<uint32_t>^ get()
				{

					uint32_t*& r = Native_CTheScripts::GetGlobalVariables();

					array<uint32_t>^ vars = gcnew array<uint32_t>(65535);
					for (int i = 0; i < vars->Length; i++)
					{
						vars[i] = r[i];
					}

					return vars;

				}
		}

		static property uint32_t CurrentThread {
			public:
				uint32_t get() { return Native_CTheScripts::GetCurrentThread(); }
				void	 set(uint32_t value) { Native_CTheScripts::SetCurrentThread(value); }
		}

		/// <summary>
		/// Sets the current thread to a dummy thread: uint8_t threadDummy[256]; - Needed for the GivePedScriptedTask method and some native functions.
		/// </summary>
		static void SetDummyThread();
		/// <summary>
		/// Restores the current thread to the thread previously stored by the SetDummyThread method. Should be called after you called SetDummyThread for a native function.
		/// </summary>
		static void RestorePreviousThread();

		/// <summary>
		/// Gets the native address from the given native hash.
		/// </summary>
		/// <param name="nativeHash">The native hash.</param>
		/// <returns>The native address.</returns>
		static uint32_t FindNativeAddress(uint32_t nativeHash);

		/// <summary>
		/// Gets if the player is on a mission.
		/// </summary>
		/// <returns>True if the player is on a mission. Otherwise, false.</returns>
		static bool IsPlayerOnAMission();

		/// <summary>
		/// Gives the specified ped a task.
		/// </summary>
		/// <param name="handle">The ped handle.</param>
		/// <param name="task">The task you want to assign to the ped.</param>
		/// <param name="unk">Unknown.</param>
		static void GivePedScriptedTask(int handle, UIntPtr task, int unk);

	private:
		static uint32_t m_iPreviousThread;

	};

}