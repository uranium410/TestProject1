#include "stdafx.h"
#include "AllHead.h"

//�L�[�{�[�h���͔���p�}�N��
#define KEYDOWN(name, key) (name[key] & 0x80)

//http://marupeke296.com/DI_InitDirectInput.html
//�����炨�؂肵���֐��ł��B
//ref https://msdn.microsoft.com/ja-jp/library/cc351699.aspx
//�f�o�C�X�񋓗p�̃R�[���o�b�N�֐�
BOOL CALLBACK DIEnumDevBySemanticsCallback(
	LPCDIDEVICEINSTANCE lpddi,
	LPDIRECTINPUTDEVICE8 lpdid,
	DWORD dwFlags,
	DWORD dwRemaining,
	LPVOID pvRef
)
{
	// ��2������DIDEVICEINSTANCE�\���̂�vecor STL���Ƃ��܂�
	//std::vector<DIDEVICEINSTANCE>* ptr = (std::vector<DIDEVICEINSTANCE>*)pvRef;
	//DIDEVICEINSTANCE tmp = *lpdi;
	std::vector<LPCDIDEVICEINSTANCE>* ptr = (std::vector<LPCDIDEVICEINSTANCE>*)pvRef;

	// �z��Ɋi�[
	if(dwFlags == DIEDBS_MAPPEDPRI1)ptr->push_back(lpddi);

	// �񋓂𑱂���ꍇ��DIENUM_CONTINUE�A�~�߂�ꍇ��DIENUM_STOP���w��
	// �S�Ă̗񋓂��I������Ǝ����I�ɃR�[���o�b�N���I������̂ŁA
	// �~�߂闝�R���������DIENUM_CONTINUE�ɂ���B
	return DIENUM_CONTINUE;
}


namespace BasicSystem {

	InputManager::InputManager(HINSTANCE _hInst, HWND _hWnd) {
		
		

		//DIACTIONFORMAT�̒�`
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
		//�E�B���h�E�n���h���擾
		hWnd = _hWnd;

		//DirectInput8�쐬
		hr = DirectInput8Create(_hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&lpDirect8, NULL);
		if (FAILED(hr)) {
			
			return;
		}
		
		//�L�[�{�[�h�f�o�C�X�擾
		hr = lpDirect8->CreateDevice(GUID_SysKeyboard, &lpdiKeyboard, NULL);
		//�f�[�^�`���̐ݒ�
		hr = lpdiKeyboard->SetDataFormat(&c_dfDIKeyboard);
		//����̐ݒ�
		hr = lpdiKeyboard->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		//�A�N�Z�X���̎擾
		if (lpdiKeyboard)lpdiKeyboard->Acquire();

		//�Q�[���p�b�h�f�o�C�X�擾//
		//�Q�[���p�b�h�f�o�C�X��
		/*
		lpDirect8->EnumDevices(DI8DEVCLASS_GAMECTRL, //�S�Ẵf�o�C�X��
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

			//�A�N�V�����}�b�v�̕\��
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
		//�L�[�{�[�h�f�o�C�X�j��
		lpdiKeyboard->Unacquire();
		lpdiKeyboard->Release();
		//DirectInput�j��
		lpDirect8->Release();
	}

	void InputManager::InputUpdate() {
		//�L�[�{�[�h
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

		//�Q�[���p�b�h
		if (gamePadDeviceNum >= 1) {
			//�A�N�Z�X���̎擾
			GamePad1->Poll();
			hr = GamePad1->Acquire();

			DIDEVICEOBJECTDATA getData;
			GamePad1->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),&getData,NULL,0);

			//���擾
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
			//�A�N�Z�X���̎擾
			GamePad1->Poll();
			hr = GamePad1->Acquire();

			//���擾
			DIJOYSTATE dijs;
			ZeroMemory(&dijs, sizeof(DIJOYSTATE));
			GamePad1->GetDeviceState(sizeof(DIJOYSTATE), &dijs);

		}
		return;
	}

	void InputManager::ResetInput() {
		//�L�[�{�[�h�f�o�C�X�j��
		lpdiKeyboard->Unacquire();
		lpdiKeyboard->Release();


		//�L�[�{�[�h�f�o�C�X�擾
		hr = lpDirect8->CreateDevice(GUID_SysKeyboard, &lpdiKeyboard, NULL);
		//�f�[�^�`���̐ݒ�
		hr = lpdiKeyboard->SetDataFormat(&c_dfDIKeyboard);
		//����̐ݒ�
		hr = lpdiKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		//�A�N�Z�X���̎擾
		if (lpdiKeyboard)lpdiKeyboard->Acquire();

	}
}