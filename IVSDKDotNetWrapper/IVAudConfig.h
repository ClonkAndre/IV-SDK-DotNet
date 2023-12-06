#pragma once

namespace IVSDKDotNet
{
	public ref class IVAudConfig
	{
	public:
		/// <summary>
		/// Undocumented.
		/// </summary>
		/// <param name="path">The path to the file to load the audio config from?</param>
		void LoadFromFile(String^ path);

		/// <summary>
		/// Gets the managed UIntPtr from the native pointer.
		/// </summary>
		/// <returns>The managed UIntPtr from the native pointer</returns>
		UIntPtr GetUIntPtr();

	internal:
		IVAudConfig(audConfig* nativePtr);

	internal:
		audConfig* NativeAudConfig;
	};
}