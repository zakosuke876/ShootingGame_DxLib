#include "GameManager.h"
#include "SoundManager.h"
#include "DxLib.h"

void GameManager::UpdateTitle(Player& player, EnemyManager& enemyManager, ScoreManager& scoreManager) {
	// スペースキーでゲーム開始
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		// 各オブジェクトをリセット
		player = Player();
		enemyManager = EnemyManager();
		scoreManager = ScoreManager();

		StopSoundMem(SoundManager::GetTitleBGM());
		StopSoundMem(SoundManager::GetPlayBGM());
		PlaySoundMem(SoundManager::GetPlayBGM(), DX_PLAYTYPE_LOOP);

		// ゲーム開始状態へ遷移
		state = GameState::Playing;
	}
}

void GameManager::UpdatePlaying(Player& player, EnemyManager& enemyManager, ScoreManager& scoreManager, RankingManager& rankingManager) {
	player.Update();

	enemyManager.Update(player);

	// 弾と敵の当たり判定
	enemyManager.CheckBulletHit(
		player.GetBullets(),
		Player::MAX_BULLETS,
		scoreManager);

	// プレイヤーと敵・敵弾の当たり判定
	bool isDead = enemyManager.CheckPlayerHit(player) || enemyManager.CheckEnemyBulletHit(player);

	// プレイヤー死亡時
	if (isDead)
	{
		// 死亡演出状態へ遷移、ランキングにスコアを記録
		state = GameState::Dying;
		rankingManager.AddScore(scoreManager.GetScore());
	}
}

void GameManager::UpdateDying(Player& player) {
	// 爆発演出更新
	player.Update();

	// 爆発演出終了後ゲームオーバーへ遷移
	if (player.IsExplosionFinished())
	{
		state =  GameState::GameOver;
		StopSoundMem(SoundManager::GetPlayBGM());
		StopSoundMem(SoundManager::GetGameOverBGM());
		PlaySoundMem(SoundManager::GetGameOverBGM(), DX_PLAYTYPE_BACK);
	}
}

void GameManager::UpdateGameOver(RankingManager& rankingManager) {
	// エンターキーでタイトルへ戻る
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		state = GameState::Title;
		StopSoundMem(SoundManager::GetGameOverBGM());
		StopSoundMem(SoundManager::GetTitleBGM());
		PlaySoundMem(SoundManager::GetTitleBGM(), DX_PLAYTYPE_LOOP);
	}

	// ランキングを更新
	rankingManager.Update();
}