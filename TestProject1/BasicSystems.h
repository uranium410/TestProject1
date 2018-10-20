#pragma once
#include "AllHead.h"

namespace BasicSystem {
	class BSystem {
	private:
		GraphicSystem::GraphFactory graphFactory;
		std::shared_ptr<GraphicSystem::GraphicManager> graphicManager;

		GameSystem::SceneBase* nowScene = 0;

	public: 
		void AtFirst(HWND hwnd);
		void AtLoop();

		~BSystem() {
		}
	};
}