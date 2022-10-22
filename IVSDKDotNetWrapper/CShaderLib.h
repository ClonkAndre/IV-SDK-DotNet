#pragma once

class Native_CShaderLib
{
public:
	// default, unlit, deferred, etc.
	static int GetTechniqueID(char* name)
	{
		return ((int(__cdecl*)(char*))(AddressSetter::Get(0x2340C0, 0x185D0)))(name);
	}
};

namespace IVSDKDotNet {

	public ref class CShaderLib
	{
	public:

		/// <summary>
		/// default, unlit, deferred, etc.
		/// </summary>
		/// <param name="name"></param>
		/// <returns>The technique ID.</returns>
		static int GetTechniqueID(String^ name);

	};

}