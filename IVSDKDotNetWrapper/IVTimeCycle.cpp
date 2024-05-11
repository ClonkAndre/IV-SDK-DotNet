#include "pch.h"
#include "IVTimeCycle.h"

namespace IVSDKDotNet
{

    // - - - Constructor - - -
    IVTimeCycleParams::IVTimeCycleParams(TimeCycleParams* nativePtr)
    {
        NativeTimeCycleParams = nativePtr;
    }
    IVTimeCycle::IVTimeCycle(CTimeCycle* nativePtr)
    {
        NativeTimeCycle = nativePtr;
    }

    // - - - Methods / Functions - - -
    IVTimeCycleParams^ IVTimeCycle::GetTimeCycleParams(int32_t gameHour, int32_t weather)
    {
        NULLPTR_CHECK_WITH_RETURN(NativeTimeCycle, nullptr);

        if (gameHour > 23)
            return nullptr;

        const int32_t gameTimeToTimecycTimeIndex[24] = { 0, 0, 0, 0, 0, 1, 2, 3, 3, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 7, 8, 9, 10, 10 };
        int32_t timecycTimeIndex = gameTimeToTimecycTimeIndex[gameHour];

        TimeCycleParams* params = &NativeTimeCycle->mParams[timecycTimeIndex][weather];

        if (params)
            return gcnew IVTimeCycleParams(params);

        return nullptr;
    }

    void IVTimeCycle::Initialise()
    {
        CTimeCycle::Initialise();
    }
    void IVTimeCycle::InitModifiers()
    {
        CTimeCycle::InitModifiers();
    }

}