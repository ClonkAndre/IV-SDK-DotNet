#include "pch.h"
#include "CPool.h"

namespace IVSDKDotNet {

	template<typename T>
	CPool::CPool(T* nativePtr, ePool type)
	{
		PoolPointer = (uint32_t*)nativePtr;
		Type = type;
	}

	CPool^ CPool::GetFromType(ePool type)
	{
		// TODO: Complete pools.
		switch (type) {
			case ePool::PedPool:
			{
				Native_CPool<Native_CPed>* pool = AddressSetter::GetRef<Native_CPool<Native_CPed>*>(0x14A82AC, 0x14CB03C);

				if (!pool)
					return nullptr;

				return gcnew CPool(pool, type);
			}
			case ePool::VehiclePool:
			{
				Native_CPool<Native_CVehicle>* pool = AddressSetter::GetRef<Native_CPool<Native_CVehicle>*>(0x1219240, 0xE52CD0);

				if (!pool)
					return nullptr;

				return gcnew CPool(pool, type);
			}
			case ePool::ObjectPool:
			{
				Native_CPool<Native_CObject>* pool = AddressSetter::GetRef<Native_CPool<Native_CObject>*>(0xF50CE0, 0xE52B48);

				if (!pool)
					return nullptr;

				return gcnew CPool(pool, type);
			}
			case ePool::BuildingPool:
			{
				Native_CPool<Native_CBuilding>* pool = AddressSetter::GetRef<Native_CPool<Native_CBuilding>*>(0x128FED0, 0xE4A5E8);

				if (!pool)
					return nullptr;

				return gcnew CPool(pool, type);
			}
			case ePool::CameraPool:
			{
				Native_CPool<Native_CCam>* pool = AddressSetter::GetRef<Native_CPool<Native_CCam>*>(0x1218020, 0xF68158);

				if (!pool)
					return nullptr;

				return gcnew CPool(pool, type);
			}
			case ePool::TaskPool:
			{
				Native_CPool<Native_CTask>* pool = AddressSetter::GetRef<Native_CPool<Native_CTask>*>(0x1218020, 0xF68158);

				if (!pool)
					return nullptr;

				return gcnew CPool(pool, type);
			}
			case ePool::InteriorInstPool:
			{
				Native_CPool<Native_CInteriorInst>* pool = AddressSetter::GetRef<Native_CPool<Native_CInteriorInst>*>(0x125D2E4, 0xE54D74);

				if (!pool)
					return nullptr;

				return gcnew CPool(pool, type);
			}
			case ePool::VehicleStructPool:
				break;
			case ePool::PedMoveBlendPool:
				break;
			case ePool::DummyPedPool:
			{
				Native_CPool<Native_CDummyPed>* pool = AddressSetter::GetRef<Native_CPool<Native_CDummyPed>*>(0x14A82BC, 0x14CB04C);

				if (!pool)
					return nullptr;

				return gcnew CPool(pool, type);
			}
			case ePool::DummyTaskPool:
			{
				Native_CPool<Native_CDummyTask>* pool = AddressSetter::GetRef<Native_CPool<Native_CDummyTask>*>(0x1306E8C, 0x128AAC0);

				if (!pool)
					return nullptr;

				return gcnew CPool(pool, type);
			}
			case ePool::UnkPedDataPool:
				break;
			case ePool::PedIntelligencePool:
				break;
			case ePool::AnimBlenderPool:
				break;
			case ePool::FragInstNMGtaPool:
				break;
			case ePool::PedDataPool:
				break;
			case ePool::QuadTreeNodePool:
				break;
			case ePool::TxdPool:
				break;
			case ePool::IplPool:
				break;
		}
		return nullptr;
	}

