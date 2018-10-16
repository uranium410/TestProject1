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
	
	class GraphFactory;
	class GraphicManager;
	class LoadedGraphicContainer;
	class LoadedGraphicCell;
	
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
		void DrawUpdate();
		///<summary>
		///<para>�摜�����[�h���āA�O���t�B�b�N�n���h����Ԃ�</para>
		///<para>_fileName ... �摜�t�@�C����</para>
		///</summary>
		int LoadGraph(LPCWSTR _fileName);
		GraphicManager(HWND hwnd);
		~GraphicManager();
	};

	class LoadedGraphicContainer {
	private:
		std::vector<LoadedGraphicCell*> container;
	public:
		int SetLoadedGraphicCell(ID2D1Bitmap* _bitmap, D2D1_SIZE_F _size, int _handle); /*�ǂݍ��񂾉摜�f�[�^�̒ǉ�*/
		LoadedGraphicContainer() { container.push_back(NULL); return; } /*�R���X�g���N�^*/
		~LoadedGraphicContainer() { 
			for (LoadedGraphicCell* temp : container) {
				if (temp != NULL)free(temp);
			} 
		}/*�f�X�g���N�^*/
	};

	class LoadedGraphicCell {
	private:
		ID2D1Bitmap*	bitmap;
		D2D1_SIZE_F		size;

	public:
		LoadedGraphicCell(ID2D1Bitmap* _bitmap, D2D1_SIZE_F _size) {
			bitmap =_bitmap;
			size =	_size;
		 }
		~LoadedGraphicCell() {
			bitmap->Release();
		}

		ID2D1Bitmap* GetBitmap(){ return bitmap; }
		D2D1_SIZE_F GetSize() { return size; }
	};
}