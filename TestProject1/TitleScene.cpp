#include "stdafx.h"
#include "AllHead.h"

namespace GameSystem {
	std::shared_ptr<AnimationMode>TitleBuckS;
	bool TitleLoaded=false;

	TitleScene::TitleScene(const std::shared_ptr<GraphicSystem::GraphicManager> &GM) 
	{
		if (!TitleLoaded) {
			TitleBuck = std::make_shared<AnimationMode>(1,
				new AnimationCell(GM, L"Materials/Title.png", 100));
			TitleBuckS = TitleBuck;
		}
		else {
			TitleBuck = TitleBuckS;
		}
		graphicManager = GM; 
	}


	void TitleScene::Update() {
		if (inputManager->inputData->P1_J.GetKeyDown() || inputManager->inputData->P2_J.GetKeyDown()) {
			fadeoutCounter--;
			nextSceneid = GameSystem::Battle;
		}
	}

	void TitleScene::GraphUpdate(std::shared_ptr<GraphicSystem::GraphicManager> graphicManager) {
		graphicManager->DrawUpdate();
		graphicManager->DrawOrder(GraphicSystem::DrawGraphicOrder(TitleBuck->GH_to_draw(), Vector2(0,0), DoubleVector2(1, 1), false));

		pushButtonCounter++;
		if (pushButtonCounter < 40) {
			float width = 1300.0f;
			float height = 100.0f;
			D2D1_RECT_F rect;

			rect.left = 400.0f;
			rect.top = 400.0f;
			rect.right = rect.left + width;
			rect.bottom = rect.top + height;

			std::wstring deviceText(L"-Aボタンでスタート-");
			graphicManager->Drawtext(deviceText, rect);
		}
		if (pushButtonCounter > 80)pushButtonCounter = 0;

		if (fadeoutCounter < 100) {
			fadeoutCounter--;
			if (fadeoutCounter < 0)sceneChange = true;
		}

		graphicManager->DrawRect(Vector2(0,0),Vector2(1000,600),GraphicSystem::BRACK,true,1.0f - (float)fadeoutCounter/100.0f);


	}

	void TitleScene::CorrectGraphUpdate() {

	}
}