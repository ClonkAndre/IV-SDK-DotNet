#include "pch.h"
#include "EventArgs.h"

namespace IVSDKDotNet {

	IVKeyEventArgs::IVKeyEventArgs(int keyValue, Keys keyCode, Keys keyData, Keys modifieres, bool control, bool alt, bool shift)
	{
		KeyValue = keyValue;
		KeyCode = keyCode;
		KeyData = keyData;
		Modifieres = modifieres;
		Control = control;
		Alt = alt;
		Shift = shift;
	}

}
