#pragma once

namespace IVSDKDotNet
{
	namespace Internal
	{
		public ref class ManagedD3D9
		{
		public:
			static bool CreateTextureFromFile(String^ ownerScriptName, String^ fileName, [OutAttribute] IntPtr% texturePtr, [OutAttribute] int% textureWidth, [OutAttribute] int% textureHeight, [OutAttribute] eResult% result);
			static bool CreateTextureFromMemory(String^ ownerScriptName, array<System::Byte>^ data, [OutAttribute] IntPtr% texturePtr, [OutAttribute] int% textureWidth, [OutAttribute] int% textureHeight, [OutAttribute] eResult% result);
			
			static IntPtr CreateTextureFromMemorySimple(array<System::Byte>^ data);

			static bool ReleaseTexture(IntPtr% texturePtr);
		};
	}
}