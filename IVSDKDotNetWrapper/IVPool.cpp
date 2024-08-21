#include "pch.h"
#include "IVPool.h"

namespace IVSDKDotNet
{

	// TODO: Cleanup this class.
	
	// - - - Constructor - - -
	template<typename T>
	IVPool::IVPool(T* nativePtr, ePool type)
	{
		NativePool = (uint32_t*)nativePtr;
		PoolType = type;
	}

	// - - - Methods / Functions - - -
	UIntPtr IVPool::Get(int slot)
	{
		NULLPTR_CHECK_WITH_RETURN(NativePool, UIntPtr::Zero);
		
		// TODO: Complete pools.
		switch(PoolType)
		{
			case ePool::PedPool:
			{
				CPed* ptr = GetNativePool<CPed>()->Get(slot);
				NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);
				return UIntPtr(ptr);
			}
			case ePool::VehiclePool:
			{
				CVehicle* ptr = GetNativePool<CVehicle>()->Get(slot);
				NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);
				return UIntPtr(ptr);
			}
			case ePool::ObjectPool:
			{
				CObject* ptr = GetNativePool<CObject>()->Get(slot);
				NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);
				return UIntPtr(ptr);
			}
			case ePool::BuildingPool:
			{
				CBuilding* ptr = GetNativePool<CBuilding>()->Get(slot);
				NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);
				return UIntPtr(ptr);
			}
			case ePool::CameraPool:
			{
				CCam* ptr = GetNativePool<CCam>()->Get(slot);
				NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);
				return UIntPtr(ptr);
			}
			case ePool::TaskPool:
			{
				CTask* ptr = GetNativePool<CTask>()->Get(slot);
				NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);
				return UIntPtr(ptr);
			}
			case ePool::InteriorInstPool:
			{
				CInteriorInst* ptr = GetNativePool<CInteriorInst>()->Get(slot);
				NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);
				return UIntPtr(ptr);
			}
			case ePool::VehicleStructPool:
				break;
			case ePool::PedMoveBlendPool:
			{
				CPedMoveBlendOnFoot* ptr = GetNativePool<CPedMoveBlendOnFoot>()->Get(slot);
				NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);
				return UIntPtr(ptr);
			}
			case ePool::DummyPedPool:
			{
				// CDummyPed
				uint32_t* ptr = GetNativePool<uint32_t>()->Get(slot);
				NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);
				return UIntPtr(ptr);
			}
			case ePool::DummyTaskPool:
			{
				// CDummyTask
				uint32_t* ptr = GetNativePool<uint32_t>()->Get(slot);
				NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);
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
			case ePool::PedTargettingPool:
			{
				// CPedTargetting
				uint32_t* ptr = GetNativePool<uint32_t>()->Get(slot);
				NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);
				return UIntPtr(ptr);
			}
			case ePool::StuntJumpPool:
			{
				CStuntJump* ptr = GetNativePool<CStuntJump>()->Get(slot);
				NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);
				return UIntPtr(ptr);
			}
		}

		return UIntPtr::Zero;
	}
	UIntPtr IVPool::GetAt(uint32_t nHandle)
	{
		NULLPTR_CHECK_WITH_RETURN(NativePool, UIntPtr::Zero);
		
		// TODO: Complete pools.
		switch(PoolType)
		{
			case ePool::PedPool:
			{
				CPed* ptr = GetNativePool<CPed>()->GetAt(nHandle);
				NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);
				return UIntPtr(ptr);
			}
			case ePool::VehiclePool:
			{
				CVehicle* ptr = GetNativePool<CVehicle>()->GetAt(nHandle);
				NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);
				return UIntPtr(ptr);
			}
			case ePool::ObjectPool:
			{
				CObject* ptr = GetNativePool<CObject>()->GetAt(nHandle);
				NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);
				return UIntPtr(ptr);
			}
			case ePool::BuildingPool:
			{
				CBuilding* ptr = GetNativePool<CBuilding>()->GetAt(nHandle);
				NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);
				return UIntPtr(ptr);
			}
			case ePool::CameraPool:
			{
				CCam* ptr = GetNativePool<CCam>()->GetAt(nHandle);
				NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);
				return UIntPtr(ptr);
			}
			case ePool::TaskPool:
			{
				CTask* ptr = GetNativePool<CTask>()->GetAt(nHandle);
				NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);
				return UIntPtr(ptr);
			}
			case ePool::InteriorInstPool:
			{
				CInteriorInst* ptr = GetNativePool<CInteriorInst>()->GetAt(nHandle);
				NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);
				return UIntPtr(ptr);
			}
			case ePool::VehicleStructPool:
				break;
			case ePool::PedMoveBlendPool:
			{
				CPedMoveBlendOnFoot* ptr = GetNativePool<CPedMoveBlendOnFoot>()->GetAt(nHandle);
				NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);
				return UIntPtr(ptr);
			}
			case ePool::DummyPedPool:
			{
				// CDummyPed
				uint32_t* ptr = GetNativePool<uint32_t>()->GetAt(nHandle);
				NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);
				return UIntPtr(ptr);
			}
			case ePool::DummyTaskPool:
			{
				// CDummyTask
				uint32_t* ptr = GetNativePool<uint32_t>()->GetAt(nHandle);
				NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);
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
			case ePool::PedTargettingPool:
			{
				// CPedTargetting
				uint32_t* ptr = GetNativePool<uint32_t>()->GetAt(nHandle);
				NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);
				return UIntPtr(ptr);
			}
			case ePool::StuntJumpPool:
			{
				CStuntJump* ptr = GetNativePool<CStuntJump>()->GetAt(nHandle);
				NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);
				return UIntPtr(ptr);
			}
		}

		return UIntPtr::Zero;
	}
	uint32_t IVPool::GetIndex(UIntPtr pObject)
	{
		NULLPTR_CHECK_WITH_RETURN(NativePool, 0);
		
		// TODO: Complete pools.
		switch(PoolType)
		{
			case ePool::PedPool:				return GetNativePool<CPed>()->GetIndex((CPed*)pObject.ToPointer());
			case ePool::VehiclePool:			return GetNativePool<CVehicle>()->GetIndex((CVehicle*)pObject.ToPointer());
			case ePool::ObjectPool:				return GetNativePool<CObject>()->GetIndex((CObject*)pObject.ToPointer());
			case ePool::BuildingPool:			return GetNativePool<CBuilding>()->GetIndex((CBuilding*)pObject.ToPointer());
			case ePool::CameraPool:				return GetNativePool<CCam>()->GetIndex((CCam*)pObject.ToPointer());
			case ePool::TaskPool:				return GetNativePool<CTask>()->GetIndex((CTask*)pObject.ToPointer());
			case ePool::InteriorInstPool:		return GetNativePool<CInteriorInst>()->GetIndex((CInteriorInst*)pObject.ToPointer());
			case ePool::VehicleStructPool:		break;
			case ePool::PedMoveBlendPool:		return GetNativePool<CPedMoveBlendOnFoot>()->GetIndex((CPedMoveBlendOnFoot*)pObject.ToPointer());
			case ePool::DummyPedPool:			return GetNativePool<uint32_t>()->GetIndex((uint32_t*)pObject.ToPointer()); // CDummyPed
			case ePool::DummyTaskPool:			return GetNativePool<uint32_t>()->GetIndex((uint32_t*)pObject.ToPointer()); // CDummyTask
			case ePool::UnkPedDataPool:			break;
			case ePool::PedIntelligencePool:	break;
			case ePool::AnimBlenderPool:		break;
			case ePool::FragInstNMGtaPool:		break;
			case ePool::PedDataPool:			break;
			case ePool::QuadTreeNodePool:		break;
			case ePool::TxdPool:				break;
			case ePool::IplPool:				break;
			case ePool::PedTargettingPool:      return GetNativePool<uint32_t>()->GetIndex((uint32_t*)pObject.ToPointer()); // CPedTargetting
			case ePool::StuntJumpPool:          return GetNativePool<CStuntJump>()->GetIndex((CStuntJump*)pObject.ToPointer());
		}
		return 0;
	}
	UIntPtr IVPool::New()
	{
		NULLPTR_CHECK_WITH_RETURN(NativePool, UIntPtr::Zero);
		
		// TODO: Complete pools.
		switch(PoolType)
		{
			case ePool::PedPool:				return UIntPtr(GetNativePool<CPed>()->New());
			case ePool::VehiclePool:			return UIntPtr(GetNativePool<CVehicle>()->New());
			case ePool::ObjectPool:				return UIntPtr(GetNativePool<CObject>()->New());
			case ePool::BuildingPool:			return UIntPtr(GetNativePool<CBuilding>()->New());
			case ePool::CameraPool:				return UIntPtr(GetNativePool<CCam>()->New());
			case ePool::TaskPool:				return UIntPtr(GetNativePool<CTask>()->New());
			case ePool::InteriorInstPool:		return UIntPtr(GetNativePool<CInteriorInst>()->New());
			case ePool::VehicleStructPool:		break;
			case ePool::PedMoveBlendPool:		return UIntPtr(GetNativePool<CPedMoveBlendOnFoot>()->New());
			case ePool::DummyPedPool:			return UIntPtr(GetNativePool<uint32_t>()->New()); // CDummyPed
			case ePool::DummyTaskPool:			return UIntPtr(GetNativePool<uint32_t>()->New()); // CDummyTask
			case ePool::UnkPedDataPool:			break;
			case ePool::PedIntelligencePool:	break;
			case ePool::AnimBlenderPool:		break;
			case ePool::FragInstNMGtaPool:		break;
			case ePool::PedDataPool:			break;
			case ePool::QuadTreeNodePool:		break;
			case ePool::TxdPool:				break;
			case ePool::IplPool:				break;
			case ePool::PedTargettingPool:		return UIntPtr(GetNativePool<uint32_t>()->New()); // CPedTargetting
			case ePool::StuntJumpPool:		    return UIntPtr(GetNativePool<CStuntJump>()->New());
		}

		return UIntPtr::Zero;
	}
	bool IVPool::IsValid(int slot)
	{
		NULLPTR_CHECK_WITH_RETURN(NativePool, false);

		// TODO: Complete pools.
		switch (PoolType)
		{
			case ePool::PedPool:				return GetNativePool<CPed>()->IsValid(slot);
			case ePool::VehiclePool:			return GetNativePool<CVehicle>()->IsValid(slot);
			case ePool::ObjectPool:				return GetNativePool<CObject>()->IsValid(slot);
			case ePool::BuildingPool:			return GetNativePool<CBuilding>()->IsValid(slot);
			case ePool::CameraPool:				return GetNativePool<CCam>()->IsValid(slot);
			case ePool::TaskPool:				return GetNativePool<CTask>()->IsValid(slot);
			case ePool::InteriorInstPool:		return GetNativePool<CInteriorInst>()->IsValid(slot);
			case ePool::VehicleStructPool:		break;
			case ePool::PedMoveBlendPool:		return GetNativePool<CPedMoveBlendOnFoot>()->IsValid(slot);
			case ePool::DummyPedPool:			return GetNativePool<uint32_t>()->IsValid(slot); // CDummyPed
			case ePool::DummyTaskPool:			return GetNativePool<uint32_t>()->IsValid(slot); // CDummyTask
			case ePool::UnkPedDataPool:			break;
			case ePool::PedIntelligencePool:	break;
			case ePool::AnimBlenderPool:		break;
			case ePool::FragInstNMGtaPool:		break;
			case ePool::PedDataPool:			break;
			case ePool::QuadTreeNodePool:		break;
			case ePool::TxdPool:				break;
			case ePool::IplPool:				break;
			case ePool::PedTargettingPool:		return GetNativePool<uint32_t>()->IsValid(slot); // CPedTargetting
			case ePool::StuntJumpPool:		    return GetNativePool<CStuntJump>()->IsValid(slot);
		}

		return false;
	}

	IVPool^ IVPool::GetFromType(ePool type)
	{
		// TODO: Complete pools.
		switch(type)
		{
			case ePool::PedPool:
			{
				NULLPTR_CHECK_WITH_RETURN(CPools::ms_pPedPool, nullptr);
				return gcnew IVPool(CPools::ms_pPedPool, type);
			}
			case ePool::VehiclePool:
			{
				NULLPTR_CHECK_WITH_RETURN(CPools::ms_pVehiclePool, nullptr);
				return gcnew IVPool(CPools::ms_pVehiclePool, type);
			}
			case ePool::ObjectPool:
			{
				NULLPTR_CHECK_WITH_RETURN(CPools::ms_pObjectPool, nullptr);
				return gcnew IVPool(CPools::ms_pObjectPool, type);
			}
			case ePool::BuildingPool:
			{
				NULLPTR_CHECK_WITH_RETURN(CPools::ms_pBuildingPool, nullptr);
				return gcnew IVPool(CPools::ms_pBuildingPool, type);
			}
			case ePool::CameraPool:
			{
				NULLPTR_CHECK_WITH_RETURN(CPools::ms_pCameraPool, nullptr);
				return gcnew IVPool(CPools::ms_pCameraPool, type);
			}
			case ePool::TaskPool:
			{
				NULLPTR_CHECK_WITH_RETURN(CPools::ms_pTaskPool, nullptr);
				return gcnew IVPool(CPools::ms_pTaskPool, type);
			}
			case ePool::InteriorInstPool:
			{
				NULLPTR_CHECK_WITH_RETURN(CPools::ms_pInteriorInstPool, nullptr);
				return gcnew IVPool(CPools::ms_pInteriorInstPool, type);
			}
			case ePool::VehicleStructPool:
			{
				NULLPTR_CHECK_WITH_RETURN(CPools::ms_pVehicleStructPool, nullptr);
				return gcnew IVPool(CPools::ms_pVehicleStructPool, type);
			}
			case ePool::PedMoveBlendPool:
			{
				NULLPTR_CHECK_WITH_RETURN(CPools::ms_pPedMoveBlendPool, nullptr);
				return gcnew IVPool(CPools::ms_pPedMoveBlendPool, type);
			}
			case ePool::DummyPedPool:
			{
				NULLPTR_CHECK_WITH_RETURN(CPools::ms_pDummyPedPool, nullptr);
				return gcnew IVPool(CPools::ms_pDummyPedPool, type);
			}
			case ePool::DummyTaskPool:
			{
				NULLPTR_CHECK_WITH_RETURN(CPools::ms_pDummyTaskPool, nullptr);
				return gcnew IVPool(CPools::ms_pDummyTaskPool, type);
			}
			case ePool::UnkPedDataPool:
			{
				NULLPTR_CHECK_WITH_RETURN(CPools::ms_pUnkPedDataPool, nullptr);
				return gcnew IVPool(CPools::ms_pUnkPedDataPool, type);
			}
			case ePool::PedIntelligencePool:
			{
				NULLPTR_CHECK_WITH_RETURN(CPools::ms_pPedIntelligencePool, nullptr);
				return gcnew IVPool(CPools::ms_pPedIntelligencePool, type);
			}
			case ePool::AnimBlenderPool:
			{
				NULLPTR_CHECK_WITH_RETURN(CPools::ms_pAnimBlenderPool, nullptr);
				return gcnew IVPool(CPools::ms_pAnimBlenderPool, type);
			}
			case ePool::FragInstNMGtaPool:
			{
				NULLPTR_CHECK_WITH_RETURN(CPools::ms_pFragInstNMGtaPool, nullptr);
				return gcnew IVPool(CPools::ms_pFragInstNMGtaPool, type);
			}
			case ePool::PedDataPool:
			{
				NULLPTR_CHECK_WITH_RETURN(CPools::ms_pPedDataPool, nullptr);
				return gcnew IVPool(CPools::ms_pPedDataPool, type);
			}
			case ePool::QuadTreeNodePool:
			{
				NULLPTR_CHECK_WITH_RETURN(CPools::ms_pQuadTreeNodePool, nullptr);
				return gcnew IVPool(CPools::ms_pQuadTreeNodePool, type);
			}
			case ePool::TxdPool:
			{
				NULLPTR_CHECK_WITH_RETURN(CPools::ms_pTxdPool, nullptr);
				return gcnew IVPool(CPools::ms_pTxdPool, type);
			}
			case ePool::IplPool:
			{
				NULLPTR_CHECK_WITH_RETURN(CPools::ms_pIplPool, nullptr);
				return gcnew IVPool(CPools::ms_pIplPool, type);
			}
			case ePool::PedTargettingPool:
			{
				NULLPTR_CHECK_WITH_RETURN(CPools::ms_pPedTargettingPool, nullptr);
				return gcnew IVPool(CPools::ms_pPedTargettingPool, type);
			}
			case ePool::StuntJumpPool:
			{
				NULLPTR_CHECK_WITH_RETURN(CStuntJumpManager::mp_poolStuntJumps, nullptr);
				return gcnew IVPool(CStuntJumpManager::mp_poolStuntJumps, type);
			}
		}

		return nullptr;
	}

	template<typename T>
	CPool<T>* IVPool::GetNativePool()
	{
		return (CPool<T>*)NativePool;
	}

}