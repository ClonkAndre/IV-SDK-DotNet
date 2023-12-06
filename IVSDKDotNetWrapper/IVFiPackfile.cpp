#include "pch.h"
#include "IVFiPackfile.h"

namespace IVSDKDotNet
{

    // - - - Constructor - - -
    IVFiPackfile::IVFiPackfile(rage::fiPackfile* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativePackfile = nativePtr;
    }

    // - - - Methods / Functions - - -
    IVFiPackfile^ IVFiPackfile::Create()
    {
        rage::fiPackfile* ptr = new rage::fiPackfile();
        NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);
        return gcnew IVFiPackfile(ptr);
    }
    bool IVFiPackfile::OpenPackfile(String^ path, char unk1_1, char unk2_0, int unk3_0or3)
    {
        NULLPTR_CHECK_WITH_RETURN(NativePackfile, false);
        CHECK_NULL_OR_WHITESPACE_STRING_WITH_RETURN(path, false);

        msclr::interop::marshal_context ctx;
        return NativePackfile->OpenPackfile((char*)ctx.marshal_as<const char*>(path), unk1_1, unk2_0, unk3_0or3);
    }
    bool IVFiPackfile::Mount(String^ mountPoint)
    {
        NULLPTR_CHECK_WITH_RETURN(NativePackfile, false);
        CHECK_NULL_OR_WHITESPACE_STRING_WITH_RETURN(mountPoint, false);

        msclr::interop::marshal_context ctx;
        return NativePackfile->Mount((char*)ctx.marshal_as<const char*>(mountPoint));
    }

}