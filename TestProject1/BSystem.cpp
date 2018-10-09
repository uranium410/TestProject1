#include "stdafx.h"
#include "AllHead.h"

namespace BasicSystem {

	void BSystem::AtFirst(HWND hwnd) {
		//D3D11CreateDevice(NULL,D3D_DRIVER_TYPE_HARDWARE,NULL,);
		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2d);

		//Obtain the size of the drawing area
		GetClientRect(hwnd, &rc);

		//Create a Direct2D render target
		pRTCreate(hwnd);

		//Create Brush
		pRT->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Black),
			&pBlackBrush
		);

		pRT->BeginDraw();

		pRT->DrawRectangle(
			D2D1::RectF(
				rc.left + 100.0f,
				rc.top + 100.0f,
				rc.right - 100.0f,
				rc.bottom - 100.0f),
			pBlackBrush);

		HRESULT hr = pRT->EndDraw();
	}

	void BSystem::AtLoop() {

	}

	void BSystem::pRTCreate(HWND hwnd) {
		HRESULT hr = d2d->CreateHwndRenderTarget(
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