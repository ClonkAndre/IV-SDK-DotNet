#include "pch.h"
#include "IVPedFactoryNY.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVSpawnData::IVSpawnData(uint8_t flag1, uint8_t flag2)
	{
		Flag1 = flag1;
		Flag2 = flag2;
	}
	IVPedFactoryNY::IVPedFactoryNY(CPedFactoryNY* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativePedFactoryNY = nativePtr;
	}

	// - - - Methods / Functions - - -
	IVSpawnData IVSpawnData::Default()
	{
		return IVSpawnData(0, 0);
	}
	IVPed^ IVPedFactoryNY::CreatePed(IVSpawnData pSpawnData, int32_t model, IVMatrix^ mat, bool bNetwork, bool bUnk1)
	{
		NULLPTR_CHECK_WITH_RETURN(NativePedFactoryNY, nullptr);
		NULLPTR_CHECK_WITH_RETURN(mat, nullptr);
		NULLPTR_CHECK_WITH_RETURN(mat->NativeMatrix, nullptr);

		tSpawnData* data = new tSpawnData();
		data->m_nFlag1 = pSpawnData.Flag1;
		data->m_nFlag2 = pSpawnData.Flag2;

		CPed* ptr = NativePedFactoryNY->CreatePed(data, model, mat->NativeMatrix, bNetwork, bUnk1);

		delete data;

		NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);

		return gcnew IVPed(ptr);
	}

}