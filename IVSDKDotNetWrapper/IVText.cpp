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

}