#include "pch.h"
#include "IVVehicleModelInfo.h"

namespace IVSDKDotNet
{

    // - - - Constructor - - -
    IVVehicleModelInfo::IVVehicleModelInfo(CVehicleModelInfo* nativePtr) : IVBaseModelInfo(nativePtr)
    {
        NULLPTR_CHECK(nativePtr);
        NativeVehicleModelInfo = nativePtr;
    }

    // - - - Methods / Functions - - -
    void IVVehicleModelInfo::SetHandlingParams(IVHandlingData^ pHandling, Vector3 pCenterOfMass)
    {
        NULLPTR_CHECK(NativeVehicleModelInfo);
        NULLPTR_CHECK(pHandling);

        CVector* v = new CVector();
        v->x = pCenterOfMass.X;
        v->y = pCenterOfMass.Y;
        v->z = pCenterOfMass.Z;

        NativeVehicleModelInfo->SetHandlingParams(pHandling->NativeHandlingData, v);

        delete v;
    }
    int IVVehicleModelInfo::GetNumberOfSeats(int modelIndex)
    {
        return CVehicleModelInfo::GetNumberOfSeats(modelIndex);
    }

    void IVVehicleModelInfo::SetSecondaryAnimGroup(String^ group)
    {
        NULLPTR_CHECK(NativeVehicleModelInfo);
        CHECK_NULL_OR_WHITESPACE_STRING(group);
        msclr::interop::marshal_context ctx;
        NativeVehicleModelInfo->SetSecondaryAnimGroup((char*)ctx.marshal_as<const char*>(group));
    }

}