#pragma once
#include "AllHead.h"

namespace GameSystem {
	class SceneBase {
	public:

		std::shared_ptr<GraphicSystem::GraphicManager> graphicManager;

		void InputUpdate();
		virtual void Update()=0;
		virtual void CollisionUpdate()=0;
		void GraphUpdate();
	};

	class TitleScene : public SceneBase {
	public:
		TitleScene(const std::shared_ptr<GraphicSystem::GraphicManager> &GM) { graphicManager = GM; }

		void Update();
		void CollisionUpdate();
	};

	class BattleScene : public SceneBase {
	public:
		BattleScene(const std::shared_ptr<GraphicSystem::GraphicManager> &GM) { graphicManager = GM; }

		void Update();
		void CollisionUpdate();
	};
}