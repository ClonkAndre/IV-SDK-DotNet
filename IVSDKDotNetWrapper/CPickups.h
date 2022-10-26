#pragma once

class Native_CPickups
{
public:
	static void DoPickUpEffects()
	{
		return ((void(__cdecl*)())(AddressSetter::Get(0x534280, 0x589100)))();
	}
};

namespace IVSDKDotNet {

	public ref class CPickups
	{
	public:
		void DoPickUpEffects();
	};

}