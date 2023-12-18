#pragma once

namespace IVSDKDotNet
{
	public ref class IVCustomShaderEffectVehicleFX
	{
	public:
		property Vector3 PrimaryColorFloat
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCustomShaderEffectVehicleFX, Vector3::Zero);
				CRGBFloat v = NativeCustomShaderEffectVehicleFX->m_fPrimaryColor;
				return Vector3(v.red, v.green, v.blue);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeCustomShaderEffectVehicleFX);

				CRGBFloat v;
				v.red = value.X;
				v.green = value.Y;
				v.blue = value.Z;
				NativeCustomShaderEffectVehicleFX->m_fPrimaryColor = v;
			}
		}
		property Color PrimaryColor
		{
		public:
			Color get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCustomShaderEffectVehicleFX, Color::Empty);
				CRGBA v = NativeCustomShaderEffectVehicleFX->m_nPrimaryColor;
				return Color::FromArgb(v.a, v.r, v.g, v.b);
			}
			void set(Color value)
			{
				NULLPTR_CHECK(NativeCustomShaderEffectVehicleFX);

				CRGBA v;
				v.a = value.A;
				v.r = value.R;
				v.g = value.G;
				v.b = value.B;
				NativeCustomShaderEffectVehicleFX->m_nPrimaryColor = v;
			}
		}
		property Vector3 SecondaryColorFloat
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCustomShaderEffectVehicleFX, Vector3::Zero);
				CRGBFloat v = NativeCustomShaderEffectVehicleFX->m_fSecondaryColor;
				return Vector3(v.red, v.green, v.blue);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeCustomShaderEffectVehicleFX);

				CRGBFloat v;
				v.red = value.X;
				v.green = value.Y;
				v.blue = value.Z;
				NativeCustomShaderEffectVehicleFX->m_fSecondaryColor = v;
			}
		}
		property Color SecondaryColor
		{
		public:
			Color get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCustomShaderEffectVehicleFX, Color::Empty);
				CRGBA v = NativeCustomShaderEffectVehicleFX->m_nSecondaryColor;
				return Color::FromArgb(v.a, v.r, v.g, v.b);
			}
			void set(Color value)
			{
				NULLPTR_CHECK(NativeCustomShaderEffectVehicleFX);

				CRGBA v;
				v.a = value.A;
				v.r = value.R;
				v.g = value.G;
				v.b = value.B;
				NativeCustomShaderEffectVehicleFX->m_nSecondaryColor = v;
			}
		}
		property Vector3 TertiaryColorFloat
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCustomShaderEffectVehicleFX, Vector3::Zero);
				CRGBFloat v = NativeCustomShaderEffectVehicleFX->m_fTertiaryColor;
				return Vector3(v.red, v.green, v.blue);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeCustomShaderEffectVehicleFX);

				CRGBFloat v;
				v.red = value.X;
				v.green = value.Y;
				v.blue = value.Z;
				NativeCustomShaderEffectVehicleFX->m_fTertiaryColor = v;
			}
		}
		property Color TertiaryColor
		{
		public:
			Color get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCustomShaderEffectVehicleFX, Color::Empty);
				CRGBA v = NativeCustomShaderEffectVehicleFX->m_nTertiaryColor;
				return Color::FromArgb(v.a, v.r, v.g, v.b);
			}
			void set(Color value)
			{
				NULLPTR_CHECK(NativeCustomShaderEffectVehicleFX);

				CRGBA v;
				v.a = value.A;
				v.r = value.R;
				v.g = value.G;
				v.b = value.B;
				NativeCustomShaderEffectVehicleFX->m_nTertiaryColor = v;
			}
		}
		property Vector3 QuaternaryColorFloat
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCustomShaderEffectVehicleFX, Vector3::Zero);
				CRGBFloat v = NativeCustomShaderEffectVehicleFX->m_fQuaternaryColor;
				return Vector3(v.red, v.green, v.blue);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeCustomShaderEffectVehicleFX);

				CRGBFloat v;
				v.red = value.X;
				v.green = value.Y;
				v.blue = value.Z;
				NativeCustomShaderEffectVehicleFX->m_fQuaternaryColor = v;
			}
		}
		property Color QuaternaryColor
		{
		public:
			Color get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCustomShaderEffectVehicleFX, Color::Empty);
				CRGBA v = NativeCustomShaderEffectVehicleFX->m_nQuaternaryColor;
				return Color::FromArgb(v.a, v.r, v.g, v.b);
			}
			void set(Color value)
			{
				NULLPTR_CHECK(NativeCustomShaderEffectVehicleFX);

				CRGBA v;
				v.a = value.A;
				v.r = value.R;
				v.g = value.G;
				v.b = value.B;
				NativeCustomShaderEffectVehicleFX->m_nQuaternaryColor = v;
			}
		}
		property Vector3 QuinaryColorFloat
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCustomShaderEffectVehicleFX, Vector3::Zero);
				CRGBFloat v = NativeCustomShaderEffectVehicleFX->m_fQuinaryColor;
				return Vector3(v.red, v.green, v.blue);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeCustomShaderEffectVehicleFX);

				CRGBFloat v;
				v.red = value.X;
				v.green = value.Y;
				v.blue = value.Z;
				NativeCustomShaderEffectVehicleFX->m_fQuinaryColor = v;
			}
		}
		property Color QuinaryColor
		{
		public:
			Color get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCustomShaderEffectVehicleFX, Color::Empty);
				CRGBA v = NativeCustomShaderEffectVehicleFX->m_nQuinaryColor;
				return Color::FromArgb(v.a, v.r, v.g, v.b);
			}
			void set(Color value)
			{
				NULLPTR_CHECK(NativeCustomShaderEffectVehicleFX);

				CRGBA v;
				v.a = value.A;
				v.r = value.R;
				v.g = value.G;
				v.b = value.B;
				NativeCustomShaderEffectVehicleFX->m_nQuinaryColor = v;
			}
		}
		property Vector3 SpecularColorFloat
		{
		public:
			Vector3 get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCustomShaderEffectVehicleFX, Vector3::Zero);
				CRGBFloat v = NativeCustomShaderEffectVehicleFX->m_fSpecularColor;
				return Vector3(v.red, v.green, v.blue);
			}
			void set(Vector3 value)
			{
				NULLPTR_CHECK(NativeCustomShaderEffectVehicleFX);

				CRGBFloat v;
				v.red = value.X;
				v.green = value.Y;
				v.blue = value.Z;
				NativeCustomShaderEffectVehicleFX->m_fSpecularColor = v;
			}
		}
		property Color SpecularColor
		{
		public:
			Color get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCustomShaderEffectVehicleFX, Color::Empty);
				CRGBA v = NativeCustomShaderEffectVehicleFX->m_nSpecularColor;
				return Color::FromArgb(v.a, v.r, v.g, v.b);
			}
			void set(Color value)
			{
				NULLPTR_CHECK(NativeCustomShaderEffectVehicleFX);

				CRGBA v;
				v.a = value.A;
				v.r = value.R;
				v.g = value.G;
				v.b = value.B;
				NativeCustomShaderEffectVehicleFX->m_nSpecularColor = v;
			}
		}

		property UIntPtr ShaderGroup
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCustomShaderEffectVehicleFX, UIntPtr::Zero);
				NULLPTR_CHECK_WITH_RETURN(NativeCustomShaderEffectVehicleFX->m_pShaderGroup, UIntPtr::Zero);
				return UIntPtr(NativeCustomShaderEffectVehicleFX->m_pShaderGroup);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativeCustomShaderEffectVehicleFX);
				UINTPTR_ZERO_CHECK(value);
				NativeCustomShaderEffectVehicleFX->m_pShaderGroup = (rage::grmShaderGroup*)value.ToPointer();
			}
		}
		property float DirtLevel
		{
		public:
			float get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCustomShaderEffectVehicleFX, 0.0F);
				return NativeCustomShaderEffectVehicleFX->m_fDirtLevel;
			}
			void set(float value)
			{
				NULLPTR_CHECK(NativeCustomShaderEffectVehicleFX);
				NativeCustomShaderEffectVehicleFX->m_fDirtLevel = value;
			}
		}
		property uint8_t Wrecked
		{
		public:
			uint8_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCustomShaderEffectVehicleFX, 0);
				return NativeCustomShaderEffectVehicleFX->m_bWrecked;
			}
			void set(uint8_t value)
			{
				NULLPTR_CHECK(NativeCustomShaderEffectVehicleFX);
				NativeCustomShaderEffectVehicleFX->m_bWrecked = value;
			}
		}
		property int32_t Livery
		{
		public:
			int32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCustomShaderEffectVehicleFX, 0);
				return NativeCustomShaderEffectVehicleFX->m_nLivery;
			}
			void set(int32_t value)
			{
				NULLPTR_CHECK(NativeCustomShaderEffectVehicleFX);
				NativeCustomShaderEffectVehicleFX->m_nLivery = value;
			}
		}

	internal:
		IVCustomShaderEffectVehicleFX(CCustomShaderEffectVehicleFX* nativePtr);

	internal:
		CCustomShaderEffectVehicleFX* NativeCustomShaderEffectVehicleFX;
	};
}