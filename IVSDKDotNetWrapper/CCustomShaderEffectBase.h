#pragma once

class CCustomShaderEffectBase
{
public:
	void Update(Native_CEntity* attachedEntity)
	{
		((void(__thiscall*)(CCustomShaderEffectBase*, Native_CEntity*))(*(void***)this)[3])(this, attachedEntity);
	}
};