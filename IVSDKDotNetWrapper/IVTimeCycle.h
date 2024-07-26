#pragma once

namespace IVSDKDotNet
{
	public ref class IVTimeCycleParams
	{
	public:
		property uint32_t Ambient0Color
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0);
				return NativeTimeCycleParams->mAmbient0Color;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mAmbient0Color = value;
			}
		}
		property uint32_t Ambient1Color
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0);
				return NativeTimeCycleParams->mAmbient1Color;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mAmbient1Color = value;
			}
		}
		property uint32_t DirLightColor
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0);
				return NativeTimeCycleParams->mDirLightColor;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mDirLightColor = value;
			}
		}
		property float DirLightMultiplier
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mDirLightMultiplier;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mDirLightMultiplier = value;
			}
		}
		property float Ambient0Multiplier
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mAmbient0Multiplier;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mAmbient0Multiplier = value;
			}
		}
		property float Ambient1Multiplier
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mAmbient1Multiplier;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mAmbient1Multiplier = value;
			}
		}
		property float AOStrength
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mAOStrength;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mAOStrength = value;
			}
		}
		property float PedAOStrength
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mPedAOStrength;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mPedAOStrength = value;
			}
		}
		property float RimLightingMultiplier
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mRimLightingMultiplier;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mRimLightingMultiplier = value;
			}
		}
		property float SkyLightMultiplier
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mSkyLightMultiplier;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mSkyLightMultiplier = value;
			}
		}
		property float DirLightSpecMultiplier
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mDirLightSpecMultiplier;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mDirLightSpecMultiplier = value;
			}
		}
		property uint32_t SkyBottomColorFogDensity
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0);
				return NativeTimeCycleParams->mSkyBottomColorFogDensity;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mSkyBottomColorFogDensity = value;
			}
		}
		property uint32_t SunCore
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0);
				return NativeTimeCycleParams->mSunCore;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mSunCore = value;
			}
		}
		property float CoronaBrightness
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mCoronaBrightness;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mCoronaBrightness = value;
			}
		}
		property float CoronaSize
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mCoronaSize;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mCoronaSize = value;
			}
		}
		property float DistantCoronaBrightness
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mDistantCoronaBrightness;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mDistantCoronaBrightness = value;
			}
		}
		property float DistantCoronaSize
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mDistantCoronaSize;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mDistantCoronaSize = value;
			}
		}
		property float FarClip
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mFarClip;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mFarClip = value;
			}
		}
		property float FogStart
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mFogStart;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mFogStart = value;
			}
		}
		property float DOFStart
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mDOFStart;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mDOFStart = value;
			}
		}
		property float NearDOFBlur
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mNearDOFBlur;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mNearDOFBlur = value;
			}
		}
		property float FarDOFBlur
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mFarDOFBlur;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mFarDOFBlur = value;
			}
		}
		property uint32_t LowCloudsColor
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0);
				return NativeTimeCycleParams->mLowCloudsColor;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mLowCloudsColor = value;
			}
		}
		property uint32_t BottomCloudsColor
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0);
				return NativeTimeCycleParams->mBottomCloudsColor;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mBottomCloudsColor = value;
			}
		}
		property uint32_t Water
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0);
				return NativeTimeCycleParams->mWater;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mWater = value;
			}
		}
		property float WaterReflectionMultiplier
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mWaterReflectionMultiplier;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mWaterReflectionMultiplier = value;
			}
		}
		property float ParticleBrightness
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mParticleBrightness;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mParticleBrightness = value;
			}
		}
		property float Exposure
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mExposure;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mExposure = value;
			}
		}
		property float BloomThreshold
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mBloomThreshold;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mBloomThreshold = value;
			}
		}
		property float MidGrayValue
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mMidGrayValue;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mMidGrayValue = value;
			}
		}
		property float BloomIntensity
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mBloomIntensity;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mBloomIntensity = value;
			}
		}
		property uint32_t ColorCorrection
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0);
				return NativeTimeCycleParams->mColorCorrection;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mColorCorrection = value;
			}
		}
		property uint32_t ColorAdd
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0);
				return NativeTimeCycleParams->mColorAdd;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mColorAdd = value;
			}
		}
		property float Desaturation
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mDesaturation;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mDesaturation = value;
			}
		}
		property float Contrast
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mContrast;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mContrast = value;
			}
		}
		property float Gamma
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mGamma;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mGamma = value;
			}
		}
		property float DesaturationFar
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mDesaturationFar;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mDesaturationFar = value;
			}
		}
		property float ContrastFar
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mContrastFar;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mContrastFar = value;
			}
		}
		property float GammaFar
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mGammaFar;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mGammaFar = value;
			}
		}
		property float DepthFxNear
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mDepthFxNear;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mDepthFxNear = value;
			}
		}
		property float DepthFxFar
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mDepthFxFar;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mDepthFxFar = value;
			}
		}
		property float LumMin
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mLumMin;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mLumMin = value;
			}
		}
		property float LumMax
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mLumMax;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mLumMax = value;
			}
		}
		property float LumDelay
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mLumDelay;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mLumDelay = value;
			}
		}
		property int32_t CloudAlpha
		{
		public:
			int32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0);
				return NativeTimeCycleParams->mCloudAlpha;
			}
			void set(int32_t value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mCloudAlpha = value;
			}
		}
		property float Temperature
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mTemperature;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mTemperature = value;
			}
		}
		property float GlobalReflectionMultiplier
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mGlobalReflectionMultiplier;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mGlobalReflectionMultiplier = value;
			}
		}
		property Vector3 SkyColor
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, Vector3::Zero);
				return CVectorToVector3(NativeTimeCycleParams->mSkyColor);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mSkyColor = Vector3ToCVector(value);
			}
		}
		property Vector3 SkyHorizonColor
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, Vector3::Zero);
				return CVectorToVector3(NativeTimeCycleParams->mSkyHorizonColor);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mSkyHorizonColor = Vector3ToCVector(value);
			}
		}
		property Vector3 SkyEastHorizonColor
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, Vector3::Zero);
				return CVectorToVector3(NativeTimeCycleParams->mSkyEastHorizonColor);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mSkyEastHorizonColor = Vector3ToCVector(value);
			}
		}
		property Vector3 Cloud1Color
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, Vector3::Zero);
				return CVectorToVector3(NativeTimeCycleParams->mCloud1Color);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mCloud1Color = Vector3ToCVector(value);
			}
		}
		property float Unknown11C
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mUnknown11C;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mUnknown11C = value;
			}
		}
		property float SkyHorizonHeight
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mSkyHorizonHeight;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mSkyHorizonHeight = value;
			}
		}
		property float SkyHorizonBrightness
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mSkyHorizonBrightness;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mSkyHorizonBrightness = value;
			}
		}
		property float SunAxisX
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mSunAxisX;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mSunAxisX = value;
			}
		}
		property float SunAxisY
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mSunAxisY;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mSunAxisY = value;
			}
		}
		property Vector3 Cloud2Color
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, Vector3::Zero);
				return CVectorToVector3(NativeTimeCycleParams->mCloud2Color);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mCloud2Color = Vector3ToCVector(value);
			}
		}
		property float Cloud2ShadowStrength
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mCloud2ShadowStrength;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mCloud2ShadowStrength = value;
			}
		}
		property float Cloud2Threshold
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mCloud2Threshold;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mCloud2Threshold = value;
			}
		}
		property float Cloud2Bias1
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mCloud2Bias1;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mCloud2Bias1 = value;
			}
		}
		property float Cloud2Scale
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mCloud2Scale;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mCloud2Scale = value;
			}
		}
		property float CloudInScatteringRange
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mCloudInScatteringRange;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mCloudInScatteringRange = value;
			}
		}
		property float Cloud2Bias2
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mCloud2Bias2;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mCloud2Bias2 = value;
			}
		}
		property float DetailNoiseScale
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mDetailNoiseScale;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mDetailNoiseScale = value;
			}
		}
		property float DetailNoiseMultiplier
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mDetailNoiseMultiplier;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mDetailNoiseMultiplier = value;
			}
		}
		property float Cloud2Offset
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mCloud2Offset;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mCloud2Offset = value;
			}
		}
		property float CloudWarp
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mCloudWarp;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mCloudWarp = value;
			}
		}
		property float CloudsFadeOut
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mCloudsFadeOut;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mCloudsFadeOut = value;
			}
		}
		property float Cloud1Bias
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mCloud1Bias;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mCloud1Bias = value;
			}
		}
		property float Cloud1Detail
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mCloud1Detail;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mCloud1Detail = value;
			}
		}
		property float Cloud1Threshold
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mCloud1Threshold;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mCloud1Threshold = value;
			}
		}
		property float Cloud1Height
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mCloud1Height;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mCloud1Height = value;
			}
		}
		property Vector3 Cloud3Color
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, Vector3::Zero);
				return CVectorToVector3(NativeTimeCycleParams->mCloud3Color);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mCloud3Color = Vector3ToCVector(value);
			}
		}
		property float Unknown190
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mUnknown190;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mUnknown190 = value;
			}
		}
		property Vector3 SunColor
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, Vector3::Zero);
				return CVectorToVector3(NativeTimeCycleParams->mSunColor);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mSunColor = Vector3ToCVector(value);
			}
		}
		property float CloudsBrightness
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mCloudsBrightness;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mCloudsBrightness = value;
			}
		}
		property float DetailNoiseOffset
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mDetailNoiseOffset;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mDetailNoiseOffset = value;
			}
		}
		property float StarsBrightness
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mStarsBrightness;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mStarsBrightness = value;
			}
		}
		property float VisibleStars
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mVisibleStars;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mVisibleStars = value;
			}
		}
		property float MoonBrightness
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mMoonBrightness;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mMoonBrightness = value;
			}
		}
		property Vector3 MoonColor
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, Vector3::Zero);
				return CVectorToVector3(NativeTimeCycleParams->mMoonColor);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mMoonColor = Vector3ToCVector(value);
			}
		}
		property float MoonGlow
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mMoonGlow;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mMoonGlow = value;
			}
		}
		property float MoonParam3
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mMoonParam3;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mMoonParam3 = value;
			}
		}
		property float SunCenterStart
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->SunCenterStart;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->SunCenterStart = value;
			}
		}
		property float SunCenterEnd
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->SunCenterEnd;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->SunCenterEnd = value;
			}
		}
		property float SunSize
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mSunSize;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mSunSize = value;
			}
		}
		property float Unknown200
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mUnknown200;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mUnknown200 = value;
			}
		}
		property float SkyBrightness
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0.0F);
				return NativeTimeCycleParams->mSkyBrightness;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mSkyBrightness = value;
			}
		}
		property int32_t FilmGrain
		{
		public:
			int32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeTimeCycleParams, 0);
				return NativeTimeCycleParams->mFilmGrain;
			}
			void set(int32_t value)
			{
				NULLPTR_CHECK(NativeTimeCycleParams);
				NativeTimeCycleParams->mFilmGrain = value;
			}
		}

	internal:
		IVTimeCycleParams(TimeCycleParams* nativePtr);

	internal:
		TimeCycleParams* NativeTimeCycleParams;
	};

	public ref class IVTimeCycle
	{
	public:
		static property IVTimeCycle^ TheTimeCycle
		{
		public:
			IVTimeCycle^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(CTimeCycle::sTheTimeCycle, nullptr);
				return gcnew IVTimeCycle(CTimeCycle::sTheTimeCycle);
			}
		}
		static property String^ TimecycleModifierPath
		{
		public:
			String^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(CTimeCycle::sTimecycleModifierPath, String::Empty);
				return gcnew String(CTimeCycle::sTimecycleModifierPath);
			}
			void set(String^ value)
			{
				CHECK_NULL_OR_WHITESPACE_STRING(value);

				msclr::interop::marshal_context ctx;
				CTimeCycle::sTimecycleModifierPath = (char*)ctx.marshal_as<const char*>(value);
			}
		}

	public:
		IVTimeCycleParams^ GetTimeCycleParams(int32_t gameHour, int32_t weather);

	internal:
		IVTimeCycle(CTimeCycle* nativePtr);

	public:
		static void Initialise();
		static void InitModifiers();

	internal:
		CTimeCycle* NativeTimeCycle;
	};
}