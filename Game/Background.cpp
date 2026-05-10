#include "Background.h"
#include "GameConfig.h"
#include "DxLib.h"

BackGround::BackGround() {
	backHandle = LoadGraph("images/BackGround.png");
}

void BackGround::Update() {
	scrollY += SCROLL_SPEED;

	// 1枚分スクロールしたらリセット
	if (scrollY >= GameConfig::screen_H)
	{
		scrollY = 0;
	}
}

void BackGround::Draw() {
	// 2枚並べる
	DrawExtendGraph(0, scrollY - GameConfig::screen_H, GameConfig::screen_W, scrollY, backHandle, TRUE);
	DrawExtendGraph(0, scrollY, GameConfig::screen_W, scrollY + GameConfig::screen_H, backHandle, TRUE);
}