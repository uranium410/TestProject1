#pragma once
#include "AllHead.h"


/*
�O�l�̌^(DIVIRITUAL_FIGHTING_THIRDPERSON)�̃A�N�V�����}�b�s���O�萔��z��
�D�揇��1�̃R���g���[��:
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
		//�L�[�{�[�h�̓��̓f�[�^�i�[�p
		char keyBuffer[256];
		//�E�B���h�E�n���h��
		HWND hWnd;
		
		//��������
		HRESULT hr;
		//DirectInput8�f�o�C�X�A�h���X
		//LPDIRECTINPUT8 lpDirect82;
		//�񋓂����Q�[���p�b�h�f�o�C�X���i�[����
		std::vector<LPCDIDEVICEINSTANCE> gamePads;
		//�L�[�{�[�h�f�o�C�X
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