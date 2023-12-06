#include "pch.h"

void Logger::Log(String^ str)
{
    Log(eConsoleLogStyle::Default, str, true);
}
void Logger::Log(String^ str, bool alsoShowInConsole)
{
    Log(eConsoleLogStyle::Default, str, alsoShowInConsole);
}

void Logger::LogDebug(String^ str)
{
#if _DEBUG
    Log(eConsoleLogStyle::Debug, str, true);
#endif
}
void Logger::LogDebug(String^ str, bool alsoShowInConsole)
{
#if _DEBUG
    Log(eConsoleLogStyle::Debug, str, alsoShowInConsole);
#endif
}

void Logger::LogWarning(String^ str)
{
    Log(eConsoleLogStyle::Warning, str, true);
}
void Logger::LogWarning(String^ str, bool alsoShowInConsole)
{
    Log(eConsoleLogStyle::Warning, str, alsoShowInConsole);
}

void Logger::LogError(String^ str)
{
    Log(eConsoleLogStyle::Error, str, true);
}
void Logger::LogError(String^ str, bool alsoShowInConsole)
{
	Log(eConsoleLogStyle::Error, str, alsoShowInConsole);
}

void Logger::ClearLogItems()
{
    m_LogItems->Clear();
}
List<Logger::tLogItem>^ Logger::GetLogItems()
{
    return m_LogItems;
}
array<String^>^ Logger::GetLogItemsAsString()
{
    if (m_LogItems == nullptr)
        return Array::Empty<String^>();
    if (m_LogItems->Count == 0)
        return Array::Empty<String^>();

    array<String^>^ items = gcnew array<String^>(m_LogItems->Count);

    for (int i = 0; i < items->Length; i++)
        items[i] = m_LogItems[i].ToString();

    return items;
}

void Logger::Initialize()
{
	m_LogItems = gcnew List<tLogItem>();
}

void Logger::Log(eConsoleLogStyle style, String^ str, bool alsoShowInConsole)
{
    if (str == nullptr)
        return;

    if (String::IsNullOrWhiteSpace(str))
    {
        m_LogItems->Add(tLogItem(DateTime::UtcNow, style, str, alsoShowInConsole));
        return;
    }

    String^ fixedStr = str;

    // Check for unsupported characters
    if (fixedStr->Contains("{"))
        fixedStr = fixedStr->Replace("{", "");
    if (fixedStr->Contains("}"))
        fixedStr = fixedStr->Replace("}", "");

    m_LogItems->Add(tLogItem(DateTime::UtcNow, style, fixedStr, alsoShowInConsole));
}
