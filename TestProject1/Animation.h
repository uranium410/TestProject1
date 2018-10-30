#pragma once
#include "AllHead.h"

class AnimationMode;

class AnimationCell {
	AnimationCell *nextCell;
	int graphHandle; /*�P�ʃZ���̃O���t�B�b�N�n���h��*/
	int flame; /*�P�ʃZ���̃t���[����*/
public:
	AnimationCell();
	AnimationCell(std::shared_ptr<GraphicSystem::GraphicManager> graphicManager, LPCWSTR graphName, int fl = 1);
	~AnimationCell();
	friend AnimationMode;
};

class AnimationMode {
	AnimationCell *animationCells;
	AnimationCell *nowCell;
	void AddCell(AnimationCell* cell);
	void CellChange(); //AnimationCell��؂�ւ�
	int flameCounter;
	int newflameCounter;
	bool copy;
public:
	bool LoopMode = true;
	bool played = false;
	void Reset();
	AnimationMode* Copy(); //Animation�C���X�^���X�𕡐��g���Ƃ��̓R�s�[���Ďg������!
	int GH_to_draw(); /*�`�悷�ׂ��O���t�B�b�N�n���h���������Ă����*/
	AnimationMode();
	AnimationMode(int cellNum, ...);
	~AnimationMode();
};