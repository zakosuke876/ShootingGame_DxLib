#pragma once

struct Rect {
	int x, y, w, h;
};

// ‹éŒ`“¯Žm‚Ì“–‚½‚è”»’è
inline bool CheckHit(const Rect& a, const Rect& b) {
	return a.x + a.w > b.x &&
		   a.x < b.x + b.w &&
		   a.y + a.h > b.y &&
		   a.y < b.y + b.h;
}