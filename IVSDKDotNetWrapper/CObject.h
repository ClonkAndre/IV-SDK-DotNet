#pragma once

//class CPhysical;

class Native_CObject : public Native_CPhysical
{
public:
	uint8_t pad[0x40];													// 210-250
	float m_fScale;														// 250-254 set by SET_OBJECT_SCALE but unused
	uint8_t pad2[0xCC];													// 254-320
};
VALIDATE_SIZE(Native_CObject, 0x320);
VALIDATE_OFFSET(Native_CObject, m_fScale, 0x250);

namespace IVSDKDotNet {

	public ref class CObject : CPhysical
	{
	public:
		CObject(int handle, Native_CObject* native);

		/// <summary>
		/// Gets the handle of this object.
		/// </summary>
		property int Handle {
			public:
				int get()				{ return m_iHandle; }
				void set(int value)		{ m_iHandle = value; }
		}

		/// <summary>
		/// Set by SET_OBJECT_SCALE but unused.
		/// </summary>
		property float Scale {
			public:
				float get()				{ return m_cNativeObject->m_fScale; }
				void set(float value)	{ m_cNativeObject->m_fScale = value; }
		}

	private:
		int m_iHandle;
		Native_CObject* m_cNativeObject;
	};

}