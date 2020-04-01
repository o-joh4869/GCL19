#include"Player.h"
#include"../../Tool/KeyManager.h"
#include<DxLib.h>

using namespace Scene::Game;

Player::Player(const Vector2<float> &pos) :
	mPos(pos),
	mHP(3),
	mRadius(20)
{
}

void Player::update() {
	Vector2<float> dPos(0.0f, 0.0f);
	if (gKey[KEY_INPUT_LEFT] > 0) dPos -= Vector2<float>(1.0f, 0.0f);
	if (gKey[KEY_INPUT_UP] > 0) dPos -= Vector2<float>(0.0f, 1.0f);
	if (gKey[KEY_INPUT_RIGHT] > 0) dPos += Vector2<float>(1.0f, 0.0f);
	if (gKey[KEY_INPUT_DOWN] > 0) dPos += Vector2<float>(0.0f, 1.0f);
	mPos += dPos.getNormalized() * 5.0f;
}
void Player::draw() const {
	DrawCircle((int)mPos[0], (int)mPos[1], (int)mRadius, GetColor(0, 0, 255));
}