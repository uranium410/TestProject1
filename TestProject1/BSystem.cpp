#include "stdafx.h"
#include "AllHead.h"

namespace BasicSystem {

	void BSystem::AtFirst(HWND hwnd) {
		//D3D11CreateDevice(NULL,D3D_DRIVER_TYPE_HARDWARE,NULL,);
		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2d);

		//Obtain the size of the drawing area
		GetClientRect(hwnd, &rc);

		//Create a Direct2D render target
		pRTCreate(hwnd);

		//Create Brush
		pRT->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Red),
			&pBlackBrush
		);

		//�s�N�Z���t�H�[�}�b�g�֘A����
		//IWICImagingFactory����
		hr = ::CoCreateInstance(CLSID_WICImagingFactory,
								NULL,
								CLSCTX_INPROC_SERVER,
								IID_IWICImagingFactory,
								reinterpret_cast<void **>(&pWICImagingFactory));
		//�f�R�[�_����
		hr = pWICImagingFactory->CreateDecoderFromFilename(
			L"aaaaa.bmp",
			NULL,
			GENERIC_READ,
			WICDecodeMetadataCacheOnLoad,
			&pWICBitmapDecoder);
		//�r�b�g�}�b�v�̃t���[���擾
		hr = pWICBitmapDecoder->GetFrame(0, &pWICBitmapFrame);
		//�t�H�[�}�b�g�R���o�[�^����
		hr = pWICImagingFactory->CreateFormatConverter(&pFormatConverter);
		hr = pFormatConverter->Initialize(
			pWICBitmapFrame,				//BitmapSource
			GUID_WICPixelFormat32bppPBGRA,	//�s�N�Z���t�H�[�}�b�g
			WICBitmapDitherTypeNone,		//BitmapDitherType
			NULL,							//�o���b�g
			1.0f,							//���ߗ�
			WICBitmapPaletteTypeMedianCut	//�o���b�g�^�C�v
			);
		//BitmapSource -> Bitmap�ϊ�
		hr = pRT->CreateBitmapFromWicBitmap(pFormatConverter, NULL, &pBitmap);
		D2D1_SIZE_F tBitmapSize = pBitmap->GetSize();

		D2D1_SIZE_F oTargetSize = pRT->GetSize();

		D2D_POINT_2F tLeftTop = D2D1::Point2F(
			(oTargetSize.width - tBitmapSize.width) / 2,
			(oTargetSize.height - tBitmapSize.height / 2)
		);
		tLeftTop = D2D1::Point2F(0.0F,0.0F);

		D2D_RECT_F oDrawRect = D2D1::RectF(
			tLeftTop.x,
			tLeftTop.y,
			tLeftTop.x + tBitmapSize.width,
			tLeftTop.y + tBitmapSize.height
		);

		pRT->BeginDraw();

		pRT->DrawBitmap(pBitmap, oDrawRect);


		pRT->DrawRectangle(
			D2D1::RectF(
				rc.left + 100.0f,
				rc.top + 100.0f,
				rc.right - 100.0f,
				rc.bottom - 100.0f),
			pBlackBrush);

		//�`��I�����ɐF�X�j��
		pBitmap->Release();
		pFormatConverter->Release();
		pWICBitmapFrame->Release();
		pWICBitmapDecoder->Release();

		hr = pRT->EndDraw();
		//�`�掸�s��
		if (FAILED(hr))return;
	}

	void BSystem::AtLoop() {

	}

	void BSystem::pRTCreate(HWND hwnd) {
			hr = d2d->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(
				hwnd,
				D2D1::SizeU(
					rc.right - rc.left,
					rc.bottom - rc.top)
			),
			&pRT
		);
	}
}