#pragma once

using namespace IVSDKDotNet::Native;

// TODO: All these native classes need to go into IV-SDK! They should not be in the managed IV-SDK .NET version
//		 The managed classes should probably receive a cpp file

class CNativeCallContext
{
public:
	void* m_pReturn;							// 00-04
	uint32_t m_nArgCount;						// 04-08
	void* m_pArgs;								// 08-0C
	uint32_t m_nDataCount;						// 0C-10
	CVector* m_pOriginalData[4];			    // 10-20
	CQuaternion m_TemporaryData[4];		        // 20-60

public:
	template<typename T>
	inline T GetArgument(size_t idx)
	{
		uintptr_t* arguments = (uintptr_t*)m_pArgs;

		if (!arguments)
			return 0;
		if (!&arguments[idx])
			return 0;
		if (!arguments[idx])
			return 0;

		return *(T*)&arguments[idx];
	}

	template<typename T>
	inline bool SetResult(size_t idx, T value)
	{
		uintptr_t* returnValues = (uintptr_t*)m_pReturn;

		if (!returnValues)
			return false;
		if (!&returnValues[idx])
			return false;
		if (!returnValues[idx])
			return false;

		*(T*)&returnValues[idx] = value;
		return true;
	}
};
VALIDATE_OFFSET(CNativeCallContext, m_pOriginalData, 0x10);
VALIDATE_OFFSET(CNativeCallContext, m_TemporaryData, 0x20);

class CNativeContext : public CNativeCallContext
{
public:
	// Configuration
	enum
	{
		MaxNativeParams = 16,
		ArgSize = 4,
	};

	// Anything temporary that we need
	uint8_t m_TempStack[MaxNativeParams * ArgSize];

public:
	inline CNativeContext()
	{
		// It's okay to point both args and return at
		// the same pointer as the game will handle this
		m_pArgs = &m_TempStack;
		m_pReturn = &m_TempStack;
		m_nArgCount = 0;
		m_nDataCount = 0;
	}

	template <typename T>
	inline bool Push(T value)
	{
		// Have we reached our argument count?
		if (m_nArgCount == MaxNativeParams)
		{
			// We can only store 16 arguments
			return false;
		}

		// Is the argument too big?
		if (sizeof(T) > ArgSize)
		{
			// We only accept 4 byte or less arguments
			return false;
		}
		else if (sizeof(T) < ArgSize) // Is the argument too small?
		{
			// Reset the argument data
			*(unsigned int*)(m_TempStack + ArgSize * m_nArgCount) = 0;
		}

		// Add to argument to the argument stack
		*(T*)(m_TempStack + ArgSize * m_nArgCount) = value;

		// Increment the total argument count
		m_nArgCount++;

		return true;
	}

	template <typename T>
	inline T GetResult()
	{
		// Copy back any vector results
		while (m_nDataCount > 0)
		{
			m_nDataCount--;
			CVector* pVec3 = m_pOriginalData[m_nDataCount];
			CQuaternion* pVec4 = &m_TemporaryData[m_nDataCount];
			pVec3->x = pVec4->x;
			pVec3->y = pVec4->y;
			pVec3->z = pVec4->z;
		}

		return *(T*)m_TempStack;
	}
};

class NativeInvoke
{
private:
	typedef void(_cdecl* NativeCall)(CNativeCallContext* pNativeContext);

public:
	static bool Invoke(uint32_t uiHash, CNativeCallContext* pNativeContext)
	{
		NativeCall NativeFunc = (NativeCall)CTheScripts::FindNativeAddress(uiHash);

		if (NativeFunc == NULL)
			return false;

		eNativeHash hash = (eNativeHash)uiHash;

		NativeFunc(pNativeContext);
		return true;
	}

	static void InvokeEx(uint32_t uiHash, CNativeCallContext* pNativeContext)
	{
		IVSDKDotNet::Manager::ManagerScript::GetInstance()->DispatchNativeCall(uiHash, UIntPtr(pNativeContext));
	}

public:
	template <typename R>
	static inline R Invoke(eNativeHash hash)
	{
		// Create new native context
		CNativeContext* cxt = new CNativeContext();

		// Invoke the call
		InvokeEx((uint32_t)hash, cxt);

		// Get result
		R result = cxt->GetResult<R>();

		// Delete the context and return the result
		delete cxt;
		return result;

		//CNativeContext cxt;
		//Invoke((uint32_t)hash, &cxt);
		//return cxt.GetResult<R>();
	}

