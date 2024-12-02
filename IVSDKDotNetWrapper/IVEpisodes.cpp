#include "pch.h"
#include "IVEpisodes.h"

namespace IVSDKDotNet
{

	// - - - Constructor - - -
	IVEpisodes::IVEpisodes(CEpisodes* ptr)
	{
		NULLPTR_CHECK(ptr);
		NativePtr = ptr;
	}

	// - - - Methods / Functions - - -
	bool IVEpisodes::IsEpisodeAvailable(int episodeId)
	{
		NULLPTR_CHECK_WITH_RETURN(NativePtr, false);
		return NativePtr->IsEpisodeAvailable(episodeId);
	}

}