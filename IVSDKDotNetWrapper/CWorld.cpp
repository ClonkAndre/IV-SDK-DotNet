#include "pch.h"
#include "CWorld.h"

namespace IVSDKDotNet {

	tLineOfSightResults::tLineOfSightResults(Native_tLineOfSightResults native)
	{
		m_pInst = native.m_pInst;
		m_vEndPosition = Vector3(native.m_vEndPosition.x, native.m_vEndPosition.y, native.m_vEndPosition.z);
		m_nUnkFlags = native.m_nUnkFlags;
		m_vUnk = Vector3(native.m_vUnk.x, native.m_vUnk.y, native.m_vUnk.z);
		m_nUnkFlags2 = native.m_nUnkFlags2;
		m_vUnk2 = Vector3(native.m_vUnk2.x, native.m_vUnk2.y, native.m_vUnk2.z);;
		m_nUnkFlags3 = native.m_nUnkFlags3;
		m_fUnk1 = native.m_fUnk1;
		m_fUnk2 = native.m_fUnk2;
		m_nUnkFlags4 = native.m_nUnkFlags4;
		m_nUnkFlags5 = native.m_nUnkFlags5;
		m_nUnkFlags6 = native.m_nUnkFlags6;
	}

	void CWorld::Add(CEntity^ entity, bool bUnk)
	{
		Native_CWorld::Add(entity->EntityPointer, bUnk);
	}
	void CWorld::Remove(CEntity^ entity, bool bUnk)
	{
		Native_CWorld::Remove(entity->EntityPointer, bUnk);
	}

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

	bool CWorld::ProcessLineOfSight(Vector3 source, Vector3 target, UIntPtr pUnk, [OutAttribute] tLineOfSightResults% pResults, uint32_t nFlags, uint32_t nUnk1, uint32_t nUnk2, uint32_t nSeeThroughShootThrough, uint32_t nUnk4)
	{
		Native_CVector* s = new Native_CVector(source);
		Native_CVector* t = new Native_CVector(target);

		Native_tLineOfSightResults nativeLineOfSightResults;
		bool result = Native_CWorld::ProcessLineOfSight(s, t, (uint32_t*)pUnk.ToPointer(), &nativeLineOfSightResults, nFlags, nUnk1, nUnk2, nSeeThroughShootThrough, nUnk4);

		pResults = tLineOfSightResults(nativeLineOfSightResults);

		delete s;
		delete t;

		return result;
	}
	bool CWorld::ProcessLineOfSight(Vector3 source, Vector3 target, [OutAttribute] tLineOfSightResults% pResults, uint32_t nSeeThroughShootThrough)
	{
		return CWorld::ProcessLineOfSight(source, target, UIntPtr::Zero, pResults, 142, 1, 0, nSeeThroughShootThrough, 4);;
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