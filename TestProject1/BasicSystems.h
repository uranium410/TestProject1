#pragma once
#include "AllHead.h"

namespace BasicSystem {
	class BSystem {
	private:
			ID2D1Factory *d2d=0;			//Direct2Dファクトリクラス
			ID2D1HwndRenderTarget *pRT=0;	//レンダーターゲット
			RECT rc;						//描画エリア
			ID2D1SolidColorBrush* pBlackBrush = 0;
			HRESULT hr;						//描画の成功判断
			D2D1_RENDER_TARGET_PROPERTIES oRenderTargetProperties;
			/*ピクセルフォーマット関連*/
			IWICImagingFactory* pWICImagingFactory = 0;
			IWICBitmapDecoder* pWICBitmapDecoder = 0;
			IWICBitmapFrameDecode* pWICBitmapFrame = 0;
			IWICFormatConverter* pFormatConverter = 0;
			ID2D1Bitmap* pBitmap = 0;

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