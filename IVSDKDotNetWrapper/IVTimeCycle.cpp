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

    generic <typename T>
    T IVTimeCycle::GetSingleTimeCycleParameter(int32_t gameHour, int32_t weather, eTimeCycleParam param)
    {
        NULLPTR_CHECK_WITH_RETURN(NativeTimeCycle, T());

        if (gameHour > 23)
            return T();

        const int32_t gameTimeToTimecycTimeIndex[24] = { 0, 0, 0, 0, 0, 1, 2, 3, 3, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 7, 8, 9, 10, 10 };
        int32_t timecycTimeIndex = gameTimeToTimecycTimeIndex[gameHour];

        TimeCycleParams* params = &NativeTimeCycle->mParams[timecycTimeIndex][weather];

        if (!params)
            return T();

        System::Object^ value = nullptr;

        switch (param)
        {
            case IVSDKDotNet::Enums::eTimeCycleParam::Ambient0Color:
                value = params->mAmbient0Color;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Ambient1Color:
                value = params->mAmbient1Color;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::DirLightColor:
                value = params->mDirLightColor;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::DirLightMultiplier:
                value = params->mDirLightMultiplier;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Ambient0Multiplier:
                value = params->mAmbient0Multiplier;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Ambient1Multiplier:
                value = params->mAmbient1Multiplier;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::AOStrength:
                value = params->mAOStrength;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::PedAOStrength:
                value = params->mPedAOStrength;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::RimLightingMultiplier:
                value = params->mRimLightingMultiplier;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::SkyLightMultiplier:
                value = params->mSkyLightMultiplier;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::DirLightSpecMultiplier:
                value = params->mDirLightSpecMultiplier;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::SkyBottomColorFogDensity:
                value = params->mSkyBottomColorFogDensity;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::SunCore:
                value = params->mSunCore;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::CoronaBrightness:
                value = params->mCoronaBrightness;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::CoronaSize:
                value = params->mCoronaSize;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::DistantCoronaBrightness:
                value = params->mDistantCoronaBrightness;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::DistantCoronaSize:
                value = params->mDistantCoronaSize;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::FarClip:
                value = params->mFarClip;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::FogStart:
                value = params->mFogStart;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::DOFStart:
                value = params->mDOFStart;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::NearDOFBlur:
                value = params->mNearDOFBlur;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::FarDOFBlur:
                value = params->mFarDOFBlur;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::LowCloudsColor:
                value = params->mLowCloudsColor;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::BottomCloudsColor:
                value = params->mBottomCloudsColor;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Water:
                value = params->mWater;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::WaterReflectionMultiplier:
                value = params->mWaterReflectionMultiplier;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::ParticleBrightness:
                value = params->mParticleBrightness;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Exposure:
                value = params->mExposure;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::BloomThreshold:
                value = params->mBloomThreshold;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::MidGrayValue:
                value = params->mMidGrayValue;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::BloomIntensity:
                value = params->mBloomIntensity;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::ColorCorrection:
                value = params->mColorCorrection;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::ColorAdd:
                value = params->mColorAdd;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Desaturation:
                value = params->mDesaturation;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Contrast:
                value = params->mContrast;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Gamma:
                value = params->mGamma;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::DesaturationFar:
                value = params->mDesaturationFar;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::ContrastFar:
                value = params->mContrastFar;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::GammaFar:
                value = params->mGammaFar;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::DepthFxNear:
                value = params->mDepthFxNear;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::DepthFxFar:
                value = params->mDepthFxFar;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::LumMin:
                value = params->mLumMin;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::LumMax:
                value = params->mLumMax;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::LumDelay:
                value = params->mLumDelay;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::CloudAlpha:
                value = params->mCloudAlpha;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::UnusedD0:
                value = params->mUnusedD0;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Temperature:
                value = params->mTemperature;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::GlobalReflectionMultiplier:
                value = params->mGlobalReflectionMultiplier;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::UnusedDC:
                value = params->mUnusedDC;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::SkyColor:
                value = CVectorToVector3(params->mSkyColor);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::UnusedEC:
                value = params->mUnusedEC;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::SkyHorizonColor:
                value = CVectorToVector3(params->mSkyHorizonColor);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::UnusedFC:
                value = params->mUnusedFC;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::SkyEastHorizonColor:
                value = CVectorToVector3(params->mSkyEastHorizonColor);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Unused10C:
                value = params->mUnused10C;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Cloud1Color:
                value = CVectorToVector3(params->mCloud1Color);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Unknown11C:
                value = params->mUnknown11C;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::SkyHorizonHeight:
                value = params->mSkyHorizonHeight;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::SkyHorizonBrightness:
                value = params->mSkyHorizonBrightness;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::SunAxisX:
                value = params->mSunAxisX;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::SunAxisY:
                value = params->mSunAxisY;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Cloud2Color:
                value = CVectorToVector3(params->mCloud2Color);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Unused13C:
                value = params->mUnused13C;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Cloud2ShadowStrength:
                value = params->mCloud2ShadowStrength;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Cloud2Threshold:
                value = params->mCloud2Threshold;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Cloud2Bias1:
                value = params->mCloud2Bias1;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Cloud2Scale:
                value = params->mCloud2Scale;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::CloudInScatteringRange:
                value = params->mCloudInScatteringRange;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Cloud2Bias2:
                value = params->mCloud2Bias2;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::DetailNoiseScale:
                value = params->mDetailNoiseScale;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::DetailNoiseMultiplier:
                value = params->mDetailNoiseMultiplier;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Cloud2Offset:
                value = params->mCloud2Offset;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::CloudWarp:
                value = params->mCloudWarp;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::CloudsFadeOut:
                value = params->mCloudsFadeOut;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Cloud1Bias:
                value = params->mCloud1Bias;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Cloud1Detail:
                value = params->mCloud1Detail;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Cloud1Threshold:
                value = params->mCloud1Threshold;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Cloud1Height:
                value = params->mCloud1Height;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Unused17C:
                value = params->mUnused17C;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Cloud3Color:
                value = CVectorToVector3(params->mCloud3Color);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Unused18C:
                value = params->mUnused18C;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Unknown190:
                value = params->mUnknown190;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::SunColor:
                value = CVectorToVector3(params->mSunColor);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Unused1AC:
                value = params->mUnused1AC;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::CloudsBrightness:
                value = params->mCloudsBrightness;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::DetailNoiseOffset:
                value = params->mDetailNoiseOffset;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::StarsBrightness:
                value = params->mStarsBrightness;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::VisibleStars:
                value = params->mVisibleStars;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::MoonBrightness:
                value = params->mMoonBrightness;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::MoonColor:
                value = CVectorToVector3(params->mMoonColor);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Unused1DC:
                value = params->mUnused1DC;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::MoonGlow:
                value = params->mMoonGlow;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::MoonParam3:
                value = params->mMoonParam3;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::SunCenterStart:
                value = params->SunCenterStart;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::SunCenterEnd:
                value = params->SunCenterEnd;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::SunSize:
                value = params->mSunSize;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Unknown200:
                value = params->mUnknown200;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::SkyBrightness:
                value = params->mSkyBrightness;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Unused208:
                value = params->mUnused208;
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::FilmGrain:
                value = params->mFilmGrain;
                break;
        }

        return safe_cast<T>(value);
    }

    generic <typename T>
    bool IVTimeCycle::SetSingleTimeCycleParameter(int32_t gameHour, int32_t weather, eTimeCycleParam param, T value)
    {
        NULLPTR_CHECK_WITH_RETURN(NativeTimeCycle, false);

        if (gameHour > 23)
            return false;

        const int32_t gameTimeToTimecycTimeIndex[24] = { 0, 0, 0, 0, 0, 1, 2, 3, 3, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 7, 8, 9, 10, 10 };
        int32_t timecycTimeIndex = gameTimeToTimecycTimeIndex[gameHour];

        TimeCycleParams* params = &NativeTimeCycle->mParams[timecycTimeIndex][weather];

        if (!params)
            return false;

        switch (param)
        {
            case IVSDKDotNet::Enums::eTimeCycleParam::Ambient0Color:
                params->mAmbient0Color = Convert::ToUInt32(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Ambient1Color:
                params->mAmbient1Color = Convert::ToUInt32(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::DirLightColor:
                params->mDirLightColor = Convert::ToUInt32(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::DirLightMultiplier:
                params->mDirLightMultiplier = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Ambient0Multiplier:
                params->mAmbient0Multiplier = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Ambient1Multiplier:
                params->mAmbient1Multiplier = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::AOStrength:
                params->mAOStrength = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::PedAOStrength:
                params->mPedAOStrength = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::RimLightingMultiplier:
                params->mRimLightingMultiplier = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::SkyLightMultiplier:
                params->mSkyLightMultiplier = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::DirLightSpecMultiplier:
                params->mDirLightSpecMultiplier = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::SkyBottomColorFogDensity:
                params->mSkyBottomColorFogDensity = Convert::ToUInt32(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::SunCore:
                params->mSunCore = Convert::ToUInt32(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::CoronaBrightness:
                params->mCoronaBrightness = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::CoronaSize:
                params->mCoronaSize = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::DistantCoronaBrightness:
                params->mDistantCoronaBrightness = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::DistantCoronaSize:
                params->mDistantCoronaSize = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::FarClip:
                params->mFarClip = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::FogStart:
                params->mFogStart = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::DOFStart:
                params->mDOFStart = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::NearDOFBlur:
                params->mNearDOFBlur = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::FarDOFBlur:
                params->mFarDOFBlur = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::LowCloudsColor:
                params->mLowCloudsColor = Convert::ToUInt32(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::BottomCloudsColor:
                params->mBottomCloudsColor = Convert::ToUInt32(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Water:
                params->mWater = Convert::ToUInt32(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::WaterReflectionMultiplier:
                params->mWaterReflectionMultiplier = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::ParticleBrightness:
                params->mParticleBrightness = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Exposure:
                params->mExposure = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::BloomThreshold:
                params->mBloomThreshold = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::MidGrayValue:
                params->mMidGrayValue = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::BloomIntensity:
                params->mBloomIntensity = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::ColorCorrection:
                params->mColorCorrection = Convert::ToUInt32(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::ColorAdd:
                params->mColorAdd = Convert::ToUInt32(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Desaturation:
                params->mDesaturation = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Contrast:
                params->mContrast = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Gamma:
                params->mGamma = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::DesaturationFar:
                params->mDesaturationFar = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::ContrastFar:
                params->mContrastFar = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::GammaFar:
                params->mGammaFar = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::DepthFxNear:
                params->mDepthFxNear = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::DepthFxFar:
                params->mDepthFxFar = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::LumMin:
                params->mLumMin = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::LumMax:
                params->mLumMax = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::LumDelay:
                params->mLumDelay = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::CloudAlpha:
                params->mCloudAlpha = Convert::ToInt32(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::UnusedD0:
                params->mUnusedD0 = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Temperature:
                params->mTemperature = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::GlobalReflectionMultiplier:
                params->mGlobalReflectionMultiplier = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::UnusedDC:
                params->mUnusedDC = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::SkyColor:
                params->mSkyColor = Vector3ToCVector(safe_cast<Vector3>(value));
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::UnusedEC:
                params->mUnusedEC = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::SkyHorizonColor:
                params->mSkyHorizonColor = Vector3ToCVector(safe_cast<Vector3>(value));
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::UnusedFC:
                params->mUnusedFC = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::SkyEastHorizonColor:
                params->mSkyEastHorizonColor = Vector3ToCVector(safe_cast<Vector3>(value));
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Unused10C:
                params->mUnused10C = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Cloud1Color:
                params->mCloud1Color = Vector3ToCVector(safe_cast<Vector3>(value));
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Unknown11C:
                params->mUnknown11C = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::SkyHorizonHeight:
                params->mSkyHorizonHeight = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::SkyHorizonBrightness:
                params->mSkyHorizonBrightness = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::SunAxisX:
                params->mSunAxisX = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::SunAxisY:
                params->mSunAxisY = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Cloud2Color:
                params->mCloud2Color = Vector3ToCVector(safe_cast<Vector3>(value));
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Unused13C:
                params->mUnused13C = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Cloud2ShadowStrength:
                params->mCloud2ShadowStrength = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Cloud2Threshold:
                params->mCloud2Threshold = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Cloud2Bias1:
                params->mCloud2Bias1 = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Cloud2Scale:
                params->mCloud2Scale = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::CloudInScatteringRange:
                params->mCloudInScatteringRange = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Cloud2Bias2:
                params->mCloud2Bias2 = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::DetailNoiseScale:
                params->mDetailNoiseScale = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::DetailNoiseMultiplier:
                params->mDetailNoiseMultiplier = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Cloud2Offset:
                params->mCloud2Offset = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::CloudWarp:
                params->mCloudWarp = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::CloudsFadeOut:
                params->mCloudsFadeOut = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Cloud1Bias:
                params->mCloud1Bias = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Cloud1Detail:
                params->mCloud1Detail = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Cloud1Threshold:
                params->mCloud1Threshold = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Cloud1Height:
                params->mCloud1Height = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Unused17C:
                params->mUnused17C = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Cloud3Color:
                params->mCloud3Color = Vector3ToCVector(safe_cast<Vector3>(value));
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Unused18C:
                params->mUnused18C = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Unknown190:
                params->mUnknown190 = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::SunColor:
                params->mSunColor = Vector3ToCVector(safe_cast<Vector3>(value));
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Unused1AC:
                params->mUnused1AC = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::CloudsBrightness:
                params->mCloudsBrightness = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::DetailNoiseOffset:
                params->mDetailNoiseOffset = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::StarsBrightness:
                params->mStarsBrightness = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::VisibleStars:
                params->mVisibleStars = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::MoonBrightness:
                params->mMoonBrightness = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::MoonColor:
                params->mMoonColor = Vector3ToCVector(safe_cast<Vector3>(value));
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Unused1DC:
                params->mUnused1DC = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::MoonGlow:
                params->mMoonGlow = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::MoonParam3:
                params->mMoonParam3 = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::SunCenterStart:
                params->SunCenterStart = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::SunCenterEnd:
                params->SunCenterEnd = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::SunSize:
                params->mSunSize = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Unknown200:
                params->mUnknown200 = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::SkyBrightness:
                params->mSkyBrightness = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::Unused208:
                params->mUnused208 = Convert::ToSingle(value);
                break;
            case IVSDKDotNet::Enums::eTimeCycleParam::FilmGrain:
                params->mFilmGrain = Convert::ToInt32(value);
                break;
        }

        return true;
    }

    void IVTimeCycle::Initialise()
    {
        if (CLR::CLRBridge::IsShuttingDown)
            return;

        CTimeCycle::Initialise();
    }
    void IVTimeCycle::InitModifiers()
    {
        if (CLR::CLRBridge::IsShuttingDown)
            return;

        CTimeCycle::InitModifiers();
    }

}