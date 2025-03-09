class C_PcSave
{
public:

	// slot -1 is autosave
	static int SaveSlot(int32_t SlotNum)
	{
		return ((int(__cdecl*)(int32_t))(AddressSetter::Get("C_PcSave", "SaveSlot")))(SlotNum);
	}
	static int LoadSlot(int32_t SlotNum)
	{
		return ((int(__cdecl*)(int32_t))(AddressSetter::Get("C_PcSave", "LoadSlot")))(SlotNum);
	}
};