#include "pch.h"
#include "IVTheZones.h"

namespace IVSDKDotNet
{
    // - - - Methods / Functions - - -
    bool IVTheZones::Save()
    {
        return CTheZones::Save();
    }
    bool IVTheZones::Load()
    {
        return CTheZones::Load();
    }
}