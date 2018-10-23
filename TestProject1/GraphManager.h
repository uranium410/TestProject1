#pragma once

#include "AllHead.h"

///<summary>
///画像処理関係
///<para>クラス:</para>
///<para>class GraphFactory</para>
///<para>class GraphicManager</para>
///</summary>
namespace GraphicSystem {
	
	class LoadedGraphicCell;
	class DrawGraphicOrder;

	class GraphFactory;
	class GraphicManager;	

	
	class LoadedGraphicCell {
	private:
		ID2D1Bitmap*	bitmap=0;
		D2D1_SIZE_F		size;

	public:
		LoadedGraphicCell(ID2D1Bitmap* _bitmap, D2D1_SIZE_F _size) {
			bitmap = _bitmap;
			size = _size;
		}
		~LoadedGraphicCell() {
			bitmap->Release();
		}

		ID2D1Bitmap* GetBitmap() { return bitmap; }
		D2D1_SIZE_F GetSize() { return size; }
	};


	class DrawGraphicOrder {
	private:
		int graphicHandle;
		Vector2 position;
		DoubleVector2 graphicScale;
	public:
		DrawGraphicOrder(int _GH, Vector2 _pos, DoubleVector2 _scale) {
			graphicHandle = _GH;
			position = _pos;
			graphicScale = _scale;
		}
		int GetHandle() { return graphicHandle; }
		D2D_POINT_2F GetPosition() { return D2D1::Point2F((float)position.x, (float)position.y); }
		DoubleVector2 GetGraphicScale() { return graphicScale; }
	};


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

		std::vector<LoadedGraphicCell*> container;
		std::queue<DrawGraphicOrder> drawOrders;

		/*bitmap形式処理系*/
		IWICImagingFactory*		pWICImagingFactory = 0;
		IWICBitmapDecoder*		pWICBitmapDecoder  = 0;
		IWICBitmapFrameDecode*	pWICBitmapFrame    = 0;
		IWICFormatConverter*	pFormatConverter   = 0;
		ID2D1Bitmap*			pBitmap			   = 0;

		/*Direct2D関連*/
		ID2D1Factory							*d2dFactory;
		ID2D1HwndRenderTarget					*renderTarget;
		RECT									rc;
		D2D1_RENDER_TARGET_PROPERTIES			oRenderTargetProperties;
		ID2D1SolidColorBrush					*blush;

		/*文字描画系*/
		IDWriteFactory *d2dWriteFactory;
		IDWriteTextFormat *pFom = NULL;

		/*メソッド*/
		void DrawOneGraphic(int _GraphicHandle, D2D_POINT_2F _Position, float _SizeX, float _SizeY);
	public:
		GraphicManager(HWND hwnd);
		~GraphicManager();
		void TestMethod();
		void pRTCreate(HWND hwnd);
		void DrawUpdate();
		void DrawUpdateEnd();
		void Drawtext(std::wstring _txt, D2D1_RECT_F _rect);
		///<summary>
		///<para>画像をロードして、グラフィックハンドルを返す</para>
		///<para>失敗すれば-1が返される</para>
		///<para>_fileName ... 画像ファイル名</para>
		///</summary>
		int LoadGraph(LPCWSTR _fileName);
	};

}