#pragma once
#include "AllHead.h"

namespace BasicSystem {
	class BSystem {
	private:
			ID2D1Factory *d2d=0;			//Direct2D
			ID2D1HwndRenderTarget *pRT=0;	//レンダーターゲット
			RECT rc;					//描画エリア
			ID2D1SolidColorBrush* pBlackBrush = 0;

	public: void AtFirst(HWND hwnd);
			void AtLoop();

	private: void pRTCreate(HWND hwnd);

	public:	~BSystem() {
		
		pRT->Release();
		pBlackBrush->Release();
		d2d->Release();
			}
	};
}