#include"./Manager.h"
#include"../../Tool/KeyManager.h"
#include"../Manager.h"
#include"../../Tool/HandleManager.h"
#include"../Game/Manager.h"
#include<DxLib.h>

using namespace Scene::Title;

Manager::Manager() {

}

Scene::Base *Manager::update() {
	DrawGraph(0, 0, gHandle[GRHANDLE_TITLE], false);
	if (gKey[KEY_INPUT_SPACE] == -1) return (std::make_unique<Scene::Game::Manager>()).release();
	else return this;
}