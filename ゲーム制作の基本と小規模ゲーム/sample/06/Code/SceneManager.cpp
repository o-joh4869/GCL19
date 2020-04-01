#include"SceneManager.h"
#include"Title.h"
#include"Game.h"

SceneManager::SceneManager() :
	mGameMode(GAMEMODE_TITLE)
{
	mScene[GAMEMODE_TITLE] = std::make_unique<Title>();
	mScene[GAMEMODE_GAME] = std::make_unique<Game>();
}

void SceneManager::changeScene(const GameMode &next) {
	mGameMode = next;
}


void SceneManager::update() {
	mScene[mGameMode]->update();
}


SceneManager gSceneManager;