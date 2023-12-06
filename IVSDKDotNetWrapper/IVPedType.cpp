#include "pch.h"
#include "IVPedType.h"

namespace IVSDKDotNet
{
	// - - - Methods / Functions - - -
	bool IVPedType::IsPedTypePlayer(String^ type)
	{
		CHECK_NULL_OR_WHITESPACE_STRING_WITH_RETURN(type, false);
		msclr::interop::marshal_context ctx;
		return CPedType::IsPedTypePlayer((char*)ctx.marshal_as<const char*>(type));
	}
	int IVPedType::FindPedType(String^ type)
	{
		CHECK_NULL_OR_WHITESPACE_STRING_WITH_RETURN(type, 0);
		msclr::interop::marshal_context ctx;
		return CPedType::FindPedType((char*)ctx.marshal_as<const char*>(type));
	}
}