#include "pch.h"
#include "CPedType.h"

namespace IVSDKDotNet {


    bool CPedType::IsPedTypePlayer(String^ type)
    {
        msclr::interop::marshal_context ctx;
        return Native_CPedType::IsPedTypePlayer((char*)ctx.marshal_as<const char*>(type));
    }

    int CPedType::FindPedType(String^ type)
    {
        msclr::interop::marshal_context ctx;
        return Native_CPedType::FindPedType((char*)ctx.marshal_as<const char*>(type));
    }

}