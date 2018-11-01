#pragma once
#include "AllHead.h"

namespace BasicSystem {

	class InputFlag {
		bool getKeyDown = false;
		bool getKeyUp = false;
		bool getKey = false;
	public:
		void SetFlag(bool _flag) {
			if (getKey == false && _flag==false) {
				getKeyUp = false;
				return;
			}
			if (getKey == false && _flag == true) {
				getKeyDown = true;
				getKey = true;
				return;
			}
			if (getKey == true && _flag == false) {
				getKeyUp = true;
				getKey = false;
				return;
			}
			if (getKey == true && _flag == true) {
				getKeyDown = false;
				return;
			}

		}
		bool GetKeyDown() { return getKeyDown; }
		bool GetKeyUp() { return getKeyUp; }
		bool GetKey() { return getKey; }
	};

	struct InputData {
		InputFlag P1_Right;
		InputFlag P1_Left;
		InputFlag P1_Up;
		InputFlag P1_Down;
		InputFlag P1_J;
		InputFlag P1_K;
	};

	class InputManager {
		//キーボードの入力データ格納用
		char keyBuffer[256];
		//ウィンドウハンドル
		HWND hWnd;

		//成功判定
		HRESULT hr;
		//DirectInput8デバイスアドレス
		LPDIRECTINPUT8 lpDirect8;
		//列挙したゲームパッドデバイスを格納する
		std::vector<DIDEVICEINSTANCE>gamePads;
		//キーボードデバイス
		LPDIRECTINPUTDEVICE8 lpdiKeyboard;
		void ResetInput();
	public:
		
		std::shared_ptr<InputData> inputData;

		bool keyDownESC=false;

		InputManager(HINSTANCE _hINst, HWND _hWnd);
		~InputManager();

		void InputUpdate();
	};

}