namespace rage
{
	template<typename T>
	class pgDictionary
	{
	public:
		T* getEntryByKey(uint32_t nHash)
		{
			return ((T * (__thiscall*)(pgDictionary*, uint32_t))(AddressSetter::Get("pgDictionary", "getEntryByKey")))(this, nHash);
		}
	};
}