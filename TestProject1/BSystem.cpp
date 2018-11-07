#include "stdafx.h"
#include "AllHead.h"
//#include <iostream>

namespace BasicSystem {

	void BSystem::AtFirst(HINSTANCE _hinst,HWND _hwnd) {
		
		//グラフィックシステム生成
		graphicManager = graphFactory.GetGraphicManager(_hwnd);
		graphicManager->TestMethod();
		//入力システム生成
		inputManager = std::make_shared<BasicSystem::InputManager>(_hinst,_hwnd);
		//シーンセット
		nowScene = new GameSystem::BattleScene(graphicManager);
		nowScene->inputManager = this->inputManager;
	}

	void BSystem::AtLoop() {
		if (nowScene == 0)return;

		nowScene->InputUpdate();
		nowScene->Update();
		nowScene->CollisionUpdate();
		nowScene->GraphUpdate(graphicManager);
		if (DEBUG_MODE)DebugDisplay();
		nowScene->GraphUpdateEnd();
	}

	void BSystem::DebugDisplay() {
		float width = 1300.0f;
		float height = 100.0f;
		std::wstring gamePadNumText(L"接続ゲームパッド数:");
		gamePadNumText += std::to_wstring(inputManager->gamePadDeviceNum);
		D2D1_RECT_F rect;
		rect.left = 20.0f;
		rect.top = 80.0f;
		rect.right = rect.left + width;
		rect.bottom = rect.top + height;
		graphicManager->Drawtext(gamePadNumText,rect);

		std::wstring testTxt(L"Player1:");
		if (inputManager->inputData->P1_Left.GetKey())testTxt += std::wstring(L"←");
		else testTxt += std::wstring(L"　");
		if (inputManager->inputData->P1_Up.GetKey())testTxt += std::wstring(L"↑");
		else testTxt += std::wstring(L"　");
		if (inputManager->inputData->P1_Right.GetKey())testTxt += std::wstring(L"→");
		else testTxt += std::wstring(L"　");
		if (inputManager->inputData->P1_Down.GetKey())testTxt += std::wstring(L"↓");
		else testTxt += std::wstring(L"　");
		if (inputManager->inputData->P1_J.GetKey())testTxt += std::wstring(L"B1");
		else testTxt += std::wstring(L"　");
		if (inputManager->inputData->P1_K.GetKey())testTxt += std::wstring(L"B2");
		else testTxt += std::wstring(L"　");
		rect.left = 20.0f;
		rect.top = 100.0f;
		rect.right = rect.left + width;
		rect.bottom = rect.top + height;
		graphicManager->Drawtext(testTxt,rect);
	}
}