	UIntPtr CPool::Get(int slot)
	{
		// TODO: Complete pools.
		switch (Type) {
			case ePool::PedPool:
			{
				Native_CPed* ptr = GetNativePool<Native_CPed>()->Get(slot);

				if (!ptr)
					return UIntPtr::Zero;

				return UIntPtr(ptr);
			}
			case ePool::VehiclePool:
			{
				Native_CVehicle* ptr = GetNativePool<Native_CVehicle>()->Get(slot);

				if (!ptr)
					return UIntPtr::Zero;

				return UIntPtr(ptr);
			}
			case ePool::ObjectPool:
			{
				Native_CObject* ptr = GetNativePool<Native_CObject>()->Get(slot);

				if (!ptr)
					return UIntPtr::Zero;

				return UIntPtr(ptr);
			}
			case ePool::BuildingPool:
			{
				Native_CBuilding* ptr = GetNativePool<Native_CBuilding>()->Get(slot);

				if (!ptr)
					return UIntPtr::Zero;

				return UIntPtr(ptr);
			}
			case ePool::CameraPool:
			{
				Native_CCam* ptr = GetNativePool<Native_CCam>()->Get(slot);

				if (!ptr)
					return UIntPtr::Zero;

				return UIntPtr(ptr);
			}
			case ePool::TaskPool:
			{
				Native_CTask* ptr = GetNativePool<Native_CTask>()->Get(slot);

				if (!ptr)
					return UIntPtr::Zero;

				return UIntPtr(ptr);
			}
			case ePool::InteriorInstPool:
			{
				Native_CInteriorInst* ptr = GetNativePool<Native_CInteriorInst>()->Get(slot);

				if (!ptr)
					return UIntPtr::Zero;

				return UIntPtr(ptr);
			}
			case ePool::VehicleStructPool:
				break;
			case ePool::PedMoveBlendPool:
				break;
			case ePool::DummyPedPool:
			{
				Native_CDummyPed* ptr = GetNativePool<Native_CDummyPed>()->Get(slot);

				if (!ptr)
					return UIntPtr::Zero;

				return UIntPtr(ptr);
			}
			case ePool::DummyTaskPool:
			{
				Native_CDummyTask* ptr = GetNativePool<Native_CDummyTask>()->Get(slot);

				if (!ptr)
					return UIntPtr::Zero;

				return UIntPtr(ptr);
			}
			case ePool::UnkPedDataPool:
				break;
			case ePool::PedIntelligencePool:
				break;
			case ePool::AnimBlenderPool:
				break;
			case ePool::FragInstNMGtaPool:
				break;
			case ePool::PedDataPool:
				break;
			case ePool::QuadTreeNodePool:
				break;
			case ePool::TxdPool:
				break;
			case ePool::IplPool:
				break;
		}
		return UIntPtr::Zero;
	}
	UIntPtr CPool::GetAt(uint32_t nHandle)
	{
		// TODO: Complete pools.
		switch (Type) {
			case ePool::PedPool:
			{
				Native_CPed* ptr = GetNativePool<Native_CPed>()->GetAt(nHandle);

				if (!ptr)
					return UIntPtr::Zero;

				return UIntPtr(ptr);
			}
			case ePool::VehiclePool:
			{
				Native_CVehicle* ptr = GetNativePool<Native_CVehicle>()->GetAt(nHandle);

				if (!ptr)
					return UIntPtr::Zero;

				return UIntPtr(ptr);
			}
			case ePool::ObjectPool:
			{
				Native_CObject* ptr = GetNativePool<Native_CObject>()->GetAt(nHandle);

				if (!ptr)
					return UIntPtr::Zero;

				return UIntPtr(ptr);
			}
			case ePool::BuildingPool:
			{
				Native_CBuilding* ptr = GetNativePool<Native_CBuilding>()->GetAt(nHandle);

				if (!ptr)
					return UIntPtr::Zero;

				return UIntPtr(ptr);
			}
			case ePool::CameraPool:
			{
				Native_CCam* ptr = GetNativePool<Native_CCam>()->GetAt(nHandle);

				if (!ptr)
					return UIntPtr::Zero;

				return UIntPtr(ptr);
			}
			case ePool::TaskPool:
			{
				Native_CTask* ptr = GetNativePool<Native_CTask>()->GetAt(nHandle);

				if (!ptr)
					return UIntPtr::Zero;

				return UIntPtr(ptr);
			}
			case ePool::InteriorInstPool:
			{
				Native_CInteriorInst* ptr = GetNativePool<Native_CInteriorInst>()->GetAt(nHandle);

				if (!ptr)
					return UIntPtr::Zero;

				return UIntPtr(ptr);
			}
			case ePool::VehicleStructPool:
				break;
			case ePool::PedMoveBlendPool:
				break;
			case ePool::DummyPedPool:
			{
				Native_CDummyPed* ptr = GetNativePool<Native_CDummyPed>()->GetAt(nHandle);

				if (!ptr)
					return UIntPtr::Zero;

				return UIntPtr(ptr);
			}
			case ePool::DummyTaskPool:
			{
				Native_CDummyTask* ptr = GetNativePool<Native_CDummyTask>()->GetAt(nHandle);

				if (!ptr)
					return UIntPtr::Zero;

				return UIntPtr(ptr);
			}
			case ePool::UnkPedDataPool:
				break;
			case ePool::PedIntelligencePool:
				break;
			case ePool::AnimBlenderPool:
				break;
			case ePool::FragInstNMGtaPool:
				break;
			case ePool::PedDataPool:
				break;
			case ePool::QuadTreeNodePool:
				break;
			case ePool::TxdPool:
				break;
			case ePool::IplPool:
				break;
		}
		return UIntPtr::Zero;
	}
	uint32_t CPool::GetIndex(UIntPtr pObject)
	{
		// TODO: Complete pools.
		switch (Type) {
			case ePool::PedPool:				return GetNativePool<Native_CPed>()->GetIndex((Native_CPed*)pObject.ToPointer());
			case ePool::VehiclePool:			return GetNativePool<Native_CVehicle>()->GetIndex((Native_CVehicle*)pObject.ToPointer());
			case ePool::ObjectPool:				return GetNativePool<Native_CObject>()->GetIndex((Native_CObject*)pObject.ToPointer());
			case ePool::BuildingPool:			return GetNativePool<Native_CBuilding>()->GetIndex((Native_CBuilding*)pObject.ToPointer());
			case ePool::CameraPool:				return GetNativePool<Native_CCam>()->GetIndex((Native_CCam*)pObject.ToPointer());
			case ePool::TaskPool:				return GetNativePool<Native_CTask>()->GetIndex((Native_CTask*)pObject.ToPointer());
			case ePool::InteriorInstPool:		return GetNativePool<Native_CInteriorInst>()->GetIndex((Native_CInteriorInst*)pObject.ToPointer());
			case ePool::VehicleStructPool:		break;
			case ePool::PedMoveBlendPool:		break;
			case ePool::DummyPedPool:			return GetNativePool<Native_CDummyPed>()->GetIndex((Native_CDummyPed*)pObject.ToPointer());
			case ePool::DummyTaskPool:			return GetNativePool<Native_CDummyTask>()->GetIndex((Native_CDummyTask*)pObject.ToPointer());
			case ePool::UnkPedDataPool:			break;
			case ePool::PedIntelligencePool:	break;
			case ePool::AnimBlenderPool:		break;
			case ePool::FragInstNMGtaPool:		break;
			case ePool::PedDataPool:			break;
			case ePool::QuadTreeNodePool:		break;
			case ePool::TxdPool:				break;
			case ePool::IplPool:				break;
		}
		return 0;
	}

