#pragma once

namespace IVSDKDotNet {

	public ref class KeyWatchDog
	{
	public:
		event KeyEventHandler^ KeyDown;
		event KeyEventHandler^ KeyUp;

		KeyWatchDog();
		~KeyWatchDog();

		//bool IsKeyPressed(Keys key)
		//{
		//	int num = (int)key;
		//	if ((num < 0) || (num > 255)) return false;
		//	return keystate[num];
		//}

		void ProcessCheck();

		property bool Shift {
			bool get() { return bShift; }
		}
		property bool Ctrl {
			bool get() { return bCtrl; }
		}
		property bool Alt {
			bool get() { return bAlt; }
		}
		property Keys Modifier {
			Keys get() { return pModifier; }
		}

	private:
		array<bool>^ keystate;
		BYTE* ckeystate;
		bool bShift;
		bool bCtrl;
		bool bAlt;
		Keys pModifier;

		bool cIsKeyPressed(Keys key)
		{
			int num = (int)key;
			if ((num < 0) || (num > 255)) return false;
			return ((ckeystate[num] & 0x80) != 0);
		}

		void CheckKeyAsync(Keys Key);

		void OnKeyDown(KeyEventArgs^ e);
		void OnKeyUp(KeyEventArgs^ e);

	};

}