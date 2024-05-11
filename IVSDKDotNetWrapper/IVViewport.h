#pragma once

namespace IVSDKDotNet
{
	public ref class IVViewport
	{
	public:
		property IVViewportData^ Data
		{
		public:
			IVViewportData^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeViewport, nullptr);
				return gcnew IVViewportData(&NativeViewport->m_pData);
			}
			void set(IVViewportData^ value)
			{
				NULLPTR_CHECK(NativeViewport);
				NULLPTR_CHECK(value->NativeData);
				NativeViewport->m_pData = *value->NativeData;
			}
		}

	internal:
		IVViewport(CViewport* nativePtr);

	internal:
		CViewport* NativeViewport;
	};

	public ref class IVViewportPrimaryOrtho : public IVViewport
	{
	internal:
		IVViewportPrimaryOrtho(CViewportPrimaryOrtho* nativePtr);

	internal:
		CViewportPrimaryOrtho* NativeViewportPrimaryOrtho;
	};
	public ref class IVViewportGame : public IVViewport
	{
	internal:
		IVViewportGame(CViewportGame* nativePtr);

	internal:
		CViewportGame* NativeViewportGame;
	};
	public ref class IVViewportRadar : public IVViewport
	{
	internal:
		IVViewportRadar(CViewportRadar* nativePtr);

	internal:
		CViewportRadar* NativeViewportRadar;
	};
	public ref class IVViewportMobilePhone : public IVViewport
	{
	internal:
		IVViewportMobilePhone(CViewportMobilePhone* nativePtr);

	internal:
		CViewportMobilePhone* NativeViewportMobilePhone;
	};
}