	UIntPtr CPool::New()
	{
		// TODO: Complete pools.
		switch (Type) {
			case ePool::PedPool:				return UIntPtr(GetNativePool<Native_CPed>()->New());
			case ePool::VehiclePool:			return UIntPtr(GetNativePool<Native_CVehicle>()->New());
			case ePool::ObjectPool:				return UIntPtr(GetNativePool<Native_CObject>()->New());
			case ePool::BuildingPool:			return UIntPtr(GetNativePool<Native_CBuilding>()->New());
			case ePool::CameraPool:				return UIntPtr(GetNativePool<Native_CCam>()->New());
			case ePool::TaskPool:				return UIntPtr(GetNativePool<Native_CTask>()->New());
			case ePool::InteriorInstPool:		return UIntPtr(GetNativePool<Native_CInteriorInst>()->New());
			case ePool::VehicleStructPool:		break;
			case ePool::PedMoveBlendPool:		break;
			case ePool::DummyPedPool:			return UIntPtr(GetNativePool<Native_CDummyPed>()->New());
			case ePool::DummyTaskPool:			return UIntPtr(GetNativePool<Native_CDummyTask>()->New());
			case ePool::UnkPedDataPool:			break;
			case ePool::PedIntelligencePool:	break;
			case ePool::AnimBlenderPool:		break;
			case ePool::FragInstNMGtaPool:		break;
			case ePool::PedDataPool:			break;
			case ePool::QuadTreeNodePool:		break;
			case ePool::TxdPool:				break;
			case ePool::IplPool:				break;
		}
		return UIntPtr::Zero;
	}

	// Helper
	bool CPool::IsValid(int slot)
	{
		// TODO: Complete pools.
		switch (Type) {
			case ePool::PedPool:				return GetNativePool<Native_CPed>()->IsValid(slot);
			case ePool::VehiclePool:			return GetNativePool<Native_CVehicle>()->IsValid(slot);
			case ePool::ObjectPool:				return GetNativePool<Native_CObject>()->IsValid(slot);
			case ePool::BuildingPool:			return GetNativePool<Native_CBuilding>()->IsValid(slot);
			case ePool::CameraPool:				return GetNativePool<Native_CCam>()->IsValid(slot);
			case ePool::TaskPool:				return GetNativePool<Native_CTask>()->IsValid(slot);
			case ePool::InteriorInstPool:		return GetNativePool<Native_CInteriorInst>()->IsValid(slot);
			case ePool::VehicleStructPool:		break;
			case ePool::PedMoveBlendPool:		break;
			case ePool::DummyPedPool:			return GetNativePool<Native_CDummyPed>()->IsValid(slot);
			case ePool::DummyTaskPool:			return GetNativePool<Native_CDummyTask>()->IsValid(slot);
			case ePool::UnkPedDataPool:			break;
			case ePool::PedIntelligencePool:	break;
			case ePool::AnimBlenderPool:		break;
			case ePool::FragInstNMGtaPool:		break;
			case ePool::PedDataPool:			break;
			case ePool::QuadTreeNodePool:		break;
			case ePool::TxdPool:				break;
			case ePool::IplPool:				break;
		}
		return false;
	}

	template<typename T>
	Native_CPool<T>* CPool::GetNativePool()
	{
		return (Native_CPool<T>*)PoolPointer;
	}

}