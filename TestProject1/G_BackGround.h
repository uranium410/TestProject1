#pragma once
#include "AllHead.h"

namespace GameObjects {
	class G_BackGround : public GameObject {
		std::shared_ptr<GraphicSystem::GraphicManager> graphicManager;
	public:
		int Graph_BackGround;
		G_BackGround(const std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager);

		void Update();
		void DrawUpdate();
	};
}