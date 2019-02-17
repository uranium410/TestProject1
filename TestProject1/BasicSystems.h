#pragma once
#include "AllHead.h"

namespace BasicSystem {
	class BSystem {
	private:
		bool DebugMode = false;

		GraphicSystem::GraphFactory graphFactory;
		std::shared_ptr<GraphicSystem::GraphicManager> graphicManager;

		GameSystem::SceneBase* nowScene = 0;

	public:
		std::shared_ptr<BasicSystem::InputManager> inputManager;

		void AtFirst(HINSTANCE _hinst,HWND _hwnd);
		void AtLoop();

		void DebugDisplay();
		~BSystem();
	};
}