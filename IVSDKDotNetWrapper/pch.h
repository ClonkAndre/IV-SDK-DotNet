// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#pragma comment(lib, "User32.lib")

// Direct3D9
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

//typedef HRESULT(__stdcall D3D9DeviceEndSceneT)(IDirect3DDevice9*);
//typedef HRESULT(__stdcall D3D9DeviceResetT)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);

// DirectInput
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

//typedef HRESULT(__stdcall DInput8DeviceGetDeviceStateT)(IDirectInputDevice8*, DWORD, LPVOID);
//typedef HRESULT(__stdcall DInput8DeviceGetDeviceDataT)(IDirectInputDevice8*, DWORD, LPDIDEVICEOBJECTDATA, LPDWORD, DWORD);
//typedef HRESULT(__stdcall DInput8DeviceAcquireT)(IDirectInputDevice8*);

// XInput
#include <XInput.h>
//typedef DWORD(WINAPI* XInputGetState_t)(DWORD, XINPUT_STATE*);

// MinHook
#include "MinHook.h"

// ImGui
#include "ImGui/ImGuiIncludes.h"

#include <windows.h>
#include <msclr/marshal.h>

#include <vector>

#include "..\IVSDKDotNet\IVSDK\IVSDK.h"
#include "..\IVSDKDotNet\IVSDK\injector\injector.hpp"
#include "..\IVSDKDotNet\AdvancedPatcher.h"

// typedefs
#include "typedefs.h"

// Managed Namespaces
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections::ObjectModel;
using namespace System::Diagnostics;
using namespace System::Drawing;
using namespace System::IO;
using namespace System::Reflection;
using namespace System::Windows::Forms;
using namespace System::Numerics;
using namespace System::Runtime::CompilerServices;
using namespace System::Text;

// Enums
#include "enums.h"
using namespace IVSDKDotNet::Enums;

// Logger
#include "Logger.h"

// Hooking.Patterns
#include "Patterns.h"

#include "defines.h"

// For any game related hooking stuff
#include "GameHooks.h"



#include "Attributes.h"

#include "SettingsFile.h"
#include "Helper.h"

// ImGuiIV
#include "ImGuiStuff.h"

#include "MemoryAccess.h"
#include "rage.h"

// GTA IV Natives Stuff
#include "NativeHashes.h"
#include "NativeInvoke.h"
#include "Native.h"
#include "NativeFunction.h"
#include "NativeHooks.h"

// Math
#include "IVMatrix.h"

// Important
#include "Scripts.h"
#include "CLRBridge.h"

// - - - IV-SDK STUFF - - -

#include "IVPlayerInfo.h"
#include "IVLineOfSightResults.h"
#include "IVWorld.h"

// Input
#include "IVValueHistoryItem.h"
#include "IVValueHistory.h"
#include "IVPadValues.h"
#include "IVPad.h"

#include "IVEntity.h"
#include "IVDynamicEntity.h"
#include "IVBuilding.h"
#include "IVInteriorInst.h"
#include "IVPhysical.h"
#include "IVCustomShaderEffectBase.h"
#include "IVObject.h"
#include "IVPool.h"
#include "IVPools.h"
#include "IVPhoneInfo.h"

// Tasks
#include "IVTask.h"
#include "IVTaskComplexWander.h"
#include "IVTaskComplexDie.h"
#include "IVTaskComplexNewGetInVehicle.h"
#include "IVTaskComplexClimbLadder.h"
#include "IVTaskComplexPlayerSettingsTask.h"
#include "IVTaskComplexInWater.h"
#include "IVTaskComplexMobileMakeCall.h"
#include "IVTaskComplexPlayerOnFoot.h"
#include "IVTaskComplexNM.h"
#include "IVTaskSimpleNMJumpRollFromRoadVehicle.h"
#include "IVTaskSimpleSidewaysDive.h"
#include "IVTaskSimpleNMHighFall.h"

// Ped
#include "IVCustomShaderEffectPedBoneDamageFX.h"
#include "IVPedMoveBlendOnFoot.h"
#include "IVPedWeaponSlot.h"
#include "IVPedWeapons.h"
#include "IVPedDrawableInfo.h"
#include "IVPedComponentModels.h"
#include "IVPed.h"
#include "IVPedFactoryNY.h"



