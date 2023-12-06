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