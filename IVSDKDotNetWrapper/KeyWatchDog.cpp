#include "pch.h"
#include "KeyWatchDog.h"

namespace IVSDKDotNet {

	KeyWatchDog::KeyWatchDog()
	{
		keystate = gcnew array<bool>(256);
		bShift = false;
		bCtrl = false;
		bAlt = false;
		pModifier = Keys::None;
		ckeystate = (BYTE*)malloc(256);
		if (ckeystate == NULL) throw gcnew System::OutOfMemoryException();

		keystate[0] = false;
		keystate[3] = false;
	}
	KeyWatchDog::~KeyWatchDog()
	{
		if (ckeystate != NULL) free(ckeystate);
	}

	void KeyWatchDog::CheckKeyAsync(Keys key)
	{
		bool pressed = Helper::IsKeyPressedAsync(key);
		if (pressed == keystate[(int)key]) return;
		keystate[(int)key] = pressed;
		if (pressed)
			OnKeyDown(gcnew KeyEventArgs(key | Modifier));
		else
			OnKeyUp(gcnew KeyEventArgs(key | Modifier));
	}

	void KeyWatchDog::ProcessCheck()
	{
		bool stat;
		Keys key;

		bShift =	cIsKeyPressed(Keys::ShiftKey)	|| cIsKeyPressed(Keys::LShiftKey)	|| cIsKeyPressed(Keys::RShiftKey);
		bCtrl =		cIsKeyPressed(Keys::ControlKey) || cIsKeyPressed(Keys::LControlKey) || cIsKeyPressed(Keys::RControlKey);
		bAlt =		cIsKeyPressed(Keys::Menu)		|| cIsKeyPressed(Keys::LMenu)		|| cIsKeyPressed(Keys::RMenu);
		pModifier = (bShift ? Keys::Shift : Keys::None) | (bCtrl ? Keys::Control : Keys::None) | (bAlt ? Keys::Alt : Keys::None);

		if (GetKeyboardState(ckeystate)) {
			for (int i = 7; i < 255; i++) { // Yes, 255 is NOT valid! // 0 undefined, 3 VK_CANCEL can be ignored, 1 2 4 5 6 mouse keys
				stat = ((ckeystate[i] & 0x80) != 0);
				if (stat != keystate[i]) {
					key = Helper::RemoveRedundantKeyModifiers(Keys(i) | Modifier);
					if (stat)
						OnKeyDown(gcnew KeyEventArgs(key));
					else
						OnKeyUp(gcnew KeyEventArgs(key));
					keystate[i] = stat;
				}
			}
		}

		// Check for mouse buttons
		CheckKeyAsync(Keys::LButton);
		CheckKeyAsync(Keys::RButton);
		CheckKeyAsync(Keys::MButton);
		CheckKeyAsync(Keys::XButton1);
		CheckKeyAsync(Keys::XButton2);
	}

	void KeyWatchDog::OnKeyDown(KeyEventArgs^ e)
	{
		KeyDown(this, e);
	}
	void KeyWatchDog::OnKeyUp(KeyEventArgs^ e)
	{
		KeyUp(this, e);
	}

}