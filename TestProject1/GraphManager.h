#pragma once

#include "AllHead.h"

///<summary>
///�摜�����֌W
///<para>�N���X:</para>
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
		HWND					myHWND;				//�E�B���h�E�n���h��
		D2D1_COLOR_F			backgroundColor = { 0.0F,0.0F,1.0F,1.0F }; //�w�i�F

		std::vector<LoadedGraphicCell*> container;
		std::queue<DrawGraphicOrder> drawOrders;

		/*bitmap�`�������n*/
		IWICImagingFactory*		pWICImagingFactory = 0;
		IWICBitmapDecoder*		pWICBitmapDecoder  = 0;
		IWICBitmapFrameDecode*	pWICBitmapFrame    = 0;
		IWICFormatConverter*	pFormatConverter   = 0;
		ID2D1Bitmap*			pBitmap			   = 0;

		/*Direct2D�֘A*/
		ID2D1Factory							*d2dFactory;
		ID2D1HwndRenderTarget					*renderTarget;
		RECT									rc;
		D2D1_RENDER_TARGET_PROPERTIES			oRenderTargetProperties;
		ID2D1SolidColorBrush					*blush;

		/*�����`��n*/
		IDWriteFactory *d2dWriteFactory;
		IDWriteTextFormat *pFom = NULL;

		/*���\�b�h*/
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
		///<para>�摜�����[�h���āA�O���t�B�b�N�n���h����Ԃ�</para>
		///<para>���s�����-1���Ԃ����</para>
		///<para>_fileName ... �摜�t�@�C����</para>
		///</summary>
		int LoadGraph(LPCWSTR _fileName);
	};

}