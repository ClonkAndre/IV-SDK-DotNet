// INI Reader / Writer by ItsClonkAndre

#include "pch.h"
#include "SettingsFile.h"

using namespace System::Globalization;

namespace IVSDKDotNet
{

	// =========================================================================
	// ========================== IniSectionValues =============================
	// =========================================================================
	IniSectionValue::IniSectionValue(String^ key, String^ value)
	{
		Values = gcnew Dictionary<String^, String^>();
		Values->Add(key, value);
	}

	// =========================================================================
	// =========================== IniInsertValue ==============================
	// =========================================================================
	IniInsertValue::IniInsertValue(int line, String^ str)
	{
		AtLine = line;
		StringToInsert = str;
	}

	// =========================================================================
	// ============================= SettingsFile ==============================
	// =========================================================================
	SettingsFile::SettingsFile(String^ filePath)
	{
		FilePath = filePath;
		m_dSections = gcnew Dictionary<String^, IniSectionValue^>();
		m_dComments = gcnew List<IniInsertValue^>();
		m_dLateInserts = gcnew List<IniInsertValue^>();
	}

	bool SettingsFile::Save()
	{
		if (!File::Exists(FilePath))
			return false;

		// Write file with content
		File::WriteAllText(FilePath, BuildAndReturnSettingsFileContent());

		return true;
	}
	bool SettingsFile::Load()
	{
		if (!File::Exists(FilePath))
			return false;

		array<String^>^ lines = File::ReadAllLines(FilePath);

		m_dSections->Clear();
		m_dComments->Clear();

		String^ currentSection = String::Empty;
		for (int i = 0; i < lines->Length; i++)
		{
			String^ line = lines[i];

			// Checks
			if (String::IsNullOrWhiteSpace(line)) // Empty line
			{
				m_dComments->Add(gcnew IniInsertValue(i, String::Empty));
				continue;
			}
			if (line->StartsWith(";")) // Comment
			{
				m_dComments->Add(gcnew IniInsertValue(i, line));
				continue;
			}

			// New section
			if (line->StartsWith("[") && line->EndsWith("]"))
			{
				line = line->Replace("[", "");
				line = line->Replace("]", "");

				m_dSections->Add(line, nullptr);
				currentSection = line;

				continue;
			}

			// Section values
			if (line->Contains("="))
			{
				array<String^>^ values = line->Split(s_aSeparator, StringSplitOptions::None);

				if (!String::IsNullOrEmpty(currentSection))
				{
					IniSectionValue^ c = m_dSections[currentSection];

					if (c)
						// Add key and value to SectionValue because it already exists.
						c->Values->Add(values[0], values[1]);
					else
						// Create new SectionValue and add key and value because it does not exists yet.
						m_dSections[currentSection] = gcnew IniSectionValue(values[0], values[1]);
				}
			}

		}

		return true;
	}

	// - - - Add - - -
	bool SettingsFile::AddSection(String^ sectionName)
	{
		if (String::IsNullOrWhiteSpace(sectionName))
			return false;
		if (m_dSections->ContainsKey(sectionName))
			return false;

		m_dSections->Add(sectionName, nullptr);
		return true;
	}
	bool SettingsFile::AddKeyToSection(String^ section, String^ keyName)
	{
		if (String::IsNullOrWhiteSpace(section))
			return false;
		if (String::IsNullOrWhiteSpace(keyName))
			return false;
		if (!m_dSections->ContainsKey(section))
			return false;

		IniSectionValue^ c = m_dSections[section];

		if (c)
			// SectionValues exists. Add key and value to SectionValues.
		{
			if (c->Values->ContainsKey(keyName)) // Key already exists in list.
				return false;

			c->Values->Add(keyName, "");
		}
		else
			// SectionValues does not exists. Create new SectionValues and add key and value to section values.
		{
			m_dSections[section] = gcnew IniSectionValue(keyName, "");
		}

		return true;
	}

	void SettingsFile::InsertAt(int line, String^ str)
	{
		if (line < 0)
			return;

		m_dLateInserts->Add(gcnew IniInsertValue(line, str));
	}

	// - - - Other - - -
	bool SettingsFile::DoesSectionExists(String^ section)
	{
		if (String::IsNullOrWhiteSpace(section))
			return false;

		return m_dSections->ContainsKey(section);
	}
	bool SettingsFile::DoesKeyExists(String^ section, String^ key)
	{
		if (String::IsNullOrWhiteSpace(section))
			return false;
		if (String::IsNullOrWhiteSpace(key))
			return false;
		if (!m_dSections->ContainsKey(section))
			return false;
		if (!m_dSections[section])
			return false;

		return m_dSections[section]->Values->ContainsKey(key);
	}
	bool SettingsFile::ClearSection(String^ section)
	{
		if (String::IsNullOrWhiteSpace(section))
			return false;
		if (!m_dSections->ContainsKey(section))
			return false;

		IniSectionValue^ c = m_dSections[section];

		if (c)
		{
			c->Values->Clear();
			m_dSections[section] = nullptr;
			return true;
		}

		return false;
	}
	int SettingsFile::GetTotalLineCount()
	{
		int totalSections = m_dSections->Count;
		int totalValues = 0;
		int totalComments = m_dComments->Count;
		int totalLateInserts = m_dLateInserts->Count;
		
		// Get number of total values
		for each (KeyValuePair<String^, IniSectionValue^> entry in m_dSections)
		{
			for each (KeyValuePair<String^, String^> sectionEntry in entry.Value->Values)
			{
				totalValues++;
			}
		}

		return totalSections + totalValues + totalComments + totalLateInserts;
	}

