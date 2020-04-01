#pragma once
#include"../Base.h"

namespace Scene {
	namespace Game {
		class Player;
		namespace Enemy {
			class Manager;
		}
		class Manager : public Scene::Base {
		public:
			Manager();
			Manager(const Manager&) = delete;
			Manager &operator= (const Manager &) = delete;
			virtual void update() override;
			virtual ~Manager();
		private:
			Player *mPlayer;
			Enemy::Manager *mEnemyManager;
		};
	}
}