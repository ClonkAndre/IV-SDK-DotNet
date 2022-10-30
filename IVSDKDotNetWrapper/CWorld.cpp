#include "pch.h"
#include "CWorld.h"

namespace IVSDKDotNet {

	void CWorld::RemoveFallenPeds()
	{
		Native_CWorld::RemoveFallenPeds();
	}
	void CWorld::RemoveFallenCars()
	{
		Native_CWorld::RemoveFallenCars();
	}
	void CWorld::RemoveFallenObjects()
	{
		Native_CWorld::RemoveFallenObjects();
	}

	void CWorld::RequestModel(int model)
	{
		Native_CWorld::RequestModel(model);
	}

	Vector3 CWorld::GetNextPositionOnPavement(Vector3 pos)
	{
		float x, y, z;
		Natives::GET_SAFE_POSITION_FOR_CHAR(pos.X, pos.Y, pos.Z, true, x, y, z);
		return Vector3(x, y, z);
	}
	Vector3 CWorld::GetNextPositionOnStreet(Vector3 pos)
	{
		float x, y, z, h;
		uint32_t inArea, outArea;
		inArea = Natives::GET_MAP_AREA_FROM_COORDS(pos);

		Natives::GET_NTH_CLOSEST_CAR_NODE_WITH_HEADING_ON_ISLAND(pos.X, pos.Y, pos.Z, 1, inArea, x, y, z, h, outArea);
		return Vector3(x, y, z);
	}

}