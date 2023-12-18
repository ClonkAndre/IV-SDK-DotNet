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