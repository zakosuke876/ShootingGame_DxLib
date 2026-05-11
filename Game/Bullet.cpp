#include "Bullet.h"
#include "GameConfig.h"
#include "DxLib.h"

int Bullet::bulletHandles[Bullet::BULLET_NUM];

void Bullet::LoadResources() {
	LoadDivGraph("images/PlayerBullets.png", 4, 2, 2, 8, 24, bulletHandles);
}

Bullet::Bullet() {
	currentBulletHandle = bulletHandles[0];
}

void Bullet::Init(int startX, int startY, int bulletTypeIndex) {
	x = startX;
	y = startY;
	currentBulletHandle = bulletHandles[bulletTypeIndex];
	isActive = true;
	bulletType = bulletTypeIndex;
}

void Bullet::Update() {
	if (!isActive) return;
	y += vY;

	// 画面上端に達したら非アクティブにする
	if (y < 0)
	{
		isActive = false;
	}
}

void Bullet::Draw() const {
	if (!isActive) return;
	DrawExtendGraph(x, y, x + SPRITE_W * BULLET_SCALE, y + SPRITE_H * BULLET_SCALE, currentBulletHandle, TRUE);
}