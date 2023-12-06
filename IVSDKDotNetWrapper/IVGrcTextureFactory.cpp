#include "pch.h"
#include "IVGrcTextureFactory.h"

namespace IVSDKDotNet
{

    // - - - Constructor - - -
    IVGrcTextureFactory::IVGrcTextureFactory(rage::grcTextureFactory* nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeTextureFactory = nativePtr;
    }
    IVGrcTextureFactoryPC::IVGrcTextureFactoryPC(rage::grcTextureFactoryPC* nativePtr) : IVGrcTextureFactory(nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeTextureFactoryPC = nativePtr;
    }

    // - - - Methods / Functions - - -
    IVGrcTexturePC^ IVGrcTextureFactoryPC::CreateTexture(String^ sName, UIntPtr pUnk)
    {
        NULLPTR_CHECK_WITH_RETURN(NativeTextureFactoryPC, nullptr);
        CHECK_NULL_OR_WHITESPACE_STRING_WITH_RETURN(sName, nullptr);

        msclr::interop::marshal_context ctx;
        rage::grcTexturePC* ptr = NativeTextureFactoryPC->CreateTexture((char*)ctx.marshal_as<const char*>(sName), pUnk == UIntPtr::Zero ? nullptr : (uint32_t*)pUnk.ToPointer());
        NULLPTR_CHECK_WITH_RETURN(ptr, nullptr);

        return gcnew IVGrcTexturePC(ptr);
    }

}