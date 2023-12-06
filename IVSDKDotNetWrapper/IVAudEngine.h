#pragma once

namespace IVSDKDotNet
{
	public ref class IVAudEngine
	{
	public:
		static property IVAudConfig^ SoundsConfig
		{
		public:
			IVAudConfig^ get()
			{
				audConfig* c = &audEngine::m_pSoundsConfig;
				NULLPTR_CHECK_WITH_RETURN(c, nullptr);

				return gcnew IVAudConfig(c);
			}
			void set(IVAudConfig^ value)
			{
				NULLPTR_CHECK(value);

				audConfig* c = &audEngine::m_pSoundsConfig;
				NULLPTR_CHECK(c);

				NULLPTR_CHECK(value->NativeAudConfig);
				c = value->NativeAudConfig;
			}
		}
		static property IVAudConfig^ CurvesConfig
		{
		public:
			IVAudConfig^ get()
			{
				audConfig* c = &audEngine::m_pCurvesConfig;
				NULLPTR_CHECK_WITH_RETURN(c, nullptr);

				return gcnew IVAudConfig(c);
			}
			void set(IVAudConfig^ value)
			{
				NULLPTR_CHECK(value);

				audConfig* c = &audEngine::m_pCurvesConfig;
				NULLPTR_CHECK(c);

				NULLPTR_CHECK(value->NativeAudConfig);
				c = value->NativeAudConfig;
			}
		}
		static property IVAudConfig^ GameConfig
		{
		public:
			IVAudConfig^ get()
			{
				audConfig* c = &audEngine::m_pGameConfig;
				NULLPTR_CHECK_WITH_RETURN(c, nullptr);

				return gcnew IVAudConfig(c);
			}
			void set(IVAudConfig^ value)
			{
				NULLPTR_CHECK(value);

				audConfig* c = &audEngine::m_pGameConfig;
				NULLPTR_CHECK(c);

				NULLPTR_CHECK(value->NativeAudConfig);
				c = value->NativeAudConfig;
			}
		}

		static property IVAudEngine^ TheAudEngine
		{
		public:
			IVAudEngine^ get()
			{
				audEngine* c = &AudioEngine;
				NULLPTR_CHECK_WITH_RETURN(c, nullptr);

				return gcnew IVAudEngine(c);
			}
			void set(IVAudEngine^ value)
			{
				NULLPTR_CHECK(value);

				audEngine* c = &AudioEngine;
				NULLPTR_CHECK(c);

				NULLPTR_CHECK(value->NativeAudEngine);
				c = value->NativeAudEngine;
			}
		}

	public:
		/// <summary>
		/// This is used after every category patch, but the parameter is 1 in ep2 and 0 in the rest.
		/// </summary>
		/// <param name="unk1">Unknown. 1 in ep2 and 0 in the rest.</param>
		void SetUnknown(float unk1);

	internal:
		IVAudEngine(audEngine* nativePtr);

	internal:
		audEngine* NativeAudEngine;
	};
}