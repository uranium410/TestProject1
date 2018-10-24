#pragma once
#include "AllHead.h"

namespace GameSystem {
	class SceneBase {
	public:
		std::shared_ptr<BasicSystem::InputManager> inputManager;

		std::shared_ptr<GraphicSystem::GraphicManager> graphicManager;

		std::vector<GameObjects::GameObjectPointer> gameObjects;

		void InputUpdate();
		void Update();
		void CollisionUpdate();
		void GraphUpdate();
		void GraphUpdateEnd();
	};

	class TitleScene : public SceneBase {
	public:
		TitleScene(const std::shared_ptr<GraphicSystem::GraphicManager> &GM) { graphicManager = GM; }

		void CollisionUpdate();
	};

	class BattleScene : public SceneBase {
	public:
		BattleScene(const std::shared_ptr<GraphicSystem::GraphicManager> &GM);
	};
}