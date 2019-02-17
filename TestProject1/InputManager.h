#pragma once
#include "AllHead.h"


/*
三人称型(DIVIRITUAL_FIGHTING_THIRDPERSON)のアクションマッピング定数を想定
優先順位1のコントロール:
DIAXIS_TPS_MOVE
DIAXIS_TPS_TURN
DIBUTTON_TPS_ACTION
DIBUTTON_TPS_JUMP
DIBUTTON_TPS_MENU
DIBUTTON_TPS_RUN
DIBUTTON_TPS_SELECT
DIBUTTON_TPS_USE
*/

#define NUMBER_OF_ACTIONS 5

namespace BasicSystem {

	class InputFlag {
		bool getKeyDown = false;
		bool getKeyUp = false;
		bool getKey = false;
	public:
		void SetFlag(bool _flag) {
			if (getKey == false && _flag==false) {
				getKeyUp = false;
				getKeyDown = false;
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
		InputFlag P1_I;

		InputFlag P2_Right;
		InputFlag P2_Left;
		InputFlag P2_Up;
		InputFlag P2_Down;
		InputFlag P2_J;
		InputFlag P2_K;
		InputFlag P2_I;

		InputFlag F3;
	};

	extern LPDIRECTINPUT8 lpDirect8;

	class InputManager {
		//キーボードの入力データ格納用
		char keyBuffer[256];
		//ウィンドウハンドル
		HWND hWnd;
		
		//成功判定
		HRESULT hr;
		//DirectInput8デバイスアドレス
		//LPDIRECTINPUT8 lpDirect82;
		//列挙したゲームパッドデバイスを格納する
		std::vector<LPCDIDEVICEINSTANCE> gamePads;
		//キーボードデバイス
		LPDIRECTINPUTDEVICE8 lpdiKeyboard;
		void ResetInput();
		DIDEVCAPS GP1Devcaps;
		DIDEVCAPS GP2Devcaps;
		DIJOYSTATE2 GP1DevState;
		DIJOYSTATE2 GP2DevState;
		double GP1CentVal;
		double GP2CentVal;
		double GP1RangeVal=5000;
		double GP2RangeVal=5000;
	public:
		int gamePadDeviceNum;

		std::shared_ptr<InputData> inputData;

		bool keyDownESC=false;

		InputManager(HINSTANCE _hINst, HWND _hWnd);
		~InputManager();

		void InputUpdate();
	};

}