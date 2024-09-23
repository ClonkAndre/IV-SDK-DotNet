class CTask
{
public:
	void* operator new(size_t nSize)
	{
		return CPools::ms_pTaskPool->New();
	}
	void operator delete(void*, size_t, uint32_t) {};

	bool IsSimple()
	{
		return ((bool(__thiscall*)(CTask*))(*(void***)this)[2])(this);
	}
	int GetType()
	{
		return ((int(__thiscall*)(CTask*))(*(void***)this)[3])(this);
	}
};

class CTaskComplex : public CTask
{
public:

};

class CTaskSimple : public CTask
{
public:

};