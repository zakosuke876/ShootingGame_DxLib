#include <algorithm>
#include "Player.h"
#include "Bullet.h"
#include "SoundManager.h"
#include "GameConfig.h"
#include "DxLib.h"

int Player::explosionHandles[FRAME_NUM];

// 初期化
Player::Player() {
	x = GameConfig::SCREEN_W / 2;
	y = GameConfig::SCREEN_H / 2;
	speed = 10;
	LoadDivGraph("images/Ships.png", 3, 3, 1, 8, 8, playerHandles);
	currentPlayerHandle = playerHandles[1];
	currentBulletIndex = 2;
	hp = 5;
	hpGaugeLength = hp - 1;
}

void Player::LoadResources() {
	LoadDivGraph("images/Explosion.png", 4, 4, 1, 8, 8, explosionHandles);
}

// 更新
void Player::Update() {
	// 爆発エフェクト関係
	for (auto& exp : explosions)
	{
		if (!exp.isActive) continue;

		exp.frame++;

		if (exp.frame >= FRAME_NUM * EFFECT_DURATION) {
			exp.isActive = false;
		}
	}

	if (!isActive) return;

	Move();
	ClampPosition();
	ChangeHandle();
	Shot();
	ChangeBullet();

	for (auto& b : bullets)
	{
		b.Update();
	}

	if (invincibleTimer > 0)
	{
		invincibleTimer--;
	}
}

void Player::Move() {
	int moveX = 0;
	int moveY = 0;

	if (CheckHitKey(KEY_INPUT_UP)) moveY--;
	if (CheckHitKey(KEY_INPUT_DOWN)) moveY++;
	if (CheckHitKey(KEY_INPUT_LEFT)) moveX--;
	if (CheckHitKey(KEY_INPUT_RIGHT)) moveX++;

	if (moveX != 0 && moveY != 0)
	{
		// 斜め入力の際に正規化
		x += (int)(moveX * speed / 1.41421f);
		y += (int)(moveY * speed / 1.41421f);
	}
	else
	{
		x += moveX * speed;
		y += moveY * speed;
	}
}

void Player::Shot() {
	if (shotCoolDown > 0)
	{
		shotCoolDown--;
		return;
	}

	if (CheckHitKey(KEY_INPUT_SPACE)) {
		for (Bullet& b : bullets) {
			if (!b.IsActive()) {
				int bx = x + (SPRITE_W * PLAYER_SCALE) / 2 - (Bullet::GetHalfW());
				int by = y - Bullet::GetHeight();

				b.Init(bx, by, currentBulletIndex);

				shotCoolDown = 10;
				PlaySoundMem(SoundManager::GetShotSound(), DX_PLAYTYPE_BACK);
				break;
			}
		}
	}
}

void Player::ChangeHandle() {
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		// 左向きの場合
		currentPlayerHandle = playerHandles[0];
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		// 右向きの場合
		currentPlayerHandle = playerHandles[2];
	}
	else
	{
		// 向きがニュートラル時は正面向き
		currentPlayerHandle = playerHandles[1];
	}
}

// 描画
void Player::Draw() const {

	for (auto& exp : explosions)
	{
		if (!exp.isActive) continue;

		DrawExtendGraph(exp.x, exp.y, exp.x + EFFECT_W * EFFECT_SCALE, exp.y + EFFECT_H * EFFECT_SCALE, explosionHandles[exp.frame / EFFECT_DURATION], TRUE);
	}

	if (!isActive) return;

	bool isInvincible = invincibleTimer > 0;

	if (isInvincible && (invincibleTimer / BLINK_INTERVAL) % 2 == 0) return;

	DrawExtendGraph(x, y, x + SPRITE_W * PLAYER_SCALE, y + SPRITE_H * PLAYER_SCALE, currentPlayerHandle, TRUE);
	
	for (auto& b : bullets) b.Draw();
}

/// <summary>
/// 移動範囲を制限する
/// </summary>
void Player::ClampPosition() {
	if (x < 0) x = 0;
	if (x > GameConfig::SCREEN_W - SPRITE_W * PLAYER_SCALE) x = GameConfig::SCREEN_W - SPRITE_W * PLAYER_SCALE;
	if (y < 0) y = 0;
	if (y > GameConfig::SCREEN_H - SPRITE_H * PLAYER_SCALE) y = GameConfig::SCREEN_H - SPRITE_H * PLAYER_SCALE;
}

void Player::ChangeBullet() {
	if (CheckHitKey(KEY_INPUT_1)) currentBulletIndex = 0;
	if (CheckHitKey(KEY_INPUT_2)) currentBulletIndex = 1;
	if (CheckHitKey(KEY_INPUT_3)) currentBulletIndex = 2;
	if (CheckHitKey(KEY_INPUT_4)) currentBulletIndex = 3;
}

void Player::Damage() {
	if (invincibleTimer > 0) return;
	
	hp--;

	PlaySoundMem(SoundManager::GetHitSound(), DX_PLAYTYPE_BACK);

	if (hp <= 0)
	{
		hp = 0;
		isActive = false;
		explosions.emplace_back(x, y);
		PlaySoundMem(SoundManager::GetExplosionSound(),DX_PLAYTYPE_BACK);
	}

	invincibleTimer = INVINCIBLE_DURATION; // 無敵時間設定
}

bool Player::IsExplosionFinished() const {
	if (explosions.empty()) return false;

	for (const auto& exp : explosions)
	{
		if (exp.isActive) return false;
	}

	return true;
}

void Player::DrawPlayerHp() const {
	int x = GameConfig::SCREEN_W - 1180;
	int y = GameConfig::SCREEN_H - 30;

	constexpr int BOX_W = 20; // 幅
	constexpr int SPACE = 5;  // 間隔

	DrawString(GameConfig::SCREEN_W - 1250, GameConfig::SCREEN_H - 30, "Energy", GetColor(255, 0, 0));

	// HPを表すBoxを描画
	for (int i = 0; i < hp; i++)
	{
		DrawBox(x + i * (BOX_W + SPACE), y, x + i * (BOX_W + SPACE) + BOX_W, y + BOX_W, GetColor(0, 255, 0), TRUE);
	}

	DrawBox(x - SPACE, y - SPACE, x + (hpGaugeLength) * (BOX_W + SPACE) + BOX_W + SPACE, y + BOX_W + SPACE, GetColor(255, 0, 0), FALSE);
}