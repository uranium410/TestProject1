#pragma once
#include "AllHead.h"
namespace PID1_State {
	enum Direction {
		Dir_Right,
		Dir_Left
	};
	enum State {
		Stay,
		D_Stay,
		A_Stay,
		WALK,
		DUSH,
		N_ATK1,
		N_ATK2,
		D_ATK1,
		D_ATK2,
		NA_ATK1,
		NA_ATK2,
		DAMAGED_S,
		DAMAGED_L,
		GETUP,
		KNOCK_OUT,
		GURD
	};
}

namespace PlayerClasses {

	enum PlayerNumber {
		PNB1,
		PNB2
	};

	class PlayerClass {
	public:
		//���n����Ƃ��W�����v�̑��x�Ƃ�
		bool onGround = true;
		int AccelGrav = 1;
		int JumpSpeed = 20;

		//�v���C���[��1P��2P��
		PlayerNumber playerID;

		//�E�B���h�E�̃T�C�Y
		int WindwoScaleX = 1000;
		int WindowScaleY = 600;

		//�`����W
		Vector2 drawPosition;
		//��ʓ�����p�T�C�Y
		Vector2 size;
		//�ړ��x�N�g��
		Vector2 movingVector;
		int floorHight = 90;
		int stageEnd = 950;

		//�Q�[����̍��W
		Vector2 gamePosition;

		PID1_State::State myState;
		PID1_State::Direction myDir;

		//�̗�
		int HP=1000;
		//���݂̎��g�̋�炢���胊�X�g
		std::vector<Collider::AccCollision> AccCollisions;
		//���݂̎��g�̍U�����胊�X�g
		std::vector<Collider::AtkCollision> AtkCollisions;
		//�_���[�W�̎󂯌�
		Collider::DamageMessage damageReciever;
		//�_���[�W�󂯔���
		bool hittedFlag = false;
		//�_���[�W�^������
		bool hitFlag = false;
		//��Ԃ��ς���Ă���̌o�߃t���[��
		int stateFlame;
		PID1_State::State beforeState;

		virtual void Update(std::shared_ptr<BasicSystem::InputManager> _inputManager, std::shared_ptr<PlayerClass> _oppPlayer) = 0;
		void  MoveUpdate();
		virtual void GraphUpdate(std::shared_ptr < GraphicSystem::GraphicManager> _graphicManager ) = 0;

		std::shared_ptr<BasicSystem::InputManager> inputManager;

		std::shared_ptr<GraphicSystem::GraphicManager> graphicManager;

		BasicSystem::InputFlag B_UP;
		BasicSystem::InputFlag B_DOWN;
		BasicSystem::InputFlag B_RIGHT;
		BasicSystem::InputFlag B_LEFT;
		BasicSystem::InputFlag B_1;
		BasicSystem::InputFlag B_2;
		bool dushInput=false;
		void DushCheck();
		int dushCounter=0;
		bool dushRightKey=false;
		bool dushLeftKey=false;

		void SetBflag() {
			if (playerID == PNB1) {
				B_UP = inputManager->inputData->P1_Up;
				B_DOWN = inputManager->inputData->P1_Down;
				B_RIGHT = inputManager->inputData->P1_Right;
				B_LEFT = inputManager->inputData->P1_Left;
				B_1 = inputManager->inputData->P1_J;
				B_2 = inputManager->inputData->P1_K;
			}
			if (playerID == PNB2) {
				B_UP = inputManager->inputData->P2_Up;
				B_DOWN = inputManager->inputData->P2_Down;
				B_RIGHT = inputManager->inputData->P2_Right;
				B_LEFT = inputManager->inputData->P2_Left;
				B_1 = inputManager->inputData->P2_J;
				B_2 = inputManager->inputData->P2_K;
			}
			return;
		}

		void TranceGraphicPosition();
		bool InputSumone() {
			if (B_UP.GetKey() || B_DOWN.GetKey() || B_RIGHT.GetKey() ||
				B_LEFT.GetKey() || B_1.GetKey() || B_2.GetKey())return true;
			return false;
		}

	};

	class PlayerID_1 : public PlayerClass {
	public:
		static bool Loaded;

		virtual void GraphLoad(std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager);

		int AStay_Dir=0;
		bool effectCreated;
		bool airDushFlag;

		/*�A�j���[�V����*/
		std::shared_ptr<AnimationMode> standingA;
		std::shared_ptr<AnimationMode> NB1A;
		std::shared_ptr<AnimationMode> walkingA;
		std::shared_ptr<AnimationMode> jumpingA;
		std::shared_ptr<AnimationMode> Damaged_SA;
		std::shared_ptr<AnimationMode> Damaged_LA;
		std::shared_ptr<AnimationMode> GetUpA;
		std::shared_ptr<AnimationMode> AB1A;
		std::shared_ptr<AnimationMode> DushA;
		std::shared_ptr<AnimationMode> GurdA;

		std::vector<std::shared_ptr<GameObjects::GameObject>>* gameObjects_Effect;

		int gurdCounter=50;
		int gurdCounterMax = 180;

		void Stay();
		void D_Stay();
		void A_Stay();
		void WALK();
		void DUSH();
		void N_ATK1();
		void N_ATK2();
		void D_ATK1();
		void D_ATK2();
		void NA_ATK1();
		void NA_ATK2();
		void DAMAGED_S();
		void DAMAGED_L();
		void GET_UP();
		void KNOCK_OUT();
		void GURD();

		PlayerID_1() {};
		PlayerID_1(std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager, bool _Player1, std::vector<std::shared_ptr<GameObjects::GameObject>>* _gameObjects_Effect);
		void Update(std::shared_ptr<BasicSystem::InputManager> _inputManager, std::shared_ptr<PlayerClass> _oppPlayer);
		void GraphUpdate(std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager);
	};

	class PlayerID_1d : public PlayerID_1 {
	public:
		static bool Loadedd;
		PlayerID_1d(std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager, bool _Player1, std::vector<std::shared_ptr<GameObjects::GameObject>>* _gameObjects_Effect);
		void GraphLoad(std::shared_ptr<GraphicSystem::GraphicManager> _graphicManager);
	};
}