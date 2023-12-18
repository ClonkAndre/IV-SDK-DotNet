#pragma once

namespace IVSDKDotNet
{
	public value struct IVGlobalScene
	{
	public:
		property IVViewportPrimaryOrtho^ PrimaryViewport
		{
		public:
			IVViewportPrimaryOrtho^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGlobalScene, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativeGlobalScene->m_pPrimaryViewport, nullptr);
				return gcnew IVViewportPrimaryOrtho(NativeGlobalScene->m_pPrimaryViewport);
			}
			void set(IVViewportPrimaryOrtho^ value)
			{
				NULLPTR_CHECK(NativeGlobalScene);
				NULLPTR_CHECK(value);
				NULLPTR_CHECK(value->NativeViewportPrimaryOrtho);
				NativeGlobalScene->m_pPrimaryViewport = value->NativeViewportPrimaryOrtho;
			}
		}
		property IVViewportGame^ GameViewport
		{
		public:
			IVViewportGame^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGlobalScene, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativeGlobalScene->m_pGameViewport, nullptr);
				return gcnew IVViewportGame(NativeGlobalScene->m_pGameViewport);
			}
			void set(IVViewportGame^ value)
			{
				NULLPTR_CHECK(NativeGlobalScene);
				NULLPTR_CHECK(value);
				NULLPTR_CHECK(value->NativeViewportGame);
				NativeGlobalScene->m_pGameViewport = value->NativeViewportGame;
			}
		}
		property IVViewportRadar^ RadarViewport
		{
		public:
			IVViewportRadar^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGlobalScene, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativeGlobalScene->m_pRadarViewport, nullptr);
				return gcnew IVViewportRadar(NativeGlobalScene->m_pRadarViewport);
			}
			void set(IVViewportRadar^ value)
			{
				NULLPTR_CHECK(NativeGlobalScene);
				NULLPTR_CHECK(value);
				NULLPTR_CHECK(value->NativeViewportRadar);
				NativeGlobalScene->m_pRadarViewport = value->NativeViewportRadar;
			}
		}
		property IVViewportMobilePhone^ PhoneViewport
		{
		public:
			IVViewportMobilePhone^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGlobalScene, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativeGlobalScene->m_pPhoneViewport, nullptr);
				return gcnew IVViewportMobilePhone(NativeGlobalScene->m_pPhoneViewport);
			}
			void set(IVViewportMobilePhone^ value)
			{
				NULLPTR_CHECK(NativeGlobalScene);
				NULLPTR_CHECK(value);
				NULLPTR_CHECK(value->NativeViewportMobilePhone);
				NativeGlobalScene->m_pPhoneViewport = value->NativeViewportMobilePhone;
			}
		}

		property UIntPtr RenderTargetTexture
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGlobalScene, UIntPtr::Zero);
				NULLPTR_CHECK_WITH_RETURN(NativeGlobalScene->m_pRenderTargetTexture, UIntPtr::Zero);
				return UIntPtr(NativeGlobalScene->m_pRenderTargetTexture);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativeGlobalScene);
				NativeGlobalScene->m_pRenderTargetTexture = (rage::ProceduralTextureRenderTargetDef*)value.ToPointer();
			}
		}
		property UIntPtr RenderTarget
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGlobalScene, UIntPtr::Zero);
				NULLPTR_CHECK_WITH_RETURN(NativeGlobalScene->m_pRenderTarget, UIntPtr::Zero);
				return UIntPtr(NativeGlobalScene->m_pRenderTarget);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativeGlobalScene);
				NativeGlobalScene->m_pRenderTarget = (rage::grcRenderTargetPC*)value.ToPointer();
			}
		}
		property array<UIntPtr>^ UnkShaderFx
		{
		public:
			array<UIntPtr>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGlobalScene, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativeGlobalScene->m_pUnkShaderFx, nullptr);

				array<UIntPtr>^ arr = gcnew array<UIntPtr>(2);
				arr[0] = UIntPtr(NativeGlobalScene->m_pUnkShaderFx[0]);
				arr[1] = UIntPtr(NativeGlobalScene->m_pUnkShaderFx[1]);

				return arr;
			}
			void set(array<UIntPtr>^ value)
			{
				NULLPTR_CHECK(NativeGlobalScene);
				NULLPTR_CHECK(value);
				CHECK_ARRAY_MINIMUM_LENGTH(value->Length, 2);

				NativeGlobalScene->m_pUnkShaderFx[0] = (rage::grmShaderFx*)value[0].ToPointer();
				NativeGlobalScene->m_pUnkShaderFx[1] = (rage::grmShaderFx*)value[1].ToPointer();
			}
		}
		// TODO
		//property RAGE::SkyhatPerlinNoise^ SkyhatNoise
		//{
		//public:
		//	RAGE::SkyhatPerlinNoise^ get()
		//	{
		//		NULLPTR_CHECK_WITH_RETURN(NativeGlobalScene, nullptr);
		//		NULLPTR_CHECK_WITH_RETURN(&NativeGlobalScene->m_sSkyhatNoise, nullptr);
		//		return gcnew RAGE::SkyhatPerlinNoise(&NativeGlobalScene->m_sSkyhatNoise);
		//	}
		//	void set(RAGE::SkyhatPerlinNoise^ value)
		//	{
		//		NULLPTR_CHECK(value);
		//		// TODO
		//	}
		//}
		property array<UIntPtr>^ VertexBuffer
		{
		public:
			array<UIntPtr>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeGlobalScene, nullptr);
				NULLPTR_CHECK_WITH_RETURN(NativeGlobalScene->m_sVertexBuffer, nullptr);

				array<UIntPtr>^ arr = gcnew array<UIntPtr>(2);
				arr[0] = UIntPtr(&NativeGlobalScene->m_sVertexBuffer[0]);
				arr[1] = UIntPtr(&NativeGlobalScene->m_sVertexBuffer[1]);

				return arr;
			}
			void set(array<UIntPtr>^ value)
			{
				NULLPTR_CHECK(NativeGlobalScene);
				NULLPTR_CHECK(value);
				CHECK_ARRAY_MINIMUM_LENGTH(value->Length, 2);

				NativeGlobalScene->m_sVertexBuffer[0] = *(rage::grcVertexBufferD3D*)value[0].ToPointer();
				NativeGlobalScene->m_sVertexBuffer[1] = *(rage::grcVertexBufferD3D*)value[1].ToPointer();
			}
		}

	public:
		static IVGlobalScene FromUIntPtr(UIntPtr ptr);
		UIntPtr GetUIntPtr();

	internal:
		IVGlobalScene(tGlobalScene* nativePtr);

	internal:
		tGlobalScene* NativeGlobalScene;

	};
}