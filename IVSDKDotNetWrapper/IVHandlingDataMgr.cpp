#include "pch.h"
#include "IVHandlingDataMgr.h"

namespace IVSDKDotNet
{
	void IVHandlingDataMgr::Initialise()
	{
		cHandlingDataMgr::Initialise();
	}
	void IVHandlingDataMgr::LoadHandlingData(String^ sPath)
	{
		CHECK_NULL_OR_WHITESPACE_STRING(sPath);
		msclr::interop::marshal_context ctx;
		cHandlingDataMgr::LoadHandlingData((char*)ctx.marshal_as<const char*>(sPath));
	}
	IVHandlingData^ IVHandlingDataMgr::GetHandlingData(int id)
	{
		tHandlingData* ptr = cHandlingDataMgr::GetHandlingData(id);
		NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);
		return gcnew IVHandlingData(ptr);
	}
	int IVHandlingDataMgr::GetHandlingId(String^ handlingName)
	{
		CHECK_NULL_OR_WHITESPACE_STRING_WITH_RETURN(handlingName, 0);
		msclr::interop::marshal_context ctx;
		return cHandlingDataMgr::GetHandlingId((char*)ctx.marshal_as<const char*>(handlingName));
	}
}