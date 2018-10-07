#include "stdafx.h"
#include "AllHead.h"

namespace BasicSystem{

	void AtFirst(HWND hwnd) {
		//D3D11CreateDevice(NULL,D3D_DRIVER_TYPE_HARDWARE,NULL,);
		ID2D1Factory *d2d;
		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2d);

		//Obtain the size of the drawing area.
		RECT rc;
		GetClientRect(hwnd, &rc);
	}
}