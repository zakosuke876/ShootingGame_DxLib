#pragma once

class FontManager {
public:
	// フォントリソースの管理
	static void Load();
	static void Unload();

	// フォント取得
	static int GetTitleFont() { return titleFont; }
	static int GetPlayingFont() { return playingFont; }
	static int GetUIFont() { return uiFont; }
	static int GetGameoverFont() { return gameoverFont; }
	static int GetScoreFont() { return scoreFont; }

private:
	static int titleFont;
	static int playingFont;
	static int uiFont;
	static int gameoverFont;
	static int scoreFont;
};