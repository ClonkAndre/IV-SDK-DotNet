#pragma once

namespace IVSDKDotNet
{
	public ref class IVDraw
	{
	public:
		static property IVDraw^ TheScene
		{
		public:
			IVDraw^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(&Scene, nullptr);
				return gcnew IVDraw(&Scene);
			}
			void set(IVDraw^ value)
			{
				NULLPTR_CHECK(value);
				NULLPTR_CHECK(value->NativeDraw);
				Scene = *value->NativeDraw;
			}
		}

	public:
		/// <summary>
		/// Use with: IVGlobalScene.FromUIntPtr(...);
		/// </summary>
		property UIntPtr GlobalScene
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeDraw, UIntPtr::Zero);
				NULLPTR_CHECK_WITH_RETURN(NativeDraw->m_pGlobalScene, UIntPtr::Zero);
				return UIntPtr(NativeDraw->m_pGlobalScene);
			}
			void set(UIntPtr value)
			{
				NULLPTR_CHECK(NativeDraw);
				UINTPTR_ZERO_CHECK(value);
				NativeDraw->m_pGlobalScene = (tGlobalScene*)value.ToPointer();
			}
		}
		/// <summary>
		/// Use with: IVRenderPhases.FromUIntPtr(...);
		/// </summary>
		property UIntPtr RenderPhases
		{
		public:
			UIntPtr get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeDraw, UIntPtr::Zero);
				NULLPTR_CHECK_WITH_RETURN(NativeDraw->m_pRenderPhases, UIntPtr::Zero);
				return UIntPtr(NativeDraw->m_pRenderPhases);
			}
		}
		property uint16_t NumRenderPhases
		{
		public:
			uint16_t get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeDraw, 0);
				return NativeDraw->m_nNumRenderPhases;
			}
			void set(uint16_t value)
			{
				NULLPTR_CHECK(NativeDraw);
				NativeDraw->m_nNumRenderPhases = value;
			}
		}
		property bool ForceHudWidescreen
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeDraw, 0);
				return NativeDraw->m_bForceHudWidescreen;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeDraw);
				NativeDraw->m_bForceHudWidescreen = value;
			}
		}

	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="bUnk">True forces it to 1.777... if ForceHudWidescreen bool is non-zero</param>
		/// <returns></returns>
		float CalculateAspectRatio(bool bUnk);

	internal:
		IVDraw(CDraw* nativePtr);

	internal:
		CDraw* NativeDraw;

	};
}