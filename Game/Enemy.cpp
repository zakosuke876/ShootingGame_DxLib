#include "Enemy.h"
#include "SoundManager.h"
#include "GameConfig.h"
#include "DxLib.h"

int Enemy::enemyHandles[Enemy::HANDLE_NUM];

void Enemy::LoadResources() {
	LoadDivGraph("images/Enemy.png", 4, 4, 1, 8, 6, enemyHandles);
}

struct EnemyData {
	int hp;
	int speed;
	int score;
};

// typeIndexに対応するステータス
static const EnemyData ENEMY_TABLE[] = {
	{1, 3, 100}, // typeIndex = 0
	{2, 3, 200},
	{3, 3, 300},
	{4, 3, 400},
	{5, 3, 500},
	{6, 3, 600}, // typeIndex = 5
};

Enemy::Enemy(int startX, int startY, int typeIndex) {
	x = startX;
	y = startY;
	hp = ENEMY_TABLE[typeIndex].hp;
	speed = ENEMY_TABLE[typeIndex].speed;
	addScore = ENEMY_TABLE[typeIndex ].score;
	currentEnemyHandle = enemyHandles[typeIndex];
	enemyType = typeIndex;
}

void Enemy::Damage() {
	hp--;
	PlaySoundMem(SoundManager::GetHitSound(), DX_PLAYTYPE_BACK);

	if (hp <= 0)
	{
		hp = 0;
		Deactivate();
		PlaySoundMem(SoundManager::GetExplosionSound(), DX_PLAYTYPE_BACK);
	}
}

void Enemy::Update(int playerX, int playerY) {
	if (!isActive) return;

	y += speed;

	// 画面外に出たら非アクティブ状態にする
	if (y > GameConfig::SCREEN_H)
	{
		isActive = false;
	}

}


bool Enemy::Shot() {
	shotTimer++;
	
	// 発射タイミングに達したらtrueを返す
	if (shotTimer >= SHOT_INTERVAL)
	{
		shotTimer = 0;
		return true;
	}

	return false;
}

void Enemy::Draw() const {
	if (!isActive) return;
	DrawExtendGraph(x, y, x + SPRITE_W * ENEMY_SCALE, y + SPRITE_H * ENEMY_SCALE, currentEnemyHandle, TRUE);
}