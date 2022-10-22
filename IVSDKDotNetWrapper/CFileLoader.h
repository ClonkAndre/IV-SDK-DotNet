#pragma once

class Native_CFileLoader
{
public:

	// common:/DATA/Ambient.dat
	static char* GetAmbientDataPath()				{ return AddressSetter::GetRef<char*>(0x583720, 0x7E9F30); }
	static void  SetAmbientDataPath(char* value)	{ AddressSetter::GetRef<char*>(0x583720, 0x7E9F30) = value; }

	// platform:/data/game.rpf
	static char* GetGameRpfPath()					{ return AddressSetter::GetRef<char*>(0x866753, 0x7E1C83); }
	static void  SetGameRpfPath(char* value)		{ AddressSetter::GetRef<char*>(0x866753, 0x7E1C83) = value; }

	// common:/DATA/Scenarios.dat
	static char* GetScenariosDatPath()				{ return AddressSetter::GetRef<char*>(0x4F8142, 0x7B17C2); }
	static void  SetScenariosDatPath(char* value)	{ AddressSetter::GetRef<char*>(0x4F8142, 0x7B17C2) = value; }

	// platform:/textures/buttons_360
	static char* GetButtonsTxdPath()				{ return AddressSetter::GetRef<char*>(0x3FA992, 0x4876C2); }
	static void  SetButtonsTxdPath(char* value)		{ AddressSetter::GetRef<char*>(0x3FA992, 0x4876C2) = value; }

	// common:/data/materials
	static char* GetProceduralDatPath()				{ return AddressSetter::GetRef<char*>(0x5081CD, 0x66E13D); }
	static void  SetProceduralDatPath(char* value)	{ AddressSetter::GetRef<char*>(0x5081CD, 0x66E13D) = value; }

	// platform:/stream.ini
	static char* GetStreamIniPath()					{ return AddressSetter::GetRef<char*>(0x43290C, 0x4B489C); }
	static void  SetStreamIniPath(char* value)		{ AddressSetter::GetRef<char*>(0x43290C, 0x4B489C) = value; }

	// Priority? It's set to 2 and 1 for loading default.dat in TBoGT but 0 everywhere else
	static void LoadLevel(char* levelName, int nUnk)
	{
		((void(__cdecl*)(char*, int))(AddressSetter::Get(0x4D79A0, 0x6CBE60)))(levelName, nUnk);
	}
	static void LoadObjectTypes(char* fileName)
	{
		((void(__cdecl*)(char*))(AddressSetter::Get(0x4D67E0, 0x6CACA0)))(fileName);
	}
	static void LoadWater(char* fileName)
	{
		((void(__cdecl*)(char*))(AddressSetter::Get(0x544920, 0x5AE4C0)))(fileName);
	}
	static void LoadSpeechData(char* fileName)
	{
		((void(__cdecl*)(char*))(AddressSetter::Get(0x8ECC70, 0x3A9620)))(fileName);
	}
	static void MountWavePack(char* fileName, char* mount)
	{
		((void(__cdecl*)(char*, char*))(AddressSetter::Get(0x8EB8D0, 0x38F8D0)))(fileName, mount);
	}
	static void LoadPedObject(char* line)
	{
		((void(__cdecl*)(char*))(AddressSetter::Get(0x4D11A0, 0x6C57E0)))(line);
	}
	static void LoadVehicleObject(char* line)
	{
		((void(__cdecl*)(char*))(AddressSetter::Get(0x4D5D70, 0x6CA230)))(line);
	}
};

namespace IVSDKDotNet {

	public ref class CFileLoader
	{
	public:

		/// <summary>
		/// Gets or sets the path to common:/DATA/Ambient.dat
		/// </summary>
		static property String^ AmbientDataPath {
			public:
				String^ get() { return gcnew String(Native_CFileLoader::GetAmbientDataPath()); }
				void set(String^ value) {
					msclr::interop::marshal_context ctx;
					Native_CFileLoader::SetAmbientDataPath((char*)ctx.marshal_as<const char*>(value));
				}
		}

		/// <summary>
		/// Gets or sets the path to platform:/data/game.rpf
		/// </summary>
		static property String^ GameRpfPath {
			public:
				String^ get() { return gcnew String(Native_CFileLoader::GetGameRpfPath()); }
				void set(String^ value) {
					msclr::interop::marshal_context ctx;
					Native_CFileLoader::SetGameRpfPath((char*)ctx.marshal_as<const char*>(value));
				}
		}

		/// <summary>
		/// Gets or sets the path to common:/DATA/Scenarios.dat
		/// </summary>
		static property String^ ScenariosDatPath {
			public:
				String^ get() { return gcnew String(Native_CFileLoader::GetScenariosDatPath()); }
				void set(String^ value) {
					msclr::interop::marshal_context ctx;
					Native_CFileLoader::SetScenariosDatPath((char*)ctx.marshal_as<const char*>(value));
				}
		}

		/// <summary>
		/// Gets or sets the path to platform:/textures/buttons_360
		/// </summary>
		static property String^ ButtonsTxdPath {
			public:
				String^ get() { return gcnew String(Native_CFileLoader::GetButtonsTxdPath()); }
				void set(String^ value) {
					msclr::interop::marshal_context ctx;
					Native_CFileLoader::SetButtonsTxdPath((char*)ctx.marshal_as<const char*>(value));
				}
		}

		/// <summary>
		/// Gets or sets the path to common:/data/materials
		/// </summary>
		static property String^ ProceduralDatPath {
			public:
				String^ get() { return gcnew String(Native_CFileLoader::GetProceduralDatPath()); }
				void set(String^ value) {
					msclr::interop::marshal_context ctx;
					Native_CFileLoader::SetProceduralDatPath((char*)ctx.marshal_as<const char*>(value));
				}
		}

		/// <summary>
		/// Gets or sets the path to platform:/stream.ini
		/// </summary>
		static property String^ StreamIniPath {
			public:
				String^ get() { return gcnew String(Native_CFileLoader::GetStreamIniPath()); }
				void set(String^ value) {
					msclr::interop::marshal_context ctx;
					Native_CFileLoader::SetStreamIniPath((char*)ctx.marshal_as<const char*>(value));
				}
		}

		/// <summary></summary>
		/// <param name="levelName"></param>
		/// <param name="nUnk">Priority? It's set to 2 and 1 for loading default.dat in TBoGT but 0 everywhere else</param>
		static void LoadLevel(String^ levelName, int nUnk);

		static void LoadObjectTypes(String^ fileName);
		static void LoadWater(String^ fileName);
		static void LoadSpeechData(String^ fileName);
		static void MountWavePack(String^ fileName, String^ mount);
		static void LoadPedObject(String^ line);
		static void LoadVehicleObject(String^ line);

	};

}