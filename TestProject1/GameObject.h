#pragma once
#include "AllHead.h"

namespace GameObjects {
	class GameObject {
	public:
		std::shared_ptr<GraphicSystem::GraphicManager> graphicManager;
		bool destroyFlag = false;
		virtual void Update()=0;
		virtual void DrawUpdate()=0;
	};
}
