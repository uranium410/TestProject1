#pragma once
#include "AllHead.h"

namespace BasicSystem {

	class InputManager {
		//�L�[�{�[�h�̓��̓f�[�^�i�[�p
		char keyBuffer[256];

		//��������
		HRESULT hr;
		//DirectInput8�f�o�C�X�A�h���X
		LPDIRECTINPUT8 lpDirect8;
		//�񋓂����Q�[���p�b�h�f�o�C�X���i�[����
		std::vector<DIDEVICEINSTANCE>gamePads;
		//�L�[�{�[�h�f�o�C�X
		LPDIRECTINPUTDEVICE8 lpdiKeyboard;
	public:
		bool keyDownESC=false;

		InputManager(HINSTANCE _hINst, HWND _hWnd);
		~InputManager();

		void InputUpdate();
	};

}