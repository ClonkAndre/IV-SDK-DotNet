#pragma once

using namespace System;
using namespace System::Windows::Forms;

namespace IVSDKDotNet {

	public ref class IVKeyEventArgs : EventArgs
	{
	public:
		IVKeyEventArgs(int keyValue, Keys keyCode, Keys keyData, Keys modifieres, bool control, bool alt, bool shift);


		property int KeyValue {
			public:		int get()				{ return m_iKeyValue; }
			private:	void set(int value)		{ m_iKeyValue = value; }
		}

		property Keys KeyCode {
			public:		Keys get()				{ return m_eKeyCode; }
			private:	void set(Keys value)	{ m_eKeyCode = value; }
		}
		property Keys KeyData {
			public:		Keys get()				{ return m_eKeyData; }
			private:	void set(Keys value)	{ m_eKeyData = value; }
		}
		property Keys Modifieres {
			public:		Keys get()				{ return m_eModifieres; }
			private:	void set(Keys value)	{ m_eModifieres = value; }
		}

		property bool Control {
			public:		bool get()				{ return m_bControl; }
			private:	void set(bool value)	{ m_bControl = value; }
		}
		property bool Alt {
			public:		bool get()				{ return m_bAlt; }
			private:	void set(bool value)	{ m_bAlt = value; }
		}
		property bool Shift {
			public:		bool get()				{ return m_bShift; }
			private:	void set(bool value)	{ m_bShift = value; }
		}

	private:
        int m_iKeyValue;
        Keys m_eKeyCode;
        Keys m_eKeyData;
		Keys m_eModifieres;
		bool m_bControl;
		bool m_bAlt;
		bool m_bShift;

	};
	public delegate void IVKeyEventHandler(System::Object^ sender, IVKeyEventArgs^ args);

}