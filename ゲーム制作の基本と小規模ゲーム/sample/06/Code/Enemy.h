#pragma once
#include"Player.h"

class Enemy {
public:
	Enemy(const Vector2<float> &pos = Vector2<float>());
protected:
	Enemy(const Vector2<float> &pos, const float &radius);
public:
	virtual ~Enemy() = default;
protected:
	Vector2<float> mPos;
	float mRadius;
public:
	virtual void update(const Vector2<float> &playerPos);
	virtual void draw() const;
	virtual bool judge(Player *const &player) const;
	const auto &getRadius() {
		return mRadius;
	}
};