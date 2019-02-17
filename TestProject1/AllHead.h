#pragma once


#define DIRECTINPUT_VIRSION		0x0800

#include <d2d1_1.h>
#include <d2d1helper.h>
#include <Windows.h>
#include <wincodec.h>
#include <wincodecsdk.h>
#include <Dwrite.h>
#include <xaudio2.h>
#include <string>
#include <vector>
#include <queue>
#include <memory>
#include <dinput.h>
#include <iostream>
#include <atlstr.h>
#include <mmsystem.h>

#define DEBUG_MODE true

/*オリジナルヘッダ*/
#include "Vector.h"
#include "GraphManager.h"
#include "CWaveFile.h"
#include "SoundSystem.h"
//#include "SoundSystem2.h"
#include "InputManager.h"
#include "Animation.h"
#include "Collision.h"
#include "LoadedGraphics.h"
#include "GameObject.h"
#include "Effects.h"
#include "PlayerClass.h"
#include "HPBar.h"
#include "SceneBase.h"
#include "BasicSystems.h"
#include "G_BackGround.h"



#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "Dwrite.lib")
#pragma comment(lib, "DXGUID.LIB")
#pragma comment(lib, "xaudio2.lib")
//#pragma comment(lib, "xaudio2_9.lib")
#pragma comment(lib, "winmm.lib")
