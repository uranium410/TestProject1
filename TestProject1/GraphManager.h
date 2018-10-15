#pragma once

#include "AllHead.h"
#include <memory>

///<summary>
///画像処理関係
///<para>クラス:</para>
///<para>class GraphFactory</para>
///<para>class GraphicManager</para>
///</summary>
namespace GraphicSystem {
	
	class GraphicManager;
	
	///<summary>
	///<para>GraphicManager関連のファクトリクラス</para>
	///</summary>
	class GraphFactory {
	private:
		std::shared_ptr<GraphicManager> graphicManager;
	public:
		//コンストラクタ
		GraphFactory() {
			//生成するまでは0を入れとく
			graphicManager = 0;
		}

		///<summary>
		///<para>GraphicManager取得</para>
		///</summary>
		std::shared_ptr<GraphicManager> GetGraphicManager(HWND hwnd);

	};




	///<summary>
	///<para>画像処理全般を行うクラス</para>
	///</summary>
	class GraphicManager {
	private:
		HRESULT					hResult;			//描画の成功判断
		/*bitmap形式処理系*/
		IWICImagingFactory*		pWICImagingFactory;
		IWICBitmapDecoder*		pWICBitmapDecoder;
		IWICBitmapFrameDecode*	pWICBitmapFrame;
		IWICFormatConverter*	pFormatConverter;
		ID2D1Bitmap*			pBitmap;
		/*Direct2D関連*/
		ID2D1Factory							*d2dFactory;
		ID2D1HwndRenderTarget					*renderTarget;
		RECT									rc;
		D2D1_RENDER_TARGET_PROPERTIES			oRenderTargetProperties;
		ID2D1SolidColorBrush					*blush;
		/*メソッド*/
		void pRTCreate(HWND hwnd);
	public:
		void TestMethod();
		GraphicManager(HWND hwnd);
		~GraphicManager();
	};
}