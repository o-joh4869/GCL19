#include"Game.h"
#include<DxLib.h>

Game::Game() :
	mPlayer(),
	mEnemyManager()
{
}

void Game::update() {
	mPlayer.update();
	mEnemyManager.update(&mPlayer);
	mPlayer.draw();
	mEnemyManager.draw();

	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", mPlayer.getHP());
}