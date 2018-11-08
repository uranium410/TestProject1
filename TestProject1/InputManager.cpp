#include "stdafx.h"
#include "AllHead.h"

//キーボード入力判定用マクロ
#define KEYDOWN(name, key) (name[key] & 0x80)

//http://marupeke296.com/DI_InitDirectInput.html
//↑からお借りした関数です。
//ref https://msdn.microsoft.com/ja-jp/library/cc351699.aspx
//デバイス列挙用のコールバック関数
BOOL CALLBACK DIEnumDevBySemanticsCallback(
	LPCDIDEVICEINSTANCE lpddi,
	LPDIRECTINPUTDEVICE8 lpdid,
	DWORD dwFlags,
	DWORD dwRemaining,
	LPVOID pvRef
)
{
	// 第2引数がDIDEVICEINSTANCE構造体のvecor STLだとします
	//std::vector<DIDEVICEINSTANCE>* ptr = (std::vector<DIDEVICEINSTANCE>*)pvRef;
	//DIDEVICEINSTANCE tmp = *lpdi;
	std::vector<LPCDIDEVICEINSTANCE>* ptr = (std::vector<LPCDIDEVICEINSTANCE>*)pvRef;

	// 配列に格納
	if(dwFlags == DIEDBS_MAPPEDPRI1)ptr->push_back(lpddi);

	// 列挙を続ける場合はDIENUM_CONTINUE、止める場合はDIENUM_STOPを指定
	// 全ての列挙が終了すると自動的にコールバックも終了するので、
	// 止める理由が無ければDIENUM_CONTINUEにする。
	return DIENUM_CONTINUE;
}


namespace BasicSystem {

	InputManager::InputManager(HINSTANCE _hInst, HWND _hWnd) {
		
		

		//DIACTIONFORMATの定義
		p1ActionFormat.dwSize		= sizeof(DIACTIONFORMAT);
		p1ActionFormat.dwActionSize = sizeof(DIACTION);
		p1ActionFormat.dwDataSize	= NUMBER_OF_ACTIONS * sizeof(DWORD);
		p1ActionFormat.dwNumActions = NUMBER_OF_ACTIONS;
//		p1ActionFormat.guidActionMap = p1Action->guidInstance;
		p1ActionFormat.dwGenre		= DIVIRTUAL_FIGHTING_THIRDPERSON;
		p1ActionFormat.rgoAction	= p1Action;
		p1ActionFormat.dwBufferSize = 16;
		p1ActionFormat.lAxisMin		= -100;
		p1ActionFormat.lAxisMax		= 100;
		wcscpy_s(p1ActionFormat.tszActionMap, L"DI Test");

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
		/*
		lpDirect8->EnumDevices(DI8DEVCLASS_GAMECTRL, //全てのデバイス列挙
			DIEnumDevCallback,
			&gamePads,
			DIEDFL_ATTACHEDONLY);*/
		hr = lpDirect8->EnumDevicesBySemantics(
			NULL,
			&p1ActionFormat,
			DIEnumDevBySemanticsCallback,
			&gamePads,
			DIEDBSFL_ATTACHEDONLY
		);

		gamePadDeviceNum = gamePads.size();

		if (gamePadDeviceNum > 0) {
			lpDirect8->CreateDevice(gamePads[0]->guidInstance, &GamePad1, NULL);
			
			GamePad1->BuildActionMap(&p1ActionFormat, NULL, 0L);
			GamePad1->SetActionMap(&p1ActionFormat, NULL, 0L);

			//アクションマップの表示
			DICOLORSET dics;
			ZeroMemory(&dics, sizeof(DICOLORSET));
			dics.dwSize = sizeof(DICOLORSET);

			DICONFIGUREDEVICESPARAMS dicdp;
			ZeroMemory(&dicdp, sizeof(dicdp));
			dicdp.dwSize = sizeof(dicdp);
			dicdp.dwcUsers = 1;
			dicdp.lptszUserNames = NULL;

			dicdp.dwcFormats = 1;
			dicdp.lprgFormats = &p1ActionFormat;
			dicdp.hwnd = _hWnd;
			dicdp.lpUnkDDSTarget = NULL;

			lpDirect8->ConfigureDevices(NULL, &dicdp, DICD_EDIT, NULL);

		}
	}

	InputManager::~InputManager() {
		//キーボードデバイス破棄
		lpdiKeyboard->Unacquire();
		lpdiKeyboard->Release();
		//DirectInput破棄
		lpDirect8->Release();
	}

	void InputManager::InputUpdate() {
		//キーボード
		hr = lpdiKeyboard->GetDeviceState(sizeof(keyBuffer),(LPVOID)&keyBuffer);
		if (hr != DI_OK)ResetInput();

		if (KEYDOWN(keyBuffer, DIK_ESCAPE))keyDownESC = true;
		else keyDownESC = false;
		
		inputData->P1_Up.SetFlag(KEYDOWN(keyBuffer, DIK_W));
		inputData->P1_Down.SetFlag(KEYDOWN(keyBuffer, DIK_S));
		inputData->P1_Right.SetFlag(KEYDOWN(keyBuffer, DIK_D));
		inputData->P1_Left.SetFlag(KEYDOWN(keyBuffer, DIK_A));
		inputData->P1_J.SetFlag(KEYDOWN(keyBuffer,DIK_J));
		inputData->P1_K.SetFlag(KEYDOWN(keyBuffer,DIK_K));
		
		return;

		//ゲームパッド
		if (gamePadDeviceNum >= 1) {
			//アクセス権の取得
			GamePad1->Poll();
			hr = GamePad1->Acquire();

			DIDEVICEOBJECTDATA getData;
			GamePad1->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),&getData,NULL,0);

			//情報取得
			DIJOYSTATE dijs;
			ZeroMemory(&dijs, sizeof(DIJOYSTATE));
			GamePad1->GetDeviceState(sizeof(DIJOYSTATE), &dijs);

			inputData->P1_Up.SetFlag(dijs.rgbButtons[0]);
			inputData->P1_Down.SetFlag(dijs.rgbButtons[1]);
			inputData->P1_Right.SetFlag(dijs.rgbButtons[2]);
			inputData->P1_Left.SetFlag(dijs.rgbButtons[3]);
			inputData->P1_J.SetFlag(dijs.rgbButtons[4]);
			inputData->P1_K.SetFlag(dijs.rgbButtons[5]);
		}
		if (gamePadDeviceNum >= 2) {
			//アクセス権の取得
			GamePad1->Poll();
			hr = GamePad1->Acquire();

			//情報取得
			DIJOYSTATE dijs;
			ZeroMemory(&dijs, sizeof(DIJOYSTATE));
			GamePad1->GetDeviceState(sizeof(DIJOYSTATE), &dijs);

		}
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