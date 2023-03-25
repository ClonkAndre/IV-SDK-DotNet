#pragma once

class Native_CTask
{
public:
	void* operator new(size_t nSize)
	{
		return CPools::GetTaskPool()->New().ToPointer();
	}
	void operator delete(void*, size_t, uint32_t) {};
};

class Native_CTaskComplex : public Native_CTask
{
public:

};
class Native_CTaskSimple : public Native_CTask
{
public:

};