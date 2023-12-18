#include "pch.h"
#include "IVPhysical.h"

namespace IVSDKDotNet
{
    
    // - - - Constructor - - -
    IVPhysicalFlags::IVPhysicalFlags(CPhysical* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativePhysical = nativePtr;
    }
    IVPhysical::IVPhysical(CPhysical* nativePtr) : IVDynamicEntity(nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativePhysical = nativePtr;
    }

    // - - - Methods / Functions - - -
    UIntPtr IVPhysical::GetConstrainedCollider()
    {
        NULLPTR_CHECK_WITH_RETURN(NativePhysical, UIntPtr::Zero);

        rage::phConstrainedCollider* ptr = NativePhysical->GetConstrainedCollider();
        NULLPTR_CHECK_WITH_RETURN(ptr, UIntPtr::Zero);

        return UIntPtr(ptr);
    }
    Vector3 IVPhysical::GetVelocity(Vector3 v)
    {
        NULLPTR_CHECK_WITH_RETURN(NativePhysical, Vector3::Zero);

        CVector* nv = new CVector();
        nv->x = v.X;
        nv->y = v.Y;
        nv->z = v.Z;

        CVector* ptr = NativePhysical->GetVelocity(nv);

        delete nv;

        NULLPTR_CHECK_WITH_RETURN(NativePhysical, Vector3::Zero);

        return Vector3(ptr->x, ptr->y, ptr->z);
    }
    bool IVPhysical::_ProcessWater()
    {
        NULLPTR_CHECK_WITH_RETURN(NativePhysical, false);
        return NativePhysical->_ProcessWater();
    }
    bool IVPhysical::ProcessWater()
    {
        NULLPTR_CHECK_WITH_RETURN(NativePhysical, false);
        return NativePhysical->ProcessWater();
    }
    float IVPhysical::GetHealth()
    {
        NULLPTR_CHECK_WITH_RETURN(NativePhysical, 0.0F);
        return NativePhysical->GetHealth();
    }

}