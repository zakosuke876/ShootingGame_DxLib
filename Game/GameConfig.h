#pragma once

namespace GameConfig {
	constexpr int SCREEN_W = 1280; // 画面の横幅
	constexpr int SCREEN_H = 720;  // 画面の縦幅
	constexpr int TARGET_FPS = 60; // フレームレート
	constexpr int FRAME_TIME = 1000000 / TARGET_FPS; //	マイクロ秒単位のフレーム時間
}