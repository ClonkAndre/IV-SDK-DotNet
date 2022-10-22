#pragma once

class Native_CTimeCycle
{
public:

	// platform:/data
	static char*	GetTimecycleModifierPath()				{ return AddressSetter::GetRef<char*>(0x48A651, 0x63AD31); }
	static void		SetTimecycleModifierPath(char* value)	{ AddressSetter::GetRef<char*>(0x48A651, 0x63AD31) = value; }

	static void Initialise()
	{
		return ((void(__cdecl*)())(AddressSetter::Get(0x48AD70, 0x63B450)))();
	}
	static void InitModifiers()
	{
		return ((void(__cdecl*)())(AddressSetter::Get(0x48A650, 0x63AD30)))();
	}
};

namespace IVSDKDotNet {

	public ref class CTimeCycle
	{
	public:

		static void Initialise();
		static void InitModifiers();

		static property String^ TimecycleModifierPath {
			public:
				String^	get() { return gcnew String(Native_CTimeCycle::GetTimecycleModifierPath()); }
				void	set(String^ value) {
					msclr::interop::marshal_context ctx;
					Native_CTimeCycle::SetTimecycleModifierPath((char*)ctx.marshal_as<const char*>(value));
				}
		}

	};

}


