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
	array<Vehicle>^ CPools::GetAllVehicleHandles()
	{
		CPool<CVehicle>* vehiclePool = Native_CPools::VehiclePool();

		if (vehiclePool) {
			array<Vehicle>^ vehicles = gcnew array<Vehicle>(vehiclePool->m_nCount);

			for (int i = 0; i < vehiclePool->m_nCount; i++) {
				if (CVehicle* veh = vehiclePool->Get(i)) {
					int handle = vehiclePool->GetIndex(veh);
					vehicles[i] = handle;
				}
			}

			return vehicles;
		}

		return Array::Empty<Vehicle>();
	}
	array<Entity>^ CPools::GetAllObjectHandles()
	{
		CPool<CObject>* objectPool = Native_CPools::ObjectPool();

		if (objectPool) {
			array<Entity>^ objects = gcnew array<Entity>(objectPool->m_nCount);

			for (int i = 0; i < objectPool->m_nCount; i++) {
				if (CObject* obj = objectPool->Get(i)) {
					int handle = objectPool->GetIndex(obj);
					objects[i] = handle;
				}
			}

			return objects;
		}

		return Array::Empty<Entity>();
	}

}