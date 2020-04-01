#pragma once
#include"./Base.h"
namespace Scene { namespace Game { 
	class Player;
namespace Enemy {
	class A : public Base {
	public:
		A(const Vector2<float> &pos = Vector2<float>());
		virtual ~A() = default;
		virtual void update(const Vector2<float> &playerPos) override;
		virtual void draw() const override;
		virtual bool judge(Player *const &player) const override;
	};
}}}