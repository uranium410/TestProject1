#include "stdafx.h"
#include "AllHead.h"
#include <memory>

namespace GraphicSystem {
	std::shared_ptr<GraphicManager> GraphFactory::GetGraphicManager() {
			if (graphicManager == 0)graphicManager = std::make_shared<GraphicManager>();
	}

	GraphicManager::GraphicManager() {
		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2dFactory);
	}

	GraphicManager::~GraphicManager() {
		d2dFactory->Release();
	}
}