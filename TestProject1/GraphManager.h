#pragma once

#include "AllHead.h"
#include <memory>

///<summary>
///�摜�����֌W
///<para>�N���X:</para>
///<para>class GraphFactory</para>
///<para>class GraphicManager</para>
///</summary>
namespace GraphicSystem {
	
	class GraphicManager;
	
	///<summary>
	///<para>GraphicManager�֘A�̃t�@�N�g���N���X</para>
	///</summary>
	class GraphFactory {
	private:
		std::shared_ptr<GraphicManager> graphicManager;
	public:
		//�R���X�g���N�^
		GraphFactory() {
			//��������܂ł�0�����Ƃ�
			graphicManager = 0;
		}

		///<summary>
		///<para>GraphicManager�擾</para>
		///</summary>
		std::shared_ptr<GraphicManager> GetGraphicManager(HWND hwnd);

	};




	///<summary>
	///<para>�摜�����S�ʂ��s���N���X</para>
	///</summary>
	class GraphicManager {
	private:
		HRESULT					hResult;			//�`��̐������f
		/*bitmap�`�������n*/
		IWICImagingFactory*		pWICImagingFactory;
		IWICBitmapDecoder*		pWICBitmapDecoder;
		IWICBitmapFrameDecode*	pWICBitmapFrame;
		IWICFormatConverter*	pFormatConverter;
		ID2D1Bitmap*			pBitmap;
		/*Direct2D�֘A*/
		ID2D1Factory							*d2dFactory;
		ID2D1HwndRenderTarget					*renderTarget;
		RECT									rc;
		D2D1_RENDER_TARGET_PROPERTIES			oRenderTargetProperties;
		ID2D1SolidColorBrush					*blush;
		/*���\�b�h*/
		void pRTCreate(HWND hwnd);
	public:
		void TestMethod();
		GraphicManager(HWND hwnd);
		~GraphicManager();
	};
}