#include "pch.h"
#include "CPools.h"

namespace IVSDKDotNet {

	// - - - Handles only - - -

	array<Ped>^ CPools::GetAllPedHandles()
	{
		CPool<CPed>* pedPool = Native_CPools::PedPool();

		if (pedPool) {
			array<Ped>^ peds = gcnew array<Ped>(pedPool->m_nUsed);

			for (uint32_t i = 0; i < pedPool->m_nUsed; i++) {
				if (CPed* ped = pedPool->Get(i)) {
					uint32_t handle = pedPool->GetIndex(ped);
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
			array<Vehicle>^ vehicles = gcnew array<Vehicle>(vehiclePool->m_nUsed);

			for (uint32_t i = 0; i < vehiclePool->m_nUsed; i++) {
				if (CVehicle* veh = vehiclePool->Get(i)) {
					uint32_t handle = vehiclePool->GetIndex(veh);
					vehicles[i] = handle;
				}
			}

			return vehicles;
		}

		return Array::Empty<Vehicle>();
	}
	array<Entity>^ CPools::GetAllObjectHandles()
	{
		CPool<Native_CObject>* objectPool = Native_CPools::ObjectPool();

		if (objectPool) {
			array<Entity>^ objects = gcnew array<Entity>(objectPool->m_nUsed);

			for (uint32_t i = 0; i < objectPool->m_nUsed; i++) {
				if (Native_CObject* obj = objectPool->Get(i)) {
					uint32_t handle = objectPool->GetIndex(obj);
					objects[i] = handle;
				}
			}

			return objects;
		}

		return Array::Empty<Entity>();
	}

	// - - - IV-SDK Objects - - -

	array<CObject^>^ CPools::GetAllObjects()
	{
		CPool<Native_CObject>* objectPool = Native_CPools::ObjectPool();

		if (objectPool) {
			array<CObject^>^ objects = gcnew array<CObject^>(objectPool->m_nUsed);

			for (uint32_t i = 0; i < objectPool->m_nUsed; i++) {
				if (Native_CObject* obj = objectPool->Get(i)) {
					uint32_t handle = objectPool->GetIndex(obj);
					objects[i] = gcnew CObject(handle, obj);
				}
			}

			return objects;
		}

		return Array::Empty<CObject^>();
	}

	void CPools::DeleteChar(Ped handle)
	{
		Natives::DELETE_CHAR(&handle);
	}
	void CPools::DeleteCar(Vehicle handle)
	{
		Natives::DELETE_CAR(&handle);
	}
	void CPools::DeleteObject(Entity handle)
	{
		Natives::DELETE_OBJECT(&handle);
	}

}