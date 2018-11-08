#pragma once
#include "AllHead.h"

//アクションマップの定義
//アクション定義
enum eGameActions
{
	P1_A_LATERAL,
	P1_A_VIRTICAL,
	P1_B_UP,
	P1_B_DOWN,
	P1_B_RIGHT,
	P1_B_LEFT,
	P1_B1,
	P1_B2,
	P1_START
};

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
		//アクションマップの定義
		DIACTION p1Action[NUMBER_OF_ACTIONS] =
		{
			{P1_A_LATERAL,	DIAXIS_TPS_MOVE,	0,	L"LATERAL",	},
			{P1_A_VIRTICAL,	DIAXIS_TPS_TURN,	0,	L"VIRTICAL",},
			{P1_B1,			DIBUTTON_TPS_JUMP,	0,	L"B1",		},
			{P1_B2,			DIBUTTON_TPS_RUN,	0,	L"B2",		},
			{P1_START,		DIBUTTON_TPS_MENU,	0,	L"START"}
		};

		DIACTION p2Action[NUMBER_OF_ACTIONS] =
		{
			{P1_A_LATERAL,	DIAXIS_TPS_MOVE,	0,	L"LATERAL",	},
			{P1_A_VIRTICAL,	DIAXIS_TPS_TURN,	0,	L"VIRTICAL",},
			{P1_B1,			DIBUTTON_TPS_JUMP,	0,	L"B1",		},
			{P1_B2,			DIBUTTON_TPS_RUN,	0,	L"B2",		},
			{P1_START,		DIBUTTON_TPS_MENU,	0,	L"START"}
		};
		//アクションフォーマット
		DIACTIONFORMAT p1ActionFormat;

		//キーボードの入力データ格納用
		char keyBuffer[256];
		//ウィンドウハンドル
		HWND hWnd;

		//成功判定
		HRESULT hr;
		//DirectInput8デバイスアドレス
		LPDIRECTINPUT8 lpDirect8;
		//列挙したゲームパッドデバイスを格納する
		std::vector<LPCDIDEVICEINSTANCE> gamePads;
		//キーボードデバイス
		LPDIRECTINPUTDEVICE8 lpdiKeyboard;
		//ゲームパッド
		LPDIRECTINPUTDEVICE8W GamePad1;
		LPDIRECTINPUTDEVICE8W GamePad2;
		void ResetInput();
	public:
		int gamePadDeviceNum;

		std::shared_ptr<InputData> inputData;

		bool keyDownESC=false;

		InputManager(HINSTANCE _hINst, HWND _hWnd);
		~InputManager();

		void InputUpdate();
	};

}