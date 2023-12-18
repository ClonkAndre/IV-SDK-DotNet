#pragma once

namespace IVSDKDotNet
{
	public ref class IVShaderLib
	{
	public:
		/// <summary>
		/// Gets the technique id based on the technique name.
		/// </summary>
		/// <param name="name">The name of the technique like default, unlit, deferred, etc.</param>
		/// <returns>The technique id.</returns>
		static int GetTechniqueID(String^ name);
	};
}