#include "pch.h"
#include "IVPools.h"

namespace IVSDKDotNet
{

	// - - - Methods / Functions
	IVPool^ IVPools::GetPedPool()
	{
		return IVPool::GetFromType(ePool::PedPool);
	}
	IVPool^ IVPools::GetVehiclePool()
	{
		return IVPool::GetFromType(ePool::VehiclePool);
	}
	IVPool^ IVPools::GetBuildingPool()
	{
		return IVPool::GetFromType(ePool::BuildingPool);
	}
	IVPool^ IVPools::GetObjectPool()
	{
		return IVPool::GetFromType(ePool::ObjectPool);
	}
	IVPool^ IVPools::GetCameraPool()
	{
		return IVPool::GetFromType(ePool::CameraPool);
	}
	IVPool^ IVPools::GetTaskPool()
	{
		return IVPool::GetFromType(ePool::TaskPool);
	}
	IVPool^ IVPools::GetInteriorInstPool()
	{
		return IVPool::GetFromType(ePool::InteriorInstPool);
	}
	IVPool^ IVPools::GetVehicleStructPool()
	{
		return IVPool::GetFromType(ePool::VehicleStructPool);
	}
	IVPool^ IVPools::GetPedMoveBlendPool()
	{
		return IVPool::GetFromType(ePool::PedMoveBlendPool);
	}
	IVPool^ IVPools::GetDummyPedPool()
	{
		return IVPool::GetFromType(ePool::DummyPedPool);
	}
	IVPool^ IVPools::GetDummyTaskPool()
	{
		return IVPool::GetFromType(ePool::DummyTaskPool);
	}
	IVPool^ IVPools::GetUnkPedDataPool()
	{
		return IVPool::GetFromType(ePool::UnkPedDataPool);
	}
	IVPool^ IVPools::GetPedIntelligencePool()
	{
		return IVPool::GetFromType(ePool::PedIntelligencePool);
	}
	IVPool^ IVPools::GetAnimBlenderPool()
	{
		return IVPool::GetFromType(ePool::AnimBlenderPool);
	}
	IVPool^ IVPools::GetFragInstNMGtaPool()
	{
		return IVPool::GetFromType(ePool::FragInstNMGtaPool);
	}
	IVPool^ IVPools::GetPedDataPool()
	{
		return IVPool::GetFromType(ePool::PedDataPool);
	}
	IVPool^ IVPools::GetQuadTreeNodePool()
	{
		return IVPool::GetFromType(ePool::QuadTreeNodePool);
	}
	IVPool^ IVPools::GetTxdPool()
	{
		return IVPool::GetFromType(ePool::TxdPool);
	}
	IVPool^ IVPools::GetIplPool()
	{
		return IVPool::GetFromType(ePool::IplPool);
	}
	IVPool^ IVPools::GetPedTargettingPool()
	{
		return IVPool::GetFromType(ePool::PedTargettingPool);
	}
	IVPool^ IVPools::GetStuntJumpPool()
	{
		return IVPool::GetFromType(ePool::StuntJumpPool);
	}
	IVPool^ IVPools::GetScriptStorePool()
	{
		return IVPool::GetFromType(ePool::ScriptStorePool);
	}

}