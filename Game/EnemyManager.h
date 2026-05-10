#pragma once
#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"
#include "ScoreManager.h"
#include <vector>

class EnemyManager {
public:
	// リソース管理
	static void LoadResources();

	// 初期化
	EnemyManager();

	// 当たり判定
	void CheckBulletHit(Bullet* bullets, int maxBullets, ScoreManager& score);
	bool CheckPlayerHit(Player& player);
	bool CheckEnemyBulletHit(Player& player);

	// 更新・描画
	void Update(Player& player);
	void Draw();
	

private:
	// 敵管理
	std::vector<Enemy> enemies;
	int spawnTimer = 0;
	static constexpr int SPAWN_INTERVAL = 80;

	// 爆発エフェクト
	struct Explosion {
		int x, y;
		int frame = 0;
		bool isActive = true;
		Explosion(int x, int y) : x(x), y(y) {}
	};
	std::vector<Explosion> explosions;
	static constexpr int FRAME_NUM = 4;
	static constexpr int EFFECT_W = 8;
	static constexpr int EFFECT_H = 8;
	static constexpr int EFFECT_SCALE = 8;
	static constexpr int EFFECT_DURATION = 6; // 1フレームの表示時間
	static int explosionHandles[FRAME_NUM];

	// 敵の弾
	std::vector<EnemyBullet> bullets;

	// 内部処理
	void Spawn();
	void RemoveInactive();
};