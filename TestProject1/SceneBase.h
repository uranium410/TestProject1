#pragma once
#include "AllHead.h"

namespace GameSystem {

	enum SceneID {
		Title,
		Battle
	};

	class SceneBase {
	public:
		std::shared_ptr<BasicSystem::InputManager> inputManager;

		std::shared_ptr<GraphicSystem::GraphicManager> graphicManager;

		std::shared_ptr<PlayerClasses::PlayerClass> P1 = 0;
		std::shared_ptr<PlayerClasses::PlayerClass> P2 = 0;

		std::vector<std::shared_ptr<GameObjects::GameObject>> gameObjects_BackGround;
		std::vector<std::shared_ptr<GameObjects::GameObject>> gameObjects_Effect;

		void InputUpdate();
		virtual void Update()=0;
		void CollisionUpdate();
		virtual void GraphUpdate(std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager)=0;
		void GraphUpdateEnd();
		virtual void CorrectGraphUpdate() {};

		bool sceneChange = false;
		SceneID nextSceneid;
	};

	class TitleScene : public SceneBase {
	public:
		std::shared_ptr<AnimationMode> TitleBuck;
		TitleScene(const std::shared_ptr<GraphicSystem::GraphicManager> &GM);
		void Update();
		void GraphUpdate(std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager);
		void CorrectGraphUpdate();

		int pushButtonCounter=0;
		int fadeoutCounter=100;
	};

	class BattleScene : public SceneBase {
		//std::shared_ptr<BasicSystem::SoundSystem::CWaveFile> BGM;
		int BGMID;

		int fadeinCounter = 30;
		bool slowMode = false;
		bool finish = false;
		bool returnflag = false;
		int slowCounter = 20;
		int pushButtonCounter=0;

		int fadeoutCounter = 100;
	public:
		GameObjects::HPBar HPBar1;
		GameObjects::HPBar HPBar2;
		void Update();
		void GraphUpdate(std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager);
		BattleScene(const std::shared_ptr<GraphicSystem::GraphicManager> &GM);
		void CorrectGraphUpdate();

	};
	
}