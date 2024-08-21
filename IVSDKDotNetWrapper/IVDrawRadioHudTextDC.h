#pragma once

namespace IVSDKDotNet
{
	public ref class IVDrawRadioHudTextDC : public IVBaseDC
	{
	public:
		property array<Vector2>^ Verts
		{
		public:
			array<Vector2>^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeDrawRadioHudTextDC, nullptr);

				array<Vector2>^ arr = gcnew array<Vector2>(4);

				for (int i = 0; i < arr->Length; i++)
					arr[i] = CVector2DToVector2(NativeDrawRadioHudTextDC->m_vVerts[i]);

				return arr;
			}
			void set(array<Vector2>^ value)
			{
				NULLPTR_CHECK(NativeDrawRadioHudTextDC);
				NULLPTR_CHECK(value);

				for (int i = 0; i < value->Length; i++)
					NativeDrawRadioHudTextDC->m_vVerts[i] = Vector2ToCVector2D(value[i]);
			}
		}
		property IVSprite2D^ Sprite
		{
		public:
			IVSprite2D^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeDrawRadioHudTextDC, nullptr);
				NULLPTR_CHECK_WITH_RETURN(&NativeDrawRadioHudTextDC->m_sSprite, nullptr);
				return gcnew IVSprite2D(&NativeDrawRadioHudTextDC->m_sSprite);
			}
			void set(IVSprite2D^ value)
			{
				NULLPTR_CHECK(NativeDrawRadioHudTextDC);
				NULLPTR_CHECK(value);

				NativeDrawRadioHudTextDC->m_sSprite = *value->NativeSprite2D;
			}
		}
		property System::Drawing::Color Color
		{
		public:
			System::Drawing::Color get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeDrawRadioHudTextDC, System::Drawing::Color::Empty);
				return System::Drawing::Color::FromArgb(
					NativeDrawRadioHudTextDC->m_nColor.a,
					NativeDrawRadioHudTextDC->m_nColor.r,
					NativeDrawRadioHudTextDC->m_nColor.g,
					NativeDrawRadioHudTextDC->m_nColor.b);
			}
			void set(System::Drawing::Color value)
			{
				NULLPTR_CHECK(NativeDrawRadioHudTextDC);

				NativeDrawRadioHudTextDC->m_nColor.a = value.A;
				NativeDrawRadioHudTextDC->m_nColor.r = value.R;
				NativeDrawRadioHudTextDC->m_nColor.g = value.G;
				NativeDrawRadioHudTextDC->m_nColor.b = value.B;
			}
		}

	internal:
		IVDrawRadioHudTextDC(CDrawRadioHudTextDC* nativePtr);

	private:
		CDrawRadioHudTextDC* NativeDrawRadioHudTextDC;

	};
}