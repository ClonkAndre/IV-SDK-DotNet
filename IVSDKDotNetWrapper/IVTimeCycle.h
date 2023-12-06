#pragma once

namespace IVSDKDotNet
{
	public ref class IVTimeCycle
	{
	public:
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
		static void Initialise();
		static void InitModifiers();
	};
}