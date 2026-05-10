#pragma once
#include "ScoreManager.h"
#include "GameConfig.h"

class SceneUIManager {
public:
	void DrawTitle() const;
	void DrawGameOver(const ScoreManager& score) const;

private:
	// ゲームのタイトル名を表示する座標
	static constexpr int TITLE_LABEL_X = 330;
	static constexpr int TITLE_LABEL_Y = 80;

	// 開始メッセージを表示する座標
	static constexpr int START_MESSAGE_X = 480;
	static constexpr int START_MESSAGE_Y = 360;

	// ゲームオーバーメッセージを表示する座標
	static constexpr int GAMEOVER_MESSAGE_X = 500;
	static constexpr int GAMEOVER_MESSAGE_Y = 80;

	static constexpr int SCORE_TEXT_X = 530;
	static constexpr int SCORE_TEXT_Y = 280;

	static constexpr int TITLE_BACK_TEXT_X = 480;
	static constexpr int TITLE_BACK_TEXT_Y = 680;
};