#include "stdafx.h"
#include "AllHead.h"

//キーボード入力判定用マクロ
#define KEYDOWN(name, key) (name[key] & 0x80)

//http://marupeke296.com/DI_InitDirectInput.html
//↑からお借りした関数です。
//ref https://msdn.microsoft.com/ja-jp/library/cc351699.aspx
//デバイス列挙用のコールバック関数
BOOL WINAPI DIEnumDevCallback(
	LPCDIDEVICEINSTANCE lpddi,
	LPVOID pvRef
)
{
	// 第2引数がDIDEVICEINSTANCE構造体のvecor STLだとします
	std::vector<DIDEVICEINSTANCE>* ptr = (std::vector<DIDEVICEINSTANCE>*)pvRef;
	DIDEVICEINSTANCE tmp = *lpddi;

	// 配列に格納
	ptr->push_back(tmp);

	// 列挙を続ける場合はDIENUM_CONTINUE、止める場合はDIENUM_STOPを指定
	// 全ての列挙が終了すると自動的にコールバックも終了するので、
	// 止める理由が無ければDIENUM_CONTINUEにする。
	return DIENUM_CONTINUE;
}


namespace BasicSystem {

	InputManager::InputManager(HINSTANCE _hInst, HWND _hWnd) {
		inputData = std::make_shared<InputData>();
		//ウィンドウハンドル取得
		hWnd = _hWnd;

		//DirectInput8作成
		hr = DirectInput8Create(_hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&lpDirect8, NULL);
		if (FAILED(hr)) {
			
			return;
		}

		//ゲームパッドデバイス列挙
		lpDirect8->EnumDevices(DI8DEVCLASS_GAMECTRL, //全てのデバイス列挙
			DIEnumDevCallback,
			&gamePads,
			DIEDFL_ATTACHEDONLY);
		
		//キーボードデバイス取得
		hr = lpDirect8->CreateDevice(GUID_SysKeyboard, &lpdiKeyboard, NULL);
		//データ形式の設定
		hr = lpdiKeyboard->SetDataFormat(&c_dfDIKeyboard);
		//動作の設定
		hr = lpdiKeyboard->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		//アクセス権の取得
		if (lpdiKeyboard)lpdiKeyboard->Acquire();
	}

	InputManager::~InputManager() {
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

		inputData->P1_Up.SetFlag(KEYDOWN(keyBuffer, DIK_W));
		inputData->P1_Down.SetFlag(KEYDOWN(keyBuffer, DIK_S));
		inputData->P1_Right.SetFlag(KEYDOWN(keyBuffer, DIK_D));
		inputData->P1_Left.SetFlag(KEYDOWN(keyBuffer, DIK_A));
		inputData->P1_J.SetFlag(KEYDOWN(keyBuffer,DIK_J));
		inputData->P1_K.SetFlag(KEYDOWN(keyBuffer,DIK_K));

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