#include "stdafx.h"
#include "AllHead.h"
//#include <iostream>

namespace BasicSystem {

	void BSystem::AtFirst(HWND hwnd) {
		
		graphicManager = graphFactory.GetGraphicManager(hwnd);
		graphicManager->TestMethod();

	}

	void BSystem::AtLoop() {

	}

	void BSystem::pRTCreate(HWND hwnd) {
			hr = d2d->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(
				hwnd,
				D2D1::SizeU(
					rc.right - rc.left,
					rc.bottom - rc.top)
			),
			&pRT
		);
		
	}
}