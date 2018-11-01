#pragma once
#include "AllHead.h"
namespace BattleS {
	enum Direction {
		Dir_Right,
		Dir_Left
	};
	enum BattleState {
		BS_Standing,
		BS_Junping,
		BS_Walking,
		BS_NB1
	};
}

namespace PlayerClasses {

	class PlayerClass {
	public:
		Vector2 movingVector;
		BattleS::BattleState myState;
		BattleS::Direction myDir;
		int HP;
		virtual void Update(std::shared_ptr<BasicSystem::InputManager> _inputManager) = 0;
		virtual void GraphUpdate(std::shared_ptr < GraphicSystem::GraphicManager> _graphicManager ) = 0;
	};

	class PlayerID_1 : public PlayerClass {
		static bool Loaded;

		std::shared_ptr<AnimationMode> standingA;
		std::shared_ptr<AnimationMode> NB1A;
		std::shared_ptr<AnimationMode> walkingA;
	public:
		PlayerID_1(std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager);
		void Update(std::shared_ptr<BasicSystem::InputManager> _inputManager);
		void GraphUpdate(std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager);
	};
}