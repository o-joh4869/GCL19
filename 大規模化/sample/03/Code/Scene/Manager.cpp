#include"Manager.h"
#include"Base.h"
#include"./Title/Manager.h"
#include"./Game./Manager.h"

using namespace Scene;

Manager::Manager() :
	mGameMode(GAMEMODE_TITLE)
{
	mScene[GAMEMODE_TITLE] = std::make_unique<Title::Manager>();
	mScene[GAMEMODE_GAME] = std::make_unique<Game::Manager>();
}

void Manager::changeScene(const GameMode &next) {
	mGameMode = next;
}


void Manager::update() {
	mScene[mGameMode]->update();
}

Manager gSceneManager;