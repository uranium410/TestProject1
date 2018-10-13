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
		std::shared_ptr<GraphicManager> GetGraphicManager();

	};

	///<summary>
	///<para>�摜�����S�ʂ��s���N���X</para>
	///</summary>
	class GraphicManager {
	private:
		std::shared_ptr<IWICImagingFactory>		pWICImagingFactory;
		std::shared_ptr<IWICBitmapDecoder>		pWICBitmapDecoder;
		std::shared_ptr<IWICBitmapFrameDecode>	pWICBitmapFrame;
		std::shared_ptr<IWICFormatConverter>	pFrameConverter;
		std::shared_ptr<ID2D1Bitmap>			pBitmap;
		ID2D1Factory							*d2dFactory;
	public:
		GraphicManager();
		~GraphicManager();
	};
}