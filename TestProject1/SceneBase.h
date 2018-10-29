#pragma once
#include "AllHead.h"

namespace GameSystem {
	class SceneBase {
	public:
		std::shared_ptr<BasicSystem::InputManager> inputManager;

		std::shared_ptr<GraphicSystem::GraphicManager> graphicManager;

		std::vector<GameObjects::GameObjectPointer> gameObjects_BackGround;
		std::vector<GameObjects::GameObjectPointer> gameObjects;
		std::vector<GameObjects::GameObjectPointer> gameObjects_UI;

		void InputUpdate();
		virtual void Update()=0;
		void CollisionUpdate();
		virtual void GraphUpdate(std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager)=0;
		void GraphUpdateEnd();
	};

	class TitleScene : public SceneBase {
	public:
		TitleScene(const std::shared_ptr<GraphicSystem::GraphicManager> &GM) { graphicManager = GM; }

		void CollisionUpdate();
	};

	class BattleScene : public SceneBase {
		std::shared_ptr<PlayerClasses::PlayerClass> P1=0;
		std::shared_ptr<PlayerClasses::PlayerClass> P2=0;
	public:
		void Update();
		void GraphUpdate(std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager);
		BattleScene(const std::shared_ptr<GraphicSystem::GraphicManager> &GM);
	};
}