#pragma once
#include"../../../Tool/Vector2.h"
namespace Scene {
	namespace Game {
		class Player;
		namespace Enemy {
			class Base {
			public:
				Base(const Vector2<float> &pos = Vector2<float>());
			protected:
				Base(const Vector2<float> &pos, const float &radius);
			public:
				virtual ~Base() = default;
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
		}
	}
}