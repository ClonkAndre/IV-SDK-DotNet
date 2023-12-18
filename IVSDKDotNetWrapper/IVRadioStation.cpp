#include "pch.h"
#include "IVRadioStation.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVRadioStation::IVRadioStation(CRadioStation* nativePtr)
	{
		NULLPTR_CHECK(nativePtr);
		NativeRadioStation = nativePtr;
	}

	// - - - Methods / Functions - - -
	void IVRadioStation::ForceTrack(String^ trackName, int unk1, int unk2)
	{
		NULLPTR_CHECK(NativeRadioStation);

		if (String::IsNullOrWhiteSpace(trackName))
			return;

		msclr::interop::marshal_context ctx;
		NativeRadioStation->ForceTrack((char*)ctx.marshal_as<const char*>(trackName), unk1, unk2);
	}

}

