#include "pch.h"
#include "AddressSetter.h"

eGameVersion AddressSetter::m_eGameVersion;
uint32_t AddressSetter::m_baseAddress;

namespace IVSDKDotNet {

	void MemoryAccess::Initialise(int version, uint32_t baseAddress)
	{
		if (!m_bGotInitialised) {
			m_eGameVersion = (eGameVersion)version;
			BaseAddress = baseAddress;
			m_bGotInitialised = true;
		}
	}

	generic <typename T>
	T MemoryAccess::GetRef(uint32_t addr1070, uint32_t addr1080)
	{
		switch (m_eGameVersion) {
			case eGameVersion::VERSION_1070: return (T)Marshal::PtrToStructure(IntPtr((int)(m_baseAddress + addr1070)), T::typeid);
			case eGameVersion::VERSION_1080: return (T)Marshal::PtrToStructure(IntPtr((int)(m_baseAddress + addr1080)), T::typeid);
		}

		return T();
	}

	uint32_t MemoryAccess::GetValue(uint32_t addr1070, uint32_t addr1080)
	{
		switch (m_eGameVersion) {
			case eGameVersion::VERSION_1070: return m_baseAddress + addr1070;
			case eGameVersion::VERSION_1080: return m_baseAddress + addr1080;
		}

		return 0;
	}
	void MemoryAccess::SetValue(uint32_t newValue, uint32_t addr1070, uint32_t addr1080)
	{
		switch (m_eGameVersion) {
			case eGameVersion::VERSION_1070: *(uint32_t*)(m_baseAddress + addr1070) = newValue; break;
			case eGameVersion::VERSION_1080: *(uint32_t*)(m_baseAddress + addr1080) = newValue; break;
		}
	}

}