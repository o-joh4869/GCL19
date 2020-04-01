#include"Enemy.h"
#include<DxLib.h>

Enemy::Enemy(const Vector2<float> &pos) :
	mPos(pos),
	mRadius(20)
{}
Enemy::Enemy(const Vector2<float> &pos, const float &radius) :
	mPos(pos),
	mRadius(radius)
{}
void Enemy::update(const Vector2<float> &playerPos) {
	mPos += Vector2<float>(0.0f, 1.0f);
}

void Enemy::draw() const {
	DrawCircle((int)mPos[0], (int)mPos[1], (int)mRadius, GetColor(255, 0, 0));
}

bool Enemy::judge(Player *const &player) const {
	bool flag = (mPos - player->getPos()).length() < (mRadius + player->getRadius());
	if (flag) player->decHP();
	return flag;
}