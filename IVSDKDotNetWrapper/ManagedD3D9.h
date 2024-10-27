#pragma once

// Internal only
private ref class ManagedD3D9
{
public:
	static bool CreateTextureFromFile(String^ fileName, [OutAttribute] IntPtr% texturePtr, [OutAttribute] int% textureWidth, [OutAttribute] int% textureHeight, [OutAttribute] eResult% result);
	static bool CreateTextureFromMemory(array<System::Byte>^ data, [OutAttribute] IntPtr% texturePtr, [OutAttribute] int% textureWidth, [OutAttribute] int% textureHeight, [OutAttribute] eResult% result);
	static bool ReleaseTexture(IntPtr% texturePtr);
	static bool IsTextureValid(IntPtr texturePtr);
};