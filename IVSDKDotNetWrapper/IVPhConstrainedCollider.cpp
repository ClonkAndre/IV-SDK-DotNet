#include "pch.h"
#include "IVPhConstrainedCollider.h"

namespace IVSDKDotNet
{

    // - - - Constructor - - -
    IVPhConstrainedCollider::IVPhConstrainedCollider(rage::phConstrainedCollider* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeConstrainedCollider = nativePtr;
    }

    // - - - Methods / Functions - - -
    IVPhConstrainedCollider^ IVPhConstrainedCollider::FromUIntPtr(UIntPtr ptr)
    {
        UINTPTR_ZERO_CHECK_WITH_RETURN(ptr, nullptr);
        return gcnew IVPhConstrainedCollider((rage::phConstrainedCollider*)ptr.ToPointer());
    }
    UIntPtr IVPhConstrainedCollider::GetUIntPtr()
    {
        NULLPTR_CHECK_WITH_RETURN(NativeConstrainedCollider, UIntPtr::Zero);
        return UIntPtr(NativeConstrainedCollider);
    }

    void IVPhConstrainedCollider::SetVelocity(Vector3 v)
    {
        NULLPTR_CHECK(NativeConstrainedCollider);

        CVector* nV = new CVector();
        nV->x = v.X;
        nV->y = v.Y;
        nV->z = v.Z;

        NativeConstrainedCollider->SetVelocity(nV);

        delete nV;
    }

}