	template <typename R, typename T1>
	static inline R Invoke(eNativeHash hash, T1 p1)
	{
		// Create new native context
		CNativeContext* cxt = new CNativeContext();

		// Push arguments to call
		cxt->Push(p1);

		// Invoke the call
		InvokeEx((uint32_t)hash, cxt);

		// Get result
		R result = cxt->GetResult<R>();

		// Delete the context and return the result
		delete cxt;
		return result;

		//CNativeContext cxt;
		//cxt.Push(p1);
		//Invoke((uint32_t)hash, &cxt);
		//return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2>
	static inline R Invoke(eNativeHash hash, T1 p1, T2 p2)
	{
		// Create new native context
		CNativeContext* cxt = new CNativeContext();

		// Push arguments to call
		cxt->Push(p1);
		cxt->Push(p2);

		// Invoke the call
		InvokeEx((uint32_t)hash, cxt);

		// Get result
		R result = cxt->GetResult<R>();

		// Delete the context and return the result
		delete cxt;
		return result;

		//CNativeContext cxt;
		//cxt.Push(p1);
		//cxt.Push(p2);
		//Invoke((uint32_t)hash, &cxt);
		//return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3>
	static inline R Invoke(eNativeHash hash, T1 p1, T2 p2, T3 p3)
	{
		// Create new native context
		CNativeContext* cxt = new CNativeContext();

		// Push arguments to call
		cxt->Push(p1);
		cxt->Push(p2);
		cxt->Push(p3);

		// Invoke the call
		InvokeEx((uint32_t)hash, cxt);

		// Get result
		R result = cxt->GetResult<R>();

		// Delete the context and return the result
		delete cxt;
		return result;

		//CNativeContext cxt;
		//cxt.Push(p1);
		//cxt.Push(p2);
		//cxt.Push(p3);
		//Invoke((uint32_t)hash, &cxt);
		//return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4>
	static inline R Invoke(eNativeHash hash, T1 p1, T2 p2, T3 p3, T4 p4)
	{
		// Create new native context
		CNativeContext* cxt = new CNativeContext();

		// Push arguments to call
		cxt->Push(p1);
		cxt->Push(p2);
		cxt->Push(p3);
		cxt->Push(p4);

		// Invoke the call
		InvokeEx((uint32_t)hash, cxt);

		// Get result
		R result = cxt->GetResult<R>();

		// Delete the context and return the result
		delete cxt;
		return result;

		//CNativeContext cxt;
		//cxt.Push(p1);
		//cxt.Push(p2);
		//cxt.Push(p3);
		//cxt.Push(p4);
		//Invoke((uint32_t)hash, &cxt);
		//return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4,
		typename T5>
	static inline R Invoke(eNativeHash hash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5)
	{
		// Create new native context
		CNativeContext* cxt = new CNativeContext();

		// Push arguments to call
		cxt->Push(p1);
		cxt->Push(p2);
		cxt->Push(p3);
		cxt->Push(p4);
		cxt->Push(p5);

		// Invoke the call
		InvokeEx((uint32_t)hash, cxt);

		// Get result
		R result = cxt->GetResult<R>();

		// Delete the context and return the result
		delete cxt;
		return result;

		//CNativeContext cxt;
		//cxt.Push(p1);
		//cxt.Push(p2);
		//cxt.Push(p3);
		//cxt.Push(p4);
		//cxt.Push(p5);
		//Invoke((uint32_t)hash, &cxt);
		//return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4,
		typename T5, typename T6>
	static inline R Invoke(eNativeHash hash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6)
	{
		// Create new native context
		CNativeContext* cxt = new CNativeContext();

		// Push arguments to call
		cxt->Push(p1);
		cxt->Push(p2);
		cxt->Push(p3);
		cxt->Push(p4);
		cxt->Push(p5);
		cxt->Push(p6);

		// Invoke the call
		InvokeEx((uint32_t)hash, cxt);

		// Get result
		R result = cxt->GetResult<R>();

		// Delete the context and return the result
		delete cxt;
		return result;

		//CNativeContext cxt;
		//cxt.Push(p1);
		//cxt.Push(p2);
		//cxt.Push(p3);
		//cxt.Push(p4);
		//cxt.Push(p5);
		//cxt.Push(p6);
		//Invoke((uint32_t)hash, &cxt);
		//return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4,
		typename T5, typename T6, typename T7>
	static inline R Invoke(eNativeHash hash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7)
	{
		// Create new native context
		CNativeContext* cxt = new CNativeContext();

		// Push arguments to call
		cxt->Push(p1);
		cxt->Push(p2);
		cxt->Push(p3);
		cxt->Push(p4);
		cxt->Push(p5);
		cxt->Push(p6);
		cxt->Push(p7);

		// Invoke the call
		InvokeEx((uint32_t)hash, cxt);

		// Get result
		R result = cxt->GetResult<R>();

		// Delete the context and return the result
		delete cxt;
		return result;

		//CNativeContext cxt;
		//cxt.Push(p1);
		//cxt.Push(p2);
		//cxt.Push(p3);
		//cxt.Push(p4);
		//cxt.Push(p5);
		//cxt.Push(p6);
		//cxt.Push(p7);
		//Invoke((uint32_t)hash, &cxt);
		//return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4,
		typename T5, typename T6, typename T7, typename T8>
	static inline R Invoke(eNativeHash hash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8)
	{
		// Create new native context
		CNativeContext* cxt = new CNativeContext();

		// Push arguments to call
		cxt->Push(p1);
		cxt->Push(p2);
		cxt->Push(p3);
		cxt->Push(p4);
		cxt->Push(p5);
		cxt->Push(p6);
		cxt->Push(p7);
		cxt->Push(p8);

		// Invoke the call
		InvokeEx((uint32_t)hash, cxt);

		// Get result
		R result = cxt->GetResult<R>();

		// Delete the context and return the result
		delete cxt;
		return result;

		//CNativeContext cxt;
		//cxt.Push(p1);
		//cxt.Push(p2);
		//cxt.Push(p3);
		//cxt.Push(p4);
		//cxt.Push(p5);
		//cxt.Push(p6);
		//cxt.Push(p7);
		//cxt.Push(p8);
		//Invoke((uint32_t)hash, &cxt);
		//return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4,
		typename T5, typename T6, typename T7, typename T8, typename T9>
	static inline R Invoke(eNativeHash hash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,
		T9 p9)
	{
		// Create new native context
		CNativeContext* cxt = new CNativeContext();

		// Push arguments to call
		cxt->Push(p1);
		cxt->Push(p2);
		cxt->Push(p3);
		cxt->Push(p4);
		cxt->Push(p5);
		cxt->Push(p6);
		cxt->Push(p7);
		cxt->Push(p8);
		cxt->Push(p9);

		// Invoke the call
		InvokeEx((uint32_t)hash, cxt);

		// Get result
		R result = cxt->GetResult<R>();

		// Delete the context and return the result
		delete cxt;
		return result;

		//CNativeContext cxt;
		//cxt.Push(p1);
		//cxt.Push(p2);
		//cxt.Push(p3);
		//cxt.Push(p4);
		//cxt.Push(p5);
		//cxt.Push(p6);
		//cxt.Push(p7);
		//cxt.Push(p8);
		//cxt.Push(p9);
		//Invoke((uint32_t)hash, &cxt);
		//return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4,
		typename T5, typename T6, typename T7, typename T8, typename T9,
		typename T10>
	static inline R Invoke(eNativeHash hash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,
		T9 p9, T10 p10)
	{
		// Create new native context
		CNativeContext* cxt = new CNativeContext();

		// Push arguments to call
		cxt->Push(p1);
		cxt->Push(p2);
		cxt->Push(p3);
		cxt->Push(p4);
		cxt->Push(p5);
		cxt->Push(p6);
		cxt->Push(p7);
		cxt->Push(p8);
		cxt->Push(p9);
		cxt->Push(p10);

		// Invoke the call
		InvokeEx((uint32_t)hash, cxt);

		// Get result
		R result = cxt->GetResult<R>();

		// Delete the context and return the result
		delete cxt;
		return result;

		//CNativeContext cxt;
		//cxt.Push(p1);
		//cxt.Push(p2);
		//cxt.Push(p3);
		//cxt.Push(p4);
		//cxt.Push(p5);
		//cxt.Push(p6);
		//cxt.Push(p7);
		//cxt.Push(p8);
		//cxt.Push(p9);
		//cxt.Push(p10);
		//Invoke((uint32_t)hash, &cxt);
		//return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4,
		typename T5, typename T6, typename T7, typename T8, typename T9,
		typename T10, typename T11>
	static inline R Invoke(eNativeHash hash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,
		T9 p9, T10 p10, T11 p11)
	{
		// Create new native context
		CNativeContext* cxt = new CNativeContext();

		// Push arguments to call
		cxt->Push(p1);
		cxt->Push(p2);
		cxt->Push(p3);
		cxt->Push(p4);
		cxt->Push(p5);
		cxt->Push(p6);
		cxt->Push(p7);
		cxt->Push(p8);
		cxt->Push(p9);
		cxt->Push(p10);
		cxt->Push(p11);

		// Invoke the call
		InvokeEx((uint32_t)hash, cxt);

		// Get result
		R result = cxt->GetResult<R>();

		// Delete the context and return the result
		delete cxt;
		return result;

		//CNativeContext cxt;
		//cxt.Push(p1);
		//cxt.Push(p2);
		//cxt.Push(p3);
		//cxt.Push(p4);
		//cxt.Push(p5);
		//cxt.Push(p6);
		//cxt.Push(p7);
		//cxt.Push(p8);
		//cxt.Push(p9);
		//cxt.Push(p10);
		//cxt.Push(p11);
		//Invoke((uint32_t)hash, &cxt);
		//return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4,
		typename T5, typename T6, typename T7, typename T8, typename T9,
		typename T10, typename T11, typename T12>
	static inline R Invoke(eNativeHash hash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,
		T9 p9, T10 p10, T11 p11, T12 p12)
	{
		// Create new native context
		CNativeContext* cxt = new CNativeContext();

		// Push arguments to call
		cxt->Push(p1);
		cxt->Push(p2);
		cxt->Push(p3);
		cxt->Push(p4);
		cxt->Push(p5);
		cxt->Push(p6);
		cxt->Push(p7);
		cxt->Push(p8);
		cxt->Push(p9);
		cxt->Push(p10);
		cxt->Push(p11);
		cxt->Push(p12);

		// Invoke the call
		InvokeEx((uint32_t)hash, cxt);

		// Get result
		R result = cxt->GetResult<R>();

		// Delete the context and return the result
		delete cxt;
		return result;

		//CNativeContext cxt;
		//cxt.Push(p1);
		//cxt.Push(p2);
		//cxt.Push(p3);
		//cxt.Push(p4);
		//cxt.Push(p5);
		//cxt.Push(p6);
		//cxt.Push(p7);
		//cxt.Push(p8);
		//cxt.Push(p9);
		//cxt.Push(p10);
		//cxt.Push(p11);
		//cxt.Push(p12);
		//Invoke((uint32_t)hash, &cxt);
		//return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4,
		typename T5, typename T6, typename T7, typename T8, typename T9,
		typename T10, typename T11, typename T12, typename T13>
	static inline R Invoke(eNativeHash hash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,
		T9 p9, T10 p10, T11 p11, T12 p12, T13 p13)
	{
		// Create new native context
		CNativeContext* cxt = new CNativeContext();

		// Push arguments to call
		cxt->Push(p1);
		cxt->Push(p2);
		cxt->Push(p3);
		cxt->Push(p4);
		cxt->Push(p5);
		cxt->Push(p6);
		cxt->Push(p7);
		cxt->Push(p8);
		cxt->Push(p9);
		cxt->Push(p10);
		cxt->Push(p11);
		cxt->Push(p12);
		cxt->Push(p13);

		// Invoke the call
		InvokeEx((uint32_t)hash, cxt);

		// Get result
		R result = cxt->GetResult<R>();

		// Delete the context and return the result
		delete cxt;
		return result;

		//CNativeContext cxt;
		//cxt.Push(p1);
		//cxt.Push(p2);
		//cxt.Push(p3);
		//cxt.Push(p4);
		//cxt.Push(p5);
		//cxt.Push(p6);
		//cxt.Push(p7);
		//cxt.Push(p8);
		//cxt.Push(p9);
		//cxt.Push(p10);
		//cxt.Push(p11);
		//cxt.Push(p12);
		//cxt.Push(p13);
		//Invoke((uint32_t)hash, &cxt);
		//return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4,
		typename T5, typename T6, typename T7, typename T8, typename T9,
		typename T10, typename T11, typename T12, typename T13, typename T14>
	static inline R Invoke(eNativeHash hash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,
		T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14)
	{
		// Create new native context
		CNativeContext* cxt = new CNativeContext();

		// Push arguments to call
		cxt->Push(p1);
		cxt->Push(p2);
		cxt->Push(p3);
		cxt->Push(p4);
		cxt->Push(p5);
		cxt->Push(p6);
		cxt->Push(p7);
		cxt->Push(p8);
		cxt->Push(p9);
		cxt->Push(p10);
		cxt->Push(p11);
		cxt->Push(p12);
		cxt->Push(p13);
		cxt->Push(p14);

		// Invoke the call
		InvokeEx((uint32_t)hash, cxt);

		// Get result
		R result = cxt->GetResult<R>();

		// Delete the context and return the result
		delete cxt;
		return result;

		//CNativeContext cxt;
		//cxt.Push(p1);
		//cxt.Push(p2);
		//cxt.Push(p3);
		//cxt.Push(p4);
		//cxt.Push(p5);
		//cxt.Push(p6);
		//cxt.Push(p7);
		//cxt.Push(p8);
		//cxt.Push(p9);
		//cxt.Push(p10);
		//cxt.Push(p11);
		//cxt.Push(p12);
		//cxt.Push(p13);
		//cxt.Push(p14);
		//Invoke((uint32_t)hash, &cxt);
		//return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4,
		typename T5, typename T6, typename T7, typename T8, typename T9,
		typename T10, typename T11, typename T12, typename T13, typename T14,
		typename T15>
	static inline R Invoke(eNativeHash hash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,
		T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15)
	{
		// Create new native context
		CNativeContext* cxt = new CNativeContext();

		// Push arguments to call
		cxt->Push(p1);
		cxt->Push(p2);
		cxt->Push(p3);
		cxt->Push(p4);
		cxt->Push(p5);
		cxt->Push(p6);
		cxt->Push(p7);
		cxt->Push(p8);
		cxt->Push(p9);
		cxt->Push(p10);
		cxt->Push(p11);
		cxt->Push(p12);
		cxt->Push(p13);
		cxt->Push(p14);
		cxt->Push(p15);

		// Invoke the call
		InvokeEx((uint32_t)hash, cxt);

		// Get result
		R result = cxt->GetResult<R>();

		// Delete the context and return the result
		delete cxt;
		return result;

		//CNativeContext cxt;
		//cxt.Push(p1);
		//cxt.Push(p2);
		//cxt.Push(p3);
		//cxt.Push(p4);
		//cxt.Push(p5);
		//cxt.Push(p6);
		//cxt.Push(p7);
		//cxt.Push(p8);
		//cxt.Push(p9);
		//cxt.Push(p10);
		//cxt.Push(p11);
		//cxt.Push(p12);
		//cxt.Push(p13);
		//cxt.Push(p14);
		//cxt.Push(p15);
		//Invoke((uint32_t)hash, &cxt);
		//return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4,
		typename T5, typename T6, typename T7, typename T8, typename T9,
		typename T10, typename T11, typename T12, typename T13, typename T14,
		typename T15, typename T16>
	static inline R Invoke(eNativeHash hash, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,
		T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16)
	{
		// Create new native context
		CNativeContext* cxt = new CNativeContext();

		// Push arguments to call
		cxt->Push(p1);
		cxt->Push(p2);
		cxt->Push(p3);
		cxt->Push(p4);
		cxt->Push(p5);
		cxt->Push(p6);
		cxt->Push(p7);
		cxt->Push(p8);
		cxt->Push(p9);
		cxt->Push(p10);
		cxt->Push(p11);
		cxt->Push(p12);
		cxt->Push(p13);
		cxt->Push(p14);
		cxt->Push(p15);
		cxt->Push(p16);

		// Invoke the call
		InvokeEx((uint32_t)hash, cxt);

		// Get result
		R result = cxt->GetResult<R>();

		// Delete the context and return the result
		delete cxt;
		return result;

		//CNativeContext cxt;
		//cxt.Push(p1);
		//cxt.Push(p2);
		//cxt.Push(p3);
		//cxt.Push(p4);
		//cxt.Push(p5);
		//cxt.Push(p6);
		//cxt.Push(p7);
		//cxt.Push(p8);
		//cxt.Push(p9);
		//cxt.Push(p10);
		//cxt.Push(p11);
		//cxt.Push(p12);
		//cxt.Push(p13);
		//cxt.Push(p14);
		//cxt.Push(p15);
		//cxt.Push(p16);
		//Invoke((uint32_t)hash, &cxt);
		//return cxt.GetResult<R>();
	}

};

namespace IVSDKDotNet
{
	namespace Native
	{

		public ref class IVNativeCallContext
		{
		public:
			property UIntPtr Return
			{
			public:
				UIntPtr get()
				{
					NULLPTR_CHECK_WITH_RETURN(NativeCallContext, UIntPtr::Zero);
					return UIntPtr(NativeCallContext->m_pReturn);
				}
				void set(UIntPtr value)
				{
					NULLPTR_CHECK(NativeCallContext);
					NativeCallContext->m_pReturn = value.ToPointer();
				}
			}
			property uint32_t ArgCount
			{
			public:
				uint32_t get()
				{
					NULLPTR_CHECK_WITH_RETURN(NativeCallContext, 0);
					return NativeCallContext->m_nArgCount;
				}
				void set(uint32_t value)
				{
					NULLPTR_CHECK(NativeCallContext);
					NativeCallContext->m_nArgCount = value;
				}
			}
			property UIntPtr Args
			{
			public:
				UIntPtr get()
				{
					NULLPTR_CHECK_WITH_RETURN(NativeCallContext, UIntPtr::Zero);
					return UIntPtr(NativeCallContext->m_pArgs);
				}
				void set(UIntPtr value)
				{
					NULLPTR_CHECK(NativeCallContext);
					NativeCallContext->m_pArgs = value.ToPointer();
				}
			}
			property uint32_t DataCount
			{
			public:
				uint32_t get()
				{
					NULLPTR_CHECK_WITH_RETURN(NativeCallContext, 0);
					return NativeCallContext->m_nDataCount;
				}
				void set(uint32_t value)
				{
					NULLPTR_CHECK(NativeCallContext);
					NativeCallContext->m_nDataCount = value;
				}
			}
			property array<Vector3>^ OriginalData
			{
			public:
				array<Vector3>^ get()
				{
					NULLPTR_CHECK_WITH_RETURN(NativeCallContext, nullptr);

					array<Vector3>^ arr = gcnew array<Vector3>(4);

					for (int i = 0; i < arr->Length; i++)
						arr[i] = CVectorToVector3(*NativeCallContext->m_pOriginalData[i]);

					return arr;
				}
				void set(array<Vector3>^ value)
				{
					NULLPTR_CHECK(NativeCallContext);

					for (int i = 0; i < value->Length; i++)
						NativeCallContext->m_pOriginalData[i] = &Vector3ToCVector(value[i]);
				}
			}
			property array<Quaternion>^ TemporaryData
			{
			public:
				array<Quaternion>^ get()
				{
					NULLPTR_CHECK_WITH_RETURN(NativeCallContext, nullptr);

					array<Quaternion>^ arr = gcnew array<Quaternion>(4);

					for (int i = 0; i < arr->Length; i++)
						arr[i] = CQuaternionToQuaternion(NativeCallContext->m_TemporaryData[i]);

					return arr;
				}
				void set(array<Quaternion>^ value)
				{
					NULLPTR_CHECK(NativeCallContext);

					for (int i = 0; i < value->Length; i++)
						NativeCallContext->m_TemporaryData[i] = QuaternionToCQuaternion(value[i]);
				}
			}

		public:
			void GetArgument(uint32_t idx, [OutAttribute] IntPtr% arg)
			{
				if (!NativeCallContext)
				{
					arg = IntPtr::Zero;
					return;
				}

				arg = IntPtr(NativeCallContext->GetArgument<void*>(idx));
			}

			void GetArgument(uint32_t idx, [OutAttribute] int32_t% arg)
			{
				if (!NativeCallContext)
				{
					arg = 0;
					return;
				}

				arg = NativeCallContext->GetArgument<int32_t>(idx);
			}
			void GetArgument(uint32_t idx, [OutAttribute] uint32_t% arg)
			{
				if (!NativeCallContext)
				{
					arg = 0;
					return;
				}

				arg = NativeCallContext->GetArgument<uint32_t>(idx);
			}
			void GetArgument(uint32_t idx, [OutAttribute] int8_t% arg)
			{
				if (!NativeCallContext)
				{
					arg = 0;
					return;
				}

				arg = NativeCallContext->GetArgument<int8_t>(idx);
			}
			void GetArgument(uint32_t idx, [OutAttribute] uint8_t% arg)
			{
				if (!NativeCallContext)
				{
					arg = 0;
					return;
				}

				arg = NativeCallContext->GetArgument<uint8_t>(idx);
			}
			void GetArgument(uint32_t idx, [OutAttribute] float% arg)
			{
				if (!NativeCallContext)
				{
					arg = 0.0F;
					return;
				}

				arg = NativeCallContext->GetArgument<float>(idx);
			}
			void GetArgument(uint32_t idx, [OutAttribute] bool% arg)
			{
				if (!NativeCallContext)
				{
					arg = false;
					return;
				}

				arg = NativeCallContext->GetArgument<bool>(idx);
			}
			void GetArgument(uint32_t idx, [OutAttribute] String^% arg)
			{
				if (!NativeCallContext)
				{
					arg = String::Empty;
					return;
				}

				arg = gcnew String(NativeCallContext->GetArgument<char*>(idx));
			}

		public:
			bool SetResult(uint32_t idx, IntPtr value)
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCallContext, false);
				return NativeCallContext->SetResult(idx, value.ToPointer());
			}

			bool SetResult(uint32_t idx, int32_t value)
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCallContext, false);
				return NativeCallContext->SetResult(idx, value);
			}
			bool SetResult(uint32_t idx, uint32_t value)
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCallContext, false);
				return NativeCallContext->SetResult(idx, value);
			}
			bool SetResult(uint32_t idx, int8_t value)
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCallContext, false);
				return NativeCallContext->SetResult(idx, value);
			}
			bool SetResult(uint32_t idx, uint8_t value)
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCallContext, false);
				return NativeCallContext->SetResult(idx, value);
			}
			bool SetResult(uint32_t idx, float value)
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCallContext, false);
				return NativeCallContext->SetResult(idx, value);
			}
			bool SetResult(uint32_t idx, bool value)
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCallContext, false);
				return NativeCallContext->SetResult(idx, value);
			}
			bool SetResult(uint32_t idx, String^ value)
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCallContext, false);
				msclr::interop::marshal_context ctx;
				return NativeCallContext->SetResult(idx, (char*)ctx.marshal_as<const char*>(value));
			}

			bool SetResult(uint32_t idx, wchar_t* value)
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCallContext, false);
				NULLPTR_CHECK_WITH_RETURN(value, false);
				return NativeCallContext->SetResult(idx, value);
			}

		public:
			bool IsReturnPointerValid()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCallContext, false);
				return NativeCallContext->m_pReturn != nullptr;
			}
			bool IsArgsPointerValid()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCallContext, false);
				return NativeCallContext->m_pArgs != nullptr;
			}

		public:
			/// <summary>
			/// Creates a new IVNativeCallContext instance from a native pointer.
			/// </summary>
			/// <param name="ptr">The native pointer to the object.</param>
			/// <returns>A new instance of the IVNativeCallContext class.</returns>
			static IVNativeCallContext^ FromUIntPtr(UIntPtr ptr)
			{
				UINTPTR_ZERO_CHECK_WITH_RETURN(ptr, nullptr);
				return gcnew IVNativeCallContext((CNativeCallContext*)ptr.ToPointer());
			}

			/// <summary>
			/// Gets the pointer of this IVNativeCallContext instance.
			/// </summary>
			/// <returns>The pointer of this IVNativeCallContext instance.</returns>
			UIntPtr GetUIntPtr()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeCallContext, UIntPtr::Zero);
				return UIntPtr(NativeCallContext);
			}

		internal:
			IVNativeCallContext(CNativeCallContext* nativePtr)
			{
				NativeCallContext = nativePtr;
			}

		internal:
			CNativeCallContext* NativeCallContext;
		};

		public ref class IVNativeContext : public IVNativeCallContext, public IDisposable
		{
		public:
			property array<uint8_t>^ TempStack
			{
			public:
				array<uint8_t>^ get()
				{
					NULLPTR_CHECK_WITH_RETURN(NativeContext, nullptr);

					array<uint8_t>^ arr = gcnew array<uint8_t>(CNativeContext::MaxNativeParams * CNativeContext::ArgSize);

					for (int i = 0; i < arr->Length; i++)
						arr[i] = NativeContext->m_TempStack[i];

					return arr;
				}
				void set(array<uint8_t>^ value)
				{
					NULLPTR_CHECK(NativeContext);

					for (int i = 0; i < value->Length; i++)
						NativeContext->m_TempStack[i] = value[i];
				}
			}

		public:
			/// <summary>
			/// Pushes an integer to this native context.
			/// </summary>
			/// <param name="value">The value to push.</param>
			/// <returns>
			/// True = The argument got pushed onto this native context.
			/// <para>False = The argument is too big (Only 4 bytes or less allowed).</para>
			/// <para>False = The maximum number of arguments to push is reached (16).</para>
			/// </returns>
			bool Push(int32_t value)
			{
				NULLPTR_CHECK_WITH_RETURN(NativeContext, false);
				return NativeContext->Push(value);
			}
			/// <summary>
			/// Pushes an unsigned integer to this native context.
			/// </summary>
			/// <param name="value">The value to push.</param>
			/// <returns>
			/// True = The argument got pushed onto this native context.
			/// <para>False = The argument is too big (Only 4 bytes or less allowed).</para>
			/// <para>False = The maximum number of arguments to push is reached (16).</para>
			/// </returns>
			bool Push(uint32_t value)
			{
				NULLPTR_CHECK_WITH_RETURN(NativeContext, false);
				return NativeContext->Push(value);
			}

			/// <summary>
			/// Pushes a signed char to this native context.
			/// </summary>
			/// <param name="value">The value to push.</param>
			/// <returns>
			/// True = The argument got pushed onto this native context.
			/// <para>False = The argument is too big (Only 4 bytes or less allowed).</para>
			/// <para>False = The maximum number of arguments to push is reached (16).</para>
			/// </returns>
			bool Push(int8_t value)
			{
				NULLPTR_CHECK_WITH_RETURN(NativeContext, false);
				return NativeContext->Push(value);
			}
			/// <summary>
			/// Pushes an unsigned char to this native context.
			/// </summary>
			/// <param name="value">The value to push.</param>
			/// <returns>
			/// True = The argument got pushed onto this native context.
			/// <para>False = The argument is too big (Only 4 bytes or less allowed).</para>
			/// <para>False = The maximum number of arguments to push is reached (16).</para>
			/// </returns>
			bool Push(uint8_t value)
			{
				NULLPTR_CHECK_WITH_RETURN(NativeContext, false);
				return NativeContext->Push(value);
			}

			/// <summary>
			/// Pushes a float to this native context.
			/// </summary>
			/// <param name="value">The value to push.</param>
			/// <returns>
			/// True = The argument got pushed onto this native context.
			/// <para>False = The argument is too big (Only 4 bytes or less allowed).</para>
			/// <para>False = The maximum number of arguments to push is reached (16).</para>
			/// </returns>
			bool Push(float value)
			{
				NULLPTR_CHECK_WITH_RETURN(NativeContext, false);
				return NativeContext->Push(value);
			}

			/// <summary>
			/// Pushes a bool to this native context.
			/// </summary>
			/// <param name="value">The value to push.</param>
			/// <returns>
			/// True = The argument got pushed onto this native context.
			/// <para>False = The argument is too big (Only 4 bytes or less allowed).</para>
			/// <para>False = The maximum number of arguments to push is reached (16).</para>
			/// </returns>
			bool Push(bool value)
			{
				NULLPTR_CHECK_WITH_RETURN(NativeContext, false);
				return NativeContext->Push(value);
			}
			/// <summary>
			/// Pushes a string to this native context.
			/// </summary>
			/// <param name="value">The value to push.</param>
			/// <returns>
			/// True = The argument got pushed onto this native context.
			/// <para>False = The argument is too big (Only 4 bytes or less allowed).</para>
			/// <para>False = The maximum number of arguments to push is reached (16).</para>
			/// </returns>
			bool Push(String^ value)
			{
				NULLPTR_CHECK_WITH_RETURN(NativeContext, false);
				msclr::interop::marshal_context ctx;
				return NativeContext->Push((char*)ctx.marshal_as<const char*>(value));
			}

			/// <summary>
			/// Pushes a Quaternion to this native context.
			/// </summary>
			/// <param name="value">The value to push.</param>
			/// <returns>
			/// True = The argument got pushed onto this native context.
			/// <para>False = The argument is too big (Only 4 bytes or less allowed).</para>
			/// <para>False = The maximum number of arguments to push is reached (16).</para>
			/// </returns>
			bool Push(Quaternion value)
			{
				NULLPTR_CHECK_WITH_RETURN(NativeContext, false);
				bool result =	NativeContext->Push(value.X);
				bool result1 =	NativeContext->Push(value.Y);
				bool result2 =	NativeContext->Push(value.Z);
				bool result3 =	NativeContext->Push(value.W);
				return result && result1 && result2 && result3;
			}
			/// <summary>
			/// Pushes a Vector3 to this native context.
			/// </summary>
			/// <param name="value">The value to push.</param>
			/// <returns>
			/// True = The argument got pushed onto this native context.
			/// <para>False = The argument is too big (Only 4 bytes or less allowed).</para>
			/// <para>False = The maximum number of arguments to push is reached (16).</para>
			/// </returns>
			bool Push(Vector3 value)
			{
				NULLPTR_CHECK_WITH_RETURN(NativeContext, false);
				bool result =	NativeContext->Push(value.X);
				bool result1 =	NativeContext->Push(value.Y);
				bool result2 =	NativeContext->Push(value.Z);
				return result && result1 && result2;
			}
			/// <summary>
			/// Pushes a Vector2 to this native context.
			/// </summary>
			/// <param name="value">The value to push.</param>
			/// <returns>
			/// True = The argument got pushed onto this native context.
			/// <para>False = The argument is too big (Only 4 bytes or less allowed).</para>
			/// <para>False = The maximum number of arguments to push is reached (16).</para>
			/// </returns>
			bool Push(Vector2 value)
			{
				NULLPTR_CHECK_WITH_RETURN(NativeContext, false);
				bool result =	NativeContext->Push(value.X);
				bool result1 =	NativeContext->Push(value.Y);
				return result && result1;
			}

			/// <summary>
			/// Pushes an OUT argument to this native context. WARNING: The returned IntPtr needs to be freed using the 'Marshal.FreeHGlobal' function
			/// </summary>
			/// <param name="allocationSize">The size to allocate for the type that is returned. Example: If you want this native call to return an integer, you need to pass in 4 (Integer = 4 Bytes).</param>
			/// <param name="value">The IntPtr which stores the value that is returned from the native call. WARNING: The returned IntPtr needs to be freed using the 'Marshal.FreeHGlobal' function!</param>
			/// <returns>
			/// True = The argument got pushed onto this native context.
			/// <para>False = The argument is too big (Only 4 bytes or less allowed).</para>
			/// <para>False = The maximum number of arguments to push is reached (16).</para>
			/// </returns>
			bool PushOut(int allocationSize, [OutAttribute] IntPtr% value)
			{
				if (!NativeContext)
				{
					value = IntPtr::Zero;
					return false;
				}

				IntPtr ptr = Marshal::AllocHGlobal(allocationSize);
				bool result = NativeContext->Push(ptr.ToPointer());
				value = ptr;
				return result;
			}

		public:
			/// <summary>
			/// Gets the result from this native context.
			/// </summary>
			/// <returns>An IntPtr which stores the result of this native context.</returns>
			void GetResult([OutAttribute] IntPtr% result)
			{
				if (!NativeContext)
				{
					result = IntPtr::Zero;
					return;
				}

				result = IntPtr(NativeContext->GetResult<void*>());
			}

			void GetResult([OutAttribute] int32_t% result)
			{
				if (!NativeContext)
				{
					result = 0;
					return;
				}

				result = NativeContext->GetResult<int32_t>();
			}
			void GetResult([OutAttribute] uint32_t% result)
			{
				if (!NativeContext)
				{
					result = 0;
					return;
				}

				result = NativeContext->GetResult<uint32_t>();
			}
			void GetResult([OutAttribute] int8_t% result)
			{
				if (!NativeContext)
				{
					result = 0;
					return;
				}

				result = NativeContext->GetResult<int8_t>();
			}
			void GetResult([OutAttribute] uint8_t% result)
			{
				if (!NativeContext)
				{
					result = 0;
					return;
				}

				result = NativeContext->GetResult<uint8_t>();
			}
			void GetResult([OutAttribute] float% result)
			{
				if (!NativeContext)
				{
					result = 0.0F;
					return;
				}

				result = NativeContext->GetResult<float>();
			}
			void GetResult([OutAttribute] bool% result)
			{
				if (!NativeContext)
				{
					result = false;
					return;
				}

				result = NativeContext->GetResult<bool>();
			}
			void GetResult([OutAttribute] String^% result)
			{
				if (!NativeContext)
				{
					result = String::Empty;
					return;
				}

				result = gcnew String(NativeContext->GetResult<const char*>());
			}

		public:
			/// <summary>
			/// Allocates and returns a new native context which HAS to be deleted once you're done using it.
			/// </summary>
			/// <returns>A new instance of the IVNativeContext class.</returns>
			static IVNativeContext^ AllocateNew()
			{
				return gcnew IVNativeContext(new CNativeContext());
			}

			/// <summary>
			/// Creates a new IVNativeContext instance from a native pointer.
			/// </summary>
			/// <param name="ptr">The native pointer to the object.</param>
			/// <returns>A new instance of the IVNativeContext class.</returns>
			static IVNativeContext^ FromUIntPtr(UIntPtr ptr)
			{
				UINTPTR_ZERO_CHECK_WITH_RETURN(ptr, nullptr);
				return gcnew IVNativeContext((CNativeContext*)ptr.ToPointer());
			}

			/// <summary>
			/// Deletes the allocated native context and frees its memory.
			/// </summary>
			void Delete()
			{
				NULLPTR_CHECK(NativeContext);

				delete NativeContext;
				NativeContext = nullptr;
			}

			/// <summary>
			/// Gets the pointer of this IVNativeContext instance.
			/// </summary>
			/// <returns>The pointer of this IVNativeContext instance.</returns>
			UIntPtr GetUIntPtr()
			{
				NULLPTR_CHECK_WITH_RETURN(NativeContext, UIntPtr::Zero);
				return UIntPtr(NativeContext);
			}

		internal:
			IVNativeContext(CNativeContext* nativePtr) : IVNativeCallContext(nativePtr)
			{
				NativeContext = nativePtr;
			}
			~IVNativeContext()
			{
				if (m_bIsDisposed)
					return;

				// Call finalizer
				this->!IVNativeContext();

				m_bIsDisposed = true;
			}
			!IVNativeContext()
			{
				// Free unmanaged data
				Delete();
			}

		internal:
			CNativeContext* NativeContext;
			bool m_bIsDisposed;
		};

		public ref class IVNativeInvoke
		{
		public:
			static bool Invoke(uint32_t uiHash, IVNativeContext^ pNativeContext)
			{
				if (uiHash == 0x0)
					return false;

				NULLPTR_CHECK_WITH_RETURN(pNativeContext, false);
				return NativeInvoke::Invoke(uiHash, pNativeContext->NativeContext);
			}
			static bool Invoke(uint32_t uiHash, UIntPtr pNativeContext)
			{
				if (uiHash == 0x0)
					return false;

				UINTPTR_ZERO_CHECK_WITH_RETURN(pNativeContext, false);
				return NativeInvoke::Invoke(uiHash, (CNativeCallContext*)pNativeContext.ToPointer());
			}

			static bool Invoke(eNativeHash uiHash, IVNativeContext^ pNativeContext)
			{
				return Invoke((uint32_t)uiHash, pNativeContext);
			}
			static bool Invoke(eNativeHash uiHash, UIntPtr pNativeContext)
			{
				return Invoke((uint32_t)uiHash, pNativeContext);
			}
		};

	}
}