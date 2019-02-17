#pragma once
#include "AllHead.h"



namespace Collider {

	enum ImpactType {
		IT_S,
		IT_L
	};
	
	class DamageMessage {
	public:
		Vector2 knockVector;
		int Damage;
		int stunFlame;
		ImpactType impactType;
		DamageMessage(Vector2 _knockVector, int _Damage, int _stunFlame, ImpactType _inpaactType=IT_S) {
			knockVector = _knockVector;
			Damage = _Damage;
			stunFlame = _stunFlame;
			impactType = _inpaactType;
		}
		DamageMessage() {};
	};

	class Collision {
	public:
		bool* flag = NULL;
		Vector2 parentGamePosition;
		Vector2 localPosition;
		Vector2 size;

		bool Hit(Collision _oppCollision);
		Vector2 GetDrawPosition(int windowSizeX, int windowSizeY, int floorhight) {
			Vector2 result;
			result = Vector2(parentGamePosition.x + localPosition.x, windowSizeY-(parentGamePosition.y + localPosition.y + floorhight));
			return result;
		}
	};


	class AccCollision : public Collision {
	public:
		DamageMessage *dmReciever;
		AccCollision(Vector2 _parentGamePosition,
			Vector2 _localPosition,
			Vector2 _size,
			bool* _flag,
			DamageMessage *_dmReciever) {
			parentGamePosition = _parentGamePosition;
			localPosition = _localPosition;
			size = _size;
			flag = _flag;
			dmReciever = _dmReciever;
		}
	};

	class AtkCollision : public Collision {
	public:
		DamageMessage dmMessenger;
		AtkCollision(Vector2 _parentGamePosition,
			Vector2 _localPosition,
			Vector2 _size,
			bool* _flag,
			DamageMessage _dmMessenger) {
			parentGamePosition = _parentGamePosition;
			localPosition = _localPosition;
			size = _size;
			flag = _flag;
			dmMessenger = _dmMessenger;
		}
		void Check(AccCollision _oppCollision);
	};


}