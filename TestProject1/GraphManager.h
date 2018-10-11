#pragma once

#include "AllHead.h"
#include <memory>

namespace GraphicSystem {
	class GraphicManager {
		std::shared_ptr<IWICImagingFactory>		pWICImagingFactory;
		std::shared_ptr<IWICBitmapDecoder>		pWICBitmapDecoder;
		std::shared_ptr<IWICBitmapFrameDecode>	pWICBitmapFrame;
		std::shared_ptr<IWICFormatConverter>	pFrameConverter;
		std::shared_ptr<ID2D1Bitmap> pBitmap;
	};
}