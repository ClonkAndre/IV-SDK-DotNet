#pragma once

class Native_CQuaternion
{
public:
	float x, y, z, w;
};

namespace IVSDKDotNet {

	public value struct CQuaternion
	{
	public:
		CQuaternion(float x, float y, float z, float w);

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

		property float W {
			public:		float get()				{ return m_fW; }
			private:	void set(float value)	{ m_fW = value; }
		}

	private:
		float m_fX, m_fY, m_fZ, m_fW;
	};

}