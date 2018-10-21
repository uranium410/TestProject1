#pragma once

#define DIRECTINPUT_VIRSION		0x0800

#include <d2d1_1.h>
#include <Windows.h>
#include <wincodec.h>
#include <wincodecsdk.h>
#include <vector>
#include <queue>
#include <memory>
#include <dinput.h>

/*オリジナルヘッダ*/
#include "Vector.h"
#include "GraphManager.h"
#include "InputManager.h"
#include "SceneBase.h"
#include "BasicSystems.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")