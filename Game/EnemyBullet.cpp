#include "EnemyBullet.h"
#include "GameConfig.h"
#include "DxLib.h"
#include <cmath>

int EnemyBullet::bulletHandle;

void EnemyBullet::LoadResources() {
	bulletHandle = LoadGraph("images/EnemyBullet.png");
}

EnemyBullet::EnemyBullet(int startX, int startY, int playerX, int playerY) {
	x = startX;
	y = startY;
	// プレイヤーに向かう方向ベクトルを正規化。速度を設定
	float dx = playerX - startX;
	float dy = playerY - startY;
	float length = sqrt(dx * dx + dy * dy);

	vX = (dx / length) * BULLET_SPEED;
	vY = (dy / length) * BULLET_SPEED;
}

void EnemyBullet::Update() {
	if (!isActive) return;

	x += vX;
	y += vY;

	// 画面外に出たら非アクティブにする
	if (x < 0 || x + SPRITE_W * BULLET_SCALE > GameConfig::SCREEN_W || // 画面の右端または左端に達した
		y < 0 || y + SPRITE_H * BULLET_SCALE > GameConfig::SCREEN_H) // 画面上端または下端に達した
	{
		isActive = false;
	}
}

void EnemyBullet::Draw() const {
	if (!isActive) return;

	DrawExtendGraph((int)x, (int)y,
		(int)x + SPRITE_W * BULLET_SCALE,
		(int)y + SPRITE_H * BULLET_SCALE,
		bulletHandle, TRUE);
}