#pragma once

namespace IVSDKDotNet
{
	public ref class IVSkyDome
	{
	public:
		static property IVSkyDome^ TheIVSkyDome
		{
		public:
			IVSkyDome^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(TheSkyDome, nullptr);
				return gcnew IVSkyDome(TheSkyDome);
			}
			void set(IVSkyDome^ value)
			{
				NULLPTR_CHECK(value);
				TheSkyDome = value->NativeSkyDome;
			}
		}
		static property String^ TexturePath
		{
		public:
			String^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(rage::SkyDome::sTexturePath, String::Empty);
				return gcnew String(rage::SkyDome::sTexturePath);
			}
			void set(String^ value)
			{
				CHECK_NULL_OR_WHITESPACE_STRING(value);

				msclr::interop::marshal_context ctx;
				rage::SkyDome::sTexturePath = (char*)ctx.marshal_as<const char*>(value);
			}
		}

	public:
		property IVSkyhatMiniNoise^ SkyhatMiniNoise
		{
		public:
			IVSkyhatMiniNoise^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSkyDome, nullptr);
				return gcnew IVSkyhatMiniNoise(&NativeSkyDome->m_sSkyhatMiniNoise);
			}
			void set(IVSkyhatMiniNoise^ value)
			{
				NULLPTR_CHECK(NativeSkyDome);
				NULLPTR_CHECK(value);
				NativeSkyDome->m_sSkyhatMiniNoise = *value->NativeSkyhatMiniNoise;
			}
		}

		property uint32_t DPSkyFront
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSkyDome, 0);
				return NativeSkyDome->m_nDPSkyFront;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeSkyDome);
				NativeSkyDome->m_nDPSkyFront = value;
			}
		}
		property uint32_t DPSkyBack
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSkyDome, 0);
				return NativeSkyDome->m_nDPSkyBack;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeSkyDome);
				NativeSkyDome->m_nDPSkyBack = value;
			}
		}
		property uint32_t Paraboloid
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSkyDome, 0);
				return NativeSkyDome->m_nParaboloid;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeSkyDome);
				NativeSkyDome->m_nParaboloid = value;
			}
		}
		property uint32_t Draw
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSkyDome, 0);
				return NativeSkyDome->m_nDraw;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeSkyDome);
				NativeSkyDome->m_nDraw = value;
			}
		}
		property uint32_t DrawWithMoon
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSkyDome, 0);
				return NativeSkyDome->m_nDrawWithMoon;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeSkyDome);
				NativeSkyDome->m_nDrawWithMoon = value;
			}
		}
		property uint32_t DrawStencil
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSkyDome, 0);
				return NativeSkyDome->m_nDrawStencil;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeSkyDome);
				NativeSkyDome->m_nDrawStencil = value;
			}
		}
		property uint32_t DrawSunOnly
		{
		public:
			uint32_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeSkyDome, 0);
				return NativeSkyDome->m_nDrawSunOnly;
			}
			void set(uint32_t value)
			{
				NULLPTR_CHECK(NativeSkyDome);
				NativeSkyDome->m_nDrawSunOnly = value;
			}
		}

	internal:
		IVSkyDome(rage::SkyDome* nativePtr);

	internal:
		rage::SkyDome* NativeSkyDome;
	};
}