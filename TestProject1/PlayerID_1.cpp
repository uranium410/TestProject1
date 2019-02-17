#include "stdafx.h"
#include "AllHead.h"

namespace LoadedGraphic {
	std::shared_ptr<AnimationMode> Player_1_StandingA;
	std::shared_ptr<AnimationMode> Player_1_NB1A;
	std::shared_ptr<AnimationMode> Player_1_walkingA;
	std::shared_ptr<AnimationMode> Player_1_jumpingA;
	std::shared_ptr<AnimationMode> Player_1_Damaged_SA;
	std::shared_ptr<AnimationMode> Player_1_Damaged_LA;
	std::shared_ptr<AnimationMode> Player_1_GetUpA;
	std::shared_ptr<AnimationMode> Player_1_AB1A;
	std::shared_ptr<AnimationMode> Player_1_DushA;
	std::shared_ptr<AnimationMode> Player_1_GurdA;

	std::shared_ptr<AnimationMode> Player_1_StandingAd;
	std::shared_ptr<AnimationMode> Player_1_NB1Ad;
	std::shared_ptr<AnimationMode> Player_1_walkingAd;
	std::shared_ptr<AnimationMode> Player_1_jumpingAd;
	std::shared_ptr<AnimationMode> Player_1_Damaged_SAd;
	std::shared_ptr<AnimationMode> Player_1_Damaged_LAd;
	std::shared_ptr<AnimationMode> Player_1_GetUpAd;
	std::shared_ptr<AnimationMode> Player_1_AB1Ad;
	std::shared_ptr<AnimationMode> Player_1_DushAd;
	std::shared_ptr<AnimationMode> Player_1_GurdAd;

}

namespace PlayerClasses {

	bool PlayerID_1::Loaded = false;

	PlayerID_1::PlayerID_1(std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager, bool _Player1, std::vector<std::shared_ptr<GameObjects::GameObject>>* _gameObjects_Effect) {
		gameObjects_Effect = _gameObjects_Effect;
		graphicManager = _graphicManager;
		if (_Player1) {
			playerID = PNB1;
			gamePosition = Vector2(300, 0);
			myDir = PID1_State::Dir_Right;
		}
		else {
			playerID = PNB2;
			gamePosition = Vector2(700, 0);
			myDir = PID1_State::Dir_Left;
		}

		if (Loaded) {
			standingA = LoadedGraphic::Player_1_StandingA;
			NB1A = LoadedGraphic::Player_1_NB1A;
			walkingA = LoadedGraphic::Player_1_walkingA;
			jumpingA = LoadedGraphic::Player_1_jumpingA;
			Damaged_SA = LoadedGraphic::Player_1_Damaged_SA;
			Damaged_LA = LoadedGraphic::Player_1_Damaged_LA;
			GetUpA = LoadedGraphic::Player_1_GetUpA;
			AB1A = LoadedGraphic::Player_1_AB1A;
			DushA = LoadedGraphic::Player_1_DushA;
			GurdA = LoadedGraphic::Player_1_GurdA;

		}else GraphLoad(_graphicManager);
		Loaded = true;

		size = Vector2(200,200);

		movingVector = Vector2(0, 0);

		myState = PID1_State::Stay;
	}