	// - - - Get/Set values - - -
	String^ SettingsFile::GetValue(String^ section, String^ key, String^ defaultValue)
	{
		if (String::IsNullOrWhiteSpace(section))
			return defaultValue;
		if (String::IsNullOrWhiteSpace(key))
			return defaultValue;
		if (!m_dSections->ContainsKey(section))
			return defaultValue;
		if (!m_dSections[section]->Values->ContainsKey(key))
			return defaultValue;

		return m_dSections[section]->Values[key];
	}
	bool SettingsFile::SetValue(String^ section, String^ key, String^ value)
	{
		if (String::IsNullOrWhiteSpace(section))
			return false;
		if (String::IsNullOrWhiteSpace(key))
			return false;
		if (!m_dSections->ContainsKey(section))
			return false;
		if (!m_dSections[section]->Values->ContainsKey(key))
			return false;

		m_dSections[section]->Values[key] = value;
		return true;
	}

#pragma region Boolean
	bool SettingsFile::GetBoolean(String^ section, String^ key, bool defaultValue)
	{
		String^ str = GetValue(section, key, "")->ToLower();
		if (String::IsNullOrWhiteSpace(str))
			return defaultValue;

		if (str == "true" || str == "yes" || str == "1")
			return true;

		return false;
	}
	bool SettingsFile::SetBoolean(String^ section, String^ key, bool value)
	{
		return SettingsFile::SetValue(section, key, value.ToString());
	}
#pragma endregion

#pragma region Integer
	Int32 SettingsFile::GetInteger(String^ section, String^ key, int defaultValue)
	{
		String^ str = GetValue(section, key, "");
		if (String::IsNullOrWhiteSpace(str))
			return defaultValue;

		return Int32::Parse(str);
	}
	bool SettingsFile::SetInteger(String^ section, String^ key, Int32 value)
	{
		return SettingsFile::SetValue(section, key, value.ToString());
	}
#pragma endregion

#pragma region Float
	float SettingsFile::GetFloat(String^ section, String^ key, float defaultValue)
	{
		String^ str = GetValue(section, key, "");
		if (String::IsNullOrWhiteSpace(str))
			return defaultValue;

		return float::Parse(str, CultureInfo::InvariantCulture);
	}
	bool SettingsFile::SetFloat(String^ section, String^ key, float value)
	{
		return SettingsFile::SetValue(section, key, value.ToString(CultureInfo::InvariantCulture));
	}
#pragma endregion

#pragma region Color
	Color SettingsFile::GetColor(String^ section, String^ key, Color defaultValue)
	{
		String^ str = GetValue(section, key, "");
		if (String::IsNullOrWhiteSpace(str))
			return defaultValue;

		array<String^>^ values = str->Split(s_aVectorSeparator, StringSplitOptions::None);

		if (values->Length > 7)
			return Color::FromArgb(
				Int32::Parse(values[1]),
				Int32::Parse(values[3]),
				Int32::Parse(values[5]),
				Int32::Parse(values[7]));

		return defaultValue;
	}
	bool SettingsFile::SetColor(String^ section, String^ key, Color value)
	{
		return SettingsFile::SetValue(section, key, String::Format("A:{0}:R:{1}:G:{2}:B:{3}",
			value.A.ToString(),
			value.R.ToString(),
			value.G.ToString(),
			value.B.ToString()));
	}
#pragma endregion

#pragma region Key
	Keys SettingsFile::GetKey(String^ section, String^ key, Keys defaultValue)
	{
		String^ str = GetValue(section, key, "");
		if (String::IsNullOrWhiteSpace(str))
			return defaultValue;

		return (Keys)Enum::Parse(Keys::typeid, str);
	}
	bool SettingsFile::SetKey(String^ section, String^ key, Keys value)
	{
		return SettingsFile::SetValue(section, key, value.ToString());
	}
#pragma endregion

#pragma region Quaternion
	Quaternion SettingsFile::GetQuaternion(String^ section, String^ key, Quaternion defaultValue)
	{
		String^ str = GetValue(section, key, "");
		if (String::IsNullOrWhiteSpace(str))
			return defaultValue;

		array<String^>^ values = str->Split(s_aVectorSeparator, StringSplitOptions::None);

		if (values->Length > 7)
			return Quaternion(
				float::Parse(values[1], s_cInvariantCulture),
				float::Parse(values[3], s_cInvariantCulture),
				float::Parse(values[5], s_cInvariantCulture),
				float::Parse(values[7], s_cInvariantCulture));

		return defaultValue;
	}
	bool SettingsFile::SetQuaternion(String^ section, String^ key, Quaternion value)
	{
		CultureInfo^ invariantCulture = CultureInfo::InvariantCulture;
		return SettingsFile::SetValue(section, key, String::Format("X:{0}:Y:{1}:Z:{2}:W:{3}",
			value.X.ToString(s_cInvariantCulture),
			value.Y.ToString(s_cInvariantCulture),
			value.Z.ToString(s_cInvariantCulture),
			value.W.ToString(s_cInvariantCulture)));
	}
#pragma endregion

#pragma region Vector2
	Vector2 SettingsFile::GetVector2(String^ section, String^ key, Vector2 defaultValue)
	{
		String^ str = GetValue(section, key, "");
		if (String::IsNullOrWhiteSpace(str))
			return defaultValue;

		array<String^>^ values = str->Split(s_aVectorSeparator, StringSplitOptions::None);
		CultureInfo^ invariantCulture = CultureInfo::InvariantCulture;

		if (values->Length > 3)
			return Vector2(
				float::Parse(values[1], s_cInvariantCulture),
				float::Parse(values[3], s_cInvariantCulture));

		return defaultValue;
	}
	bool SettingsFile::SetVector2(String^ section, String^ key, Vector2 value)
	{
		return SettingsFile::SetValue(section, key, String::Format("X:{0}:Y:{1}",
			value.X.ToString(s_cInvariantCulture),
			value.Y.ToString(s_cInvariantCulture)));
	}
#pragma endregion

#pragma region Vector3
	Vector3 SettingsFile::GetVector3(String^ section, String^ key, Vector3 defaultValue)
	{
		String^ str = GetValue(section, key, "");
		if (String::IsNullOrWhiteSpace(str))
			return defaultValue;

		array<String^>^ values = str->Split(s_aVectorSeparator, StringSplitOptions::None);

		if (values->Length > 5)
			return Vector3(
				float::Parse(values[1], s_cInvariantCulture),
				float::Parse(values[3], s_cInvariantCulture),
				float::Parse(values[5], s_cInvariantCulture));

		return defaultValue;
	}
	bool SettingsFile::SetVector3(String^ section, String^ key, Vector3 value)
	{
		return SettingsFile::SetValue(section, key, String::Format("X:{0}:Y:{1}:Z:{2}",
			value.X.ToString(s_cInvariantCulture),
			value.Y.ToString(s_cInvariantCulture),
			value.Z.ToString(s_cInvariantCulture)));
	}
#pragma endregion

#pragma region Vector4
	Vector4 SettingsFile::GetVector4(String^ section, String^ key, Vector4 defaultValue)
	{
		String^ str = GetValue(section, key, "");
		if (String::IsNullOrWhiteSpace(str))
			return defaultValue;

		array<String^>^ values = str->Split(s_aVectorSeparator, StringSplitOptions::None);

		if (values->Length > 7)
			return Vector4(
				float::Parse(values[1], s_cInvariantCulture),
				float::Parse(values[3], s_cInvariantCulture),
				float::Parse(values[5], s_cInvariantCulture),
				float::Parse(values[7], s_cInvariantCulture));

		return defaultValue;
	}
	bool SettingsFile::SetVector4(String^ section, String^ key, Vector4 value)
	{
		return SettingsFile::SetValue(section, key, String::Format("X:{0}:Y:{1}:Z:{2}:W:{3}",
			value.X.ToString(s_cInvariantCulture),
			value.Y.ToString(s_cInvariantCulture),
			value.Z.ToString(s_cInvariantCulture),
			value.W.ToString(s_cInvariantCulture)));
	}
#pragma endregion

