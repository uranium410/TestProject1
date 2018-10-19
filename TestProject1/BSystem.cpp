#include "stdafx.h"
#include "AllHead.h"
//#include <iostream>

namespace BasicSystem {

	void BSystem::GameObjectUpdate() {

	}

	void BSystem::CollisionUpdate() {

	}

	void BSystem::GraphicUpdate() {
		graphicManager->DrawUpdate();
	}

	void BSystem::AtFirst(HWND hwnd) {
		
		graphicManager = graphFactory.GetGraphicManager(hwnd);
		graphicManager->TestMethod();

	}

	void BSystem::AtLoop() {

	}

}