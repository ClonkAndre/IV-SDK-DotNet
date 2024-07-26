#include "pch.h"
#include "IVWorld.h"

namespace IVSDKDotNet
{
    // - - - Methods / Functions - - -
    void IVWorld::Add(UIntPtr entity, bool bUnk)
    {
        UINTPTR_ZERO_CHECK(entity);
        CWorld::Add((CEntity*)entity.ToPointer(), bUnk);
    }
    void IVWorld::Remove(UIntPtr entity, bool bUnk)
    {
        UINTPTR_ZERO_CHECK(entity);
        CWorld::Remove((CEntity*)entity.ToPointer(), bUnk);
    }
    void IVWorld::RemoveFallenPeds()
    {
        CWorld::RemoveFallenPeds();
    }
    void IVWorld::RemoveFallenCars()
    {
        CWorld::RemoveFallenCars();
    }
    void IVWorld::RemoveFallenObjects()
    {
        CWorld::RemoveFallenObjects();
    }

    bool IVWorld::ProcessLineOfSight(Vector3 source, Vector3 target, UIntPtr pUnk, [OutAttribute] IVLineOfSightResults% pResults, uint32_t nFlags, uint32_t nUnk1, uint32_t nUnk2, uint32_t nSeeThroughShootThrough, uint32_t nUnk4)
    {
        CVector* nSource = new CVector();
        nSource->x = source.X;
        nSource->y = source.Y;
        nSource->z = source.Z;
        CVector* nTarget = new CVector();
        nTarget->x = target.X;
        nTarget->y = target.Y;
        nTarget->z = target.Z;

        tLineOfSightResults lineOfSightResult;
        bool result = CWorld::ProcessLineOfSight(nSource, nTarget, pUnk == UIntPtr::Zero ? (uint32_t)0 : (uint32_t*)pUnk.ToPointer(), &lineOfSightResult, nFlags, nUnk1, nUnk2, nSeeThroughShootThrough, nUnk4);

        delete nSource;
        delete nTarget;

        if (result)
            pResults = IVLineOfSightResults(&lineOfSightResult);
        else
            pResults = IVLineOfSightResults::Empty();

        return result;
    }
    bool IVWorld::ProcessLineOfSight(Vector3 source, Vector3 target, [OutAttribute] IVLineOfSightResults% pResults, uint32_t nSeeThroughShootThrough)
    {
        CVector* nSource = new CVector();
        nSource->x = source.X;
        nSource->y = source.Y;
        nSource->z = source.Z;
        CVector* nTarget = new CVector();
        nTarget->x = target.X;
        nTarget->y = target.Y;
        nTarget->z = target.Z;

        tLineOfSightResults lineOfSightResult;
        bool result = CWorld::ProcessLineOfSight(nSource, nTarget, (uint32_t)0, &lineOfSightResult, 142, 1, 0, nSeeThroughShootThrough, 4);

        delete nSource;
        delete nTarget;

        if(result)
            pResults = IVLineOfSightResults(&lineOfSightResult);
        else
            pResults = IVLineOfSightResults::Empty();

        return result;
    }
}