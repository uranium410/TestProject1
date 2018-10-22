#include "stdafx.h"
#include "AllHead.h"

//�L�[�{�[�h���͔���p�}�N��
#define KEYDOWN(name, key) (name[key] & 0x80)

//http://marupeke296.com/DI_InitDirectInput.html
//�����炨�؂肵���֐��ł��B
//ref https://msdn.microsoft.com/ja-jp/library/cc351699.aspx
//�f�o�C�X�񋓗p�̃R�[���o�b�N�֐�
BOOL WINAPI DIEnumDevCallback(
	LPCDIDEVICEINSTANCE lpddi,
	LPVOID pvRef
)
{
	// ��2������DIDEVICEINSTANCE�\���̂�vecor STL���Ƃ��܂�
	std::vector<DIDEVICEINSTANCE>* ptr = (std::vector<DIDEVICEINSTANCE>*)pvRef;
	DIDEVICEINSTANCE tmp = *lpddi;

	// �z��Ɋi�[
	ptr->push_back(tmp);

	// �񋓂𑱂���ꍇ��DIENUM_CONTINUE�A�~�߂�ꍇ��DIENUM_STOP���w��
	// �S�Ă̗񋓂��I������Ǝ����I�ɃR�[���o�b�N���I������̂ŁA
	// �~�߂闝�R���������DIENUM_CONTINUE�ɂ���B
	return DIENUM_CONTINUE;
}


namespace BasicSystem {

	InputManager::InputManager(HINSTANCE _hInst, HWND _hWnd) {
		//DirectInput8�쐬
		hr = DirectInput8Create(_hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&lpDirect8, NULL);
		if (FAILED(hr)) {
			
			return;
		}

		//�Q�[���p�b�h�f�o�C�X��
		lpDirect8->EnumDevices(DI8DEVCLASS_GAMECTRL, //�S�Ẵf�o�C�X��
			DIEnumDevCallback,
			&gamePads,
			DIEDFL_ATTACHEDONLY);
		
		//�L�[�{�[�h�f�o�C�X�擾
		hr = lpDirect8->CreateDevice(GUID_SysKeyboard, &lpdiKeyboard, NULL);
		//�f�[�^�`���̐ݒ�
		hr = lpdiKeyboard->SetDataFormat(&c_dfDIKeyboard);
		//����̐ݒ�
		hr = lpdiKeyboard->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		//�A�N�Z�X���̎擾
		if (lpdiKeyboard)lpdiKeyboard->Acquire();
	}

	InputManager::~InputManager() {
		//�L�[�{�[�h�f�o�C�X�j��
		lpdiKeyboard->Unacquire();
		lpdiKeyboard->Release();
		//DirectInput�j��
		lpDirect8->Release();
	}

	void InputManager::InputUpdate() {
		lpdiKeyboard->GetDeviceState(sizeof(keyBuffer),(LPVOID)&keyBuffer);
		if (KEYDOWN(keyBuffer, DIK_ESCAPE))keyDownESC = true;
		else keyDownESC = false;

		return;
	}
}