#include "stdafx.h"
#include "AllHead.h"
#include <memory>

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

		//GraphicContainer生成
		container = std::make_shared<LoadedGraphicContainer>();
	}

	GraphicManager::~GraphicManager() {
		pFormatConverter->Release();
		pWICBitmapFrame->Release();
		pWICBitmapDecoder->Release();
		pWICImagingFactory->Release();

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
		renderTarget->EndDraw();/*描画終了*/
	}

	bool GraphicManager::LoadGraph(LPCWSTR _fileName) {

		ID2D1Bitmap* tempBitmap;

		//デコーダ生成
		hResult = pWICImagingFactory->CreateDecoderFromFilename(
			_fileName,
			NULL,
			GENERIC_READ,
			WICDecodeMetadataCacheOnLoad,
			&pWICBitmapDecoder);
		if (SUCCEEDED(hResult))return false;

		//ビットマップのフレーム取得
		hResult = pWICBitmapDecoder->GetFrame(0, &pWICBitmapFrame);
		if (SUCCEEDED(hResult))return false;

		//フォーマットコンバータ生成
		hResult = pWICImagingFactory->CreateFormatConverter(&pFormatConverter);
		if (SUCCEEDED(hResult))return false;

		hResult = pFormatConverter->Initialize(
			pWICBitmapFrame,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			1.0f,
			WICBitmapPaletteTypeMedianCut
		);
		if (SUCCEEDED(hResult))return false;

		//BitmapSource->Bitmap変換
		hResult = renderTarget->CreateBitmapFromWicBitmap(pFormatConverter, NULL, &tempBitmap);
		if (SUCCEEDED(hResult))return false;

		D2D1_SIZE_F tBitmapSize = pBitmap->GetSize();


		return true;
	}

	void GraphicManager::DrawOneGraphic() {
		return;
	}

	int LoadedGraphicContainer::SetLoadedGraphicCell(ID2D1Bitmap* _bitmap, D2D1_SIZE_F _size, int _handle) {
		container.push_back(new LoadedGraphicCell(_bitmap, _size));
		return container.size() - 1;
	}


	void GraphicManager::TestMethod() {

		/*
		//ブラシ生成
		renderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Red),
			&blush);

		//ピクセルフォーマット関連生成
		//デコーダ生成
		hResult = pWICImagingFactory->CreateDecoderFromFilename(
			L"party_birthdaycake_kao_tsukkomu.png",
			NULL,
			GENERIC_READ,
			WICDecodeMetadataCacheOnLoad,
			&pWICBitmapDecoder);

		//ビットマップのフレーム取得
		hResult = pWICBitmapDecoder->GetFrame(0, &pWICBitmapFrame);
		//フォーマットコンバータ生成
		hResult = pWICImagingFactory->CreateFormatConverter(&pFormatConverter);
		hResult = pFormatConverter->Initialize(
			pWICBitmapFrame,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			1.0f,
			WICBitmapPaletteTypeMedianCut
		);

		//BitmapSource->Bitmap変換
		hResult = renderTarget->CreateBitmapFromWicBitmap(pFormatConverter, NULL, &pBitmap);

		*/
		D2D1_SIZE_F tBitmapSize = pBitmap->GetSize();
		
		D2D1_SIZE_F oTargetSize = renderTarget->GetSize();
		

		D2D_POINT_2F tLeftTop = D2D1::Point2F(
			(oTargetSize.width - tBitmapSize.width) / 2,
			(oTargetSize.height - tBitmapSize.height) / 2
		);
		tLeftTop = D2D1::Point2F(0.0F, 0.0F);
		

		D2D_RECT_F oDrawRect = D2D1::RectF(
			tLeftTop.x,
			tLeftTop.y,
			tLeftTop.x + tBitmapSize.width / 2,
			tLeftTop.y + tBitmapSize.height / 2
		);
		renderTarget->BeginDraw();/*描画開始*/
		renderTarget->Clear(backgroundColor);/*描画のクリア*/

		renderTarget->DrawBitmap(pBitmap, oDrawRect);

		pBitmap->Release();

		renderTarget->EndDraw();/*描画終了*/

		return;
	}

}