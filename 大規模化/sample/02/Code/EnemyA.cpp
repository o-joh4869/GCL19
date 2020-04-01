#include"EnemyA.h"
#include"Player.h"
#include<DxLib.h>

EnemyA::EnemyA(const Vector2<float> &pos) :
	Enemy(pos, 15.0f)
{}

void EnemyA::update(const Vector2<float> &playerPos) {
	mPos += (playerPos - mPos).getNormalized();
}

void EnemyA::draw() const {
	DrawCircle((int)mPos[0], (int)mPos[1], (int)mRadius, GetColor(0, 255, 0));
}

bool EnemyA::judge(Player *const &player) const {
	bool flag = (mPos - player->getPos()).length() < (mRadius + player->getRadius());
	if (flag) player->decHP();
	return flag;
}