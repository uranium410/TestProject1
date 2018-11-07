#pragma once
#include "AllHead.h"
namespace BattleS {
	enum Direction {
		Dir_Right,
		Dir_Left
	};
	enum BattleState {
		BS_Undecided,
		BS_Standing,
		BS_Junping,
		BS_Walking,
		BS_NB1
	};
}

namespace PlayerClasses {

	class PlayerClass {
		int WorldBottom = 500;
	public:
		int Bottom;
		int Right;
		int Left;
		Vector2 position;
		Vector2 movingVector;
		Vector2 JumpPowerFirst;
		Vector2 JumpPowerNow;
		bool sternness;
		bool onGround;
		int GravAccel = 10;
		int JumpAccel;
		Vector2 nowAccel;
		BattleS::BattleState myState;
		BattleS::Direction myDir;
		int HP;
		virtual void Update(std::shared_ptr<BasicSystem::InputManager> _inputManager) = 0;
		void  MoveUpdate();
		virtual void GraphUpdate(std::shared_ptr < GraphicSystem::GraphicManager> _graphicManager ) = 0;
	};

	class PlayerID_1 : public PlayerClass {
		static bool Loaded;

		void GraphLoad(std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager);

		std::shared_ptr<AnimationMode> standingA;
		std::shared_ptr<AnimationMode> NB1A;
		std::shared_ptr<AnimationMode> walkingA;
	public:
		PlayerID_1(std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager);
		void Update(std::shared_ptr<BasicSystem::InputManager> _inputManager);
		void GraphUpdate(std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager);
	};
}