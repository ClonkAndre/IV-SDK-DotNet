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
		CObject(Native_CObject* nativePtr);

		static CObject^ FromPointer(UIntPtr ptr);
		UIntPtr GetUIntPtr();

		/// <summary>
		/// Set by SET_OBJECT_SCALE but unused.
		/// </summary>
		property float Scale {
			public:
				float get()				{ return m_cNativeObject->m_fScale; }
				void set(float value)	{ m_cNativeObject->m_fScale = value; }
		}

		property Native_CObject* ObjectPointer {
			public:
				Native_CObject*		get()						{ return m_cNativeObject; }
				void				set(Native_CObject* value)	{ m_cNativeObject = value; }
		}

	private:
		Native_CObject* m_cNativeObject;
	};

}