// Thanks to AssaultKifle47 for the offsets and the TimeCycleParams struct!
// From his InGameTimecycEditor project: https://github.com/akifle47/InGameTimecycEditor

struct TimeCycleParams
{
	// Unknown means its a timecyc.dat parameter and i dont know what it does
    // Unused means its not a timecyc.dat parameter and i dont care what it does
	uint32_t mAmbient0Color;
	uint32_t mAmbient1Color;
	uint32_t mDirLightColor;
	float mDirLightMultiplier;
	float mAmbient0Multiplier;
	float mAmbient1Multiplier;
	float mAOStrength;
	float mPedAOStrength;
	float mRimLightingMultiplier;
	float mSkyLightMultiplier;
	float mDirLightSpecMultiplier;
	uint32_t mSkyBottomColorFogDensity;
	uint32_t mSunCore;
	float mCoronaBrightness;
	float mCoronaSize;
	float mDistantCoronaBrightness;
	float mDistantCoronaSize;
	float mFarClip;
	float mFogStart;
	float mDOFStart;
	float mNearDOFBlur;
	float mFarDOFBlur;
	uint32_t mLowCloudsColor;
	uint32_t mBottomCloudsColor;
	uint32_t mWater;
	float mUnused64[7];
	float mWaterReflectionMultiplier;
	float mParticleBrightness;
	float mExposure;
	float mBloomThreshold;
	float mMidGrayValue;
	float mBloomIntensity;
	uint32_t mColorCorrection;
	uint32_t mColorAdd;
	float mDesaturation;
	float mContrast;
	float mGamma;
	float mDesaturationFar;
	float mContrastFar;
	float mGammaFar;
	float mDepthFxNear;
	float mDepthFxFar;
	float mLumMin;
	float mLumMax;
	float mLumDelay;
	int32_t mCloudAlpha;
	float mUnusedD0;
	float mTemperature;
	float mGlobalReflectionMultiplier;
	float mUnusedDC;
	CVector mSkyColor;
	float mUnusedEC;
	CVector mSkyHorizonColor;
	float mUnusedFC;
	CVector mSkyEastHorizonColor;
	float mUnused10C;
	CVector mCloud1Color;
	float mUnknown11C;
	float mSkyHorizonHeight;
	float mSkyHorizonBrightness;
	float mSunAxisX;
	float mSunAxisY;
	CVector mCloud2Color;
	float mUnused13C;
	float mCloud2ShadowStrength;
	float mCloud2Threshold;
	float mCloud2Bias1;
	float mCloud2Scale;
	float mCloudInScatteringRange;
	float mCloud2Bias2;
	float mDetailNoiseScale;
	float mDetailNoiseMultiplier;
	float mCloud2Offset;
	float mCloudWarp;
	float mCloudsFadeOut;
	float mCloud1Bias;
	float mCloud1Detail;
	float mCloud1Threshold;
	float mCloud1Height;
	float mUnused17C;
	CVector mCloud3Color;
	float mUnused18C;
	float mUnknown190;
	float mUnused198[3];
	CVector mSunColor;
	float mUnused1AC;
	float mCloudsBrightness;
	float mDetailNoiseOffset;
	float mStarsBrightness;
	float mVisibleStars;
	float mMoonBrightness;
	float mUnused1C4[3];
	CVector mMoonColor;
	float mUnused1DC;
	float mMoonGlow;
	float mMoonParam3;
	float SunCenterStart;
	float SunCenterEnd;
	float mSunSize;
	float mUnused1F8[3];
	float mUnknown200;
	float mSkyBrightness;
	float mUnused208;
	int32_t mFilmGrain;
};

class CTimeCycle
{
public:
	TimeCycleParams mParams[11][9]; // 11 = Number of hours, 9 = Number of weathers

	static inline CTimeCycle* sTheTimeCycle = (CTimeCycle*)AddressSetter::Get(0xDF6080, 0xFF1150);
	static inline char*& sTimecycleModifierPath = AddressSetter::GetRef<char*>(0x48A651, 0x63AD31); // platform:/data

	static void Initialise()
	{
		return ((void(__cdecl*)())(AddressSetter::Get(0x48AD70, 0x63B450)))();
	}
	static void InitModifiers()
	{
		return ((void(__cdecl*)())(AddressSetter::Get(0x48A650, 0x63AD30)))();
	}
};