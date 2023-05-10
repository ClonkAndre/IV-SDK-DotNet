#include "pch.h"
#include "CPedFactoryNY.h"

namespace IVSDKDotNet {

	tSpawnData::tSpawnData(uint8_t flag1, uint8_t flag2)
	{
		Flag1 = flag1;
		Flag2 = flag2;
	}
	tSpawnData tSpawnData::Default()
	{
		return tSpawnData(0, 0);
	}

	CPed^ CPedFactoryNY::CreatePed(tSpawnData pSpawnData, int32_t model, GTAMatrix mat, bool bNetwork, bool bUnk1)
	{
		Native_tSpawnData* spawnData = new Native_tSpawnData();
		spawnData->m_nFlag1 = pSpawnData.Flag1;
		spawnData->m_nFlag2 = pSpawnData.Flag2;

		Native_CMatrix* matrix = new Native_CMatrix(mat.right, mat.up, mat.at, mat.pos);

		Native_CPedFactoryNY* pedFactory = AddressSetter::GetRef<Native_CPedFactoryNY*>(0x11E35A0, 0xE52DE0);
		Native_CPed* nativePed = pedFactory->CreatePed(spawnData, model, matrix, bNetwork, bUnk1);

		if (nativePed)
		{
			CPed^ ped = gcnew CPed(nativePed);

			delete spawnData;
			delete matrix;

			return ped;
		}

		delete spawnData;
		delete matrix;

		return nullptr;
	}

}