#include "pch.h"
#include "IVTxdStore.h"

namespace IVSDKDotNet
{
    // - - - Methods / Functions - - -
    void IVTxdStore::AddRef(int slot)
    {
        CTxdStore::AddRef(slot);
    }
    int IVTxdStore::AddTxdSlot(String^ sName)
    {
        CHECK_NULL_OR_WHITESPACE_STRING_WITH_RETURN(sName, 0);
        msclr::interop::marshal_context ctx;
        return CTxdStore::AddTxdSlot((char*)ctx.marshal_as<const char*>(sName));
    }
    int IVTxdStore::FindTxdSlot(uint32_t nHash)
    {
        return CTxdStore::FindTxdSlot(nHash);
    }
    int IVTxdStore::FindTxdSlot(String^ sName)
    {
        CHECK_NULL_OR_WHITESPACE_STRING_WITH_RETURN(sName, 0);
        msclr::interop::marshal_context ctx;
        return CTxdStore::FindTxdSlot((char*)ctx.marshal_as<const char*>(sName));
    }
    bool IVTxdStore::LoadTxd(int slot, String^ sName)
    {
        CHECK_NULL_OR_WHITESPACE_STRING_WITH_RETURN(sName, false);
        msclr::interop::marshal_context ctx;
        return CTxdStore::LoadTxd(slot, (char*)ctx.marshal_as<const char*>(sName));
    }
    void IVTxdStore::PushCurrentTxd()
    {
        CTxdStore::PushCurrentTxd();
    }
    void IVTxdStore::SetCurrentTxd(int slot)
    {
        CTxdStore::SetCurrentTxd(slot);
    }
    void IVTxdStore::PopCurrentTxd()
    {
        CTxdStore::PopCurrentTxd();
    }
    IVSprite2D^ IVTxdStore::GetTexture(String^ sName)
    {
        CHECK_NULL_OR_WHITESPACE_STRING_WITH_RETURN(sName, nullptr);

        msclr::interop::marshal_context ctx;
        CSprite2d ptr = CTxdStore::GetTexture((char*)ctx.marshal_as<const char*>(sName));
        NULLPTR_CHECK_WITH_RETURN(&ptr, nullptr);

        return gcnew IVSprite2D(&ptr);
    }
}