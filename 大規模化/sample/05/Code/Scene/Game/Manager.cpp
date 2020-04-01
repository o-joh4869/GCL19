#include"./Manager.h"
#include"./Player.h"
#include"./Enemy/Manager.h"
#include"./Enemy/Base.h"
#include"Base.h"
#include"State.h"
#include"StageSelect/Manager.h"
#include<DxLib.h>

using namespace Scene::Game;

Manager::Manager(Scene::State *state) :
	mState(new State(state)),
	mScene(std::make_unique<StageSelect::Manager>(mState))
{
}

Manager::~Manager() {
	delete mState;
}

Scene::Base *Manager::update() {

	Scene::Base *p = mScene->update();
	if (p != mScene.get()) {
		if (dynamic_cast<Scene::Game::Base*>(p) != nullptr) {
			mScene.reset(p);
		}
		else return p;
	}
	return this;
}