#pragma once

class ScoreManager {
public:
	void AddScore(int value);
	void ScoreTextDraw() const;
	int GetScore() const { return score; }

private:
	int score = 0;
};