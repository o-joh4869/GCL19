#include"./Manager.h"
#include"../../Tool/KeyManager.h"
#include"../Manager.h"
#include"../../Tool/HandleManager.h"
#include<DxLib.h>

using namespace Scene::Title;

Manager::Manager() {

}

void Manager::update() {
	DrawGraph(0, 0, gHandle[GRHANDLE_TITLE], false);
	if (gKey[KEY_INPUT_SPACE] == -1) gSceneManager.changeScene(Scene::Manager::GAMEMODE_GAME);
}