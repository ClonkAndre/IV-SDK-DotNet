#include "pch.h"
#include "IVPool.h"

namespace IVSDKDotNet
{

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
		
		uint32_t* ptr = GetNativePool<uint32_t>()->Get(slot);
		NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);
		return UIntPtr(ptr);
	}
	UIntPtr IVPool::GetAt(uint32_t nHandle)
	{
		NULLPTR_CHECK_WITH_RETURN(NativePool, UIntPtr::Zero);
		
		uint32_t* ptr = GetNativePool<uint32_t>()->GetAt(nHandle);
		NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);
		return UIntPtr(ptr);
	}
	uint32_t IVPool::GetIndex(UIntPtr pObject)
	{
		NULLPTR_CHECK_WITH_RETURN(NativePool, 0);
		return GetNativePool<uint32_t>()->GetIndex((uint32_t*)pObject.ToPointer());
	}
	UIntPtr IVPool::New()
	{
		NULLPTR_CHECK_WITH_RETURN(NativePool, UIntPtr::Zero);
		return UIntPtr(GetNativePool<uint32_t>()->New());
	}
	bool IVPool::IsValid(int slot)
	{
		NULLPTR_CHECK_WITH_RETURN(NativePool, false);
		return GetNativePool<uint32_t>()->IsValid(slot);
	}

	IVPool^ IVPool::GetFromType(ePool type)
	{
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
			case ePool::ScriptStorePool:
			{
				NULLPTR_CHECK_WITH_RETURN(CPools::ms_pScriptStorePool, nullptr);
				return gcnew IVPool(CPools::ms_pScriptStorePool, type);
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