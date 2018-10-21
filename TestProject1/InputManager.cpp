#include "stdafx.h"
#include "AllHead.h"

namespace BasicSystem {
	
	InputManager::InputManager(HINSTANCE _hInst, HWND _hWnd) {
		hr = DirectInput8Create(_hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&lpDI, NULL);
		if (FAILED(hr)) {
			
			return;
		}

		//キーボードデバイスの設定
		hr = lpDI->CreateDevice(GUID_SysKeyboard, &lpKeyboard,NULL);
		if (FAILED(hr)) {
			lpDI->Release();
			return;
		}
		//入力データ形式のセット
		hr = lpKeyboard->SetDataFormat(&c_dfDIKeyboard);
		if (FAILED(hr)) {
			lpKeyboard->Release();
			lpDI->Release();
			return;
		}
		//排他制御のセット
		hr = lpKeyboard->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND|DISCL_NONEXCLUSIVE|DISCL_NOWINKEY);
		if (FAILED(hr)) {
			lpKeyboard->Release();
			lpDI -> Release();
			return;
		}
	}

	InputManager::~InputManager() {
		if(lpKeyboard!=NULL)lpKeyboard->Release();
		if(lpGamepad1!=NULL)lpGamepad1->Release();
		if(lpGamepad2!=NULL)lpGamepad2->Release();
		if(lpDI!=NULL)		lpDI->Release();
	}

	void InputManager::InputUpdate() {
		BYTE key[256];
		ZeroMemory(key,sizeof(key));
		hr = lpKeyboard->GetDeviceState(sizeof(key),key);
		if (FAILED(hr)) {
			lpKeyboard->Acquire();
			lpKeyboard->GetDeviceState(sizeof(key),key);
		}
	}
}