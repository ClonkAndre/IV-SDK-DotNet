// INI Reader / Writer by ItsClonkAndre

#include "pch.h"
#include "SettingsFile.h"

using namespace System::Globalization;
using namespace System::IO;

namespace IVSDKDotNet {

	// =========================================================================
	// ============================ SectionValues ==============================
	// =========================================================================
	SectionValues::SectionValues(String^ firstkey, String^ firstValue)
	{
		Values = gcnew Dictionary<String^, String^>();
		Values->Add(firstkey, firstValue);
	}

	// =========================================================================
	// ============================= SettingsFile ==============================
	// =========================================================================
	SettingsFile::SettingsFile(String^ filePath)
	{
		FilePath = filePath;
		m_dSections = gcnew Dictionary<String^, SectionValues^>();
	}

	bool SettingsFile::Save()
	{
		if (!File::Exists(FilePath))
			return false;
		if (m_dSections->Count == 0)
			return false;

		List<String^>^ lines = gcnew List<String^>();

		for each (KeyValuePair<String^, SectionValues^> entry in m_dSections) {

			// Add section
			lines->Add(String::Format("[{0}]", entry.Key));

			// Add section values
			if (entry.Value) {
				for each (KeyValuePair<String^, String^> sectionEntry in entry.Value->Values) {
					lines->Add(String::Format("{0}={1}", sectionEntry.Key, sectionEntry.Value));
				}
			}

		}

		File::WriteAllLines(FilePath, lines);

		return true;
	}
	bool SettingsFile::Load()
	{
		if (!File::Exists(FilePath))
			return false;

		array<String^>^ lines = File::ReadAllLines(FilePath);

		m_dSections->Clear();

		String^ currentSection = String::Empty;
		for (int i = 0; i < lines->Length; i++) {
			String^ line = lines[i];

			// Checks
			if (String::IsNullOrWhiteSpace(line)) // Empty line
				continue;
			if (line->StartsWith(";")) // Comment
				continue;

			// New section
			if (line->Contains("[") && line->Contains("]")) {
				if (line->StartsWith("[") && line->EndsWith("]")) {
					line = line->Replace("[", "");
					line = line->Replace("]", "");

					m_dSections->Add(line, nullptr);
					currentSection = line;

					continue;
				}
			}

			// Section values
			if (line->Contains("=")) {
				array<String^>^ values = line->Split(s_aSeparator, StringSplitOptions::None);

				if (!String::IsNullOrEmpty(currentSection)) {

					SectionValues^ c = m_dSections[currentSection];
					if (c) { // SectionValues exists. Add key and value to SectionValues.
						c->Values->Add(values[0], values[1]);
					}
					else { // SectionValues does not exists. Create new SectionValues and add key and value to section values.
						m_dSections[currentSection] = gcnew SectionValues(values[0], values[1]);
					}

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

		SectionValues^ c = m_dSections[section];
		if (c) { // SectionValues exists. Add key and value to SectionValues.
			if (c->Values->ContainsKey(keyName)) // Key already exists in list.
				return false;

			c->Values->Add(keyName, "");
		}
		else { // SectionValues does not exists. Create new SectionValues and add key and value to section values.
			m_dSections[section] = gcnew SectionValues(keyName, "");
		}
		return true;
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
				float::Parse(values[1], CultureInfo::InvariantCulture),
				float::Parse(values[3], CultureInfo::InvariantCulture),
				float::Parse(values[5], CultureInfo::InvariantCulture),
				float::Parse(values[7], CultureInfo::InvariantCulture));

		return defaultValue;
	}
	bool SettingsFile::SetQuaternion(String^ section, String^ key, Quaternion value)
	{
		return SettingsFile::SetValue(section, key, String::Format("X:{0}:Y:{1}:Z:{2}:W:{3}",
			value.X.ToString(CultureInfo::InvariantCulture),
			value.Y.ToString(CultureInfo::InvariantCulture),
			value.Z.ToString(CultureInfo::InvariantCulture),
			value.W.ToString(CultureInfo::InvariantCulture)));
	}
#pragma endregion

#pragma region Vector2
	Vector2 SettingsFile::GetVector2(String^ section, String^ key, Vector2 defaultValue)
	{
		String^ str = GetValue(section, key, "");
		if (String::IsNullOrWhiteSpace(str))
			return defaultValue;

		array<String^>^ values = str->Split(s_aVectorSeparator, StringSplitOptions::None);

		if (values->Length > 3)
			return Vector2(
				float::Parse(values[1], CultureInfo::InvariantCulture),
				float::Parse(values[3], CultureInfo::InvariantCulture));

		return defaultValue;
	}
	bool SettingsFile::SetVector2(String^ section, String^ key, Vector2 value)
	{
		return SettingsFile::SetValue(section, key, String::Format("X:{0}:Y:{1}",
			value.X.ToString(CultureInfo::InvariantCulture),
			value.Y.ToString(CultureInfo::InvariantCulture)));
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
				float::Parse(values[1], CultureInfo::InvariantCulture),
				float::Parse(values[3], CultureInfo::InvariantCulture),
				float::Parse(values[5], CultureInfo::InvariantCulture));

		return defaultValue;
	}
	bool SettingsFile::SetVector3(String^ section, String^ key, Vector3 value)
	{
		return SettingsFile::SetValue(section, key, String::Format("X:{0}:Y:{1}:Z:{2}",
			value.X.ToString(CultureInfo::InvariantCulture),
			value.Y.ToString(CultureInfo::InvariantCulture),
			value.Z.ToString(CultureInfo::InvariantCulture)));
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
				float::Parse(values[1], CultureInfo::InvariantCulture),
				float::Parse(values[3], CultureInfo::InvariantCulture),
				float::Parse(values[5], CultureInfo::InvariantCulture),
				float::Parse(values[7], CultureInfo::InvariantCulture));

		return defaultValue;
	}
	bool SettingsFile::SetVector4(String^ section, String^ key, Vector4 value)
	{
		return SettingsFile::SetValue(section, key, String::Format("X:{0}:Y:{1}:Z:{2}:W:{3}",
			value.X.ToString(CultureInfo::InvariantCulture),
			value.Y.ToString(CultureInfo::InvariantCulture),
			value.Z.ToString(CultureInfo::InvariantCulture),
			value.W.ToString(CultureInfo::InvariantCulture)));
	}
#pragma endregion

}