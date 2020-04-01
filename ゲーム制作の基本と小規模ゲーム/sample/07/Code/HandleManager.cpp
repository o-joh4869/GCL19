#include"HandleManager.h"
#include<DxLib.h>

HandleManager::HandleManager() {
}
void HandleManager::load() {
	mHandle[GRHANDLE_TITLE] = LoadGraph("./images/Title.png");
	//...
}
HandleManager gHandle;