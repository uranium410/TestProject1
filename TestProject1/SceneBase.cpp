#include "stdafx.h"
#include "AllHead.h"

namespace GameSystem {
	void SceneBase::InputUpdate() {

	}

	void SceneBase::GraphUpdate() {
		graphicManager->DrawUpdate();
	}
}