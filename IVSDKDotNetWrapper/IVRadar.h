#pragma once

namespace IVSDKDotNet
{
	public ref class IVRadar
	{
	public:
		static property array<String^>^ BlipSpriteFilenames
		{
		public:
			array<String^>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(RadarBlipSpriteFilenames, nullptr);

				array<String^>^ arr = gcnew array<String^>(130);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = gcnew String(RadarBlipSpriteFilenames[i]);

				return arr;
			}
			void set(array<String^>^ value)
			{
				NULLPTR_CHECK(value);
				NULLPTR_CHECK(RadarBlipSpriteFilenames);

				msclr::interop::marshal_context ctx;
				for(int i = 0; i < value->Length; i++)
					RadarBlipSpriteFilenames[i] = ctx.marshal_as<const char*>(value[i]);
			}
		}

		// TODO
		//static property array<IVRadarTrace^>^ RadarTrace
		//{
		//public:
		//	array<IVRadarTrace^>^ get()
		//	{
		//		NULLPTR_CHECK_WITH_RETURN(CRadar::RadarTrace, nullptr);

		//		array<IVRadarTrace^>^ arr = gcnew array<IVRadarTrace^>(1500);

		//		for(int i = 0; i < arr->Length; i++)
		//			arr[i] = gcnew IVRadarTrace(CRadar::RadarTrace[i]);

		//		return arr;
		//	}
		//	void set(array<IVRadarTrace^>^ value)
		//	{
		//		NULLPTR_CHECK(value);
		//		NULLPTR_CHECK(CRadar::RadarTrace);

		//		for(int i = 0; i < value->Length; i++)
		//			CRadar::RadarTrace[i] = value[i]->NativeRadarTrace;
		//	}
		//}
		static property UIntPtr RadarRingBack
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(&CRadar::m_pRadarRingBack, UIntPtr::Zero);
				return UIntPtr(&CRadar::m_pRadarRingBack);
			}
			void set(UIntPtr value)
			{
				UINTPTR_ZERO_CHECK(value);
				CRadar::m_pRadarRingBack = *(CSprite2d*)value.ToPointer();
			}
		}
		static property UIntPtr RadarRingFront
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(&CRadar::m_pRadarRingFront, UIntPtr::Zero);
				return UIntPtr(&CRadar::m_pRadarRingFront);
			}
			void set(UIntPtr value)
			{
				UINTPTR_ZERO_CHECK(value);
				CRadar::m_pRadarRingFront = *(CSprite2d*)value.ToPointer();
			}
		}
		static property array<UIntPtr>^ RadarBlipSprites
		{
		public:
			array<UIntPtr>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(CRadar::RadarBlipSprites, nullptr);

				array<UIntPtr>^ arr = gcnew array<UIntPtr>(128);

				for(int i = 0; i < arr->Length; i++)
					arr[i] = UIntPtr(CRadar::RadarBlipSprites[i]);

				return arr;
			}
			void set(array<UIntPtr>^ value)
			{
				NULLPTR_CHECK(value);
				NULLPTR_CHECK(CRadar::RadarBlipSprites);

				for(int i = 0; i < value->Length; i++)
					CRadar::RadarBlipSprites[i] = (CSprite2d*)value[i].ToPointer();
			}
		}
		static property int32_t iNumCreatedBlipSprites
		{
		public:
			int32_t get()
			{
				return CRadar::iNumCreatedBlipSprites;
			}
			void set(int32_t value)
			{
				CRadar::iNumCreatedBlipSprites = value;
			}
		}
		static property float fRange
		{
		public:
			float get()
			{
				return CRadar::fRange;
			}
			void set(float value)
			{
				CRadar::fRange = value;
			}
		}
		static property Vector2 vec2DRadarOrigin
		{
		public:
			Vector2 get()
			{
				CVector2D& vec = CRadar::vec2DRadarOrigin;
				return Vector2(vec.x, vec.y);
			}
			void set(Vector2 value)
			{
				CVector2D vec;
				vec.x = value.X;
				vec.y = value.Y;
				CRadar::vec2DRadarOrigin = vec;
			}
		}

		static property int32_t iCentreBlip
		{
		public:
			int32_t get()
			{
				return CRadar::iCentreBlip;
			}
			void set(int32_t value)
			{
				CRadar::iCentreBlip = value;
			}
		}
		static property int32_t iNorthBlip
		{
		public:
			int32_t get()
			{
				return CRadar::iNorthBlip;
			}
			void set(int32_t value)
			{
				CRadar::iNorthBlip = value;
			}
		}
		static property int32_t iSimpleBlip
		{
		public:
			int32_t get()
			{
				return CRadar::iSimpleBlip;
			}
			void set(int32_t value)
			{
				CRadar::iSimpleBlip = value;
			}
		}
		static property int32_t iBlipHovering
		{
		public:
			int32_t get()
			{
				return CRadar::iBlipHovering;
			}
			void set(int32_t value)
			{
				CRadar::iBlipHovering = value;
			}
		}

	public:
		static void DrawBlips();
		static void DrawBlipNames();
		static void DrawFrameFront();
		static void DrawFrameBack();
		static void DrawRoute(bool bMenu);
		static int32_t ConvertUniqueBlipToActualBlip(int32_t index);
		static int32_t CreateBlip(bool unk, int32_t blipType, Vector3 vecPosition, int32_t dispFlag, String^ pScriptName);
		static void SetBlipParameter(int paramId, int32_t index, int value);
		static void SetBlipParameter(int paramId, int32_t index, float value);
		static bool RemoveBlip(int32_t index, bool isScriptHandle);
		static bool IsBlipIdInUse(int32_t index);
	};
}