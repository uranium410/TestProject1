#include "stdafx.h"
#include "AllHead.h"

/*コンストラクタ*/
AnimationCell::AnimationCell() {
	OutputDebugString(L"new AnimationCell");
	return;
}

AnimationCell::AnimationCell(std::shared_ptr<GraphicSystem::GraphicManager> graphicManager,LPCWSTR graphName, int fl) {
	OutputDebugString(L"LoadGraph\n");
	if ((graphHandle = graphicManager->LoadGraph(graphName)) == -1)OutputDebugString(L"画像読み込みエラー: 指定された画像ファイルがありません\n");
	flame = fl;
	nextCell = NULL;
	return;
}

/*デストラクタ*/
AnimationCell::~AnimationCell() {
	if(nextCell != NULL)delete nextCell;
	return;
}

AnimationMode* AnimationMode::Copy() {
	//OutputDebugString("Copy関数呼び出し\n");
	AnimationMode* copyClass;
	//OutputDebugString("new AnimationMode\n");
	copyClass = new AnimationMode;
	copyClass->animationCells = this->animationCells;
	copyClass->nowCell = copyClass->animationCells;
	copyClass->copy = true;
	return copyClass;
}

/*AnimationCell を追加*/
void AnimationMode::AddCell(AnimationCell* cell) {
	//空っぽだったら
	if (animationCells == NULL) {
		animationCells = cell;
		return;
	}
	//一つ以上あれば
	AnimationCell* temp = animationCells;
	while (temp->nextCell != NULL) {
		temp = temp->nextCell;
	}
	temp->nextCell = cell;
	return;
}

int AnimationMode::GH_to_draw() {
	//OutputDebugString("GH_to_draw\n");
	flameCounter++;
	if (flameCounter > nowCell->flame) {
		CellChange();
		flameCounter = 0;
	}
	return nowCell->graphHandle;
}

void AnimationMode::CellChange() {
	if (nowCell->nextCell == NULL) {
		nowCell = animationCells;
	}
	else {
		nowCell = nowCell->nextCell;
	}
	return;
}

/*コンストラクタ*/
AnimationMode::AnimationMode(int cellNum, ...) {
	int i;

	animationCells = NULL;
	nowCell = NULL;
	va_list cells;
	va_start(cells, cellNum);
	for (i = 0; i < cellNum; i++) {
		OutputDebugString(L"AnimationCell追加\n");
		AddCell(va_arg(cells,AnimationCell*));
	}
	va_end(cells);
	flameCounter = 0;
	copy = false;
	nowCell = animationCells;

	return;
}

AnimationMode::AnimationMode() {
	animationCells = NULL;
	nowCell = NULL;
	flameCounter = 0;
	copy = false;
	nowCell = animationCells;
	return;
}

/*デストラクタ*/
AnimationMode::~AnimationMode() {
	if(animationCells != NULL && !copy)delete animationCells;
	return;
}