#include"Title.h"
#include"KeyManager.h"
#include"SceneManager.h"
#include"HandleManager.h"
#include<DxLib.h>

Title::Title() {

}

void Title::update() {
	DrawGraph(0, 0, gHandle[GRHANDLE_TITLE], false);
	if (gKey[KEY_INPUT_SPACE] == -1) gSceneManager.changeScene(SceneManager::GAMEMODE_GAME);
}