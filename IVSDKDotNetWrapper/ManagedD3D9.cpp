#include "pch.h"
#include "ManagedD3D9.h"

// - - - Methods / Functions - - -
bool ManagedD3D9::CreateTextureFromFile(String^ fileName, [OutAttribute] IntPtr% texturePtr, [OutAttribute] int% textureWidth, [OutAttribute] int% textureHeight, [OutAttribute] eResult% result)
{
	if (ImGui::GetCurrentContext() == nullptr)
	{
		result = eResult::ImGuiNotInitialized;
		texturePtr = IntPtr::Zero;
		textureWidth = 0;
		textureHeight = 0;
		return false;
	}
	if (String::IsNullOrWhiteSpace(fileName))
	{
		result = eResult::InvalidName;
		texturePtr = IntPtr::Zero;
		textureWidth = 0;
		textureHeight = 0;
		return false;
	}

	msclr::interop::marshal_context ctx;

	// Try create texture
	PDIRECT3DTEXTURE9 texture;
	HRESULT hr = D3DXCreateTextureFromFileExA(rage::g_pDirect3DDevice, ctx.marshal_as<const char*>(fileName), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &texture);

	if (hr != S_OK)
	{
		WRITE_TO_DEBUG_OUTPUT(String::Format("Failed to create texture from file {0}! HRESULT: {1}", Path::GetFileName(fileName), hr));
		result = (eResult)hr;
		texturePtr = IntPtr::Zero;
		textureWidth = 0;
		textureHeight = 0;
		return false;
	}

	// Keeping track of the amount of references
	texture->AddRef();

	// Get the texture surface description
	D3DSURFACE_DESC imageDesc;
	texture->GetLevelDesc(0, &imageDesc);

	// Set stuff
	result = eResult::OK;
	texturePtr = IntPtr(texture);
	textureWidth = imageDesc.Width;
	textureHeight = imageDesc.Height;

	// Register texture to script
	Assembly^ callingAssembly = Assembly::GetCallingAssembly();
	if (IVSDKDotNet::Manager::ManagerScript::s_Instance)
		IVSDKDotNet::Manager::ManagerScript::s_Instance->Direct3D9_RegisterScriptTexture(callingAssembly == nullptr ? nullptr : callingAssembly->GetName()->Name->Replace(".ivsdk", ""), texturePtr);

	return true;
}
bool ManagedD3D9::CreateTextureFromMemory(array<System::Byte>^ data, [OutAttribute] IntPtr% texturePtr, [OutAttribute] int% textureWidth, [OutAttribute] int% textureHeight, [OutAttribute] eResult% result)
{
	if (ImGui::GetCurrentContext() == nullptr)
	{
		result = eResult::ImGuiNotInitialized;
		texturePtr = IntPtr::Zero;
		textureWidth = 0;
		textureHeight = 0;
		return false;
	}
	if (data == nullptr)
	{
		result = eResult::InvalidData;
		texturePtr = IntPtr::Zero;
		textureWidth = 0;
		textureHeight = 0;
		return false;
	}

	// Pin managed array
	pin_ptr<System::Byte> pinnedData = &data[0];
	unsigned char* pby = pinnedData;
	void* dataPtr = reinterpret_cast<void*>(pby);

	msclr::interop::marshal_context ctx;

	// Try create texture
	PDIRECT3DTEXTURE9 texture;
	HRESULT hr = D3DXCreateTextureFromFileInMemoryEx(rage::g_pDirect3DDevice, dataPtr, data->Length, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &texture);

	if (hr != S_OK)
	{
		WRITE_TO_DEBUG_OUTPUT(String::Format("Failed to create texture from memory! HRESULT: {0}", hr));
		result = (eResult)hr;
		texturePtr = IntPtr::Zero;
		textureWidth = 0;
		textureHeight = 0;
		return false;
	}

	// Keeping track of the amount of references
	texture->AddRef();

	// Get the texture surface description
	D3DSURFACE_DESC imageDesc;
	texture->GetLevelDesc(0, &imageDesc);

	// Set stuff
	result = eResult::OK;
	texturePtr = IntPtr(texture);
	textureWidth = imageDesc.Width;
	textureHeight = imageDesc.Height;

	// Register texture to script
	Assembly^ callingAssembly = Assembly::GetCallingAssembly();
	if (IVSDKDotNet::Manager::ManagerScript::s_Instance)
		IVSDKDotNet::Manager::ManagerScript::s_Instance->Direct3D9_RegisterScriptTexture(callingAssembly == nullptr ? nullptr : callingAssembly->GetName()->Name->Replace(".ivsdk", ""), texturePtr);

	return true;
}
bool ManagedD3D9::ReleaseTexture(IntPtr% texturePtr)
{
	if (texturePtr == IntPtr::Zero)
		return false;

	PDIRECT3DTEXTURE9 texture = (PDIRECT3DTEXTURE9)texturePtr.ToPointer();

	if (texture)
	{
		texture->Release();

		texturePtr = IntPtr::Zero;
		return true;
	}

	return false;
}
bool ManagedD3D9::IsTextureValid(IntPtr texturePtr)
{
	PDIRECT3DTEXTURE9 texture = (PDIRECT3DTEXTURE9)texturePtr.ToPointer();

	if (!texture)
		return false;

	// Check reference count
	texture->AddRef();

	return texture->Release() > 0;
}
