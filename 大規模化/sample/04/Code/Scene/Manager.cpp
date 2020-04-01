#include"Manager.h"
#include"Base.h"
#include"./Title/Manager.h"

using namespace Scene;

Manager::Manager() :
	mScene(std::make_unique<Title::Manager>())
{
}

void Manager::update() {
	Base *p = mScene->update();
	if (p != mScene.get()) mScene.reset(p);
}

Manager gSceneManager;