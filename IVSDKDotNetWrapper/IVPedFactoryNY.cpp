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
	int IVPedFactoryNY::DeletePed(IVPed^ ped)
	{
		NULLPTR_CHECK_WITH_RETURN(NativePedFactoryNY, 0);
		NULLPTR_CHECK_WITH_RETURN(ped, 0);
		NULLPTR_CHECK_WITH_RETURN(ped->NativePed, 0);

		return NativePedFactoryNY->DeletePed(ped->NativePed);
	}
	IVPed^ IVPedFactoryNY::CreatePed(IVControlledByInfo info, int32_t model, IVMatrix^ mat, bool bNetwork, bool bUnk1)
	{
		NULLPTR_CHECK_WITH_RETURN(NativePedFactoryNY, nullptr);
		NULLPTR_CHECK_WITH_RETURN(mat, nullptr);
		NULLPTR_CHECK_WITH_RETURN(mat->NativeMatrix, nullptr);

		CControlledByInfo* controlledByInfo = new CControlledByInfo(info.m_bIsControlledByNetwork, info.m_bIsPlayer);

		CPed* ptr = NativePedFactoryNY->CreatePed(controlledByInfo, model, mat->NativeMatrix, bNetwork, bUnk1);

		delete controlledByInfo;

		NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);

		return gcnew IVPed(ptr);
	}
	IVPed^ IVPedFactoryNY::CreatePed(IVControlledByInfo info, int32_t model, Vector3 pos, bool bNetwork, bool bUnk1)
	{
		return CreatePed(info, model, gcnew IVMatrix(Vector3::Zero, Vector3::Zero, Vector3::Zero, pos), bNetwork, bUnk1);
	}

}