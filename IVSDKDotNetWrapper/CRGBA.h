#pragma once

struct Native_CRGBA
{
	uint8_t b;
	uint8_t g;
	uint8_t r;
	uint8_t a;
};

struct Native_CRGBFloat
{
	float red;
	float green;
	float blue;
};

namespace IVSDKDotNet {

	public ref struct CRGBA
	{
	public:
		CRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

		property uint8_t R {
			public:		uint8_t get()			{ return m_r; }
			private:	void set(uint8_t value) { m_r = value; }
		}

		property uint8_t G {
			public:		uint8_t get()			{ return m_g; }
			private:	void set(uint8_t value) { m_g = value; }
		}

		property uint8_t B {
			public:		uint8_t get()			{ return m_b; }
			private:	void set(uint8_t value) { m_b = value; }
		}

		property uint8_t A {
			public:		uint8_t get()			{ return m_a; }
			private:	void set(uint8_t value) { m_a = value; }
		}

		virtual String^ ToString() override
		{
			return String::Format("R: {0}, G: {1}, B: {2}, A: {3}", R.ToString(), G.ToString(), B.ToString(), A.ToString());
		}

	private:
		uint8_t m_b;
		uint8_t m_g;
		uint8_t m_r;
		uint8_t m_a;
	};

	public ref struct CRGBFloat
	{
	public:
		CRGBFloat(float r, float g, float b);

		property uint8_t R {
			public:		uint8_t get()			{ return m_fR; }
			private:	void set(uint8_t value) { m_fR = value; }
		}

		property uint8_t G {
			public:		uint8_t get()			{ return m_fG; }
			private:	void set(uint8_t value) { m_fG = value; }
		}

		property uint8_t B {
			public:		uint8_t get()			{ return m_fB; }
			private:	void set(uint8_t value) { m_fB = value; }
		}

		virtual String^ ToString() override
		{
			return String::Format("R: {0}, G: {1}, B: {2}", R.ToString(), G.ToString(), B.ToString());
		}

	private:
		float m_fR;
		float m_fG;
		float m_fB;
	};

}