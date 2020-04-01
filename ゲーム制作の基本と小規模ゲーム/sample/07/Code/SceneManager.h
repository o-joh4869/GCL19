#pragma once
#include"SceneBase.h"
#include<array>

class SceneManager {
public:
	SceneManager();
	enum GameMode {
		GAMEMODE_TITLE,
		GAMEMODE_GAME,

		GAMEMODE_SIZE
	};
	void changeScene(const GameMode &next);
	void update();
private:
	std::array<std::unique_ptr<SceneBase>, static_cast<size_t>(GAMEMODE_SIZE)> mScene;
	GameMode mGameMode;
};

extern SceneManager gSceneManager;