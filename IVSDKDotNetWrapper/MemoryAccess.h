#pragma once

using namespace System::Runtime::InteropServices;
//using namespace IVSDKDotNet;
//using namespace IVSDKDotNet::Enums;

namespace IVSDKDotNet 
{
	public ref class MemoryAccess
	{
	public:

		static void Initialise(uint32_t version, uint32_t baseAddress);

		generic <typename T>
		static T GetRef(uint32_t addr1070, uint32_t addr1080);

		static uint32_t GetValue(uint32_t addr1070, uint32_t addr1080);
		static void		SetValue(uint32_t newValue, uint32_t addr1070, uint32_t addr1080);

		/// <summary>
		/// The base address of GTA IV.
		/// </summary>
		static property uint32_t BaseAddress
		{
			public:		uint32_t get()				{ return m_baseAddress; }
			private:	void set(uint32_t value)	{ m_baseAddress = value; }
		}

		/// <summary>
		/// Gets the current version of GTA IV.
		/// </summary>
		static property eGameVersion GameVersion
		{
			public:		eGameVersion get() { return m_eGameVersion; }
			private:	void set(eGameVersion value) { m_eGameVersion = value; }
		}

	private:
		static bool m_bGotInitialised;
		static eGameVersion m_eGameVersion;
		static uint32_t m_baseAddress;
	};
}