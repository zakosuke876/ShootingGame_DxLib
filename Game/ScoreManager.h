#pragma once

class ScoreManager {
public:
	void AddScore(int value);
	void ScoreTextDraw() const;
	int GetScore() const { return score; }

private:
	int score = 0;
	static constexpr int SCORE_TEXT_X = 30;
	static constexpr int SCORE_TEXT_Y = 20;
};