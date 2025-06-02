#pragma once

namespace IVSDKDotNet
{
	public ref class IVText
	{
	public:
		static property IVText^ TheIVText
		{
		public:
			IVText^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(&TheText, nullptr);
				return gcnew IVText(&TheText);
			}
		}

	public:
		String^ Get(String^ ident);
		String^ Get(uint32_t hash, String^ ident);

		void ReplaceTextOfTextLabel(String^ ident, String^ newText);
		void ReplaceTextOfTextLabel(uint32_t hash, String^ newText);

	internal:
		IVText(CText* nativePtr);

	internal:
		CText* NativeText;
	};
}