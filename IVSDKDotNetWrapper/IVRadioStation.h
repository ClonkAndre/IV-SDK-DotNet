#pragma once

namespace IVSDKDotNet
{
	public ref class IVRadioStation
	{
	public:
		/// <summary>
		/// Gets the name of the radio station.
		/// </summary>
		property String^ Name
		{
		public:
			String^ get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeRadioStation, String::Empty);
				return gcnew String(NativeRadioStation->m_sName);
			}
		}

		property bool IsFrozen
		{
		public:
			bool get()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeRadioStation, false);
				return NativeRadioStation->m_bFrozen == 0 ? false : true;
			}
			void set(bool value)
			{
				NULLPTR_CHECK(NativeRadioStation);
				NativeRadioStation->m_bFrozen = value ? 1 : 0;
			}
		}

	public:
		void ForceTrack(String^ trackName, int unk1, int unk2);

	internal:
		IVRadioStation(CRadioStation* nativePtr);

	internal:
		CRadioStation* NativeRadioStation;
	};
}