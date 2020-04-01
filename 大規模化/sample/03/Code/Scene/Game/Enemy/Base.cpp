#include"./Base.h"
#include"../Player.h"
#include<DxLib.h>

using namespace Scene::Game::Enemy;

Base::Base(const Vector2<float> &pos) :
	mPos(pos),
	mRadius(20)
{}
Base::Base(const Vector2<float> &pos, const float &radius) :
	mPos(pos),
	mRadius(radius)
{}
void Base::update(const Vector2<float> &playerPos) {
	mPos += Vector2<float>(0.0f, 1.0f);
}

void Base::draw() const {
	DrawCircle((int)mPos[0], (int)mPos[1], (int)mRadius, GetColor(255, 0, 0));
}

bool Base::judge(Scene::Game::Player *const &player) const {
	bool flag = (mPos - player->getPos()).length() < (mRadius + player->getRadius());
	if (flag) player->decHP();
	return flag;
}