#pragma once

class BackGround {
public:
	BackGround();
	void Update();
	void Draw();

private:
	int backHandle;
	int scrollY = 0; // ”wŒi‰æ‘œ‚Ì¶ãÀ•W
	static constexpr int SCROLL_SPEED = 2;
};