using System;
using System.Drawing;
using System.Numerics;

using IVSDKDotNet;
using IVSDKDotNet.Enums;

namespace TestScript
{
    static class LightHelper
    {
        // IV calls:
        //DrawLight(0, 0x2, 0x504, vector1, vector2, vector3, vector4, 30.92f, 4139616000.0f, 9, 20.0f, 1.0f, 25.0f, 0.0f, 0.0f, -1, 0x3F, ((GTA.Ped)CPlayer.LocalPlayer.Ped).MemoryAddress);
        //DrawLight(0, 0x2, 0x114, vector1, vector2, vector3, vector4, 140.0f, 1, 1, 16.0f, 1.0f, 45.0f, 10.0f, 1.0f, -1, -1, 0);
        // 0, 0x2, 0x504, vec, vec, vec, vec, 25.92, unknown, 9, 75.0, 20.0 50.0, 0.0, 0.0, -1, 0x3F, 0x0
        //0, 2, 0x114, { 0.71, 0.70, -0.07 }, { 0.0, -0.10, -0.99 }, { -542, 1224, 40 }, { 1.0, 1.0, 1.0 }, 14.38f, 0, 0, 16.0, 0, 45.0, 0.0, 0.0, -1, -1, 0

        public static void DrawLightCone(Vector3 source, Vector3 direction, Color color, float intensity, float range, float innerConeAngleMaybe, float volConeAngle, float volIntensity, float volScale, int txdSlot, int txdHash, int interior, uint ptr)
        {
            Vector3 tanDir = -Vector3.UnitZ;

            // 0x500 = ?
            // 0x4 = Cast Shadow
            // 0x8 = Draw Volume
            //uint flags = 0x500 | 0x4 | 0x8;

            // If you set
            // TXD Slot: 2152
            // TEX Hash: 1382732640
            // this will apply the disco ball texture you can see in the strip club to the light

            // txdSlot
            // txdHash

            eLightFlags newFlags = eLightFlags.Vehicle | eLightFlags.DrawVolume | eLightFlags.InteriorOnly | eLightFlags.ExteriorOnly;
            IVShadows.AddSceneLight(0, (uint)eLightType.Spot, (uint)newFlags, direction, tanDir, source, color, intensity, txdSlot, txdHash, range, innerConeAngleMaybe, volConeAngle, volIntensity, volScale, interior, 0, ptr);
        }

    }
}
