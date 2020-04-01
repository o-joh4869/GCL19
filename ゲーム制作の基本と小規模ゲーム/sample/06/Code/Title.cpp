#include"Title.h"
#include"KeyManager.h"
#include"SceneManager.h"
#include<DxLib.h>

Title::Title() {

}

void Title::update() {
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Title");
	if (gKey[KEY_INPUT_SPACE] == -1) gSceneManager.changeScene(SceneManager::GAMEMODE_GAME);
}