#include "pch.h"
#include "IVGenericGameStorage.h"

namespace IVSDKDotNet
{
	String^ IVGenericGameStorage::GetDefaultPCSaveFileName()
	{
		return gcnew String(CGenericGameStorage::GetDefaultPCSaveFileName());
	}
	void IVGenericGameStorage::MakeValidSaveName(String^ pString, int slotNumber)
	{
		CHECK_NULL_OR_WHITESPACE_STRING(pString);
		msclr::interop::marshal_context ctx;
		CGenericGameStorage::MakeValidSaveName(ctx.marshal_as<const char*>(pString), slotNumber);
	}
	bool IVGenericGameStorage::SaveDataToWorkBuffer(IntPtr pData, int32_t sizeOfData)
	{
		INTPTR_ZERO_CHECK_WITH_RETURN(pData, false);
		return CGenericGameStorage::SaveDataToWorkBuffer(pData.ToPointer(), sizeOfData);
	}
	bool IVGenericGameStorage::LoadDataFromWorkBuffer(IntPtr pData, int32_t sizeOfData)
	{
		INTPTR_ZERO_CHECK_WITH_RETURN(pData, false);
		return CGenericGameStorage::LoadDataFromWorkBuffer(pData.ToPointer(), sizeOfData);
	}
}