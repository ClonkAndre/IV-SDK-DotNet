// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#pragma comment(lib, "User32.lib")

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "defines.h"

#include <windows.h>

#include <msclr/marshal.h>

#include "enums.h"
#include "CRGBA.h"
#include "CVectors.h"

#include "Helper.h"

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

//#include "CRGBA.h"
//#include "rage.h"
#include "CPlayerInfo.h"
#include "CPad.h"
#include "CEntity.h"
#include "CDynamicEntity.h"
#include "CPhysical.h"
#include "CCustomShaderEffectBase.h"
#include "CObject.h"
#include "CPool.h"
#include "CPools.h"
#include "CPed.h"
#include "phBound.h"
#include "phInstGta.h"
//#include "CTheScripts.h"
#include "phConstrainedCollider.h"
//#include "CTimer.h"
#include "CFileLoader.h"
#include "CdStream.h"
//#include "CGame.h"
#include "CHudColours.h"
#include "CVisibilityPlugins.h"
#include "CNetwork.h"
#include "CShadows.h"
#include "CClock.h"
#include "CCutsceneMgr.h"
#include "CDraw.h"
#include "CFont.h"
#include "audRadioAudioEntity.h"
#include "CMenuManager.h"
#include "CShaderLib.h"
#include "CTimeCycle.h"
#include "CPickups.h"
#include "CPedType.h"

#endif //PCH_H
