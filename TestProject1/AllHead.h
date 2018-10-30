#pragma once

#define DIRECTINPUT_VIRSION		0x0800

#include <d2d1_1.h>
#include <Windows.h>
#include <wincodec.h>
#include <wincodecsdk.h>
#include <Dwrite.h>
#include <string>
#include <vector>
#include <queue>
#include <memory>
#include <dinput.h>

#define DEBUG_MODE true

/*オリジナルヘッダ*/
#include "Vector.h"
#include "GraphManager.h"
#include "InputManager.h"
#include "Animation.h"
#include "Collision.h"
#include "LoadedGraphics.h"
#include "GameObject.h"
#include "PlayerClass.h"
#include "SceneBase.h"
#include "BasicSystems.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "Dwrite.lib")