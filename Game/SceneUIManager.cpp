#include "SceneUIManager.h"
#include "FontManager.h"
#include "DxLib.h"

void SceneUIManager::DrawTitle() const {
	//タイトル描画
	DrawStringToHandle(
		TITLE_LABEL_X,
		TITLE_LABEL_Y,
		"シューティングゲーム",
		GetColor(255, 0, 255),
		FontManager::GetGameoverFont());

	DrawStringToHandle(
		START_MESSAGE_X,
		START_MESSAGE_Y,
		"Press SPACE to START!!!",
		GetColor(255, 0, 255),
		FontManager::GetUIFont());
}

void SceneUIManager::DrawGameOver(const ScoreManager& score) const {
	DrawStringToHandle(
		GAMEOVER_MESSAGE_X,
		GAMEOVER_MESSAGE_Y,
		"GAME OVER",
		GetColor(255, 0, 255),
		FontManager::GetGameoverFont());

	// スコア表示
	DrawFormatStringToHandle(
		SCORE_TEXT_X,
		SCORE_TEXT_Y,
		GetColor(255, 0, 255),
		FontManager::GetScoreFont(),
		"Score : %d",
		score.GetScore());

	DrawStringToHandle(
		TITLE_BACK_TEXT_X,
		TITLE_BACK_TEXT_Y,
		"Press ENTER to TitleBack",
		GetColor(255, 0, 255),
		FontManager::GetUIFont());
}