#pragma once

class SoundManager {
public:
	// サウンドリソースの読み込み
	static void Load();

	// サウンドリソースの開放
	static void Unload();

	// 効果音取得
	static int GetExplosionSound() { return explosionSoundHandle; }
	static int GetShotSound() { return shotSoundHandle; }
	static int GetHitSound() { return hitSoundHandle; }
	static int GetReflectSound() { return reflectSoundHandle; }

	// BGM取得
	static int GetTitleBGM() { return titleBgmHandle; }
	static int GetPlayBGM() { return playBgmHandle; }
	static int GetGameOverBGM() { return gameOverBgmHandle; }

private:
	static int explosionSoundHandle; // 死亡時の爆発効果音
	static int shotSoundHandle; // 自機・敵の攻撃効果音
	static int hitSoundHandle; // 攻撃ヒット効果音
	static int reflectSoundHandle; // 攻撃反射効果音

	static int titleBgmHandle;
	static int playBgmHandle;
	static int gameOverBgmHandle;
};