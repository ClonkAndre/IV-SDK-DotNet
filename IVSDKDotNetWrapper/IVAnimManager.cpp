#include "pch.h"
#include "IVAnimManager.h"

namespace IVSDKDotNet
{
	void IVAnimManager::Initialise()
	{
		CAnimManager::Initialise();
	}
	void IVAnimManager::AddAnimAssocDefinition(int id, String^ pName, String^ pFile, uint32_t numAnims, array<String^>^ pAnimNames, UIntPtr pAnimDescs, int unk1, int unk2, int unk3, bool unk4)
	{
		throw gcnew NotImplementedException();
	}
}