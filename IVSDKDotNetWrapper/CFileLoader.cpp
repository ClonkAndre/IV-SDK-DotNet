#include "pch.h"
#include "CFileLoader.h"

namespace IVSDKDotNet {

	void CFileLoader::LoadLevel(String^ levelName, int nUnk)
	{
		msclr::interop::marshal_context ctx;
		Native_CFileLoader::LoadLevel((char*)ctx.marshal_as<const char*>(levelName), nUnk);
	}

	void CFileLoader::LoadObjectTypes(String^ fileName)
	{
		msclr::interop::marshal_context ctx;
		Native_CFileLoader::LoadObjectTypes((char*)ctx.marshal_as<const char*>(fileName));
	}
	void CFileLoader::LoadWater(String^ fileName)
	{
		msclr::interop::marshal_context ctx;
		Native_CFileLoader::LoadWater((char*)ctx.marshal_as<const char*>(fileName));
	}
	void CFileLoader::LoadSpeechData(String^ fileName)
	{
		msclr::interop::marshal_context ctx;
		Native_CFileLoader::LoadSpeechData((char*)ctx.marshal_as<const char*>(fileName));
	}
	void CFileLoader::MountWavePack(String^ fileName, String^ mount)
	{
		msclr::interop::marshal_context ctx;
		Native_CFileLoader::MountWavePack((char*)ctx.marshal_as<const char*>(fileName), (char*)ctx.marshal_as<const char*>(mount));
	}
	void CFileLoader::LoadPedObject(String^ line)
	{
		msclr::interop::marshal_context ctx;
		Native_CFileLoader::LoadPedObject((char*)ctx.marshal_as<const char*>(line));
	}
	void CFileLoader::LoadVehicleObject(String^ line)
	{
		msclr::interop::marshal_context ctx;
		Native_CFileLoader::LoadVehicleObject((char*)ctx.marshal_as<const char*>(line));
	}

}