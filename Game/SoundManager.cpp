#include "SoundManager.h"
#include "DxLib.h"

int SoundManager::explosionSoundHandle;
int SoundManager::shotSoundHandle;
int SoundManager::hitSoundHandle;
int SoundManager::reflectSoundHandle;
int SoundManager::playBgmHandle;
int SoundManager::gameOverBgmHandle;
int SoundManager::titleBgmHandle;

void SoundManager::Load() {
	explosionSoundHandle = LoadSoundMem("sounds/Explosion.mp3");
	ChangeVolumeSoundMem(100, explosionSoundHandle);

	shotSoundHandle = LoadSoundMem("sounds/Shot.mp3");
	ChangeVolumeSoundMem(100, shotSoundHandle);

	hitSoundHandle = LoadSoundMem("sounds/Hit.mp3");
	ChangeVolumeSoundMem(100, hitSoundHandle);

	reflectSoundHandle = LoadSoundMem("sounds/BulletMirror.mp3");
	ChangeVolumeSoundMem(120, reflectSoundHandle);

	playBgmHandle = LoadSoundMem("sounds/PlayBGM.mp3");
	ChangeVolumeSoundMem(100, playBgmHandle);

	gameOverBgmHandle = LoadSoundMem("sounds/GameOverBGM.mp3");
	ChangeVolumeSoundMem(200, gameOverBgmHandle);

	titleBgmHandle = LoadSoundMem("sounds/TitleBGM.mp3");
	ChangeVolumeSoundMem(100, titleBgmHandle);
}

void SoundManager::Unload() {
	DeleteSoundMem(explosionSoundHandle);
	DeleteSoundMem(shotSoundHandle);
	DeleteSoundMem(hitSoundHandle);
	DeleteSoundMem(reflectSoundHandle);
	DeleteSoundMem(playBgmHandle);
	DeleteSoundMem(gameOverBgmHandle);
	DeleteSoundMem(titleBgmHandle);
}