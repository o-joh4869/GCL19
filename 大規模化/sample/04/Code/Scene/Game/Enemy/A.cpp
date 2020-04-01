#include"./A.h"
#include"../Player.h"
#include<DxLib.h>

using namespace Scene::Game::Enemy;

A::A(const Vector2<float> &pos) :
	Base(pos, 15.0f)
{}

void A::update(const Vector2<float> &playerPos) {
	mPos += (playerPos - mPos).getNormalized();
}

void A::draw() const {
	DrawCircle((int)mPos[0], (int)mPos[1], (int)mRadius, GetColor(0, 255, 0));
}

bool A::judge(Scene::Game::Player *const &player) const {
	bool flag = (mPos - player->getPos()).length() < (mRadius + player->getRadius());
	if (flag) player->decHP();
	return flag;
}