#include "pch.h"
#include "CPools.h"

namespace IVSDKDotNet {

	// - - - Handles only - - -

	array<Ped>^ CPools::GetAllPedHandles()
	{
		Native_CPool<Native_CPed>* pedPool = Native_CPools::GetPedPool();

		if (pedPool) {
			array<Ped>^ peds = gcnew array<Ped>(pedPool->m_nUsed);

			for (uint32_t i = 0; i < pedPool->m_nUsed; i++) {
				if (Native_CPed* ped = pedPool->Get(i)) {
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
		Native_CPool<Native_CVehicle>* vehiclePool = Native_CPools::GetVehiclePool();

		if (vehiclePool) {
			array<Vehicle>^ vehicles = gcnew array<Vehicle>(vehiclePool->m_nUsed);

			for (uint32_t i = 0; i < vehiclePool->m_nUsed; i++) {
				if (Native_CVehicle* veh = vehiclePool->Get(i)) {
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
		Native_CPool<Native_CObject>* objectPool = Native_CPools::GetObjectPool();

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

	// - - - IV-SDK Pools - - -
	CPool^ CPools::GetPedPool()
	{
		return CPool::GetFromType(ePool::PedPool);
	}
	CPool^ CPools::GetVehiclePool()
	{
		return CPool::GetFromType(ePool::VehiclePool);
	}
	CPool^ CPools::GetObjectPool()
	{
		return CPool::GetFromType(ePool::ObjectPool);
	}
	CPool^ CPools::GetBuildingPool()
	{
		return CPool::GetFromType(ePool::BuildingPool);
	}
	CPool^ CPools::GetCameraPool()
	{
		return CPool::GetFromType(ePool::CameraPool);
	}
	CPool^ CPools::GetTaskPool()
	{
		return CPool::GetFromType(ePool::TaskPool);
	}
	CPool^ CPools::GetInteriorInstPool()
	{
		return CPool::GetFromType(ePool::InteriorInstPool);
	}
	CPool^ CPools::GetDummyPedPool()
	{
		return CPool::GetFromType(ePool::DummyPedPool);
	}
	CPool^ CPools::GetDummyTaskPool()
	{
		return CPool::GetFromType(ePool::DummyTaskPool);
	}

	// - - - IV-SDK Objects - - -

	array<CPed^>^ CPools::GetAllPeds()
	{
		Native_CPool<Native_CPed>* pedPool = Native_CPools::GetPedPool();

		if (pedPool) {
			array<CPed^>^ vehicles = gcnew array<CPed^>(pedPool->m_nUsed);

			for (uint32_t i = 0; i < pedPool->m_nUsed; i++) {
				if (Native_CPed* obj = pedPool->Get(i)) {
					//uint32_t handle = vehiclePool->GetIndex(obj);
					vehicles[i] = gcnew CPed(obj);
				}
			}

			return vehicles;
		}

		return Array::Empty<CPed^>();
	}
	array<CVehicle^>^ CPools::GetAllVehicles()
	{
		Native_CPool<Native_CVehicle>* vehiclePool = Native_CPools::GetVehiclePool();

		if (vehiclePool) {
			array<CVehicle^>^ vehicles = gcnew array<CVehicle^>(vehiclePool->m_nUsed);

			for (uint32_t i = 0; i < vehiclePool->m_nUsed; i++) {
				if (Native_CVehicle* obj = vehiclePool->Get(i)) {
					//uint32_t handle = vehiclePool->GetIndex(obj);
					vehicles[i] = gcnew CVehicle(obj);
				}
			}

			return vehicles;
		}

		return Array::Empty<CVehicle^>();
	}
	array<CObject^>^ CPools::GetAllObjects()
	{
		Native_CPool<Native_CObject>* objectPool = Native_CPools::GetObjectPool();

		if (objectPool) {
			array<CObject^>^ objects = gcnew array<CObject^>(objectPool->m_nUsed);

			for (uint32_t i = 0; i < objectPool->m_nUsed; i++) {
				if (Native_CObject* obj = objectPool->Get(i)) {
					//uint32_t handle = objectPool->GetIndex(obj);
					objects[i] = gcnew CObject(obj);
				}
			}

			return objects;
		}

		return Array::Empty<CObject^>();
	}
	array<CBuilding^>^ CPools::GetAllBuildings()
	{
		Native_CPool<Native_CBuilding>* buildingPool = Native_CPools::GetBuildingPool();

		if (buildingPool) {
			array<CBuilding^>^ buildings = gcnew array<CBuilding^>(buildingPool->m_nUsed);

			for (uint32_t i = 0; i < buildingPool->m_nUsed; i++) {
				if (Native_CBuilding* obj = buildingPool->Get(i)) {
					buildings[i] = gcnew CBuilding(obj);
				}
			}

			return buildings;
		}

		return Array::Empty<CBuilding^>();
	}
	array<CCam^>^ CPools::GetAllCameras()
	{
		Native_CPool<Native_CCam>* cameraPool = Native_CPools::GetCameraPool();

		if (cameraPool) {
			array<CCam^>^ cameras = gcnew array<CCam^>(cameraPool->m_nUsed);

			for (uint32_t i = 0; i < cameraPool->m_nUsed; i++) {
				if (Native_CCam* obj = cameraPool->Get(i)) {
					cameras[i] = gcnew CCam(obj);
				}
			}

			return cameras;
		}

		return Array::Empty<CCam^>();
	}

}