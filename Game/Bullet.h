#pragma once
#include "CollisionUtil.h"

class Bullet {
public:
	// リソース管理
	static void LoadResources();
	static int GetBulletHandle(int index) { return bulletHandles[index]; }
	static int GetBulletNUM() { return BULLET_NUM; }

	// 初期化・状態管理
	Bullet();
	void Init(int startX, int startY, int bulletTypeNum);
	void Deactivate() { isActive = false; }
	bool IsActive() const { return isActive; }
	int GetBulletType() const { return bulletType; }

	// 座標・サイズ取得
	Rect GetRect() const {
		return { x, y, SPRITE_W * BULLET_SCALE, SPRITE_H * BULLET_SCALE };
	}
	static int GetHalfW() { return (SPRITE_W * BULLET_SCALE) / 2; }
	static int GetHeight() { return SPRITE_H * BULLET_SCALE; }

	// 更新・描画
	void Update();
	void Draw() const;
	
private:
	// スプライト設定
	static constexpr int BULLET_NUM = 4; // 弾の種類
	static constexpr int SPRITE_W = 8;
	static constexpr int SPRITE_H = 24;
	static constexpr int BULLET_SCALE = 3;
	static int bulletHandles[BULLET_NUM];

	// 状態
	int x = 0;
	int y = 0;
	int vY = -30;
	int currentBulletHandle;
	int bulletType = 0;
	bool isActive = false;
};