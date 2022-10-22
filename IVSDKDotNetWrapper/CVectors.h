#pragma once

class Native_CVector
{
public:
	float x, y, z;
};
class Native_CVector2D
{
public:
	float x, y;
};

class Native_CVector_pad : public Native_CVector
{
public:
	unsigned int flags; // ???
};

namespace IVSDKDotNet {

	public value struct CVector
	{
	public:
		CVector(float x, float y, float z);

		property float X {
			public:		float get()				{ return m_fX; }
			private:	void set(float value)	{ m_fX = value; }
		}

		property float Y {
			public:		float get()				{ return m_fY; }
			private:	void set(float value)	{ m_fY = value; }
		}

		property float Z {
			public:		float get()				{ return m_fZ; }
			private:	void set(float value)	{ m_fZ = value; }
		}

	private:
		float m_fX, m_fY, m_fZ;
	};

	public value struct CVector2D
	{
	public:
		CVector2D(float x, float y);

		property float X {
			public:		float get()				{ return m_fX; }
			private:	void set(float value)	{ m_fX = value; }
		}

		property float Y {
			public:		float get()				{ return m_fY; }
			private:	void set(float value)	{ m_fY = value; }
		}

	private:
		float m_fX, m_fY;
	};

	public value struct CVector_pad
	{
	public:
		CVector_pad(unsigned int flags, float x, float y, float z);

		property unsigned int Flags {
			public:		unsigned int get()				{ return m_iFlags; }
			private:	void set(unsigned int value)	{ m_iFlags = value; }
		}

		property float X {
			public:		float get()				{ return m_fX; }
			private:	void set(float value)	{ m_fX = value; }
		}

		property float Y {
			public:		float get()				{ return m_fY; }
			private:	void set(float value)	{ m_fY = value; }
		}

		property float Z {
			public:		float get()				{ return m_fZ; }
			private:	void set(float value)	{ m_fZ = value; }
		}

	private:
		unsigned int m_iFlags; // ???
		float m_fX, m_fY, m_fZ;
	};

}