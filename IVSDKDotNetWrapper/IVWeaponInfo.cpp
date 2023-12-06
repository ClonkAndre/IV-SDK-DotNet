#include "pch.h"
#include "IVWeaponInfo.h"

namespace IVSDKDotNet
{

    // - - - Constructor - - -
    IVWeaponFlags::IVWeaponFlags(CWeaponInfo* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeWeaponInfo = nativePtr;
    }
    IVWeaponInfo::IVWeaponInfo(CWeaponInfo* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeWeaponInfo = nativePtr;
    }

    // - - - Methods / Functions - - -
    IVWeaponInfo^ IVWeaponInfo::GetWeaponInfo(uint32_t weaponID)
    {
        CWeaponInfo* ptr = CWeaponInfo::GetWeaponInfo(weaponID);
        NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);
        return gcnew IVWeaponInfo(ptr);
    }
    void IVWeaponInfo::LoadWeaponData(String^ path)
    {
        CHECK_NULL_OR_WHITESPACE_STRING(path);
        msclr::interop::marshal_context ctx;
        CWeaponInfo::LoadWeaponData(ctx.marshal_as<const char*>(path));
    }
    int IVWeaponInfo::FindWeaponType(uint32_t nameHash, int defaultReturn)
    {
        return CWeaponInfo::FindWeaponType(nameHash, defaultReturn);
    }
    int IVWeaponInfo::FindWeaponType(String^ pString, int defaultReturn)
    {
        CHECK_NULL_OR_WHITESPACE_STRING_WITH_RETURN(pString, defaultReturn);
        msclr::interop::marshal_context ctx;
        return CWeaponInfo::FindWeaponType(ctx.marshal_as<const char*>(pString), defaultReturn);
    }
    int IVWeaponInfo::FindWeaponFireType(String^ pString)
    {
        CHECK_NULL_OR_WHITESPACE_STRING_WITH_RETURN(pString, 0);
        msclr::interop::marshal_context ctx;
        return CWeaponInfo::FindWeaponFireType(ctx.marshal_as<const char*>(pString));
    }
    int IVWeaponInfo::FindWeaponDamageType(String^ pString)
    {
        CHECK_NULL_OR_WHITESPACE_STRING_WITH_RETURN(pString, 0);
        msclr::interop::marshal_context ctx;
        return CWeaponInfo::FindWeaponDamageType(ctx.marshal_as<const char*>(pString));
    }

}