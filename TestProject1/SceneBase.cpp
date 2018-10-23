#include "stdafx.h"
#include "AllHead.h"

namespace GameSystem {
	void SceneBase::InputUpdate() {
		inputManager->InputUpdate();
	}

	void SceneBase::GraphUpdate() {
		graphicManager->DrawUpdate();
	}

	void SceneBase::GraphUpdateEnd() {
		graphicManager->DrawUpdateEnd();
	}
}