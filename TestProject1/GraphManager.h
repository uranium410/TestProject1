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
		std::shared_ptr<GraphicManager> GetGraphicManager();

	};

	///<summary>
	///<para>画像処理全般を行うクラス</para>
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