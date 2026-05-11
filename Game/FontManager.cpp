#include "FontManager.h"
#include "DxLib.h"

int FontManager::titleFont;
int FontManager::playingFont;
int FontManager::uiFont;
int FontManager::gameoverFont;
int FontManager::scoreFont;

void FontManager::Load() {
	titleFont = CreateFontToHandle(NULL, 64, 3);
	playingFont = CreateFontToHandle(NULL, 25, 3);
	uiFont = CreateFontToHandle(NULL, 25, 3);
	gameoverFont = CreateFontToHandle(NULL, 60, 3);
	scoreFont = CreateFontToHandle(NULL, 35, 3);
}

void FontManager::Unload() {
    DeleteFontToHandle(titleFont);
	DeleteFontToHandle(playingFont);
    DeleteFontToHandle(uiFont);
	DeleteFontToHandle(gameoverFont);
    DeleteFontToHandle(scoreFont);
}