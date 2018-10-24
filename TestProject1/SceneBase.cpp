#include "stdafx.h"
#include "AllHead.h"

namespace GameSystem {
	void SceneBase::Update() {
		for (GameObjects::GameObjectPointer temp : gameObjects) {
			temp.myGO->Update();
		}
	}

	void SceneBase::InputUpdate() {
		inputManager->InputUpdate();
	}

	void SceneBase::CollisionUpdate() {

	}

	void SceneBase::GraphUpdate() {
		for (GameObjects::GameObjectPointer temp : gameObjects) {
			temp.myGO->DrawUpdate();
		}
		graphicManager->DrawUpdate();
	}

	void SceneBase::GraphUpdateEnd() {
		graphicManager->DrawUpdateEnd();
	}
}