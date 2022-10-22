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
	T% MemoryAccess::GetRef(uint32_t addr1070, uint32_t addr1080)
	{
		GCHandle^ handle;

		switch (m_eGameVersion) {
			case eGameVersion::VERSION_1070: handle = GCHandle::FromIntPtr(IntPtr((int)(m_baseAddress + addr1070)));
			case eGameVersion::VERSION_1080: handle = GCHandle::FromIntPtr(IntPtr((int)(m_baseAddress + addr1080)));
		}

		if (handle)
			return static_cast<T>(handle->Target);

		return T();
	}

	uint32_t MemoryAccess::Get(uint32_t addr1070, uint32_t addr1080)
	{
		switch (m_eGameVersion) {
			case eGameVersion::VERSION_1070: return m_baseAddress + addr1070;
			case eGameVersion::VERSION_1080: return m_baseAddress + addr1080;
		}

		return 0;
	}

}