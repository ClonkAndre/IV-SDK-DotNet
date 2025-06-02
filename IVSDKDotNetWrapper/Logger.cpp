#include "Logger.h"
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

void Logger::ForceFlush()
{
    if (!AreStreamsCreated())
        return;

    m_StreamWriter->Flush();
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

void Logger::Initialize(IVSDKDotNet::SettingsFile^ settings)
{
    if (m_bWasInitialized)
        return;

	m_LogItems = gcnew List<tLogItem>();

    // Get where to create the log file
    String^ fileName = "IVSDKDotNet.log";

    if (!settings->GetBoolean("Main", "CreateLogFilesInMainDirectory", true))
        fileName = Path::Combine("IVSDKDotNet", "logs", DateTime::Now.ToString()->Replace(":", "-"));

    // Now create the file at the given path
    CreateStream(fileName);

    m_bWasInitialized = true;
}
void Logger::Shutdown()
{
    if (!m_bWasInitialized)
        return;

    m_bWasInitialized = false;

    CloseStream();

    if (m_LogItems)
    {
        m_LogItems->Clear();
        m_LogItems = nullptr;
    }
}

void Logger::CreateStream(String^ fileName)
{
    if (AreStreamsCreated())
        return;

    String^ dirName = Path::GetDirectoryName(fileName);

    if (!String::IsNullOrWhiteSpace(dirName) && !Directory::Exists(fileName))
        Directory::CreateDirectory(fileName);

    //m_FileStream = File::Create(fileName);
    //m_StreamWriter = gcnew StreamWriter(m_FileStream);

    m_StreamWriter = File::CreateText(fileName);
}
void Logger::CloseStream()
{
    if (!AreStreamsCreated())
        return;

    m_StreamWriter->Close();
    m_StreamWriter = nullptr;
    //m_FileStream = nullptr;
}

void Logger::Log(eConsoleLogStyle style, String^ str, bool alsoShowInConsole)
{
    if (!m_bWasInitialized)
        return;
    if (str == nullptr)
        return;

    if (String::IsNullOrWhiteSpace(str))
    {
        tLogItem item = tLogItem(DateTime::UtcNow, style, str, alsoShowInConsole);
        m_LogItems->Add(item);
        m_StreamWriter->WriteLine(item.ToString());
        return;
    }

    String^ fixedStr = str;

    // Check for unsupported characters
    if (fixedStr->Contains("{"))
        fixedStr = fixedStr->Replace("{", "");
    if (fixedStr->Contains("}"))
        fixedStr = fixedStr->Replace("}", "");

    tLogItem item = tLogItem(DateTime::UtcNow, style, fixedStr, alsoShowInConsole);
    m_LogItems->Add(item);
    m_StreamWriter->WriteLine(item.ToString());
}
