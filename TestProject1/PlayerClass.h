#pragma once
#include "AllHead.h"

namespace PlayerClasses {

	class PlayerClass {
	public:
		virtual void Update() = 0;
		virtual void GraphUpdate(std::shared_ptr < GraphicSystem::GraphicManager> _graphicManager ) = 0;
	};

	class PlayerID_1 : public PlayerClass {
		static bool Loaded;

		std::shared_ptr<AnimationMode> standingA;
	public:
		PlayerID_1(std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager);
		void Update();
		void GraphUpdate(std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager);
	};
}