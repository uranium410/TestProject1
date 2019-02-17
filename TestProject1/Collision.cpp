#include "stdafx.h"
#include "AllHead.h"

namespace Collider {
	bool Collision::Hit(Collision _oppCollision) {
		Vector2 col1Center = parentGamePosition + localPosition + Vector2(size.x/2,-size.y/2);
		Vector2 col2Center = _oppCollision.parentGamePosition + _oppCollision.localPosition + Vector2(_oppCollision.size.x/2,-_oppCollision.size.y/2);

		int distanceHight = abs(col1Center.y - col2Center.y);
		int distanceWidth = abs(col1Center.x - col2Center.x);

		if ((distanceHight < this->size.y / 2 + _oppCollision.size.y / 2) && (distanceWidth < this->size.x / 2 + _oppCollision.size.x / 2))
			return true;
		else return false;
	}
	
	void AtkCollision::Check(AccCollision _oppCollision) {
		if (!Hit(_oppCollision))return;
		*(_oppCollision.dmReciever) = dmMessenger;
		*(_oppCollision.flag) = true;
		*flag = true;
		size.y = 1;
		return;
	}


}