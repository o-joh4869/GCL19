#include"State.h"

#include"Player.h"
#include"Enemy/Manager.h"
#include"Enemy/Base.h"

using namespace Scene::Game;

State::State(const Scene::State *bstate) : 
	bState(bstate),
	player(new Player),
	enemyManager(new Enemy::Manager()),
	stageID(0)
{

}

State::~State() {
	delete player;
	delete enemyManager;
}