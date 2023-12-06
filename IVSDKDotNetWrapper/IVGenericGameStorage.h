#pragma once

namespace IVSDKDotNet
{
	public ref class IVGenericGameStorage
	{
	public:
		static property String^ ValidSaveName
		{
		public:
			String^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(CGenericGameStorage::ms_ValidSaveName, String::Empty);
				return gcnew String(CGenericGameStorage::ms_ValidSaveName);
			}
			void set(String^ value)
			{
				CHECK_NULL_OR_WHITESPACE_STRING(value);
				msclr::interop::marshal_context ctx;
				CGenericGameStorage::ms_ValidSaveName = (char*)ctx.marshal_as<const char*>(value);
			}
		}

	public:
		/// <summary>
		/// Gets the default save file name for GTA IV on PC.
		/// </summary>
		/// <returns>Will return "SGTA4".</returns>
		static String^ GetDefaultPCSaveFileName();
		static void MakeValidSaveName(String^ pString, int slotNumber);
		static bool SaveDataToWorkBuffer(IntPtr pData, int32_t sizeOfData);
		static bool LoadDataFromWorkBuffer(IntPtr pData, int32_t sizeOfData);

	};
}