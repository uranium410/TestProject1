#include "stdafx.h"
#include "AllHead.h"

namespace PlayerClasses {
	bool PlayerID_1::Loaded = false;

	PlayerID_1::PlayerID_1(std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager) {
		
		if (Loaded) {
			//standingA = LoadedGraphic::Player_1_StandingA;
			return;
		}

		standingA = std::make_shared<AnimationMode>(8,
			new AnimationCell(_graphicManager, L"Materials/Character_1/Standing/S_1.png", 5),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Standing/S_2.png", 5),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Standing/S_3.png", 5),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Standing/S_4.png", 5),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Standing/S_5.png", 5),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Standing/S_6.png", 5),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Standing/S_7.png", 5),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Standing/S_8.png", 5));

		//LoadedGraphic::Player_1_StandingA = standingA;
		
	}

	void PlayerID_1::Update(){

	}

	void PlayerID_1::GraphUpdate(std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager) {
		_graphicManager->DrawOrder(GraphicSystem::DrawGraphicOrder(standingA->GH_to_draw(),Vector2(600,300),DoubleVector2(3,3)));
	}
}