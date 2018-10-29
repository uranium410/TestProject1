#include "stdafx.h"
#include "AllHead.h"

namespace GameSystem {
	void SceneBase::InputUpdate() {
		inputManager->InputUpdate();
	}

	void SceneBase::CollisionUpdate() {

	}

	void SceneBase::GraphUpdateEnd() {
		graphicManager->DrawUpdateEnd();
	}
}