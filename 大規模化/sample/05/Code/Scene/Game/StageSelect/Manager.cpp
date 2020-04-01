#include"Manager.h"
#include"../Play/Manager.h"
#include"../../../Tool/KeyManager.h"
#include"../State.h"
#include<DxLib.h>

using namespace Scene::Game::StageSelect;

Manager::Manager(Scene::Game::State *state) : 
	mState(state),
	mStageid(mState->stageID)
{

}

Scene::Base *Manager::update() {

	if (gKey[KEY_INPUT_LEFT] == 1) mStageid = 0;
	if (gKey[KEY_INPUT_RIGHT] == 1) mStageid = 1;

	DrawFormatString(5, 0, 0xffffff, "0 1");

	if (mStageid == 0) DrawFormatString(0, 0, 0xffffff, "\nª");
	else DrawFormatString(0, 0, 0xffffff, "\n  ª");

	if (gKey[KEY_INPUT_RETURN] == -1) {
		mState->stageID = mStageid;
		return (new Scene::Game::Play::Manager(mState));
	}
	else return this;
}