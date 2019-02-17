#include "stdafx.h"
#include "AllHead.h"

namespace GameObjects {
	std::shared_ptr<AnimationMode> BackGround_00=0;

	G_BackGround::G_BackGround(const std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager) {
		graphicManager = _graphicManager;
		if (BackGround_00 == 0) {
			graph = std::make_shared<AnimationMode>(1,
				new AnimationCell(_graphicManager, L"Materials/BackGround_00.png", 6));
			BackGround_00 = graph;
		}
		else graph = BackGround_00;
	}

	void G_BackGround::Update() {

	}

	void G_BackGround::DrawUpdate() {
		graphicManager->DrawOrder(GraphicSystem::DrawGraphicOrder(graph->GH_to_draw(),Vector2(0,-200),DoubleVector2(0.8,0.8)));
	}
}