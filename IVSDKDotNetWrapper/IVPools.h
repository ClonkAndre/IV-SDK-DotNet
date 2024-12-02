#pragma once

namespace IVSDKDotNet
{
	public ref class IVPools
	{
	public:
		static IVPool^ GetPedPool();
		static IVPool^ GetVehiclePool();
		static IVPool^ GetBuildingPool();
		static IVPool^ GetObjectPool();
		static IVPool^ GetCameraPool();
		static IVPool^ GetTaskPool();
		static IVPool^ GetInteriorInstPool();
		static IVPool^ GetVehicleStructPool();
		static IVPool^ GetPedMoveBlendPool();
		static IVPool^ GetDummyPedPool();
		static IVPool^ GetDummyTaskPool();
		static IVPool^ GetUnkPedDataPool();
		static IVPool^ GetPedIntelligencePool();
		static IVPool^ GetAnimBlenderPool();
		static IVPool^ GetFragInstNMGtaPool();
		static IVPool^ GetPedDataPool();
		static IVPool^ GetQuadTreeNodePool();
		static IVPool^ GetTxdPool();
		static IVPool^ GetIplPool();
		static IVPool^ GetPedTargettingPool();
		static IVPool^ GetStuntJumpPool();
		static IVPool^ GetScriptStorePool();
	};
}