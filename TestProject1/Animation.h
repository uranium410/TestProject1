#pragma once
#include "AllHead.h"

class AnimationMode;

class AnimationCell {
	AnimationCell *nextCell;
	int graphHandle; /*単位セルのグラフィックハンドル*/
	int flame; /*単位セルのフレーム数*/
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
	void CellChange(); //AnimationCellを切り替え
	int flameCounter;
	int newflameCounter;
	bool copy;
public:
	bool LoopMode = true;
	bool played = false;
	void Reset();
	AnimationMode* Copy(); //Animationインスタンスを複数使うときはコピーして使うこと!
	int GH_to_draw(); /*描画すべきグラフィックハンドルを教えてくれる*/
	AnimationMode();
	AnimationMode(int cellNum, ...);
	~AnimationMode();
};