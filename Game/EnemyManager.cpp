#include "EnemyManager.h"
#include "SoundManager.h"
#include "GameConfig.h"
#include "DxLib.h"
#include <algorithm>

int EnemyManager::explosionHandles[FRAME_NUM];

EnemyManager::EnemyManager() {
	
}

void EnemyManager::LoadResources() {
	LoadDivGraph("images/Explosion.png", 4, 4, 1, 8, 8, explosionHandles);
}

void EnemyManager::Update(Player& player) {
	Spawn();
	for (auto& e : enemies)
	{
		e.Update(player.GetX(), player.GetY());

		// 敵が撃つタイミングなら弾を生成する
		if (e.IsActive() && e.Shot())
		{
			bullets.emplace_back(e.GetBulletStartX(), e.GetBulletStartY(), player.GetX(), player.GetY());
			PlaySoundMem(SoundManager::GetShotSound(), DX_PLAYTYPE_BACK);
		}
	}

	// 弾の更新
	for (auto& b : bullets)
	{
		b.Update();
	}

	 // h非アクティブな弾の削除
	bullets.erase(
		std::remove_if(bullets.begin(), bullets.end(),
			[](const EnemyBullet& b) { return !b.IsActive(); }),
		bullets.end()
	);

	// 爆発エフェクト更新
	for (auto& exp : explosions)
	{
		if (!exp.isActive) continue;
		exp.frame++;

		if (exp.frame >= FRAME_NUM * EFFECT_DURATION)
		{
			exp.isActive = false;
		}
	}

	RemoveInactive();
}

void EnemyManager::Draw() {
	for (auto& e : enemies)
	{
		e.Draw();
	}

	for (auto& b : bullets)
	{
		b.Draw();
	}

	for (auto& exp : explosions)
	{
		if (!exp.isActive) continue;

		DrawExtendGraph(
			exp.x, exp.y,
			exp.x + EFFECT_W * EFFECT_SCALE,
			exp.y + EFFECT_H * EFFECT_SCALE,
			explosionHandles[exp.frame / EFFECT_DURATION], TRUE);
	}
}

bool EnemyManager::CheckPlayerHit(Player& player) {
	for (auto& e : enemies)
	{
		if (!e.IsActive()) continue;

		if (CheckHit(player.GetRect(), e.GetRect())) {
			player.Damage(); // ダメージを与える
			return !player.IsActive(); // 死亡したかどうかを返す
		}
	}

	return false;
}

void EnemyManager::CheckBulletHit(Bullet* bullets, int maxBullets, ScoreManager& score) {
	for (int i = 0; i < maxBullets; i++) {
		if (!bullets[i].IsActive()) continue;
		for (auto& e : enemies)
		{
			if (!e.IsActive()) continue;

			if (CheckHit(bullets[i].GetRect(), e.GetRect()))
			{
				if (bullets[i].GetBulletType() == e.GetEnemyType()) // 敵と弾の種類(色)が一致
				{
					e.Damage();

					if (!e.IsActive()) // 倒した場合にスコアを加算・エフェクトを生成
					{
						score.AddScore(e.GetScore());
						explosions.emplace_back(e.GetX(), e.GetY());
					}
				}
				else
				{
					// 種類が一致しない場合は反射
					PlaySoundMem(SoundManager::GetReflectSound(), DX_PLAYTYPE_BACK);
				}
				 
				bullets[i].Deactivate();
				break;
			}
		}
	}
}

bool EnemyManager::CheckEnemyBulletHit(Player& player)
{
	for (auto& e : enemies)
	{
		for (auto& b : bullets)
		{
			if (!b.IsActive()) continue;

			if (CheckHit(b.GetRect(), player.GetRect()))
			{
				b.Deactivate();
				player.Damage();

				if (!player.IsActive())
				{
					return true; // 死亡した
				}
			}
		}
	}
	return false;
}

void EnemyManager::Spawn() {
	spawnTimer++;
	if (spawnTimer >= SPAWN_INTERVAL) {
		int rx = GetRand(GameConfig::screen_W - 100) + 50;

		// 生成する敵の種類を決める
		int typeIndex = GetRand(Enemy::GetHandleNum() - 1);

		enemies.emplace_back(rx, -50, typeIndex);
		spawnTimer = 0;
	}
}

void EnemyManager::RemoveInactive() {
	// 非アクティブな敵と爆発エフェクトを削除
	enemies.erase(
		std::remove_if(enemies.begin(), enemies.end(),
			[](const Enemy& e) { return !e.IsActive(); }),
		enemies.end()
	);

	explosions.erase(
		std::remove_if(explosions.begin(), explosions.end(),
			[](const Explosion& exp) { return !exp.isActive; }),
		explosions.end()
	);
}