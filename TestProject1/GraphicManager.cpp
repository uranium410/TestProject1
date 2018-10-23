#include "stdafx.h"
#include "AllHead.h"

namespace GraphicSystem {
	std::shared_ptr<GraphicManager> GraphFactory::GetGraphicManager(HWND hwnd) {
		if (graphicManager == 0)graphicManager = std::make_shared<GraphicManager>(hwnd);
		return graphicManager;
	}

	GraphicManager::GraphicManager(HWND hwnd) {
		/*d2dファクトリクラス取得*/
		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2dFactory);

		/*描画エリアの取得*/
		GetClientRect(hwnd, &rc);

		/*Direct2D用レンダーターゲット生成*/
		pRTCreate(hwnd);
		
		myHWND = hwnd;

		CoInitialize(NULL);

		//IWICImagingFactory生成
		hResult = ::CoCreateInstance(CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWICImagingFactory,
			reinterpret_cast<void **>(&pWICImagingFactory));

		//d2dWriteFactoryの生成
		DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&d2dWriteFactory));

		d2dWriteFactory->CreateTextFormat(
		L"メイリオ",
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			20.0f,
			L"ja-jp",
			&pFom);

		renderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::White),
			&blush);
	}

	GraphicManager::~GraphicManager() {
		if(pFormatConverter!= 0)pFormatConverter->Release();
		if(pWICBitmapFrame != 0)pWICBitmapFrame->Release();
		if(pWICBitmapDecoder!=0)pWICBitmapDecoder->Release();
		if(pWICImagingFactory!=0)pWICImagingFactory->Release();
		if (blush != 0)blush->Release();

		for (LoadedGraphicCell* temp : container) {
			if (temp != 0)delete temp;
		}

		CoUninitialize();

		d2dFactory->Release();
	}

	void GraphicManager::pRTCreate(HWND hwnd) {
		hResult = d2dFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(
				hwnd,
				D2D1::SizeU(
					rc.right - rc.left,
					rc.bottom - rc.top)
			),
			&renderTarget
		);
	}

	void GraphicManager::DrawUpdate() {
		renderTarget->BeginDraw();/*描画開始*/

		renderTarget->Clear(backgroundColor);/*描画のクリア*/

		while (drawOrders.size()>0) {
			DrawGraphicOrder order = drawOrders.front();
			drawOrders.pop();
			DrawOneGraphic(order.GetHandle(),order.GetPosition(),(float)order.GetGraphicScale().x,(float)order.GetGraphicScale().y);
		}
	}

	void GraphicManager::DrawUpdateEnd() {
		renderTarget->EndDraw();/*描画終了*/
	}

	void GraphicManager::DrawOneGraphic(int _GraphicHandle, D2D_POINT_2F _Position, float _SizeX, float _SizeY) {

		D2D_SIZE_F graphSize = container[_GraphicHandle]->GetSize();

		D2D_RECT_F oDrawRect = D2D1::RectF(
			_Position.x,
			_Position.y,
			_Position.x + graphSize.width * _SizeX,
			_Position.y + graphSize.height * _SizeY
		); 

		renderTarget->DrawBitmap(container[_GraphicHandle]->GetBitmap(), oDrawRect);
		return;
	}

	void GraphicManager::Drawtext(std::wstring _txt, D2D1_RECT_F _rect) {
		renderTarget->DrawTextW(_txt.c_str(), _txt.size(), pFom, _rect, blush);
	}

	int GraphicManager::LoadGraph(LPCWSTR _fileName) {

		ID2D1Bitmap* tempBitmap;

		//デコーダ生成
		hResult = pWICImagingFactory->CreateDecoderFromFilename(
			_fileName,
			NULL,
			GENERIC_READ,
			WICDecodeMetadataCacheOnLoad,
			&pWICBitmapDecoder);
		if (!SUCCEEDED(hResult))return -1;

		//ビットマップのフレーム取得
		hResult = pWICBitmapDecoder->GetFrame(0, &pWICBitmapFrame);
		if (!SUCCEEDED(hResult))return -1;

		//フォーマットコンバータ生成
		hResult = pWICImagingFactory->CreateFormatConverter(&pFormatConverter);
		if (!SUCCEEDED(hResult))return -1;

		hResult = pFormatConverter->Initialize(
			pWICBitmapFrame,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			1.0f,
			WICBitmapPaletteTypeMedianCut
		);
		if (!SUCCEEDED(hResult))return -1;

		//BitmapSource->Bitmap変換
		hResult = renderTarget->CreateBitmapFromWicBitmap(pFormatConverter, NULL, &tempBitmap);
		if (!SUCCEEDED(hResult))return -1;

		D2D1_SIZE_F tBitmapSize = tempBitmap->GetSize();

		container.emplace_back(new LoadedGraphicCell(tempBitmap,tBitmapSize));

		return container.size() - 1;
	}

	void GraphicManager::TestMethod() {

		int birthdayGraph = LoadGraph(L"party_birthdaycake_kao_tsukkomu.png");
		if (birthdayGraph == -1)return;

		renderTarget->BeginDraw();/*描画開始*/
		renderTarget->Clear(backgroundColor);/*描画のクリア*/

		//renderTarget->DrawBitmap(pBitmap, oDrawRect);
		DrawOneGraphic(birthdayGraph, D2D1::Point2F(0.0F, 0.0F), 0.5F, 0.5F);

		//pBitmap->Release();

		renderTarget->EndDraw();/*描画終了*/

		return;
	}

}