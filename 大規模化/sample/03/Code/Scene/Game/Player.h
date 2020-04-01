#pragma once
#include"../../Tool/Vector2.h"
namespace Scene {
	namespace Game {
		class Player {
		public:
			Player(const Vector2<float> &pos = Vector2<float>());
		private:
			Vector2<float> mPos;
			float mRadius;
			int mHP;
		public:
			void update();
			void draw() const;
			const auto &getPos() const {
				return mPos;
			}
			const auto &getRadius() const {
				return mRadius;
			}
			const auto &getHP() const {
				return mHP;
			}
			void decHP() {
				mHP--;
			}
		};
	}
}