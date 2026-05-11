#include "Background.h"
#include "GameConfig.h"
#include "DxLib.h"

BackGround::BackGround() {
	backHandle = LoadGraph("images/BackGround.png");
}

void BackGround::Update() {
	scrollY += SCROLL_SPEED;

	// 1枚分スクロールしたらリセット
	if (scrollY >= GameConfig::SCREEN_H)
	{
		scrollY = 0;
	}
}

void BackGround::Draw() const {
	// 2枚並べる
	DrawExtendGraph(0, scrollY - GameConfig::SCREEN_H, GameConfig::SCREEN_W, scrollY, backHandle, TRUE);
	DrawExtendGraph(0, scrollY, GameConfig::SCREEN_W, scrollY + GameConfig::SCREEN_H, backHandle, TRUE);
}