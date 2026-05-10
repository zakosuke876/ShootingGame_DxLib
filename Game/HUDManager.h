#pragma once
#include "Player.h"
#include "Bullet.h"
#include "ScoreManager.h"

class HUDManager {
public:
	void Draw(const Player& player, const ScoreManager& score) const;
	void DrawBulletUI(const Player& player) const;

private:
	// 弾一覧UI
	static constexpr int BULLET_UI_BASE_X = 55;  // Boxを描画する座標(X)
	static constexpr int BULLET_UI_BASE_Y = 435; //(Y)
	static constexpr int BULLET_UI_W = 30;
	static constexpr int BULLET_UI_Y = 30;
	static constexpr int BULLET_UI_SPACE = 50;  // 描画間隔
	static constexpr int BULLET_UI_MARGIN = 3;  // 余白
	static constexpr int BULLET_SPRITE_W = 8;   // 元画像のサイズ
	static constexpr int BULLET_SPRITE_H = 7;

	// キー番号表示
	static constexpr int KEY_LABEL_X = 30;  // 弾切り替えボタンを描画する座標(X)
	static constexpr int KEY_LABEL_Y = 440; // (Y)

	// BulletTypeテキスト
	static constexpr int BULLET_TYPE_TEXT_X = 30;
	static constexpr int BULLET_TYPE_TEXT_Y = 640;

	// 選択中の弾UI
	static constexpr int CURRENT_BULLET_IMAGE_X = 150; // 選択中の弾画像の座標
	static constexpr int CURRENT_BULLET_IMAGE_Y = 640;
	static constexpr int CURRENT_BULLET_IMAGE_W = 32;
	static constexpr int CURRENT_BULLET_IMAGE_H = 28;
	static constexpr int CURRENT_BULLET_BOX_MARGIN = 6;
	static constexpr int CURRENT_BULLET_BOX_X = 150;
	static constexpr int CURRENT_BULLET_BOX_Y = 640;
	static constexpr int CURRENT_BULLET_BOX_W = 32;
	static constexpr int CURRENT_BULLET_BOX_H = 28;
};