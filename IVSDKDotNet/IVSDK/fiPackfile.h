namespace rage
{
	class fiPackfile
	{
	public:
		uint8_t pad[0x478];						// 000-478

		fiPackfile()
		{
			((void(__thiscall*)(fiPackfile*))(AddressSetter::Get("fiPackfile", "fiPackfile")))(this);
		}

		bool OpenPackfile(char* path, char unk1_1, char unk2_0, int unk3_0or3)
		{
			return ((bool(__thiscall*)(fiPackfile*, char*, char, char, int))(AddressSetter::Get("fiPackfile", "OpenPackfile")))(this, path, unk1_1, unk2_0, unk3_0or3);
		}

		bool Mount(char* mountPoint)
		{
			return ((bool(__thiscall*)(fiPackfile*, char*))(AddressSetter::Get("fiPackfile", "Mount")))(this, mountPoint);
		}
	};
	VALIDATE_SIZE(fiPackfile, 0x478);
}