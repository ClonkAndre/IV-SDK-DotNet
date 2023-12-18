#include "pch.h"
#include "IVRadioTrackManager.h"

namespace IVSDKDotNet
{
	IVRadioStation^ IVRadioTrackManager::GetRadioStation(int32_t id)
	{
		CRadioStation* c = CAERadioTrackManager::GetRadioStation(id);
		NULLPTR_CHECK_WITH_RETURN(c, nullptr);

		return gcnew IVRadioStation(c);
	}
	IVRadioStation^ IVRadioTrackManager::GetRadioStationByName(String^ name)
	{
		if (String::IsNullOrWhiteSpace(name))
			return nullptr;

		msclr::interop::marshal_context ctx;

		CRadioStation* c = CAERadioTrackManager::GetRadioStationByName((char*)ctx.marshal_as<const char*>(name));
		NULLPTR_CHECK_WITH_RETURN(c, nullptr);

		return gcnew IVRadioStation(c);
	}
	IVRadioStation^ IVRadioTrackManager::GetRadioStationByHash(uint32_t hash)
	{
		CRadioStation* c = CAERadioTrackManager::GetRadioStationByHash(hash);
		NULLPTR_CHECK_WITH_RETURN(c, nullptr);

		return gcnew IVRadioStation(c);
	}
}