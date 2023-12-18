#include "pch.h"
#include "IVWeather.h"

namespace IVSDKDotNet
{
    // - - - Methods / Functions - - -
    void IVWeather::ForceWeatherNow(int type)
    {
        CWeather::ForceWeatherNow(type);
    }
}