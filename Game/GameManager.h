#pragma once
#include "Player.h"
#include "EnemyManager.h"
#include "ScoreManager.h"
#include "RankingManager.h"

// ƒQ[ƒ€‚Ìó‘ÔŠÇ—
enum class GameState {
	Title,
	Playing,
	Dying, // €–S‰‰o’†
	GameOver,
};

class GameManager {
public:
	GameState GetState() const { return state; }

	void UpdateTitle(Player& player, EnemyManager& enemyManager, ScoreManager& scoreManager);
	void UpdatePlaying(Player& player, EnemyManager& enemyManager, ScoreManager& scoreManager, RankingManager& rankingManager);
	void UpdateDying(Player& player);
	void UpdateGameOver(RankingManager& rankingManager);

	void SetState(GameState newState) { state = newState; }

private:
	GameState state = GameState::Title;
};