#include"Manager.h"
#include"Base.h"
#include"./Title/Manager.h"
#include"./State.h"

using namespace Scene;

Manager::Manager() :
	mState(new State()),
	mScene(std::make_unique<Title::Manager>(mState))
{
}

Manager::~Manager() {
	delete mState;
}

void Manager::update() {
	Base *p = mScene->update();
	if (p != mScene.get()) mScene.reset(p);
}

Manager gSceneManager;