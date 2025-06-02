#include "pch.h"
#include "IVPedFactoryNY.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVPedFactoryNY::IVPedFactoryNY(CPedFactoryNY* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativePedFactoryNY = nativePtr;
	}

	// - - - Methods / Functions - - -
	IVPed^ IVPedFactoryNY::CreatePed(IVControlledByInfo info, int32_t model, IVMatrix mat, bool bNetwork, bool bUnk1)
	{
		NULLPTR_CHECK_WITH_RETURN(NativePedFactoryNY, nullptr);

		CControlledByInfo* controlledByInfo = new CControlledByInfo(info.m_bIsControlledByNetwork, info.m_bIsPlayer);

		CPed* ptr = NativePedFactoryNY->CreatePed(controlledByInfo, model, &mat.ToCMatrix(), bNetwork, bUnk1);

		delete controlledByInfo;

		NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);

		return gcnew IVPed(ptr);
	}
	IVPed^ IVPedFactoryNY::CreatePed(IVControlledByInfo info, int32_t model, Vector3 pos, bool bNetwork, bool bUnk1)
	{
		return CreatePed(info, model, IVMatrix::Translation(pos), bNetwork, bUnk1);
	}
	int IVPedFactoryNY::DeletePed(IVPed^ ped)
	{
		NULLPTR_CHECK_WITH_RETURN(NativePedFactoryNY, 0);
		NULLPTR_CHECK_WITH_RETURN(ped, 0);
		NULLPTR_CHECK_WITH_RETURN(ped->NativePed, 0);

		return NativePedFactoryNY->DeletePed(ped->NativePed);
	}

}