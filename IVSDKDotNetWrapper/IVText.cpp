#include "pch.h"
#include "IVText.h"

namespace IVSDKDotNet
{

    // - - - Constructor - - -
    IVText::IVText(CText* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeText = nativePtr;
    }

    // - - - Methods / Functions - - -
    String^ IVText::Get(String^ ident)
    {
        NULLPTR_CHECK_WITH_RETURN(NativeText, String::Empty);
        CHECK_NULL_OR_WHITESPACE_STRING_WITH_RETURN(ident, String::Empty);

        msclr::interop::marshal_context ctx;
        return gcnew String(NativeText->Get(ctx.marshal_as<const char*>(ident)));
    }
    String^ IVText::Get(uint32_t hash, String^ ident)
    {
        NULLPTR_CHECK_WITH_RETURN(NativeText, String::Empty);
        CHECK_NULL_OR_WHITESPACE_STRING_WITH_RETURN(ident, String::Empty);

        msclr::interop::marshal_context ctx;
        return gcnew String(NativeText->Get(hash, ctx.marshal_as<const char*>(ident)));
    }

    void IVText::ReplaceTextOfTextLabel(String^ ident, String^ newText)
    {
        NULLPTR_CHECK(NativeText);
        NULLPTR_CHECK(ident);
        NULLPTR_CHECK(newText);

        msclr::interop::marshal_context ctx;
        wmemcpy(const_cast<wchar_t*>(NativeText->Get(ctx.marshal_as<const char*>(ident))), ctx.marshal_as<const wchar_t*>(newText), newText->Length + 1);
    }
    void IVText::ReplaceTextOfTextLabel(uint32_t hash, String^ newText)
    {
        NULLPTR_CHECK(NativeText);
        NULLPTR_CHECK(newText);

        msclr::interop::marshal_context ctx;
        wmemcpy(const_cast<wchar_t*>(NativeText->Get(hash, NULL)), ctx.marshal_as<const wchar_t*>(newText), newText->Length + 1);
    }

}