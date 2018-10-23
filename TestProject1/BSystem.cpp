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
		nowScene->InputUpdate();
		nowScene->Update();
		nowScene->CollisionUpdate();
		nowScene->GraphUpdate();
		if (DEBUG_MODE)DebugDisplay();
		nowScene->GraphUpdateEnd();

		if (nowScene == 0)return;
		nowScene->InputUpdate();
		nowScene->Update();
		nowScene->CollisionUpdate();
		nowScene->GraphUpdate();
	}

	void BSystem::DebugDisplay() {
		float width = 1300.0f;
		float height = 100.0f;
		std::wstring testTxt(L"Player1:");
		D2D1_RECT_F rect;
		rect.left = 20.0f;
		rect.top = 20.0f;
		rect.right = rect.left + width;
		rect.bottom = rect.top + height;
		graphicManager->Drawtext(testTxt,rect);
	}
}