	void PlayerID_1::Update(std::shared_ptr<BasicSystem::InputManager> _inputManager, std::shared_ptr<PlayerClass> _oppPlayer){
		inputManager = _inputManager;
		if (myState != PID1_State::DUSH) {
			if (gamePosition.x < _oppPlayer->gamePosition.x) {
				myDir = PID1_State::Dir_Right;
			}
			else {
				myDir = PID1_State::Dir_Left;
			}
		}

		if (myState != PID1_State::GURD && gurdCounter < gurdCounterMax) {
			gurdCounter++;
		}

		/*ダメージ処理*/
		if (hittedFlag) {
			hittedFlag = false;
			stateFlame = 0;
			float damageCut = 1;
			if (myState == PID1_State::GURD)damageCut = 1 - (float)gurdCounter / (float)gurdCounterMax;
			HP -= damageReciever.Damage * damageCut;
			damageReciever.Damage = 0;

			if (myState != PID1_State::GURD) {
				switch (damageReciever.impactType) {
				case Collider::IT_S:
					myState = PID1_State::DAMAGED_S;
					break;
				case Collider::IT_L:
					myState = PID1_State::DAMAGED_L;
					break;
				}
			}
			/*死亡判定*/
			if (HP <= 0) {
				if (myDir == PID1_State::Dir_Right)damageReciever.knockVector = Vector2(-25, 10);
				else damageReciever.knockVector = Vector2(25, 10);
				myState = PID1_State::KNOCK_OUT;
			}
		}

		/*ボタン入力取得*/
		if (_oppPlayer->HP > 0 ) {
			SetBflag();
			DushCheck();
		}


		if (myState != PID1_State::DAMAGED_L) {
			AccCollisions.push_back(Collider::AccCollision(gamePosition, Vector2(-30, 180), Vector2(60, 160), &hittedFlag, &damageReciever));
		}else AccCollisions.push_back(Collider::AccCollision(gamePosition, Vector2(-80, 60), Vector2(160, 60), &hittedFlag, &damageReciever));

		switch (myState)
		{
		case PID1_State::Stay:
			Stay();
			break;
		case PID1_State::D_Stay:
			D_Stay();
			break;
		case PID1_State::A_Stay:
			A_Stay();
			break;
		case PID1_State::WALK:
			WALK();
			break;
		case PID1_State::DUSH:
			DUSH();
			break;
		case PID1_State::N_ATK1:
			N_ATK1();
			break;
		case PID1_State::N_ATK2:
			N_ATK2();
			break;
		case PID1_State::D_ATK1:
			D_ATK1();
			break;
		case PID1_State::D_ATK2:
			D_ATK2();
			break;
		case PID1_State::NA_ATK1:
			NA_ATK1();
			break;
		case PID1_State::NA_ATK2:
			NA_ATK2();
			break;
		case PID1_State::DAMAGED_S:
			DAMAGED_S();
			break;
		case PID1_State::DAMAGED_L:
			DAMAGED_L();
			break;
		case PID1_State::GETUP:
			GET_UP();
			break;
		case PID1_State::KNOCK_OUT:
			KNOCK_OUT();
			break;
		case PID1_State::GURD:
			GURD();
			break;
		default:
			break;
		}
		stateFlame++;
		if (beforeState != myState) {
			beforeState = myState;
			stateFlame = 0;
		}
	}

	void PlayerID_1::GraphUpdate(std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager) {
		bool reverse = myDir == PID1_State::Dir_Left ? false : true;
		TranceGraphicPosition();

		switch (myState) {
		case PID1_State::Stay:
			_graphicManager->DrawOrder(GraphicSystem::DrawGraphicOrder(standingA->GH_to_draw(), drawPosition, DoubleVector2(1, 1),reverse));
			break;
		case PID1_State::N_ATK1:
			_graphicManager->DrawOrder(GraphicSystem::DrawGraphicOrder(NB1A->GH_to_draw(), drawPosition, DoubleVector2(1, 1),reverse));
			break;
		case PID1_State::WALK:
			_graphicManager->DrawOrder(GraphicSystem::DrawGraphicOrder(walkingA->GH_to_draw(), drawPosition, DoubleVector2(1 , 1),reverse));
			break;
		case  PID1_State::DUSH:
			_graphicManager->DrawOrder(GraphicSystem::DrawGraphicOrder(DushA->GH_to_draw(), drawPosition, DoubleVector2(1, 1), reverse));
			break;
		case PID1_State::A_Stay:
			_graphicManager->DrawOrder(GraphicSystem::DrawGraphicOrder(jumpingA->GH_to_draw(), drawPosition, DoubleVector2(1, 1), reverse));
			break;
		case PID1_State::NA_ATK1:
			_graphicManager->DrawOrder(GraphicSystem::DrawGraphicOrder(AB1A->GH_to_draw(), drawPosition, DoubleVector2(1, 1), reverse));
			break;
		case PID1_State::DAMAGED_S:
			_graphicManager->DrawOrder(GraphicSystem::DrawGraphicOrder(Damaged_SA->GH_to_draw(), drawPosition, DoubleVector2(1, 1), reverse));
			break;
		case PID1_State::DAMAGED_L:
			_graphicManager->DrawOrder(GraphicSystem::DrawGraphicOrder(Damaged_LA->GH_to_draw(), drawPosition, DoubleVector2(1, 1), reverse));
			break;
		case PID1_State::GETUP:
			_graphicManager->DrawOrder(GraphicSystem::DrawGraphicOrder(GetUpA->GH_to_draw(), drawPosition, DoubleVector2(1, 1), reverse));
			break;
		case PID1_State::KNOCK_OUT:
			_graphicManager->DrawOrder(GraphicSystem::DrawGraphicOrder(Damaged_LA->GH_to_draw(), drawPosition, DoubleVector2(1, 1), reverse));
			break;
		case PID1_State::GURD:
			_graphicManager->DrawOrder(GraphicSystem::DrawGraphicOrder(GurdA->GH_to_draw(), drawPosition, DoubleVector2(1, 1), reverse));
			break;
		}
	}

