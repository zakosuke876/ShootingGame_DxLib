#include "RankingManager.h"
#include "DxLib.h"
#include <algorithm>


void RankingManager::AddScore(int score) {

	// 何位に入るか調べる
	for (int i = 0; i < RANKING_NUM; i++)
	{
		if (score > ranking[i])
		{
			newRank = i + 1;
			break;
		}
	}

	// ランキング更新時にのみ記録更新
	if (newRank <= RANKING_NUM)
	{
		ranking[RANKING_NUM - 1] = score;

		// 降順に並び替える
		std::sort(ranking, ranking + RANKING_NUM, std::greater<int>());
	}

}

void RankingManager::Update() {
	// 更新時のみ点滅タイマーを進める
	if (newRank <= RANKING_NUM)
	{
		blinkTimer++;
	}
}

void RankingManager::Draw() const {

	// 1～3位までの記録を表示
	for (int i = 0; i < RANKING_NUM; i++)
	{
		DrawFormatString(BASE_X - LINE_WIDTH, BASE_Y + (i * LINE_HEIGHT), GetColor(255, 0, 255), "%d位Score : %d", i + 1, ranking[i]);
	}

	// 記録を更新していた場合にのみ表示
	if (newRank <= RANKING_NUM && (blinkTimer / BLINK_INTERVAL) % 2 == 0)
	{
		DrawFormatString(BASE_X - 100, BASE_Y - 140, GetColor(255, 0, 255), "ランキング更新");
	}	
}