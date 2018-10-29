#include "stdafx.h"
#include "AllHead.h"

namespace GameObjects {
	int G_BackGround::Graph_BackGround = 0;

	G_BackGround::G_BackGround(const std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager) {
		if (Graph_BackGround != 0)return;
		graphicManager = _graphicManager;
		Graph_BackGround = _graphicManager->LoadGraph(L"Materials/BackGround_00.png");
	}

	void G_BackGround::Update() {

	}

	void G_BackGround::DrawUpdate() {
		graphicManager->DrawOrder(GraphicSystem::DrawGraphicOrder(Graph_BackGround,Vector2(0,-200),DoubleVector2(0.8,0.8)));
	}
}