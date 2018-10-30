#include "stdafx.h"
#include "AllHead.h"

namespace LoadedGraphic {
	std::shared_ptr<AnimationMode> Player_1_StandingA;
	std::shared_ptr<AnimationMode> Player_1_NB1A;
}

namespace PlayerClasses {
	bool PlayerID_1::Loaded = false;

	PlayerID_1::PlayerID_1(std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager) {
		
		if (Loaded) {
			standingA = LoadedGraphic::Player_1_StandingA;
			NB1A = LoadedGraphic::Player_1_NB1A;
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
		standingA->LoopMode = true;
		NB1A = std::make_shared<AnimationMode>(5,
			new AnimationCell(_graphicManager, L"Materials/Character_1/NB1/NB1_1.png", 3),
			new AnimationCell(_graphicManager, L"Materials/Character_1/NB1/NB1_2.png", 2),
			new AnimationCell(_graphicManager, L"Materials/Character_1/NB1/NB1_3.png", 3),
			new AnimationCell(_graphicManager, L"Materials/Character_1/NB1/NB1_4.png", 3),
			new AnimationCell(_graphicManager, L"Materials/Character_1/NB1/NB1_5.png", 3));
		NB1A->LoopMode = false;

		LoadedGraphic::Player_1_StandingA = standingA;
		LoadedGraphic::Player_1_NB1A = NB1A;
		
		myState = BattleS::BS_Standing;
	}

	void PlayerID_1::Update(std::shared_ptr<BasicSystem::InputManager> _inputManager){
		if (_inputManager->inputData->P1_J.GetKeyDown()) {
			NB1A->Reset();
			myState = BattleS::BS_NB1;
		}
		if (NB1A->played) {
			myState = BattleS::BS_Standing;

		}
	}

	void PlayerID_1::GraphUpdate(std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager) {
		if(myState == BattleS::BS_Standing)_graphicManager->DrawOrder(GraphicSystem::DrawGraphicOrder(standingA->GH_to_draw(),Vector2(600,300),DoubleVector2(1,1)));
		if (myState == BattleS::BS_NB1)_graphicManager->DrawOrder(GraphicSystem::DrawGraphicOrder(NB1A->GH_to_draw(), Vector2(600, 300), DoubleVector2(1, 1)));
	}
}