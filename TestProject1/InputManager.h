#pragma once
#include "AllHead.h"

namespace BasicSystem {

	class InputManager {
		//キーボードの入力データ格納用
		char keyBuffer[256];

		//成功判定
		HRESULT hr;
		//DirectInput8デバイスアドレス
		LPDIRECTINPUT8 lpDirect8;
		//列挙したゲームパッドデバイスを格納する
		std::vector<DIDEVICEINSTANCE>gamePads;
		//キーボードデバイス
		LPDIRECTINPUTDEVICE8 lpdiKeyboard;
	public:
		bool keyDownESC=false;

		InputManager(HINSTANCE _hINst, HWND _hWnd);
		~InputManager();

		void InputUpdate();
	};

}