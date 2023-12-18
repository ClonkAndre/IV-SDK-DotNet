#pragma once

namespace IVSDKDotNet
{
	public ref class IVFileLoader
	{
	public:
		/// <summary>
		/// common:/DATA/Ambient.dat
		/// </summary>
		static property String^ AmbientDataPath
		{
		public:
			String^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(CFileLoader::sAmbientDataPath, String::Empty);
				return gcnew String(CFileLoader::sAmbientDataPath);
			}
			void set(String^ value)
			{
				CHECK_NULL_OR_WHITESPACE_STRING(value);

				msclr::interop::marshal_context ctx;
				CFileLoader::sAmbientDataPath = (char*)ctx.marshal_as<const char*>(value);
			}
		}
		/// <summary>
		/// platform:/data/game.rpf
		/// </summary>
		static property String^ GameRpfPath
		{
		public:
			String^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(CFileLoader::sGameRpfPath, String::Empty);
				return gcnew String(CFileLoader::sGameRpfPath);
			}
			void set(String^ value)
			{
				CHECK_NULL_OR_WHITESPACE_STRING(value);

				msclr::interop::marshal_context ctx;
				CFileLoader::sGameRpfPath = (char*)ctx.marshal_as<const char*>(value);
			}
		}
		/// <summary>
		/// common:/DATA/Scenarios.dat
		/// </summary>
		static property String^ ScenariosDatPath
		{
		public:
			String^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(CFileLoader::sScenariosDatPath, String::Empty);
				return gcnew String(CFileLoader::sScenariosDatPath);
			}
			void set(String^ value)
			{
				CHECK_NULL_OR_WHITESPACE_STRING(value);

				msclr::interop::marshal_context ctx;
				CFileLoader::sScenariosDatPath = (char*)ctx.marshal_as<const char*>(value);
			}
		}
		/// <summary>
		/// platform:/textures/buttons_360
		/// </summary>
		static property String^ ButtonsTxdPath
		{
		public:
			String^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(CFileLoader::sButtonsTxdPath, String::Empty);
				return gcnew String(CFileLoader::sButtonsTxdPath);
			}
			void set(String^ value)
			{
				CHECK_NULL_OR_WHITESPACE_STRING(value);

				msclr::interop::marshal_context ctx;
				CFileLoader::sButtonsTxdPath = (char*)ctx.marshal_as<const char*>(value);
			}
		}
		/// <summary>
		/// common:/data/materials
		/// </summary>
		static property String^ ProceduralDatPath
		{
		public:
			String^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(CFileLoader::sProceduralDatPath, String::Empty);
				return gcnew String(CFileLoader::sProceduralDatPath);
			}
			void set(String^ value)
			{
				CHECK_NULL_OR_WHITESPACE_STRING(value);

				msclr::interop::marshal_context ctx;
				CFileLoader::sProceduralDatPath = (char*)ctx.marshal_as<const char*>(value);
			}
		}
		/// <summary>
		/// platform:/stream.ini
		/// </summary>
		static property String^ StreamIniPath
		{
		public:
			String^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(CFileLoader::sStreamIniPath, String::Empty);
				return gcnew String(CFileLoader::sStreamIniPath);
			}
			void set(String^ value)
			{
				CHECK_NULL_OR_WHITESPACE_STRING(value);

				msclr::interop::marshal_context ctx;
				CFileLoader::sStreamIniPath = (char*)ctx.marshal_as<const char*>(value);
			}
		}

	public:
		/// <summary>
		/// Undocumented.
		/// </summary>
		/// <param name="levelName"></param>
		/// <param name="nUnk">Priority? It's set to 2 and 1 for loading default.dat in TBoGT but 0 everywhere else.</param>
		static void LoadLevel(String^ levelName, int nUnk);
		static void LoadObjectTypes(String^ fileName);
		static void LoadWater(String^ fileName);
		static void LoadSpeechData(String^ fileName);
		static void MountWavePack(String^ fileName, String^ mount);
		static void LoadObject(String^ pLine);
		static void LoadPedObject(String^ pLine);
		static void LoadVehicleObject(String^ pLine);
	};
}