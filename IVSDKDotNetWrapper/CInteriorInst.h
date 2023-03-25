#pragma once

class Native_CInteriorInst : public Native_CBuilding
{
public:
	uint8_t pad[0xF0];										// 070-160
};
VALIDATE_SIZE(Native_CInteriorInst, 0x160);

namespace IVSDKDotNet {

	public ref class CInteriorInst : CBuilding
	{
	public:
		CInteriorInst(Native_CInteriorInst* nativePtr) : CBuilding(nativePtr)
		{
			m_cNativeInteriorInst = nativePtr;
		}

		property Native_CInteriorInst* InteriorInstPointer {
			public:
				Native_CInteriorInst*	get()								{ return m_cNativeInteriorInst; }
				void					set(Native_CInteriorInst* value)	{ m_cNativeInteriorInst = value; }
		}

	private:
		Native_CInteriorInst* m_cNativeInteriorInst;
	};

}