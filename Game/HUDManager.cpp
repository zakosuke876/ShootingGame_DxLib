#include "HUDManager.h"
#include "GameConfig.h"
#include "DxLib.h"

void HUDManager::Draw(const Player& player, const ScoreManager& score) const {
	score.ScoreTextDraw();
	player.DrawPlayerHp();
	DrawBulletUI(player);
}

void HUDManager::DrawBulletUI(const Player& player) const {

	// ’eUI‚ğc‚É•À‚×‚Ä•`‰æ
	for (int i = 0; i < Bullet::GetBulletNUM(); i++)
	{
		DrawBox(
			BULLET_UI_BASE_X - BULLET_UI_MARGIN,
			BULLET_UI_BASE_Y + i * BULLET_UI_SPACE - BULLET_UI_MARGIN,
			BULLET_UI_BASE_X + BULLET_UI_W,
			BULLET_UI_BASE_Y + i * BULLET_UI_SPACE + BULLET_UI_Y + BULLET_UI_MARGIN,
			GetColor(255, 0, 0),
			FALSE);

		// ‘€ìƒ{ƒ^ƒ“‚ğ•\¦
		DrawFormatString(KEY_LABEL_X, KEY_LABEL_Y + i  * BULLET_UI_SPACE, GetColor(255, 0, 0), "%d", i + 1, TRUE);

		// ’e‚Ì‰æ‘œ‚ğ•\¦
		DrawRectExtendGraph(
			BULLET_UI_BASE_X,
			BULLET_UI_BASE_Y + i * BULLET_UI_SPACE,
			BULLET_UI_BASE_X + BULLET_UI_W,
			BULLET_UI_BASE_Y + BULLET_UI_Y + i * BULLET_UI_SPACE,
			0, 0, BULLET_SPRITE_W, BULLET_SPRITE_H, Bullet::GetBulletHandle(0 + i), TRUE);
	}

	DrawString(BULLET_TYPE_TEXT_X, BULLET_TYPE_TEXT_Y, "BulletType", GetColor(255, 0, 0));

	// Œ»İ‘I‘ğ’†‚Ì’e‚ğ•\¦
	DrawRectExtendGraph(
		CURRENT_BULLET_IMAGE_X,
		CURRENT_BULLET_IMAGE_Y,
		CURRENT_BULLET_IMAGE_X + CURRENT_BULLET_IMAGE_W,
		CURRENT_BULLET_IMAGE_Y + CURRENT_BULLET_IMAGE_H,
		0, 0, 8, 7, Bullet::GetBulletHandle(player.GetCurrentBulletIndex()), TRUE); // ‘I‘ğ’†‚Ì’e‚ğ•\¦

	// ‘I‘ğ’†‚Ì’e‚ğˆÍ‚Ş˜g‚ğ•`‰æ
	DrawBox(
		CURRENT_BULLET_BOX_X - CURRENT_BULLET_BOX_MARGIN,
		CURRENT_BULLET_BOX_Y - CURRENT_BULLET_BOX_MARGIN,
		CURRENT_BULLET_BOX_X + CURRENT_BULLET_IMAGE_W + CURRENT_BULLET_BOX_MARGIN,
		CURRENT_BULLET_BOX_Y + CURRENT_BULLET_IMAGE_H + CURRENT_BULLET_BOX_MARGIN,
		GetColor(255, 0, 0), FALSE);
}