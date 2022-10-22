#include "pch.h"
#include "CCutsceneMgr.h"

namespace IVSDKDotNet {

	bool CCutsceneMgr::IsRunning()
	{
		return Native_CCutsceneMgr::IsRunning();
	}

}