// ImGuiIV
#include "ImGuiIV.h"

// Hooks
#include "DXHook.h"
#include "DirectInputHook.h"
#include "XInputHook.h"


#include "IVRadar.h"

// Garage
#include "IVStoredCar.h"
#include "IVGarage.h"
#include "IVSaveGarage.h"
#include "IVGarages.h"

// Handling
#include "IVHandlingData.h"
#include "IVHandlingDataMgr.h"

// Vehicle
#include "IVVehicleDoor.h"
#include "IVVehicleWheel.h"
#include "IVCustomShaderEffectVehicleFX.h"
#include "IVVehicle.h"
#include "IVVehicleFactoryNY.h"

// Model
#include "IVBaseModelInfo.h"
#include "IVPedModelInfo.h"
#include "IVVehicleStructure.h"
#include "IVVehicleModelInfo.h"
#include "IVModelInfo.h"

#include "IVPhBound.h"

// Inst
#include "IVPhArchetypeGta.h"
#include "IVCrSkeletonData.h"
#include "IVCrSkeleton.h"
#include "IVRmcDrawable.h"
#include "IVPhInst.h"
#include "IVGtaFragType.h"
#include "IVPhInstGta.h"

#include "IVTheScripts.h"

// Collider
#include "IVPhSleep.h"
#include "IVUnkColliderParams.h"
#include "IVPhConstrainedCollider.h"

#include "IVTimer.h"
#include "IVStreaming.h"
#include "IVFileLoader.h"
#include "IVCdStream.h"
#include "IVGame.h"
#include "IVCam.h"
#include "IVCamFollowVehicle.h"
#include "IVCamera.h"
#include "IVExplosion.h"
#include "IVHudColours.h"
#include "IVVisibilityPlugins.h"
#include "IVNetwork.h"
#include "IVShadows.h"
#include "IVWeaponInfo.h"
#include "IVClock.h"
#include "IVCutsceneMgr.h"
#include "IVRenderPhases.h"
#include "IVGrcTexture.h"
#include "IVGrcTextureFactory.h"
#include "IVSprite2D.h"
#include "IVDraw.h"
#include "IVTxdStore.h"
#include "IVFileMgr.h"
#include "IVFont.h"
#include "IVAudConfig.h"
#include "IVAudEngine.h"
#include "IVAudRadioAudioEntity.h"
#include "IVSkyhatMiniNoise.h"
#include "IVSkyDome.h"
#include "IVBaseDC.h"
#include "IVViewportData.h"
#include "IVViewport.h"
#include "IVGlobalScene.h"
#include "IVDrawRectDC.h"
#include "IVDrawCurvedWindowDC.h"
//#include "IVDrawSpriteDC.h"  // TODO
//#include "IVDrawSpriteUVDC.h"  // TODO
#include "IVDrawRadioHudTextDC.h"
#include "IVControlRemapInfo.h"
#include "IVMenuManager.h"
#include "IVShaderLib.h"
#include "IVTimeCycle.h"
#include "IVPickups.h"
#include "IVGameConfigReader.h"
#include "IVFiDevice.h"
#include "IVFiPackfile.h"
#include "IVAudEngine.h"
#include "IVPedType.h"
#include "IVQuadTreeNode.h"
#include "IVIplStore.h"
#include "IVGameLogic.h"
#include "IVStats.h"
#include "IVGenericGameStorage.h"
#include "IVReplay.h"
#include "IVAudioZones.h"
#include "IVStore.h"
#include "IVAnimManager.h"
#include "IVPopulation.h"
#include "IVWeather.h"
#include "IVAchievements.h"
#include "IVProjectileInfo.h"
#include "IVCheat.h"
#include "IVWanted.h"
#include "IVText.h"
#include "IVPcSave.h"
#include "IVSafehouse.h"
#include "IVRestart.h"

// Zones
#include "IVZone.h"
#include "IVTheZones.h"

// Gangs
#include "IVGangInfo.h"
#include "IVGangs.h"

// Stunt Jump
#include "IVBoundBox.h"
#include "IVStuntJump.h"
#include "IVStuntJumpManager.h"

// Radio
#include "IVRadioStation.h"
#include "IVRadioTrackManager.h"

#include "IVFrontEnd.h"

#endif //PCH_H
