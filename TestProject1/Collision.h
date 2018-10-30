#pragma once
#include "AllHead.h"



namespace Collider {
	enum CollisionType {
		ColType_Attack,
		ColType_Recieve
	};

	class DamageMessage {
		Vector2 knockVector;
		int Damage;

	};

	class Collision {
		CollisionType colType;
		Vector2 position;
		Vector2 size;
		std::shared_ptr<bool> flag;
		DamageMessage DM;
	public:
		Collision(CollisionType _colType,Vector2 _position, Vector2 _size, std::shared_ptr<bool> _flag, DamageMessage _DM);
		bool Hit(Collision _opponent);
	};
}