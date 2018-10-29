#include "stdafx.h"
#include "AllHead.h"

namespace GameSystem {
	BattleScene::BattleScene(const std::shared_ptr<GraphicSystem::GraphicManager> &GM) {
		graphicManager = GM;
		gameObjects_BackGround.push_back(GameObjects::GameObjectPointer(std::make_shared<GameObjects::G_BackGround>(graphicManager)));
		P1 = std::make_shared<PlayerClasses::PlayerID_1>(graphicManager);
	}

	void BattleScene::Update() {
		for (GameObjects::GameObjectPointer temp : gameObjects_BackGround) {
			temp.myGO->Update();
		}

		if(P1!=0)P1->Update();
		if(P2!=0)P2->Update();

		for (GameObjects::GameObjectPointer temp : gameObjects) {
			temp.myGO->Update();
		}
		for (GameObjects::GameObjectPointer temp : gameObjects_UI) {
			temp.myGO->Update();
		}
	}

	void BattleScene::GraphUpdate(std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager) {
		for (GameObjects::GameObjectPointer temp : gameObjects_BackGround) {
			temp.myGO->DrawUpdate();
		}
		
		P1->GraphUpdate(graphicManager);
		//P2->GraphUpdate(graphicManager);

		for (GameObjects::GameObjectPointer temp : gameObjects) {
			temp.myGO->DrawUpdate();
		}

		for (GameObjects::GameObjectPointer temp : gameObjects_UI) {
			temp.myGO->DrawUpdate();
		}

		graphicManager->DrawUpdate();
	}
}