class CSprite2d
{
public:
	rage::grcTexturePC* m_pTexture = nullptr;

	void SetTexture(char* sName)
	{
		((void(__thiscall*)(CSprite2d*, char*))(AddressSetter::Get("CSprite2d", "SetTexture")))(this, sName);
	}
	void Delete()
	{
		((void(__thiscall*)(CSprite2d*))(AddressSetter::Get("CSprite2d", "Delete")))(this);
	}
};
VALIDATE_SIZE(CSprite2d, 0x4);