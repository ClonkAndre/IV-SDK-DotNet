#include "pch.h"
#include "IVFileLoader.h"

namespace IVSDKDotNet
{
	void IVFileLoader::LoadLevel(String^ levelName, int nUnk)
	{
		CHECK_NULL_OR_WHITESPACE_STRING(levelName);
		msclr::interop::marshal_context ctx;
		CFileLoader::LoadLevel((char*)ctx.marshal_as<const char*>(levelName), nUnk);
	}
	void IVFileLoader::LoadObjectTypes(String^ fileName)
	{
		CHECK_NULL_OR_WHITESPACE_STRING(fileName);
		msclr::interop::marshal_context ctx;
		CFileLoader::LoadObjectTypes((char*)ctx.marshal_as<const char*>(fileName));
	}
	void IVFileLoader::LoadWater(String^ fileName)
	{
		CHECK_NULL_OR_WHITESPACE_STRING(fileName);
		msclr::interop::marshal_context ctx;
		CFileLoader::LoadWater((char*)ctx.marshal_as<const char*>(fileName));
	}
	void IVFileLoader::LoadSpeechData(String^ fileName)
	{
		CHECK_NULL_OR_WHITESPACE_STRING(fileName);
		msclr::interop::marshal_context ctx;
		CFileLoader::LoadSpeechData((char*)ctx.marshal_as<const char*>(fileName));
	}
	void IVFileLoader::MountWavePack(String^ fileName, String^ mount)
	{
		CHECK_NULL_OR_WHITESPACE_STRING(fileName);
		msclr::interop::marshal_context ctx;
		CFileLoader::MountWavePack((char*)ctx.marshal_as<const char*>(fileName), (char*)ctx.marshal_as<const char*>(mount));
	}
	void IVFileLoader::LoadObject(String^ pLine)
	{
		CHECK_NULL_OR_WHITESPACE_STRING(pLine);
		msclr::interop::marshal_context ctx;
		CFileLoader::LoadObject((char*)ctx.marshal_as<const char*>(pLine));
	}
	void IVFileLoader::LoadPedObject(String^ pLine)
	{
		CHECK_NULL_OR_WHITESPACE_STRING(pLine);
		msclr::interop::marshal_context ctx;
		CFileLoader::LoadPedObject((char*)ctx.marshal_as<const char*>(pLine));
	}
	void IVFileLoader::LoadVehicleObject(String^ pLine)
	{
		CHECK_NULL_OR_WHITESPACE_STRING(pLine);
		msclr::interop::marshal_context ctx;
		CFileLoader::LoadVehicleObject((char*)ctx.marshal_as<const char*>(pLine));
	}
}