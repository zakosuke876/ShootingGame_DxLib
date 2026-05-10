#pragma once
#include "CollisionUtil.h"

class EnemyBullet {
public:
	// リソース管理
	static void LoadResources();

	// 初期化・状態管理
	EnemyBullet(int startX, int startY, int playerX, int playerY);
	void Deactivate() { isActive = false; }
	bool IsActive() const { return isActive; }
	Rect GetRect() const {
		return { (int)x, (int)y, SPRITE_W * BULLET_SCALE, SPRITE_H * BULLET_SCALE };
	}

	// 更新・描画
	void Update();
	void Draw() const;
	

private:
	// スプライト設定
	static constexpr int SPRITE_W = 8;
	static constexpr int SPRITE_H = 8;
	static constexpr int BULLET_SCALE = 5;
	static constexpr int BULLET_SPEED = 5;
	static int bulletHandle;

	// 状態
	float x, y;
	float vX, vY; // プレイヤーに向かう方向ベクトル
	bool isActive = true;
};