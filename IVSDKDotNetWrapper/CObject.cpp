#include "pch.h"
#include "CObject.h"

namespace IVSDKDotNet {

	CObject::CObject(uint32_t handle, Native_CObject* native) : CPhysical(native)
	{
		Handle = handle;
		m_cNativeObject = native;
	}

}