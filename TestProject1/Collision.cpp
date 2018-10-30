#include "stdafx.h"
#include "AllHead.h"

namespace Collider {
	Collision::Collision(CollisionType _colType,Vector2 _position, Vector2 _size, std::shared_ptr<bool> _flag, DamageMessage _DM) {
		colType = _colType;
		position = _position;
		size = _size;
		flag = _flag;
		DM = _DM;
	}

	bool insidePoint(Vector2 _point, Vector2 _rectPos, Vector2 _size) {
		if (_point.x < _rectPos.x)return false;
		if (_point.x > _rectPos.x + _size.x)return false;
		if (_point.y < _rectPos.y)return false;
		if (_point.y > _rectPos.y + _size.y)return false;

		return true;
	}

	bool Collision::Hit(Collision _opponent) {
		Vector2 targetPos = position;
		if (position.x + size.x < _opponent.position.x)return false;
		if (position.x > _opponent.position.x + _opponent.size.x)return false;
		if (position.y + size.y < _opponent.position.y)return false;
		if (position.y > _opponent.position.y + _opponent.size.y)return false;

		if (insidePoint(targetPos, _opponent.position, _opponent.size))return true;
		targetPos = position + Vector2(size.x,0);
		if (insidePoint(targetPos, _opponent.position, _opponent.size))return true;
		targetPos = position + Vector2(0,size.y);
		if (insidePoint(targetPos, _opponent.position, _opponent.size))return true;
		targetPos = position + size;
		if (insidePoint(targetPos, _opponent.position, _opponent.size))return true;

		if (_opponent.Hit(*this))return true;

		return false;
	}

}