#include "ScoreManager.h"
#include "GameConfig.h"
#include "DxLib.h"

void ScoreManager::AddScore(int value) {
	score += value;
}

void ScoreManager::ScoreTextDraw() const {
	DrawFormatString(SCORE_TEXT_X, SCORE_TEXT_Y, GetColor(255, 255, 0), "Score : %d", score);
}