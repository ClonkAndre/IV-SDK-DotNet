#include "pch.h"
#include "IVIplStore.h"

namespace IVSDKDotNet
{
    // - - - Methods / Functions - - -
    void IVIplStore::LoadIpls(Vector3 pos, bool unk)
    {
        CIplStore::LoadIpls(VectorToCVector(pos), unk);
    }
    void IVIplStore::SetIplsRequired(Vector3 pos)
    {
        CIplStore::SetIplsRequired(VectorToCVector(pos));
    }
    void IVIplStore::SetIfIplIsRequiredAtPos(Vector2 pos, UIntPtr def)
    {
        UINTPTR_ZERO_CHECK(def);
        SetIfIplIsRequired(&Vector2ToCVector2D(pos), (IplDef*)def.ToPointer());
    }
    void IVIplStore::SetIfIplIsRequiredAtPosReducedBB(Vector2 pos, UIntPtr def)
    {
        UINTPTR_ZERO_CHECK(def);
        SetIfIplIsRequiredReducedBB(&Vector2ToCVector2D(pos), (IplDef*)def.ToPointer());
    }
}