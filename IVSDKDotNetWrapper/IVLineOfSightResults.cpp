#include "pch.h"
#include "IVLineOfSightResults.h"

namespace IVSDKDotNet
{

    // - - - Constructor - - -
    IVLineOfSightResults::IVLineOfSightResults(tLineOfSightResults* nativePtr)
    {
        if (!nativePtr)
        {
            m_bValid = false;
            return;
        }

        // Copy stuff from unmanaged struct to managed
        Inst = nativePtr->m_pInst == nullptr ? UIntPtr::Zero : UIntPtr(nativePtr->m_pInst);
        EndPosition = CVectorToVector3(nativePtr->m_vEndPosition);
        UnkFlags = nativePtr->m_nUnkFlags;
        Unk = CVectorToVector3(nativePtr->m_vUnk);
        UnkFlags2 = nativePtr->m_nUnkFlags2;
        Unk2 = CVectorToVector3(nativePtr->m_vUnk2);
        UnkFlags3 = nativePtr->m_nUnkFlags3;
        UnkFloat1 = nativePtr->m_fUnk1;
        UnkFloat2 = nativePtr->m_fUnk2;
        UnkFlags4 = nativePtr->m_nUnkFlags4;
        UnkFlags5 = nativePtr->m_nUnkFlags5;
        UnkFlags6 = nativePtr->m_nUnkFlags6;

        m_bValid = true;
    }

    // - - - Methods / Functions - - -
    IVLineOfSightResults IVLineOfSightResults::Empty()
    {
        return IVLineOfSightResults(nullptr);
    }

}