#include "stdafx.h"
#include "AllHead.h"
#include <memory>

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
	
	}

	GraphicManager::~GraphicManager() {
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

	void GraphicManager::TestMethod() {

		//�u���V����
		renderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Red),
			&blush);
		
		//�s�N�Z���t�H�[�}�b�g�֘A����
		//IWICImagingFactory����
		hResult = ::CoCreateInstance(CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWICImagingFactory,
			reinterpret_cast<void **>(&pWICImagingFactory));

		//�f�R�[�_����
		hResult = pWICImagingFactory->CreateDecoderFromFilename(
			L"aaaaa.bmp",
			NULL,
			GENERIC_READ,
			WICDecodeMetadataCacheOnLoad,
			&pWICBitmapDecoder);

		//�r�b�g�}�b�v�̃t���[���擾
		hResult = pWICBitmapDecoder->GetFrame(0, &pWICBitmapFrame);
		//�t�H�[�}�b�g�R���o�[�^����
		hResult = pWICImagingFactory->CreateFormatConverter(&pFormatConverter);
		hResult = pFormatConverter->Initialize(
			pWICBitmapFrame,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			1.0f,
			WICBitmapPaletteTypeMedianCut
			);

		//BitmapSource->Bitmap�ϊ�
		hResult = renderTarget->CreateBitmapFromWicBitmap(pFormatConverter, NULL, &pBitmap);
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
			tLeftTop.x + tBitmapSize.width,
			tLeftTop.y + tBitmapSize.height
		);

		renderTarget->BeginDraw();/*�`��J�n*/

		renderTarget->DrawBitmap(pBitmap, oDrawRect);

		renderTarget->DrawRectangle(
			D2D1::RectF(
				rc.left + 100.0f,
				rc.top + 100.0f,
				rc.right - 100.0f,
				rc.bottom - 100.0f),
			blush);

		pBitmap->Release();
		pFormatConverter->Release();
		pWICBitmapFrame->Release();
		pWICBitmapDecoder->Release();

		renderTarget->EndDraw();/*�`��I��*/

		return;
	}
}