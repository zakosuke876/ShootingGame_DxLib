#pragma once
#include "CollisionUtil.h"
#include "EnemyBullet.h"
#include <vector>

class Enemy {
public:
	// リソース管理
	static void LoadResources();
	static int GetHandleNum() { return HANDLE_NUM; }

	// 初期化・状態管理
	Enemy(int startX, int startY, int typeIndex);
	void Deactivate() { isActive = false; }
	void Damage();
	bool IsActive() const { return isActive; }
	int GetEnemyType() const { return enemyType; }
	int GetScore() const { return addScore; }

	// 座標取得
	int GetX() const { return x; }
	int GetY() const { return y; }
	Rect GetRect() const {
		return { x, y, SPRITE_W * ENEMY_SCALE, SPRITE_H * ENEMY_SCALE };
	}

	// 弾発射
	/// <summary>
	/// タイマーを更新し、発射タイミングに達したか判定する
	/// </summary>
	/// <returns>発射タイミングであれば,true : そうでなければ,false</returns>
	bool Shot();
	int GetBulletStartX() const { return x + SPRITE_W * ENEMY_SCALE / 2; } // 弾の発射X座標(敵の中央)
	int GetBulletStartY() const { return y + SPRITE_H * ENEMY_SCALE; }    // 弾の発射Y座標(敵の下端)

	// 更新・描画
	void Update(int playerX, int playerY);
	void Draw() const;

private:
	// スプライト設定
	static constexpr int HANDLE_NUM = 4;
	static constexpr int SPRITE_W = 8;
	static constexpr int SPRITE_H = 6;
	static int enemyHandles[HANDLE_NUM];
	static constexpr int ENEMY_SCALE = 8; // 描画時の拡大倍率(元画像に対する倍率)

	// 状態
	int x, y;
	int speed;
	int hp;
	int addScore; // 倒した際に加算するスコア
	int enemyType;
	int currentEnemyHandle; // 表示中の敵画像ハンドル
	bool isActive = true;

	// 射撃
	int shotTimer = 0;
	static constexpr int SHOT_INTERVAL = 120; // 弾を発射する間隔(フレーム数)
};
