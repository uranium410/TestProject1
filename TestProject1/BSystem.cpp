#include "stdafx.h"
#include "AllHead.h"
//#include <iostream>

namespace BasicSystem {

	void BSystem::AtFirst(HINSTANCE _hinst,HWND _hwnd) {
		
		//グラフィックシステム生成
		graphicManager = graphFactory.GetGraphicManager(_hwnd);
		//graphicManager->TestMethod();
		//入力システム生成
		inputManager = std::make_shared<BasicSystem::InputManager>(_hinst,_hwnd);
		//サウンドシステム初期化
		SoundSystem::init();
		//シーンセット
		nowScene = new GameSystem::TitleScene(graphicManager);
		nowScene->inputManager = this->inputManager;
	}

	BSystem::~BSystem() {
		SoundSystem::cleanup();
	}

	void BSystem::AtLoop() {
		if (nowScene == 0)return;

		nowScene->InputUpdate();
		nowScene->Update();
		nowScene->CollisionUpdate();
		nowScene->GraphUpdate(graphicManager);
		if (DEBUG_MODE)DebugDisplay();
		nowScene->CorrectGraphUpdate();
		nowScene->GraphUpdateEnd();


		if (nowScene->sceneChange) {

			switch (nowScene->nextSceneid) {
			case GameSystem::Title:
				delete nowScene;
				nowScene = new GameSystem::TitleScene(graphicManager);
				nowScene->inputManager = this->inputManager;
				break;
			case GameSystem::Battle:
				delete nowScene;
				nowScene = new GameSystem::BattleScene(graphicManager);
				nowScene->inputManager = this->inputManager;
				break;
			}
		}
	}

	void BSystem::DebugDisplay() {
		if (DebugMode) {
			if (inputManager->inputData->F3.GetKeyDown())DebugMode = false;
		}
		else {
			if (inputManager->inputData->F3.GetKeyDown())DebugMode = true;
		}

		if (!DebugMode)return;


		float width = 1300.0f;
		float height = 100.0f;
		D2D1_RECT_F rect;

		rect.left = 20.0f;
		rect.top = 100.0f;
		rect.right = rect.left + width;
		rect.bottom = rect.top + height;

		std::wstring deviceText(L"接続デバイス数:");
		deviceText += std::to_wstring(inputManager->gamePadDeviceNum);
		graphicManager->Drawtext(deviceText, rect);

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
		if (inputManager->inputData->P1_I.GetKey())testTxt += std::wstring(L"B3");
		else testTxt += std::wstring(L"　");
		rect.left = 40.0f;
		rect.top = 120.0f;
		rect.right = rect.left + width;
		rect.bottom = rect.top + height;
		graphicManager->Drawtext(testTxt,rect);

		testTxt = std::wstring(L"Player2:");
		if (inputManager->inputData->P2_Left.GetKey())testTxt += std::wstring(L"←");
		else testTxt += std::wstring(L"　");
		if (inputManager->inputData->P2_Up.GetKey())testTxt += std::wstring(L"↑");
		else testTxt += std::wstring(L"　");
		if (inputManager->inputData->P2_Right.GetKey())testTxt += std::wstring(L"→");
		else testTxt += std::wstring(L"　");
		if (inputManager->inputData->P2_Down.GetKey())testTxt += std::wstring(L"↓");
		else testTxt += std::wstring(L"　");
		if (inputManager->inputData->P2_J.GetKey())testTxt += std::wstring(L"B1");
		else testTxt += std::wstring(L"　");
		if (inputManager->inputData->P2_K.GetKey())testTxt += std::wstring(L"B2");
		else testTxt += std::wstring(L"　");
		if (inputManager->inputData->P2_I.GetKey())testTxt += std::wstring(L"B3");
		else testTxt += std::wstring(L"　");
		rect.left = 40.0f;
		rect.top = 140.0f;
		rect.right = rect.left + width;
		rect.bottom = rect.top + height;
		graphicManager->Drawtext(testTxt, rect);

		if (nowScene->P1 != 0 || nowScene->P2 != 0) {
			for (Collider::AccCollision temp : nowScene->P1->AccCollisions) {
				graphicManager->DrawRect(temp.GetDrawPosition(1000,600,90),temp.size,GraphicSystem::GREEN);
			}
			for (Collider::AccCollision temp : nowScene->P2->AccCollisions) {
				graphicManager->DrawRect(temp.GetDrawPosition(1000, 600, 90), temp.size, GraphicSystem::GREEN);
			}
			for (Collider::AtkCollision temp : nowScene->P1->AtkCollisions) {
				graphicManager->DrawRect(temp.GetDrawPosition(1000, 600, 90), temp.size, GraphicSystem::RED);
			}
			for (Collider::AtkCollision temp : nowScene->P2->AtkCollisions) {
				graphicManager->DrawRect(temp.GetDrawPosition(1000, 600, 90), temp.size, GraphicSystem::RED);
			}
		}
	}
}