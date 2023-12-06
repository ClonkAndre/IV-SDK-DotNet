#include "pch.h"
#include "IVTimer.h"

namespace IVSDKDotNet
{
    // - - - Methods / Functions - - -
    bool IVTimer::GetIsPaused()
    {
        return CTimer::GetIsPaused();
    }
}