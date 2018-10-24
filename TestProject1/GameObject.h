#pragma once
#include "AllHead.h"

namespace GameObjects {
	class GameObject {
	public:
		virtual void Update()=0;
		virtual void DrawUpdate()=0;
	};

	class GameObjectPointer {
	public:
		GameObjectPointer(const std::shared_ptr<GameObject> _instance) {
			myGO = _instance;
		}
		std::shared_ptr<GameObject> myGO;
	};
}

#include "G_BackGround.h"