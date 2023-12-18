#include "pch.h"
#include "IVShaderLib.h"

namespace IVSDKDotNet
{
	// - - - Methods / Functions - - -
	int IVShaderLib::GetTechniqueID(String^ name)
	{
		CHECK_NULL_OR_WHITESPACE_STRING_WITH_RETURN(name, 0);
		msclr::interop::marshal_context ctx;
		return CShaderLib::GetTechniqueID((char*)ctx.marshal_as<const char*>(name));
	}
}