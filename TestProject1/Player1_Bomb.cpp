#include "stdafx.h"
#include "AllHead.h"

namespace Effects {

	namespace LoadedGraphic {
		std::shared_ptr<AnimationMode> P1BombA;
	}

	bool Player1_Bomb::loaded = false;

	Player1_Bomb::Player1_Bomb(Vector2 _position, std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager, bool _right) {

		if (!loaded) {

			P1BombA = std::make_shared<AnimationMode>(6,
				new AnimationCell(_graphicManager, L"Materials/Effect/Bomb/Bomb_1.png", 4),
				new AnimationCell(_graphicManager, L"Materials/Effect/Bomb/Bomb_2.png", 4),
				new AnimationCell(_graphicManager, L"Materials/Effect/Bomb/Bomb_3.png", 7),
				new AnimationCell(_graphicManager, L"Materials/Effect/Bomb/Bomb_4.png", 4),
				new AnimationCell(_graphicManager, L"Materials/Effect/Bomb/Bomb_5.png", 8),
				new AnimationCell(_graphicManager, L"Materials/Effect/Bomb/Bomb_6.png", 8)
				);
			P1BombA->LoopMode = false;
			LoadedGraphic::P1BombA = P1BombA;
			loaded = true;
		}
		else {
			P1BombA = LoadedGraphic::P1BombA;
		}
		graphicManager = _graphicManager;
		right = _right;
		position = _position;
	}


	void Player1_Bomb::Update() {
	}


	void Player1_Bomb::DrawUpdate() {
		graphicManager->DrawOrder(GraphicSystem::DrawGraphicOrder(P1BombA->GH_to_draw(), position, DoubleVector2(1, 1), right));
		if (P1BombA->played) {
			P1BombA->Reset();
			destroyFlag = true;
		}
	}
}