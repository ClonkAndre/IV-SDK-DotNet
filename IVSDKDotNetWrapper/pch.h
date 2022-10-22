// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#pragma comment(lib, "User32.lib")

#include <d3dx9core.h>
#include <d3d9.h>

#include "defines.h"

#include <windows.h>

#include <msclr/marshal.h>

#include "Helper.h"

#include "enums.h"
#include "CRGBA.h"
#include "CVectors.h"
#include "CQuaternion.h"

#include "AddressSetter.h"
#include "rage.h"

#include "CTheScripts.h"

#include "NativeHashes.h"
#include "NativeInvoke.h"
#include "Native.h"

#include "Scripts.h"

#include "CPlayerInfo.h"
#include "CGame.h"
#include "CTimer.h"

#endif //PCH_H
