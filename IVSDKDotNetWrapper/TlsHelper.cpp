#include "pch.h"
#include "TlsHelper.h"

#pragma unmanaged

// Read FS:[0x2C] (the linear address of the TLS array on x86)
DWORD_PTR __cdecl _GetTlsContext()
{
	return __readfsdword(0x2C);
}

// Write FS:[0x2C]
void __cdecl _SetTlsContext(DWORD_PTR ctx)
{
	__writefsdword(0x2C, static_cast<DWORD>(ctx));
}

#pragma managed

namespace IVSDKDotNet
{
	namespace Internal
	{

		UIntPtr TlsHelper::GetTlsContext()
		{
			return UIntPtr(static_cast<uint32_t>(_GetTlsContext()));
		}
		void TlsHelper::SetTlsContext(UIntPtr ctx)
		{
			_SetTlsContext(static_cast<DWORD>(ctx.ToUInt32()));
		}

	}
}