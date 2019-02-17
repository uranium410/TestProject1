#include "stdafx.h"
#include "AllHead.h"

namespace Effects {
	namespace LoadedGraphic {
		std::shared_ptr<AnimationMode> DE01graph;
	}

	bool DamageEffect_01::loaded = false;
	//int DamageEffect_01::sound1 = -1;
	//int DamageEffect_01::sound2 = -1;
	//bool DamageEffect_01::sound1Played = true;

	DamageEffect_01::DamageEffect_01(Vector2 _position, std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager) {
		position = _position;
		graphicManager = _graphicManager;
		if (loaded) {
			graph = LoadedGraphic::DE01graph;
			//if(sound1Played)BasicSystem::SoundSystem::SoundReset(sound1);
			//else BasicSystem::SoundSystem::SoundReset(sound2);
			return;
		}else {
			graph = std::make_shared<AnimationMode>(1,new AnimationCell(_graphicManager, L"Materials/Effect/Effect_01.png", 1));
			LoadedGraphic::DE01graph = graph;
			//sound1 = BasicSystem::SoundSystem::LoadSound(LPTSTR(L"Materials/Sound/Dageki_2.wav"),false,true);
			//sound2 = BasicSystem::SoundSystem::LoadSound(LPTSTR(L"Materials/Sound/Dageki_2.wav"), false, true);
			loaded = true;
		}
	}

	void DamageEffect_01::Update() {
		flame--;
		//if(sound1Played)BasicSystem::SoundSystem::polling(sound1);
		//else BasicSystem::SoundSystem::polling(sound2);
		if (flame <= -400) {
			destroyFlag = true;
			//sound1Played = sound1Played ? false : true;
		}
	}

	void DamageEffect_01::DrawUpdate() {
		if(flame>0)graphicManager->DrawOrder(GraphicSystem::DrawGraphicOrder(graph->GH_to_draw(), position, DoubleVector2(1, 1), false));
		
	}
}