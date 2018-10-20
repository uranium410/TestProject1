#include "stdafx.h"
#include "AllHead.h"
//#include <iostream>

namespace BasicSystem {

	void BSystem::AtFirst(HWND hwnd) {
		
		graphicManager = graphFactory.GetGraphicManager(hwnd);
		graphicManager->TestMethod();
		nowScene = new GameSystem::BattleScene(graphicManager);

	}

	void BSystem::AtLoop() {
		if (nowScene == 0)return;
		nowScene->InputUpdate();
		nowScene->Update();
		nowScene->CollisionUpdate();
		nowScene->GraphUpdate();
	}

}