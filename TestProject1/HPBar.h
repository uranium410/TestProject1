#pragma once
#include "AllHead.h"


namespace GameObjects {
	class HPBar {
		int maxHP;
		int nowHP;
		Vector2 position;
		Vector2 MaxSize;
		Vector2 size;
		bool revarse;
	public:
		HPBar(int _maxHP, Vector2 _position);
		HPBar() {};
		void DrawUpdate(int nowHP,bool _revarse);
		void Draw(std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager);
	};
}