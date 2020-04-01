#include"./Manager.h"
#include"./Player.h"
#include"./Enemy/Manager.h"
#include"./Enemy/Base.h"
#include<DxLib.h>

using namespace Scene::Game;

Manager::Manager() :
	mPlayer(new Player()),
	mEnemyManager(new Enemy::Manager())
{
}

Manager::~Manager() {
	delete mPlayer;
	delete mEnemyManager;
}

void Manager::update() {
	mPlayer->update();
	mEnemyManager->update(mPlayer);
	mPlayer->draw();
	mEnemyManager->draw();

	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", mPlayer->getHP());
}