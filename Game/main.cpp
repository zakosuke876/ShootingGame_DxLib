#include "GameConfig.h"
#include "Player.h"
#include "Bullet.h"
#include "EnemyManager.h"
#include "EnemyBullet.h"
#include "ScoreManager.h"
#include "RankingManager.h"
#include "FontManager.h"
#include "SoundManager.h"
#include "Background.h"
#include "GameManager.h"
#include "HUDManager.h"
#include "SceneUIManager.h"
#include "DxLib.h"


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(FALSE);
	SetGraphMode(GameConfig::SCREEN_W, GameConfig::SCREEN_H, 32);
	SetMainWindowText("Game");
	SetWaitVSyncFlag(FALSE);

	if (DxLib_Init() == -1) return -1;

	SetDrawMode(DX_DRAWMODE_NEAREST);

	SetDrawScreen(DX_SCREEN_BACK);

	// リソース読み込み
	FontManager::Load();
	int backGroundHandles[2];
	LoadDivGraph("images/BackGrounds.png", 2, 1, 2, 386, 256, backGroundHandles);

	{
		Bullet::LoadResources();
		Player::LoadResources();
		Enemy::LoadResources();
		EnemyBullet::LoadResources();
		EnemyManager::LoadResources();
		SoundManager::Load();

		PlaySoundMem(SoundManager::GetTitleBGM(), DX_PLAYTYPE_LOOP);

		// インスタンス生成
		Player player;
		EnemyManager enemyManager;
		ScoreManager scoreManager;
		RankingManager rankingManager;
		GameManager gameManager;
		BackGround backGround;
		HUDManager hudManager;
		SceneUIManager sceneUIManager;

		while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
		{
			LONGLONG start = GetNowHiPerformanceCount();

			ClearDrawScreen();

			// 更新
			switch (gameManager.GetState()) {
			case GameState::Title:

				gameManager.UpdateTitle(player, enemyManager, scoreManager);

				break;

			case GameState::Playing:

				backGround.Update();
				gameManager.UpdatePlaying(player, enemyManager, scoreManager, rankingManager);
				
				break;

			case GameState::Dying:

				gameManager.UpdateDying(player);
				
				break;

			case GameState::GameOver:

				gameManager.UpdateGameOver(rankingManager);
				break;

			default:

				break;
			}

			// 描画
			switch (gameManager.GetState()) {
			case GameState::Title:

				backGround.Draw();

				sceneUIManager.DrawTitle();

				break;

			case GameState::Playing:

				backGround.Draw();

				player.Draw();

				enemyManager.Draw();

				hudManager.Draw(player, scoreManager);

				break;

			case GameState::Dying:

				backGround.Draw();

				player.Draw();

				enemyManager.Draw();

				break;

			case GameState::GameOver:

				backGround.Draw();

				sceneUIManager.DrawGameOver(scoreManager);

				rankingManager.Draw();

				break;

			default:

				break;
			}

			ScreenFlip();

			// フレームレート制御
			while (GetNowHiPerformanceCount() - start < GameConfig::FRAME_TIME) {}
		}
	}

	
	FontManager::Unload();
	SoundManager::Unload();
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0 ;				// ソフトの終了 
}