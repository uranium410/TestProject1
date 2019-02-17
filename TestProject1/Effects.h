#pragma once
#include "AllHead.h"

namespace Effects {
	class DamageEffect_01 : public GameObjects::GameObject {
		std::shared_ptr<AnimationMode> graph;
		Vector2 position;
		static bool loaded;
		static int sound1;
		static int sound2;
		static bool sound1Played;
	public:
		int flame = 20;
		DamageEffect_01(Vector2 _position, std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager);

		void Update();
		void DrawUpdate();
	};

	class Player1_Bomb : public GameObjects::GameObject {
		std::shared_ptr<AnimationMode> P1BombA;
		static bool loaded;
		bool right;
		Vector2 position;
	public:
		Player1_Bomb(Vector2 _position, std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager, bool _right);

		void Update();
		void DrawUpdate();
	};
}