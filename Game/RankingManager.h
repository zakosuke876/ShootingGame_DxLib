#pragma once
#include "GameConfig.h"

class RankingManager {
public:
	void AddScore(int score);
	void Update();
	void Draw() const;

private:
	// ランキングデータ
	static constexpr int RANKING_NUM = 3;
	int ranking[RANKING_NUM] = { 1000, 500, 300 }; // スコアを保存する配列
	int newRank = RANKING_NUM + 1; // 初期状態は圏外
	
	// 描画設定
	static constexpr int BASE_X = GameConfig::screen_W / 2 + 30; // 中央から少し左にずらす
	static constexpr int BASE_Y = GameConfig::screen_H / 2 + 30; // 中央から少し下にずらす
	static constexpr int LINE_WIDTH = 100; // 中央からずらす値(X)
	static constexpr int LINE_HEIGHT = 100; // 中央からずらす値(Y)
	
	// 点滅
	int blinkTimer = 0;
	static constexpr int BLINK_INTERVAL = 30; // 点滅間隔
};