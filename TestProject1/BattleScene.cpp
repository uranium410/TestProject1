#include "stdafx.h"
#include "AllHead.h"

namespace GameSystem {
	BattleScene::BattleScene(const std::shared_ptr<GraphicSystem::GraphicManager> &GM) {
		graphicManager = GM;
		gameObjects.push_back(GameObjects::GameObjectPointer(std::make_shared<GameObjects::G_BackGround>(graphicManager)));
	}

}