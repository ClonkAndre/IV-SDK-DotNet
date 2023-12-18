#include "pch.h"
#include "IVRadar.h"

namespace IVSDKDotNet
{
    // - - - Methods / Functions - - -
    void IVRadar::DrawBlips()
    {
        CRadar::DrawBlips();
    }
    void IVRadar::DrawBlipNames()
    {
        CRadar::DrawBlipNames();
    }
    void IVRadar::DrawFrameFront()
    {
        CRadar::DrawFrameFront();
    }
    void IVRadar::DrawFrameBack()
    {
        CRadar::DrawFrameBack();
    }
    void IVRadar::DrawRoute(bool bMenu)
    {
        CRadar::DrawRoute(bMenu);
    }
    int32_t IVRadar::ConvertUniqueBlipToActualBlip(int32_t index)
    {
        return CRadar::ConvertUniqueBlipToActualBlip(index);
    }
    int32_t IVRadar::CreateBlip(bool unk, int32_t blipType, Vector3 vecPosition, int32_t dispFlag, String^ pScriptName)
    {
        CVector* vec = new CVector();
        vec->x = vecPosition.X;
        vec->y = vecPosition.Y;
        vec->z = vecPosition.Z;

        msclr::interop::marshal_context ctx;
        int32_t result = CRadar::CreateBlip(unk, blipType, vec, dispFlag, (char*)ctx.marshal_as<const char*>(pScriptName));

        delete vec;

        return result;
    }
    void IVRadar::SetBlipParameter(int paramId, int32_t index, int value)
    {
        CRadar::SetBlipParameter(paramId, index, value);
    }
    void IVRadar::SetBlipParameter(int paramId, int32_t index, float value)
    {
        CRadar::SetBlipParameter(paramId, index, value);
    }
    bool IVRadar::RemoveBlip(int32_t index, bool isScriptHandle)
    {
        return CRadar::RemoveBlip(index, isScriptHandle);
    }
    bool IVRadar::IsBlipIdInUse(int32_t index)
    {
        return CRadar::IsBlipIdInUse(index);
    }
}