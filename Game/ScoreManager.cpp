#include "ScoreManager.h"
#include "GameConfig.h"
#include "DxLib.h"

void ScoreManager::AddScore(int value) {
	score += value;
}

void ScoreManager::ScoreTextDraw() const {
	DrawFormatString(GameConfig::screen_W - 1250, GameConfig::screen_H - 700, GetColor(255, 255, 0), "Score : %d", score);
}