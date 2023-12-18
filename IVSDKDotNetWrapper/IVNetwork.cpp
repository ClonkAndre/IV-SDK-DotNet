#include "pch.h"
#include "IVNetwork.h"

namespace IVSDKDotNet
{
	// - - - Methods / Functions - - -
	bool IVNetwork::IsNetworkGameRunning()
	{
		return CNetwork::IsNetworkGameRunning();
	}
	bool IVNetwork::IsNetworkSession()
	{
		return CNetwork::IsNetworkSession();
	}
	void IVNetwork::CheckFramerate(bool bUnk, int time)
	{
		CNetwork::CheckFramerate(bUnk, time);
	}
}