	void PlayerID_1::GraphLoad(std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager) {
		standingA = std::make_shared<AnimationMode>(8,
			new AnimationCell(_graphicManager, L"Materials/Character_1/Standing/S_1.png", 10),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Standing/S_2.png", 10),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Standing/S_3.png", 10),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Standing/S_4.png", 10),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Standing/S_5.png", 10),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Standing/S_6.png", 10),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Standing/S_7.png", 10),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Standing/S_8.png", 10));
		standingA->LoopMode = true;
		NB1A = std::make_shared<AnimationMode>(5,
			new AnimationCell(_graphicManager, L"Materials/Character_1/NB1/NB1_1.png", 10),
			new AnimationCell(_graphicManager, L"Materials/Character_1/NB1/NB1_2.png", 2),
			new AnimationCell(_graphicManager, L"Materials/Character_1/NB1/NB1_3.png", 3),
			new AnimationCell(_graphicManager, L"Materials/Character_1/NB1/NB1_4.png", 3),
			new AnimationCell(_graphicManager, L"Materials/Character_1/NB1/NB1_5.png", 3));
		NB1A->LoopMode = false;
		walkingA = std::make_shared<AnimationMode>(5,
			new AnimationCell(_graphicManager, L"Materials/Character_1/Walking/Wlk_1.png", 6),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Walking/Wlk_2.png", 6),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Walking/Wlk_3.png", 6),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Walking/Wlk_4.png", 6),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Walking/Wlk_5.png", 6)
			);
		walkingA->LoopMode = true;
		jumpingA = std::make_shared<AnimationMode>(1,
			new AnimationCell(_graphicManager, L"Materials/Character_1/Jump.png", 100));
		Damaged_SA = std::make_shared<AnimationMode>(1,
			new AnimationCell(_graphicManager, L"Materials/Character_1/Damage/Damage_S.png", 100));
		Damaged_LA = std::make_shared<AnimationMode>(4,
			new AnimationCell(_graphicManager, L"Materials/Character_1/Damage/Damage_S.png", 6),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Damage/Damage_1.png", 6),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Damage/Damage_2.png", 6),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Damage/Damage_3.png", 6)
			);
		Damaged_LA->LoopMode = false;
		GetUpA = std::make_shared<AnimationMode>(1,
			new AnimationCell(_graphicManager, L"Materials/Character_1/Damage/GetUp.png", 6));
		AB1A = std::make_shared<AnimationMode>(1,
			new AnimationCell(_graphicManager, L"Materials/Character_1/AB1/AB1.png", 6));
		DushA = std::make_shared<AnimationMode>(1,
			new AnimationCell(_graphicManager, L"Materials/Character_1/Dush.png", 6));
		GurdA = std::make_shared<AnimationMode>(1,
			new AnimationCell(_graphicManager, L"Materials/Character_1/Gurd.png", 6));


		LoadedGraphic::Player_1_StandingA = standingA;
		LoadedGraphic::Player_1_NB1A = NB1A;
		LoadedGraphic::Player_1_walkingA = walkingA;
		LoadedGraphic::Player_1_jumpingA = jumpingA;
		LoadedGraphic::Player_1_Damaged_SA = Damaged_SA;
		LoadedGraphic::Player_1_Damaged_LA = Damaged_LA;
		LoadedGraphic::Player_1_GetUpA = GetUpA;
		LoadedGraphic::Player_1_AB1A = AB1A;
		LoadedGraphic::Player_1_DushA = DushA;
		LoadedGraphic::Player_1_GurdA = GurdA;
	}
	
	//////////////////////////////////////*各状態での処理*////////////////////////////
	void PlayerID_1::Stay() {
		airDushFlag = true;
		if (B_2.GetKeyDown()) {
			myState = PID1_State::GURD;
			return;
		}
		if (B_UP.GetKeyDown() && onGround) {
			movingVector.y += JumpSpeed;
			myState = PID1_State::A_Stay;
			onGround = false;

		}else if (B_1.GetKeyDown()) {
			if (B_RIGHT.GetKey())myDir = PID1_State::Dir_Right;
			if (B_LEFT.GetKey())myDir = PID1_State::Dir_Left;
			myState = PID1_State::N_ATK1;
		}
		else if (dushInput) {
			if (B_RIGHT.GetKey())myDir = PID1_State::Dir_Right;
			if (B_LEFT.GetKey())myDir = PID1_State::Dir_Left;
			myState = PID1_State::DUSH;
		}
		else if (B_RIGHT.GetKey()) {
			myDir = PID1_State::Dir_Right;
			myState = PID1_State::WALK;
		}
		else if (B_LEFT.GetKey()) {
			myDir = PID1_State::Dir_Left;
			myState = PID1_State::WALK;
		}
	}
	void PlayerID_1::D_Stay() {

	}
	void PlayerID_1::A_Stay() {
		if (stateFlame<2 && AStay_Dir == 0) {
			if (B_RIGHT.GetKey())
			{
				AStay_Dir = 2;
			}
			else if (B_LEFT.GetKey())
			{
				AStay_Dir = 1;
			}
			else 
			{
				AStay_Dir = 0;
			}
		}
		else {
			if (B_1.GetKeyDown()) {
				myState = PID1_State::NA_ATK1;
				AStay_Dir = 0;
			}
		}

		if (AStay_Dir == 2) {
			myDir = PID1_State::Dir_Right;
			movingVector += Vector2(5, 0);
		}
		if (AStay_Dir == 1) {
			myDir = PID1_State::Dir_Left;
			movingVector += Vector2(-5, 0);
		}

		if (dushInput && airDushFlag) {
			airDushFlag = false;
			myState = PID1_State::DUSH;
			if (B_RIGHT.GetKey())myDir = PID1_State::Dir_Right;
			if (B_LEFT.GetKey())myDir = PID1_State::Dir_Left;
			AStay_Dir = 0;
		}

		if (onGround) {
			AStay_Dir = 0;
			myState = PID1_State::Stay;
		}
	}
	void PlayerID_1::WALK() {
		airDushFlag = true;
		if (B_RIGHT.GetKey())myDir = PID1_State::Dir_Right;
		else if (B_LEFT.GetKey())myDir = PID1_State::Dir_Left;

		if (B_UP.GetKeyDown() && onGround) {
			movingVector.y += JumpSpeed;
			myState = PID1_State::A_Stay;
			onGround = false;
		}
		else if (B_1.GetKeyDown()) {
			myState = PID1_State::N_ATK1;
			return;
		}
		else if (B_RIGHT.GetKey()) {
			movingVector.x = 4;
			myDir = PID1_State::Dir_Right;
		}
		else if (B_LEFT.GetKey()) {
			movingVector.x = -4;
			myDir = PID1_State::Dir_Left;
		}
		else {
			myState = PID1_State::Stay;
		}
	}


	void PlayerID_1::DUSH() {
		//右向き
		if (B_1.GetKeyDown()) {
			if(onGround)myState = PID1_State::N_ATK1;
			else myState = PID1_State::NA_ATK1;
			return;
		}


		if (myDir == PID1_State::Dir_Right) {
			movingVector = Vector2(10,0);
			if (B_UP.GetKeyDown()&&onGround) {
				onGround = false;
				movingVector.y = JumpSpeed;
				myState = PID1_State::A_Stay;
			}
			if ((!B_RIGHT.GetKey()||stateFlame>20)&&onGround) {
				myState = PID1_State::Stay;
			}
			if((!B_RIGHT.GetKey() || stateFlame > 20) && !onGround) {
				myState = PID1_State::A_Stay;
			}
		}
		//左向き
		else {
			movingVector = Vector2(-10, 0);
			if (B_1.GetKeyDown()) {
				myState = PID1_State::NA_ATK1;
			}
			if (B_UP.GetKeyDown() && onGround) {
				onGround = false;
				movingVector.y = JumpSpeed;
				myState = PID1_State::A_Stay;
			}
			if ((!B_LEFT.GetKey() || stateFlame > 20) && onGround) {
				myState = PID1_State::Stay;
			}
			if ((!B_LEFT.GetKey() || stateFlame > 20) && !onGround) {
				myState = PID1_State::A_Stay;
			}

		}
	}


	void PlayerID_1::N_ATK1() {
		if (stateFlame == 0) {
			effectCreated = false;
		}
		if (stateFlame < 10)return;
		if (!hitFlag) {
			if (myDir == PID1_State::Dir_Right)
				AtkCollisions.push_back(Collider::AtkCollision(gamePosition, Vector2(20, 130), Vector2(60, 20), &hitFlag, Collider::DamageMessage(Vector2(5,0), 60, 20, Collider::IT_S)));
			else AtkCollisions.push_back(Collider::AtkCollision(gamePosition, Vector2(-80, 130), Vector2(60, 20), &hitFlag, Collider::DamageMessage(Vector2(-5,0), 60, 20, Collider::IT_S)));
		}
		else if(!effectCreated){
			if (myDir == PID1_State::Dir_Right)gameObjects_Effect->push_back(std::make_shared<Effects::DamageEffect_01>(drawPosition+Vector2(50,0),graphicManager));
			else gameObjects_Effect->push_back(std::make_shared<Effects::DamageEffect_01>(drawPosition+Vector2(-50,0), graphicManager));
			effectCreated = true;
		}
		if (NB1A->played) {
			NB1A->Reset();
			hitFlag = false;
			myState = PID1_State::Stay;
		}
	}
	void PlayerID_1::N_ATK2() {

	}
	void PlayerID_1::D_ATK1() {

	}
	void PlayerID_1::D_ATK2() {

	}
	void PlayerID_1::NA_ATK1() {
		if (stateFlame == 0) {
			if(myDir == PID1_State::Dir_Right)gameObjects_Effect->push_back(std::make_shared<Effects::Player1_Bomb>(drawPosition, graphicManager, true));
			else gameObjects_Effect->push_back(std::make_shared<Effects::Player1_Bomb>(drawPosition, graphicManager, false));

			if(myDir==PID1_State::Dir_Right)AtkCollisions.push_back(Collider::AtkCollision(gamePosition, Vector2(20, 50), Vector2(60, 60), &hitFlag, Collider::DamageMessage(Vector2(12, 8), 80, 80, Collider::IT_L)));
		else AtkCollisions.push_back(Collider::AtkCollision(gamePosition, Vector2(-80, 50), Vector2(60, 60), &hitFlag, Collider::DamageMessage(Vector2(-12, 8), 80, 80, Collider::IT_L)));
			movingVector.y = 10;
		}
		if (myDir == PID1_State::Dir_Right) {
			movingVector.x = -3;
		}
		else {
			movingVector.x = 3;
		}

		if (onGround) {
			myState = PID1_State::Stay;
		}

	}
	void PlayerID_1::NA_ATK2() {
	}
	void PlayerID_1::DAMAGED_S() {
		damageReciever.stunFlame--;
		movingVector += damageReciever.knockVector;
		damageReciever.knockVector /= 2;
		if (damageReciever.stunFlame <= 0) {
			damageReciever = Collider::DamageMessage(Vector2(),0,0);
			myState = PID1_State::Stay;
		}
	}
	void PlayerID_1::DAMAGED_L() {
		damageReciever.stunFlame--;
		movingVector += damageReciever.knockVector;
		damageReciever.knockVector /= 2;
		if (InputSumone()) {
			Damaged_LA->Reset();
			damageReciever = Collider::DamageMessage(Vector2(0,0), 0, 0);
			myState = PID1_State::GETUP;
		}
	}

	void PlayerID_1::GET_UP() {
		if (stateFlame > 5)myState = PID1_State::Stay;
	}

	void PlayerID_1::KNOCK_OUT() {
		if (abs(damageReciever.knockVector.x) <= 0)return;
		movingVector += damageReciever.knockVector;
		damageReciever.knockVector.y /= 2;
		damageReciever.knockVector.x = (int)(damageReciever.knockVector.x * 0.95);
	}

	void PlayerID_1::GURD() {
		gurdCounter--;

		if (!B_2.GetKey() || gurdCounter<=0) {
			myState = PID1_State::Stay;
		}
	}

	bool PlayerID_1d::Loadedd = false;

	PlayerID_1d::PlayerID_1d(std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager, bool _Player1, std::vector<std::shared_ptr<GameObjects::GameObject>>* _gameObjects_Effect) {
		gameObjects_Effect = _gameObjects_Effect;
		graphicManager = _graphicManager;
		if (_Player1) {
			playerID = PNB1;
			gamePosition = Vector2(300, 0);
			myDir = PID1_State::Dir_Right;
		}
		else {
			playerID = PNB2;
			gamePosition = Vector2(700, 0);
			myDir = PID1_State::Dir_Left;
		}

		if (Loadedd) {
			standingA = LoadedGraphic::Player_1_StandingAd;
			NB1A = LoadedGraphic::Player_1_NB1Ad;
			walkingA = LoadedGraphic::Player_1_walkingAd;
			jumpingA = LoadedGraphic::Player_1_jumpingAd;
			Damaged_SA = LoadedGraphic::Player_1_Damaged_SAd;
			Damaged_LA = LoadedGraphic::Player_1_Damaged_LAd;
			GetUpA = LoadedGraphic::Player_1_GetUpAd;
			AB1A = LoadedGraphic::Player_1_AB1Ad;
			DushA = LoadedGraphic::Player_1_DushAd;
			GurdA = LoadedGraphic::Player_1_GurdAd;

		}
		else GraphLoad(_graphicManager);
		Loadedd = true;

		size = Vector2(200, 200);

		movingVector = Vector2(0, 0);

		myState = PID1_State::Stay;
	}

	void PlayerID_1d::GraphLoad(std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager) {
		standingA = std::make_shared<AnimationMode>(8,
			new AnimationCell(_graphicManager, L"Materials/Character_1/Standing/S_1d.png", 10),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Standing/S_2d.png", 10),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Standing/S_3d.png", 10),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Standing/S_4d.png", 10),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Standing/S_5d.png", 10),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Standing/S_6d.png", 10),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Standing/S_7d.png", 10),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Standing/S_8d.png", 10));
		standingA->LoopMode = true;
		NB1A = std::make_shared<AnimationMode>(5,
			new AnimationCell(_graphicManager, L"Materials/Character_1/NB1/NB1_1d.png", 10),
			new AnimationCell(_graphicManager, L"Materials/Character_1/NB1/NB1_2d.png", 2),
			new AnimationCell(_graphicManager, L"Materials/Character_1/NB1/NB1_3d.png", 3),
			new AnimationCell(_graphicManager, L"Materials/Character_1/NB1/NB1_4d.png", 3),
			new AnimationCell(_graphicManager, L"Materials/Character_1/NB1/NB1_5d.png", 3));
		NB1A->LoopMode = false;
		walkingA = std::make_shared<AnimationMode>(5,
			new AnimationCell(_graphicManager, L"Materials/Character_1/Walking/Wlk_1d.png", 6),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Walking/Wlk_2d.png", 6),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Walking/Wlk_3d.png", 6),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Walking/Wlk_4d.png", 6),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Walking/Wlk_5d.png", 6)
			);
		walkingA->LoopMode = true;
		jumpingA = std::make_shared<AnimationMode>(1,
			new AnimationCell(_graphicManager, L"Materials/Character_1/Jumpd.png", 100));
		Damaged_SA = std::make_shared<AnimationMode>(1,
			new AnimationCell(_graphicManager, L"Materials/Character_1/Damage/Damage_Sd.png", 100));
		Damaged_LA = std::make_shared<AnimationMode>(4,
			new AnimationCell(_graphicManager, L"Materials/Character_1/Damage/Damage_Sd.png", 6),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Damage/Damage_1d.png", 6),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Damage/Damage_2d.png", 6),
			new AnimationCell(_graphicManager, L"Materials/Character_1/Damage/Damage_3d.png", 6)
			);
		Damaged_LA->LoopMode = false;
		GetUpA = std::make_shared<AnimationMode>(1,
			new AnimationCell(_graphicManager, L"Materials/Character_1/Damage/GetUpd.png", 6));
		AB1A = std::make_shared<AnimationMode>(1,
			new AnimationCell(_graphicManager, L"Materials/Character_1/AB1/AB1d.png", 6));
		DushA = std::make_shared<AnimationMode>(1,
			new AnimationCell(_graphicManager, L"Materials/Character_1/Dushd.png", 6));
		GurdA = std::make_shared<AnimationMode>(1,
			new AnimationCell(_graphicManager, L"Materials/Character_1/Gurdd.png", 6));


		LoadedGraphic::Player_1_StandingAd = standingA;
		LoadedGraphic::Player_1_NB1Ad = NB1A;
		LoadedGraphic::Player_1_walkingAd = walkingA;
		LoadedGraphic::Player_1_jumpingAd = jumpingA;
		LoadedGraphic::Player_1_Damaged_SAd = Damaged_SA;
		LoadedGraphic::Player_1_Damaged_LAd = Damaged_LA;
		LoadedGraphic::Player_1_GetUpAd = GetUpA;
		LoadedGraphic::Player_1_AB1Ad = AB1A;
		LoadedGraphic::Player_1_DushAd = DushA;
		LoadedGraphic::Player_1_GurdAd = GurdA;
	}
}