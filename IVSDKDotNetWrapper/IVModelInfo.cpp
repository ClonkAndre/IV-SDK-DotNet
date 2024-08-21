#include "pch.h"
#include "IVModelInfo.h"

namespace IVSDKDotNet
{

	// - - - Methods / Functions - - -
	IVBaseModelInfo^ IVModelInfo::GetModelInfo(uint32_t hashKey, [OutAttribute] int% index)
	{
		int i;
		CBaseModelInfo* ptr = CModelInfo::GetModelInfo(hashKey, &i);
		NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);
		index = i;
		return gcnew IVBaseModelInfo(ptr);
	}
	IVPedModelInfo^ IVModelInfo::AddPedModel(String^ modelName)
	{
		CHECK_NULL_OR_WHITESPACE_STRING_WITH_RETURN(modelName, nullptr);
		msclr::interop::marshal_context ctx;
		CPedModelInfo* ptr = CModelInfo::AddPedModel((char*)ctx.marshal_as<const char*>(modelName));
		NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);
		return gcnew IVPedModelInfo(ptr);
	}
	IVVehicleModelInfo^ IVModelInfo::AddVehicleModel(String^ modelName)
	{
		CHECK_NULL_OR_WHITESPACE_STRING_WITH_RETURN(modelName, nullptr);
		msclr::interop::marshal_context ctx;
		CVehicleModelInfo* ptr = CModelInfo::AddVehicleModel((char*)ctx.marshal_as<const char*>(modelName));
		NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);
		return gcnew IVVehicleModelInfo(ptr);
	}
	IVBaseModelInfo^ IVModelInfo::AddAtomicModel(String^ modelName)
	{
		CHECK_NULL_OR_WHITESPACE_STRING_WITH_RETURN(modelName, nullptr);
		msclr::interop::marshal_context ctx;
		CBaseModelInfo* ptr = CModelInfo::AddAtomicModel((char*)ctx.marshal_as<const char*>(modelName));
		NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);
		return gcnew IVBaseModelInfo(ptr);
	}
	void IVModelInfo::Initialise()
	{
		CModelInfo::Initialise();
	}

	int IVModelInfo::GetIndexFromHashKey(uint32_t hashKey)
	{
		int i;

		if (!CModelInfo::GetModelInfo(hashKey, &i))
			return -1;

		return i;
	}
	IVBaseModelInfo^ IVModelInfo::GetModelInfoFromIndex(int index)
	{
		if (index >= 0 && index < 30999)
		{
			CBaseModelInfo* ptr = CModelInfo::ms_modelInfoPtrs[index];
			NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);
			return gcnew IVBaseModelInfo(ptr);
		}

		return nullptr;
	}

}