	String^ SettingsFile::BuildAndReturnSettingsFileContent()
	{
		//if (m_dSections->Count == 0)
		//	return String::Empty;

		List<String^>^ listBuilder = gcnew List<String^>();
		StringBuilder^ strBuilder = gcnew StringBuilder();

		// Add section keys and values
		for each (KeyValuePair<String^, IniSectionValue^> entry in m_dSections)
		{

			// Add section
			listBuilder->Add(String::Format("[{0}]", entry.Key));

			// Add values
			if (entry.Value)
			{
				for each (KeyValuePair<String^, String^> sectionEntry in entry.Value->Values)
				{
					listBuilder->Add(String::Format("{0}={1}", sectionEntry.Key, sectionEntry.Value));
				}
			}

		}

		// Insert any comments or whitelines that where present before so we don't loose them
		for (int i = 0; i < m_dComments->Count; i++)
		{
			IniInsertValue^ value = m_dComments[i];
			listBuilder->Insert(value->AtLine, value->StringToInsert);
		}

		// Insert any late inserts
		for (int i = 0; i < m_dLateInserts->Count; i++)
		{
			IniInsertValue^ value = m_dLateInserts[i];
			listBuilder->Insert(value->AtLine, value->StringToInsert);
		}

		// Start building the final string
		for (int i = 0; i < listBuilder->Count; i++)
			strBuilder->AppendLine(listBuilder[i]);

		return strBuilder->ToString();
	}

	String^ SettingsFile::ToString()
	{
		return BuildAndReturnSettingsFileContent();
	}

}