#include"Game.h"
#include"Player.h"
#include"EnemyManager.h"
#include"Enemy.h"
#include<DxLib.h>

Game::Game() :
	mPlayer(new Player()),
	mEnemyManager(new EnemyManager())
{
}

Game::~Game() {
	delete mEnemyManager;
	delete mPlayer;
}

void Game::update() {
	mPlayer->update();
	mEnemyManager->update(mPlayer);
	mPlayer->draw();
	mEnemyManager->draw();

	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", mPlayer->getHP());
}

