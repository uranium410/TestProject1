#include "stdafx.h"
#include "AllHead.h"

//キーボード入力判定用マクロ
#define KEYDOWN(name, key) (name[key] & 0x80)


namespace BasicSystem {

	LPDIRECTINPUT8 lpDirect8;
	LPDIRECTINPUTDEVICE8W gamePad1=NULL;
	LPDIRECTINPUTDEVICE8W gamePad2=NULL;

	//ジョイスティックデバイス列挙用コールバック関数
	BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE*pdidInstance, VOID* pContext)
	{

		HRESULT hr;
		std::vector<LPCDIDEVICEINSTANCE> *gamePads = (std::vector<LPCDIDEVICEINSTANCE>*)pContext;
		gamePads->push_back(pdidInstance);
		if(gamePads->size()==1)hr = lpDirect8->CreateDevice(pdidInstance->guidInstance, &gamePad1, NULL);
		if (gamePads->size() == 2)hr = lpDirect8->CreateDevice(pdidInstance->guidInstance, &gamePad2, NULL);
		return true;
	}

	InputManager::InputManager(HINSTANCE _hInst, HWND _hWnd) {
		
	
		inputData = std::make_shared<InputData>();
		//ウィンドウハンドル取得
		hWnd = _hWnd;

		//DirectInput8作成
		hr = DirectInput8Create(_hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&lpDirect8, NULL);
		if (FAILED(hr)) {
			
			return;
		}

		
		//キーボードデバイス取得
		hr = lpDirect8->CreateDevice(GUID_SysKeyboard, &lpdiKeyboard, NULL);
		//データ形式の設定
		hr = lpdiKeyboard->SetDataFormat(&c_dfDIKeyboard);
		//動作の設定
		hr = lpdiKeyboard->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		//アクセス権の取得
		if (lpdiKeyboard)lpdiKeyboard->Acquire();

		//ゲームパッドデバイス取得//
		//ゲームパッドデバイス列挙
		hr = lpDirect8->EnumDevices(DI8DEVCLASS_GAMECTRL, //全てのデバイス列挙
			EnumJoysticksCallback,
			&gamePads,
			DIEDFL_ATTACHEDONLY);

		gamePadDeviceNum = gamePads.size();

		if (gamePadDeviceNum > 0) {	
			gamePad1->SetDataFormat(&c_dfDIJoystick2);
			gamePad1->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
			GP1Devcaps.dwSize = sizeof(DIDEVCAPS);
			gamePad1->GetCapabilities(&GP1Devcaps);
			gamePad1->Acquire();

			hr = gamePad1->Poll();
			hr = gamePad1->GetDeviceState(sizeof(DIJOYSTATE2), &GP1DevState);
			GP1CentVal = GP1DevState.lY;
		}

		if (gamePadDeviceNum > 1) {
			gamePad2->SetDataFormat(&c_dfDIJoystick2);
			gamePad2->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
			GP2Devcaps.dwSize = sizeof(DIDEVCAPS);
			gamePad2->GetCapabilities(&GP2Devcaps);
			gamePad2->Acquire();

			hr = gamePad2->Poll();
			hr = gamePad2->GetDeviceState(sizeof(DIJOYSTATE2), &GP2DevState);
			GP2CentVal = GP2DevState.lY;

		}
	}

	InputManager::~InputManager() {
		if (gamePad1 != NULL) {
			gamePad1->Unacquire();
			gamePad1->Release();
		}
		if (gamePad2 != NULL) {
			gamePad2->Unacquire();
			gamePad2->Release();
		}
		//キーボードデバイス破棄
		lpdiKeyboard->Unacquire();
		lpdiKeyboard->Release();
		//DirectInput破棄
		lpDirect8->Release();
	}

	void InputManager::InputUpdate() {
		hr = lpdiKeyboard->GetDeviceState(sizeof(keyBuffer),(LPVOID)&keyBuffer);
		if (hr != DI_OK)ResetInput();

		if (KEYDOWN(keyBuffer, DIK_ESCAPE))keyDownESC = true;
		else keyDownESC = false;

		bool P1UP=false;
		bool P1DOWN=false;
		bool P1RIGHT=false;
		bool P1LEFT=false;
		bool P1B1=false;
		bool P1B2=false;
		bool P1B3 = false;
		bool P2UP=false;
		bool P2DOWN=false;
		bool P2RIGHT=false;
		bool P2LEFT=false;
		bool P2B1=false;
		bool P2B2=false;
		bool P2B3 = false;

		P1UP = KEYDOWN(keyBuffer, DIK_W);
		P1DOWN = KEYDOWN(keyBuffer, DIK_S);
		P1RIGHT = KEYDOWN(keyBuffer, DIK_D);
		P1LEFT = KEYDOWN(keyBuffer, DIK_A);
		P1B1 = KEYDOWN(keyBuffer, DIK_J);
		P1B2 = KEYDOWN(keyBuffer, DIK_K);
		P1B3 = KEYDOWN(keyBuffer, DIK_I);
				
		//ゲームパッド
		if (gamePadDeviceNum > 0) {
			hr = gamePad1->Poll();
			if (FAILED(hr))
			{
				hr = gamePad1->Acquire();
				return;
			}
			hr = gamePad1->GetDeviceState(sizeof(DIJOYSTATE2), &GP1DevState);
		}
		if (gamePadDeviceNum > 1) {
			hr = gamePad2->Poll();
			if (FAILED(hr))
			{
				hr = gamePad2->Acquire();
				return;
			}
			hr = gamePad2->GetDeviceState(sizeof(DIJOYSTATE2), &GP2DevState);
		}

		if (gamePadDeviceNum > 1) {
			P1B1 = (bool)GP1DevState.rgbButtons[0] | P1B1;
			P1B2 = (bool)GP1DevState.rgbButtons[1] | P1B2;
			P1B3 = (bool)GP1DevState.rgbButtons[2] | P1B3;
			P1UP = (bool)(GP1DevState.lY < GP1CentVal - GP1RangeVal) | P1UP;
			P1DOWN = (bool)(GP1DevState.lY > GP1CentVal + GP1RangeVal) | P1DOWN;
			P1RIGHT = (bool)(GP1DevState.lX > GP1CentVal + GP1RangeVal) | P1RIGHT;
			P1LEFT = (bool)(GP1DevState.lX < GP1CentVal - GP1RangeVal) | P1LEFT;

			P2B1 = (bool)(GP2DevState.rgbButtons[0]) | P2B1;
			P2B2 = (bool)(GP2DevState.rgbButtons[1]) | P2B2;
			P2B3 = (bool)GP2DevState.rgbButtons[2] | P2B3;
			P2UP = (GP2DevState.lY < GP2CentVal - GP2RangeVal) | P2UP;
			P2DOWN = (GP2DevState.lY > GP2CentVal + GP2RangeVal) | P2DOWN;
			P2RIGHT = (GP2DevState.lX > GP2CentVal + GP2RangeVal) | P2RIGHT;
			P2LEFT = (GP2DevState.lX < GP2CentVal - GP2RangeVal) | P2LEFT;

		}
		else if (gamePadDeviceNum > 0) {
			P2B1 = (bool)GP1DevState.rgbButtons[0] | P2B1;
			P2B2 = (bool)GP1DevState.rgbButtons[1] | P2B2;
			P2B3 = (bool)GP1DevState.rgbButtons[2] | P2B3;
			P2UP = (GP1DevState.lY < GP1CentVal - GP1RangeVal) | P2UP;
			P2DOWN = (GP1DevState.lY > GP1CentVal + GP1RangeVal) | P2DOWN;
			P2RIGHT = (GP1DevState.lX > GP1CentVal + GP1RangeVal) | P2RIGHT;
			P2LEFT = (GP1DevState.lX < GP1CentVal - GP1RangeVal) | P2LEFT;
		}

		inputData->P1_Up.SetFlag(P1UP);
		inputData->P1_Down.SetFlag(P1DOWN);
		inputData->P1_Right.SetFlag(P1RIGHT);
		inputData->P1_Left.SetFlag(P1LEFT);
		inputData->P1_J.SetFlag(P1B1);
		inputData->P1_K.SetFlag(P1B2);
		inputData->P1_I.SetFlag(P1B3);
		inputData->P2_Up.SetFlag(P2UP);
		inputData->P2_Down.SetFlag(P2DOWN);
		inputData->P2_Right.SetFlag(P2RIGHT);
		inputData->P2_Left.SetFlag(P2LEFT);
		inputData->P2_J.SetFlag(P2B1);
		inputData->P2_K.SetFlag(P2B2);
		inputData->P2_I.SetFlag(P2B3);

		inputData->F3.SetFlag(KEYDOWN(keyBuffer, DIK_F3));
		return;
	}

	void InputManager::ResetInput() {
		//キーボードデバイス破棄
		lpdiKeyboard->Unacquire();
		lpdiKeyboard->Release();


		//キーボードデバイス取得
		hr = lpDirect8->CreateDevice(GUID_SysKeyboard, &lpdiKeyboard, NULL);
		//データ形式の設定
		hr = lpdiKeyboard->SetDataFormat(&c_dfDIKeyboard);
		//動作の設定
		hr = lpdiKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		//アクセス権の取得
		if (lpdiKeyboard)lpdiKeyboard->Acquire();

	}
}