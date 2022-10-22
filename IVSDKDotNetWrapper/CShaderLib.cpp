#include "pch.h"
#include "CShaderLib.h"

namespace IVSDKDotNet {

	int CShaderLib::GetTechniqueID(String^ name)
	{
		msclr::interop::marshal_context ctx;
		return Native_CShaderLib::GetTechniqueID((char*)ctx.marshal_as<const char*>(name));
	}

}