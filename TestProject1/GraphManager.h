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
	
	class GraphFactory;
	class GraphicManager;
	class LoadedGraphicContainer;
	class LoadedGraphicCell;
	
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
		HWND					myHWND;				//ウィンドウハンドル
		D2D1_COLOR_F			backgroundColor = { 0.0F,0.0F,1.0F,1.0F }; //背景色

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
		void DrawUpdate();
		///<summary>
		///<para>画像をロードして、グラフィックハンドルを返す</para>
		///<para>_fileName ... 画像ファイル名</para>
		///</summary>
		int LoadGraph(LPCWSTR _fileName);
		GraphicManager(HWND hwnd);
		~GraphicManager();
	};

	class LoadedGraphicContainer {
	private:
		std::vector<LoadedGraphicCell*> container;
	public:
		int SetLoadedGraphicCell(ID2D1Bitmap* _bitmap, D2D1_SIZE_F _size, int _handle); /*読み込んだ画像データの追加*/
		LoadedGraphicContainer() { container.push_back(NULL); return; } /*コンストラクタ*/
		~LoadedGraphicContainer() { 
			for (LoadedGraphicCell* temp : container) {
				if (temp != NULL)free(temp);
			} 
		}/*デストラクタ*/
	};

	class LoadedGraphicCell {
	private:
		ID2D1Bitmap*	bitmap;
		D2D1_SIZE_F		size;

	public:
		LoadedGraphicCell(ID2D1Bitmap* _bitmap, D2D1_SIZE_F _size) {
			bitmap =_bitmap;
			size =	_size;
		 }
		~LoadedGraphicCell() {
			bitmap->Release();
		}

		ID2D1Bitmap* GetBitmap(){ return bitmap; }
		D2D1_SIZE_F GetSize() { return size; }
	};
}