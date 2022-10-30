#pragma once

using namespace System::Runtime::InteropServices;
using namespace IVSDKDotNet;
using namespace IVSDKDotNet::Enums;

class AddressSetter
{
public:

	static void Initialise(int version, uint32_t baseAddress)
	{
		m_eGameVersion = (eGameVersion)version;
		m_baseAddress = baseAddress;
	}

	template<typename T>
	static T& GetRef(uint32_t addr1070, uint32_t addr1080)
	{
		switch (m_eGameVersion) {
			case eGameVersion::VERSION_1070: return *reinterpret_cast<T*>(m_baseAddress + addr1070);
			case eGameVersion::VERSION_1080: return *reinterpret_cast<T*>(m_baseAddress + addr1080);
		}

		return *reinterpret_cast<T*>(nullptr);
	}

	static uint32_t Get(uint32_t addr1070, uint32_t addr1080)
	{
		switch (m_eGameVersion) {
			case eGameVersion::VERSION_1070: return m_baseAddress + addr1070;
			case eGameVersion::VERSION_1080: return m_baseAddress + addr1080;
		}
		return 0;
	}

private:
	static eGameVersion m_eGameVersion;
	static uint32_t m_baseAddress;
};

namespace IVSDKDotNet {

	public ref class MemoryAccess
	{
	public:

		static void Initialise(int version, uint32_t baseAddress);

		generic <typename T>
		static T GetRef(uint32_t addr1070, uint32_t addr1080);

		static uint32_t GetValue(uint32_t addr1070, uint32_t addr1080);
		static void		SetValue(uint32_t newValue, uint32_t addr1070, uint32_t addr1080);

		/// <summary>
		/// The base address of GTA IV.
		/// </summary>
		static property uint32_t BaseAddress {
			public:		uint32_t get()				{ return m_baseAddress; }
			private:	void set(uint32_t value)	{ m_baseAddress = value; }
		}

	private:
		static bool m_bGotInitialised;
		static eGameVersion m_eGameVersion;
		static uint32_t m_baseAddress;
	};

}