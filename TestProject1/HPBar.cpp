#include "stdafx.h"
#include "AllHead.h"


namespace GameObjects {
	HPBar::HPBar(int _maxHP, Vector2 _position){
		maxHP = _maxHP;
		position = _position;
		MaxSize = Vector2(400,30);
	}

	void HPBar::DrawUpdate(int nowHP,bool _revarse) {
		if (nowHP < 0)nowHP = 0;
		revarse = _revarse;
		size = Vector2(MaxSize.x * nowHP/maxHP, MaxSize.y);
	}

	void HPBar::Draw(std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager) {
		Vector2 drawPosition=position;
		if (revarse) {
			drawPosition.x += MaxSize.x - size.x;
		}
		_graphicManager->DrawRect(position+Vector2(-2,-2), MaxSize+Vector2(4,4), GraphicSystem::WHITE, true);
		_graphicManager->DrawRect(position, MaxSize, GraphicSystem::RED, true);
		_graphicManager->DrawRect(drawPosition, size, GraphicSystem::GREEN, true);
	}
}