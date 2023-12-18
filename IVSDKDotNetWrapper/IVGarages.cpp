#include "pch.h"
#include "IVGarages.h"

namespace IVSDKDotNet
{
	bool IVGarages::CameraShouldBeOutside()
	{
		return CGarages::CameraShouldBeOutside();
	}
	void IVGarages::CloseHideOutGaragesBeforeSave(bool unk)
	{
		CGarages::CloseHideOutGaragesBeforeSave(unk);
	}
	void IVGarages::Init()
	{
		CGarages::Init();
	}
	bool IVGarages::Load()
	{
		return CGarages::Load();
	}
	void IVGarages::PlayerArrestedOrDied()
	{
		CGarages::PlayerArrestedOrDied();
	}
	bool IVGarages::Save()
	{
		return CGarages::Save();
	}
	void IVGarages::Shutdown()
	{
		CGarages::Shutdown();
	}
	void IVGarages::Update()
	{
		CGarages::Update();
	}
}