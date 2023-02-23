#pragma once

class Native_CBuilding : public Native_CEntity
{
public:

};
VALIDATE_SIZE(Native_CBuilding, 0x70);

namespace IVSDKDotNet {

	public ref class CBuilding : CEntity
	{
	public:
		CBuilding(Native_CBuilding* native);
	};

}