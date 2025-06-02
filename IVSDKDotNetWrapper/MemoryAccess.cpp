#include "pch.h"
#include "MemoryAccess.h"

namespace IVSDKDotNet
{

	// - - - Methods / Functions - - -
	void MemoryAccess::Initialise(uint32_t version, uint32_t baseAddress)
	{
		if (!m_bGotInitialised)
		{
			GameVersion = (eGameVersion)version;
			BaseAddress = baseAddress;
			m_bGotInitialised = true;
		}
	}

	uint32_t MemoryAccess::GetAddressFromConfigFile(String^ section, String^ key)
	{
		msclr::interop::marshal_context ctx;
		return AddressSetter::GetAddressFromConfig(ctx.marshal_as<const char*>(section), ctx.marshal_as<const char*>(key));
	}

	uint32_t MemoryAccess::GetAbsoluteAddress(String^ section, String^ key)
	{
		msclr::interop::marshal_context ctx;
		return AddressSetter::Get(ctx.marshal_as<const char*>(section), ctx.marshal_as<const char*>(key));
	}
	uint32_t MemoryAccess::GetAbsoluteAddress(uint32_t addr1070, uint32_t addr1080)
	{
		return AddressSetter::Get(addr1070, addr1080);
	}
	uint32_t MemoryAccess::GetAbsoluteAddress(uint32_t addr)
	{
		return AddressSetter::Get(addr);
	}

	uint32_t MemoryAccess::GetValue(uint32_t addr1070, uint32_t addr1080)
	{
		switch (m_eGameVersion)
		{
			case eGameVersion::VERSION_1070: return m_baseAddress + addr1070;
			case eGameVersion::VERSION_1080: return m_baseAddress + addr1080;
		}

		return 0;
	}
	void MemoryAccess::SetValue(uint32_t newValue, uint32_t addr1070, uint32_t addr1080)
	{
		switch (m_eGameVersion)
		{
			case eGameVersion::VERSION_1070: *(uint32_t*)(m_baseAddress + addr1070) = newValue; break;
			case eGameVersion::VERSION_1080: *(uint32_t*)(m_baseAddress + addr1080) = newValue; break;
		}
	}

}