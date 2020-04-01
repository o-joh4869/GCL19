#include"Manager.h"

#include"../State.h"
#include"../Player.h"
#include"../Enemy/Manager.h"

#include<DxLib.h>

using namespace Scene::Game::Play;

Manager::Manager(Scene::Game::State *state) : 
	Scene::Game::Base(),
	mState(state)
{
}

Scene::Base *Manager::update() {

	mState->player->update();
	mState->enemyManager->update(mState->player);
	mState->player->draw();
	mState->enemyManager->draw();

	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", mState->stageID);

	return this;
}