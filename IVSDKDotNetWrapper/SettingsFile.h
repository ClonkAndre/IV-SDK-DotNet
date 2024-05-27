// Basic INI Reader / Writer by ItsClonkAndre

#pragma once

namespace IVSDKDotNet
{

	private ref class IniSectionValue
	{
	public:
		IniSectionValue(String^ key, String^ value);

		Dictionary<String^, String^>^ Values;
	};
	private ref class IniInsertValue
	{
	public:
		IniInsertValue(int line, String^ str);

		int AtLine;
		String^ StringToInsert;
	};

	/// <summary>
	/// Can be used to save and load settings.
	/// If your script has a settings file, it will be automatically loaded.
	/// Inline comments are not supported!
	/// </summary>
	public ref class SettingsFile
	{
	public:
		/// <summary>
		/// The path to the ini file.
		/// </summary>
		property String^ FilePath
		{
		public:		String^ get() { return m_sFilePath; }
		internal:	void set(String^ value) { m_sFilePath = value; }
		}

	public:
		/// <summary>
		/// Creates a new instance of the SettingsFile class.
		/// </summary>
		/// <param name="filePath">The path to the ini file.</param>
		SettingsFile(String^ filePath);
		~SettingsFile()
		{
			m_sFilePath = String::Empty;

			if (m_dSections)
			{
				m_dSections->Clear();
				m_dSections = nullptr;
			}
			if (m_dComments)
			{
				m_dComments->Clear();
				m_dComments = nullptr;
			}
			if (m_dLateInserts)
			{
				m_dLateInserts->Clear();
				m_dLateInserts = nullptr;
			}
		}

		/// <summary>
		/// Overrides the current ini file with the new content.
		/// </summary>
		/// <returns>True if the file got saved. False when the file does not exists or if there is nothing to save.</returns>
		bool Save();

		/// <summary>
		/// Loads the content of the specified ini file.
		/// If you made changes to the ini via SetValue and reload the file those changes are getting lost if you haven't saved the file first with Save.
		/// </summary>
		/// <returns>True if the file got loaded. False when the file does not exists.</returns>
		bool Load();

		/// <summary>
		/// Clears everything from the loaded ini file.
		/// </summary>
		void Clear();

		/// <summary>
		/// Adds a new section to the ini file.
		/// </summary>
		/// <param name="section">The name of the new section.</param>
		/// <returns>True if the section got created. Otherwise false if the section already exists in the ini or if the name is null.</returns>
		bool AddSection(String^ section);

		/// <summary>
		/// Adds a new key to the specified section.
		/// </summary>
		/// <param name="section">The section to add the new key.</param>
		/// <param name="key">The name of the new key.</param>
		/// <returns>True if the key got created in the section. Otherwise false if the section does not exists, the key already exists in the ini or if the name is null.</returns>
		bool AddKeyToSection(String^ section, String^ key);

		/// <summary>
		/// Allows you to insert a string at the given line number.
		/// An ideal usecase of this method would be to add comments to the settings file.
		/// </summary>
		/// <param name="line">At which line you would like to add the new string.</param>
		/// <param name="str">The string to add at the given line.</param>
		void InsertAt(int line, String^ str);

		/// <summary>
		/// Checks if a section exists.
		/// </summary>
		/// <param name="section">The name of the section.</param>
		/// <returns>True if the section exists. False if the given name is null or whitespace, or if the section does not exists.</returns>
		bool DoesSectionExists(String^ section);

		/// <summary>
		/// Checks if the key exists in the given section.
		/// </summary>
		/// <param name="section">The section to check if the key exists in it.</param>
		/// <param name="key">The key to check for if it exists in the given section.</param>
		/// <returns>True if the key exists in the given secrion. False if any of the names is null or whitespace, or if the section or key does not exists.</returns>
		bool DoesKeyExists(String^ section, String^ key);

		/// <summary>
		/// Clears all keys that are within the given section.
		/// </summary>
		/// <param name="section">The section to clear all keys from.</param>
		/// <returns>True if the keys should be removed from this section. False if the given name is null or whitespace, or if the section does not exists.</returns>
		bool ClearSection(String^ section);

		/// <summary>
		/// Gets the total number of lines there are currently in the settings file.
		/// </summary>
		/// <returns>The current number of lines there will be file.</returns>
		int GetTotalLineCount();

		/// <summary>
		/// Gets the value from the given section and key strings from the loaded ini file.
		/// </summary>
		/// <param name="section">The section the key is located.</param>
		/// <param name="key">The key you want to get the value from.</param>
		/// <param name="defaultValue">The default value if get value fails.</param>
		/// <returns>The value from the given section and key strings. Otherwise it returns defaultValue.</returns>
		String^ GetValue(String^ section, String^ key, String^ defaultValue);

		/// <summary>
		/// Sets the value from the given section and key strings from the loaded ini file.
		/// </summary>
		/// <param name="section">The section the key is located.</param>
		/// <param name="key">The key you want to set the value to.</param>
		/// <param name="value">The new value.</param>
		/// <returns>True if the value from the given section and key got changed. Otherwise false if the section or key does not exists.</returns>
		bool	SetValue(String^ section, String^ key, String^ value);

#pragma region Boolean
		/// <summary>
		/// Gets the boolean from the given section and key strings from the loaded ini file.
		/// </summary>
		/// <param name="section">The section the key is located.</param>
		/// <param name="key">The key you want to get the value from.</param>
		/// <param name="defaultValue">The default value if get value fails.</param>
		/// <returns>The boolean from the given section and key strings. Otherwise it returns defaultValue.</returns>
		bool GetBoolean(String^ section, String^ key, bool defaultValue);

		/// <summary>
		/// Sets the boolean from the given section and key strings from the loaded ini file.
		/// </summary>
		/// <param name="section">The section the key is located.</param>
		/// <param name="key">The key you want to set the value to.</param>
		/// <param name="value">The new value.</param>
		/// <returns>True if the value from the given section and key got changed. Otherwise false if the section or key does not exists.</returns>
		bool SetBoolean(String^ section, String^ key, bool value);
#pragma endregion

#pragma region Integer
		/// <summary>
		/// Gets the integer from the given section and key strings from the loaded ini file.
		/// </summary>
		/// <param name="section">The section the key is located.</param>
		/// <param name="key">The key you want to get the value from.</param>
		/// <param name="defaultValue">The default value if get value fails.</param>
		/// <returns>The integer from the given section and key strings. Otherwise it returns defaultValue.</returns>
		int GetInteger(String^ section, String^ key, int defaultValue);

		/// <summary>
		/// Sets the integer from the given section and key strings from the loaded ini file.
		/// </summary>
		/// <param name="section">The section the key is located.</param>
		/// <param name="key">The key you want to set the value to.</param>
		/// <param name="value">The new value.</param>
		/// <returns>True if the value from the given section and key got changed. Otherwise false if the section or key does not exists.</returns>
		bool SetInteger(String^ section, String^ key, int value);
#pragma endregion

#pragma region Float
		/// <summary>
		/// Gets the float from the given section and key strings from the loaded ini file.
		/// </summary>
		/// <param name="section">The section the key is located.</param>
		/// <param name="key">The key you want to get the value from.</param>
		/// <param name="defaultValue">The default value if get value fails.</param>
		/// <returns>The float from the given section and key strings. Otherwise it returns defaultValue.</returns>
		float GetFloat(String^ section, String^ key, float defaultValue);

		/// <summary>
		/// Sets the float from the given section and key strings from the loaded ini file.
		/// </summary>
		/// <param name="section">The section the key is located.</param>
		/// <param name="key">The key you want to set the value to.</param>
		/// <param name="value">The new value.</param>
		/// <returns>True if the value from the given section and key got changed. Otherwise false if the section or key does not exists.</returns>
		bool SetFloat(String^ section, String^ key, float value);
#pragma endregion

#pragma region Color
		/// <summary>
		/// Gets the color from the given section and key strings from the loaded ini file.
		/// </summary>
		/// <param name="section">The section the key is located.</param>
		/// <param name="key">The key you want to get the value from.</param>
		/// <param name="defaultValue">The default value if get value fails.</param>
		/// <returns>The color from the given section and key strings. Otherwise it returns defaultValue.</returns>
		Color GetColor(String^ section, String^ key, Color defaultValue);

		/// <summary>
		/// Sets the color from the given section and key strings from the loaded ini file.
		/// </summary>
		/// <param name="section">The section the key is located.</param>
		/// <param name="key">The key you want to set the value to.</param>
		/// <param name="value">The new value.</param>
		/// <returns>True if the value from the given section and key got changed. Otherwise false if the section or key does not exists.</returns>
		bool SetColor(String^ section, String^ key, Color value);
#pragma endregion

#pragma region Key
		/// <summary>
		/// Gets the WinForms Key from the given section and key strings from the loaded ini file.
		/// </summary>
		/// <param name="section">The section the key is located.</param>
		/// <param name="key">The key you want to get the value from.</param>
		/// <param name="defaultValue">The default value if get value fails.</param>
		/// <returns>The WinForms Key from the given section and key strings. Otherwise it returns defaultValue.</returns>
		Keys GetKey(String^ section, String^ key, Keys defaultValue);

		/// <summary>
		/// Sets the WinForms Key from the given section and key strings from the loaded ini file.
		/// </summary>
		/// <param name="section">The section the key is located.</param>
		/// <param name="key">The key you want to set the value to.</param>
		/// <param name="value">The new value.</param>
		/// <returns>True if the value from the given section and key got changed. Otherwise false if the section or key does not exists.</returns>
		bool SetKey(String^ section, String^ key, Keys value);
#pragma endregion

#pragma region Quaternion
		/// <summary>
		/// Gets an Quaternion from the given section and key strings from the loaded ini file.
		/// </summary>
		/// <param name="section">The section the key is located.</param>
		/// <param name="key">The key you want to get the value from.</param>
		/// <param name="defaultValue">The default value if get value fails.</param>
		/// <returns>The Quaternion from the given section and key strings. Otherwise it returns defaultValue.</returns>
		Quaternion	GetQuaternion(String^ section, String^ key, Quaternion defaultValue);

		/// <summary>
		/// Sets the Quaternion from the given section and key strings from the loaded ini file.
		/// </summary>
		/// <param name="section">The section the key is located.</param>
		/// <param name="key">The key you want to set the value to.</param>
		/// <param name="value">The new value.</param>
		/// <returns>True if the value from the given section and key got changed. Otherwise false if the section or key does not exists.</returns>
		bool		SetQuaternion(String^ section, String^ key, Quaternion value);
#pragma endregion

#pragma region Vector2
		/// <summary>
		/// Gets an Vector2 from the given section and key strings from the loaded ini file.
		/// </summary>
		/// <param name="section">The section the key is located.</param>
		/// <param name="key">The key you want to get the value from.</param>
		/// <param name="defaultValue">The default value if get value fails.</param>
		/// <returns>The Vector2 from the given section and key strings. Otherwise it returns defaultValue.</returns>
		Vector2 GetVector2(String^ section, String^ key, Vector2 defaultValue);

		/// <summary>
		/// Sets the Vector2 from the given section and key strings from the loaded ini file.
		/// </summary>
		/// <param name="section">The section the key is located.</param>
		/// <param name="key">The key you want to set the value to.</param>
		/// <param name="value">The new value.</param>
		/// <returns>True if the value from the given section and key got changed. Otherwise false if the section or key does not exists.</returns>
		bool	SetVector2(String^ section, String^ key, Vector2 value);
#pragma endregion

#pragma region Vector3
		/// <summary>
		/// Gets an Vector3 from the given section and key strings from the loaded ini file.
		/// </summary>
		/// <param name="section">The section the key is located.</param>
		/// <param name="key">The key you want to get the value from.</param>
		/// <param name="defaultValue">The default value if get value fails.</param>
		/// <returns>The Vector3 from the given section and key strings. Otherwise it returns defaultValue.</returns>
		Vector3 GetVector3(String^ section, String^ key, Vector3 defaultValue);

		/// <summary>
		/// Sets the Vector3 from the given section and key strings from the loaded ini file.
		/// </summary>
		/// <param name="section">The section the key is located.</param>
		/// <param name="key">The key you want to set the value to.</param>
		/// <param name="value">The new value.</param>
		/// <returns>True if the value from the given section and key got changed. Otherwise false if the section or key does not exists.</returns>
		bool	SetVector3(String^ section, String^ key, Vector3 value);
#pragma endregion

#pragma region Vector4
		/// <summary>
		/// Gets an Vector4 from the given section and key strings from the loaded ini file.
		/// </summary>
		/// <param name="section">The section the key is located.</param>
		/// <param name="key">The key you want to get the value from.</param>
		/// <param name="defaultValue">The default value if get value fails.</param>
		/// <returns>The Vector4 from the given section and key strings. Otherwise it returns defaultValue.</returns>
		Vector4 GetVector4(String^ section, String^ key, Vector4 defaultValue);

		/// <summary>
		/// Sets the Vector4 from the given section and key strings from the loaded ini file.
		/// </summary>
		/// <param name="section">The section the key is located.</param>
		/// <param name="key">The key you want to set the value to.</param>
		/// <param name="value">The new value.</param>
		/// <returns>True if the value from the given section and key got changed. Otherwise false if the section or key does not exists.</returns>
		bool	SetVector4(String^ section, String^ key, Vector4 value);
#pragma endregion

		virtual String^ ToString() override;

	private:
		String^ BuildAndReturnSettingsFileContent();

	private:
		static System::Globalization::CultureInfo^ s_cInvariantCulture = System::Globalization::CultureInfo::InvariantCulture;
		static array<String^>^ s_aSeparator =		gcnew array<String^>(1)	{ "=" };
		static array<String^>^ s_aVectorSeparator = gcnew array<String^>(1)	{ ":" };

		String^ m_sFilePath;
		Dictionary<String^, IniSectionValue^>^ m_dSections;
		List<IniInsertValue^>^ m_dComments;
		List<IniInsertValue^>^ m_dLateInserts;
		
	};

}