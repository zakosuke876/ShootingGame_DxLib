#pragma once
#include "Bullet.h"
#include <vector>


class Player {
public:
	// リソース管理
	static void LoadResources();

	// 初期化
	Player();
	~Player() = default;

	// 状態取得
	bool IsActive() const { return isActive; }
	bool IsExplosionFinished() const;
	int GetCurrentBulletIndex() const { return currentBulletIndex; }
	int GetX() const { return x; }
	int GetY() const { return y; }
	Rect GetRect() const {
		return { x, y, SPRITE_W * PLAYER_SCALE, SPRITE_H * PLAYER_SCALE };
	}
	Bullet* GetBullets() { return bullets; }
	static constexpr int MAX_BULLETS = 20;

	// ダメージ
	void Damage();

	// 更新・描画
	void Update();
	void Draw();
	void DrawPlayerHp() const;

private:
	// スプライト設定
	static constexpr int HANDLE_NUM = 3; // 左・正面・右向きの画像ハンドル
	static constexpr int SPRITE_W = 8;
	static constexpr int SPRITE_H = 8;
	static constexpr int PLAYER_SCALE = 8; // 描画時の拡大倍率(元画像に対する倍率)
	int playerHandles[HANDLE_NUM];
	int currentPlayerHandle;

	// 移動
	int x, y;
	int speed;

	// 射撃
	int currentBulletIndex = 2;
	int shotCoolDown = 0;
	Bullet bullets[MAX_BULLETS];

	// HP・無敵
	int hp;
	int hpGaugeLength; // HPゲージの長さ・枠の調整に使う
	bool isActive = true;
	int invincibleTimer = 0; // 無敵状態の切り替えに使う
	static constexpr int INVINCIBLE_DURATION = 60; // 無敵時間
	static constexpr int BLINK_INTERVAL = 8;       // 点滅間隔

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
	static constexpr int EFFECT_DURATION = 6; // 表示フレーム数
	static int explosionHandles[FRAME_NUM];

	// 内部処理
	void Move();
	void Shot();
	void ChangeHandle();
	void ClampPosition();
	void ChangeBullet();
};