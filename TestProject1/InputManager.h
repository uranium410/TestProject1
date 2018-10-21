#pragma once
#include "AllHead.h"

namespace BasicSystem {

	class InputManager {
		LPDIRECTINPUT8 lpDI = NULL;	//DirectInput�I�u�W�F�N�g
		HRESULT hr;

		LPDIRECTINPUTDEVICE8 lpKeyboard = NULL;
		LPDIRECTINPUTDEVICE8 lpGamepad1 = NULL;
		LPDIRECTINPUTDEVICE8 lpGamepad2 = NULL;
	public:
		InputManager(HINSTANCE _hINst, HWND _hWnd);
		~InputManager();

		void InputUpdate();
	};

}