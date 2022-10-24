#include "pch.h"
#include "CPools.h"

namespace IVSDKDotNet {

	array<Ped>^ CPools::GetAllPedHandles()
	{
		CPool<CPed>* pedPool = Native_CPools::PedPool();

		if (pedPool) {
			array<Ped>^ peds = gcnew array<Ped>(pedPool->m_nCount);

			for (int i = 0; i < pedPool->m_nCount; i++) {
				if (CPed* ped = pedPool->Get(i)) {
					int handle = pedPool->GetIndex(ped);
					peds[i] = handle;
				}
			}

			return peds;
		}

		return Array::Empty<Ped>();
	}

}