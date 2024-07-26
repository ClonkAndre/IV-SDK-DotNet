#include "pch.h"
#include "IVSprite2D.h"

namespace IVSDKDotNet
{

    // - - - Constructor - - -
    IVSprite2D::IVSprite2D(CSprite2d* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeSprite2D = nativePtr;
    }

    // - - - Methods / Functions - - -
    IVSprite2D^ IVSprite2D::FromUIntPtr(UIntPtr ptr)
    {
        UINTPTR_ZERO_CHECK_WITH_RETURN(ptr, nullptr);
        return gcnew IVSprite2D((CSprite2d*)ptr.ToPointer());
    }
    UIntPtr IVSprite2D::GetUIntPtr()
    {
        NULLPTR_CHECK_WITH_RETURN(NativeSprite2D, UIntPtr::Zero);
        return UIntPtr(NativeSprite2D);
    }

    void IVSprite2D::SetTexture(String^ sName)
    {
        NULLPTR_CHECK(NativeSprite2D);
        CHECK_NULL_OR_WHITESPACE_STRING(sName);

        msclr::interop::marshal_context ctx;
        NativeSprite2D->SetTexture((char*)ctx.marshal_as<const char*>(sName));
    }
    void IVSprite2D::Delete()
    {
        NULLPTR_CHECK(NativeSprite2D);
        NativeSprite2D->Delete();
    }



}