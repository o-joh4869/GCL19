#pragma once
#include"Enemy.h"

class EnemyA : public Enemy {
public:
	EnemyA(const Vector2<float> &pos = Vector2<float>());
	virtual ~EnemyA() = default;
	virtual void update(const Vector2<float> &playerPos) override;
	virtual void draw() const override;
	virtual bool judge(Player *const &player) const override;
};