#include "stdafx.h"
#include "AllHead.h"

namespace GraphicSystem {
	std::shared_ptr<GraphicManager> GraphFactory::GetGraphicManager(HWND hwnd) {
		if (graphicManager == 0)graphicManager = std::make_shared<GraphicManager>(hwnd);
		return graphicManager;
	}

	GraphicManager::GraphicManager(HWND hwnd) {
		/*d2d�t�@�N�g���N���X�擾*/
		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2dFactory);

		/*�`��G���A�̎擾*/
		GetClientRect(hwnd, &rc);

		/*Direct2D�p�����_�[�^�[�Q�b�g����*/
		pRTCreate(hwnd);
		myHWND = hwnd;

		CoInitialize(NULL);

		//IWICImagingFactory����
		hResult = ::CoCreateInstance(CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWICImagingFactory,
			reinterpret_cast<void **>(&pWICImagingFactory));
	}

	GraphicManager::~GraphicManager() {
		if(pFormatConverter!= 0)pFormatConverter->Release();
		if(pWICBitmapFrame != 0)pWICBitmapFrame->Release();
		if(pWICBitmapDecoder!=0)pWICBitmapDecoder->Release();
		if(pWICImagingFactory!=0)pWICImagingFactory->Release();

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
		renderTarget->BeginDraw();/*�`��J�n*/
		renderTarget->EndDraw();/*�`��I��*/
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

	int GraphicManager::LoadGraph(LPCWSTR _fileName) {

		ID2D1Bitmap* tempBitmap;

		//�f�R�[�_����
		hResult = pWICImagingFactory->CreateDecoderFromFilename(
			_fileName,
			NULL,
			GENERIC_READ,
			WICDecodeMetadataCacheOnLoad,
			&pWICBitmapDecoder);
		if (!SUCCEEDED(hResult))return -1;

		//�r�b�g�}�b�v�̃t���[���擾
		hResult = pWICBitmapDecoder->GetFrame(0, &pWICBitmapFrame);
		if (!SUCCEEDED(hResult))return -1;

		//�t�H�[�}�b�g�R���o�[�^����
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

		//BitmapSource->Bitmap�ϊ�
		hResult = renderTarget->CreateBitmapFromWicBitmap(pFormatConverter, NULL, &tempBitmap);
		if (!SUCCEEDED(hResult))return -1;

		D2D1_SIZE_F tBitmapSize = tempBitmap->GetSize();

		container.emplace_back(new LoadedGraphicCell(tempBitmap,tBitmapSize));

		return container.size() - 1;
	}

	void GraphicManager::TestMethod() {

		int birthdayGraph = LoadGraph(L"party_birthdaycake_kao_tsukkomu.png");
		if (birthdayGraph == -1)return;

		renderTarget->BeginDraw();/*�`��J�n*/
		renderTarget->Clear(backgroundColor);/*�`��̃N���A*/

		//renderTarget->DrawBitmap(pBitmap, oDrawRect);
		DrawOneGraphic(birthdayGraph, D2D1::Point2F(0.0F, 0.0F), 0.5F, 0.5F);

		//pBitmap->Release();

		renderTarget->EndDraw();/*�`��I��*/

		return;
	}


}