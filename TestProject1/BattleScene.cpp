#include "stdafx.h"
#include "AllHead.h"

namespace GameSystem {

	std::shared_ptr<AnimationMode> FINISHGraph=0;

	BattleScene::BattleScene(const std::shared_ptr<GraphicSystem::GraphicManager> &GM) {
		
		graphicManager = GM;
		gameObjects_BackGround.push_back(std::make_shared<GameObjects::G_BackGround>(graphicManager));
		P1 = std::make_shared<PlayerClasses::PlayerID_1>(graphicManager, true, &gameObjects_Effect);
		P2 = std::make_shared<PlayerClasses::PlayerID_1d>(graphicManager, false,&gameObjects_Effect);

		HPBar1 = GameObjects::HPBar(1000,Vector2(10,30));
		HPBar2 = GameObjects::HPBar(1000,Vector2(570,30));

		if(FINISHGraph==0)FINISHGraph = std::make_shared<AnimationMode>(1,
			new AnimationCell(graphicManager, L"Materials/FINISH.png", 6));

		BGMID = BasicSystem::SoundSystem::LoadSound(LPTSTR(L"Materials/Sound/BGM.wav"));
	}

	void BattleScene::Update() {


		if (slowMode) {
			slowCounter--;
			Sleep(100);
			if (slowCounter < 0) {
				slowMode = false;
				returnflag = true;
			}
		}
		int i;
		BasicSystem::SoundSystem::polling(BGMID);


		for (std::shared_ptr<GameObjects::GameObject> temp : gameObjects_BackGround) {
			temp->Update();
		}

		for (i = 0; i < (signed)gameObjects_Effect.size();i++) {
			if (gameObjects_Effect[i]->destroyFlag) {
				std::shared_ptr<GameObjects::GameObject> temp;
				temp = gameObjects_Effect[i];
				gameObjects_Effect[i] = gameObjects_Effect[gameObjects_Effect.size() - 1];
				gameObjects_Effect[gameObjects_Effect.size() - 1] = temp;
				gameObjects_Effect.pop_back();
			}
		}

		if (P1 != 0) {
			P1->AccCollisions.clear();
			P1->AtkCollisions.clear();
		}
		if (P2 != 0) {
			P2->AccCollisions.clear();
			P2->AtkCollisions.clear();
		}


		if(P1!=0)P1->Update(inputManager,P2);
		if(P2!=0)P2->Update(inputManager,P1);


		if (P1 != 0)P1->MoveUpdate();
		if (P2 != 0)P2->MoveUpdate();

		for (std::shared_ptr<GameObjects::GameObject> temp : gameObjects_Effect) {
			temp->Update();
		}

	}

	void BattleScene::GraphUpdate(std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager) {



		if ((P1->HP <= 0 || P2->HP <= 0) && slowCounter > 0) {
			slowMode = true;
			finish = true;
		}

		for (std::shared_ptr<GameObjects::GameObject> temp : gameObjects_BackGround) {
			temp->DrawUpdate();
		}

		P1->GraphUpdate(graphicManager);
		P2->GraphUpdate(graphicManager);

		if (finish)graphicManager->DrawOrder(GraphicSystem::DrawGraphicOrder(FINISHGraph->GH_to_draw(), Vector2(220, 180), DoubleVector2(1, 1), false));

		for (std::shared_ptr<GameObjects::GameObject> temp : gameObjects_Effect) {
			temp->DrawUpdate();
		}


		HPBar1.DrawUpdate(P1->HP,true);
		HPBar2.DrawUpdate(P2->HP,false);


		int i, j;
		for (i = 0; i < (signed)P1->AtkCollisions.size(); i++) {
			for (j = 0; j < (signed)P2->AccCollisions.size();j++) {
				P1->AtkCollisions[i].Check(P2->AccCollisions[j]);
			}
		}
		for (i = 0; i < (signed)P2->AtkCollisions.size(); i++) {
			for (j = 0; j < (signed)P1->AccCollisions.size(); j++) {
				P2->AtkCollisions[i].Check(P1->AccCollisions[j]);
			}
		}

		graphicManager->DrawUpdate();
	}

	void BattleScene::CorrectGraphUpdate() {

		HPBar1.Draw(graphicManager);
		HPBar2.Draw(graphicManager);

		if (returnflag) {
			pushButtonCounter++;
			if (pushButtonCounter < 40) {
				float width = 1300.0f;
				float height = 100.0f;
				D2D1_RECT_F rect;

				rect.left = 400.0f;
				rect.top = 400.0f;
				rect.right = rect.left + width;
				rect.bottom = rect.top + height;

				std::wstring deviceText(L"-Aƒ{ƒ^ƒ“‚ÅI—¹-");
				graphicManager->Drawtext(deviceText, rect);

				if (inputManager->inputData->P1_J.GetKeyDown() || inputManager->inputData->P2_J.GetKeyDown())fadeoutCounter--;
			}
			if (pushButtonCounter > 80)pushButtonCounter = 0;
		}

		if (fadeinCounter > 0) {
			fadeinCounter--;
			graphicManager->DrawRect(Vector2(0,0),Vector2(1000,600),GraphicSystem::BRACK,true,(float)fadeinCounter/30);
		}

		if (fadeoutCounter < 100) {
			fadeoutCounter--;
			if (fadeoutCounter < 0)sceneChange = true;
			nextSceneid = GameSystem::Title;
		}
		graphicManager->DrawRect(Vector2(0, 0), Vector2(1000, 600), GraphicSystem::BRACK, true, 1.0f - (float)fadeoutCounter / 100.0f);

	}
}