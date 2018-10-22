#include "stdafx.h"
#include "AllHead.h"
//#include <iostream>

namespace BasicSystem {

	void BSystem::AtFirst(HINSTANCE _hinst,HWND _hwnd) {
		
		graphicManager = graphFactory.GetGraphicManager(_hwnd);
		graphicManager->TestMethod();
		inputManager = std::make_shared<BasicSystem::InputManager>(_hinst,_hwnd);
		nowScene = new GameSystem::BattleScene(graphicManager);

	}

	void BSystem::AtLoop() {
		inputManager->InputUpdate();

		if (nowScene == 0)return;
		nowScene->InputUpdate();
		nowScene->Update();
		nowScene->CollisionUpdate();
		nowScene->GraphUpdate();
	}

}