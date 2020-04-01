#pragma once
#include"../Base.h"
#include<memory>

namespace Scene {
	class State;
	namespace Game {
		class State;
		class Manager : public Scene::Base {
		public:
			Manager(Scene::State *state);
			Manager(const Manager&) = delete;
			Manager &operator= (const Manager &) = delete;
			virtual Scene::Base *update() override;
			virtual ~Manager();
		private:
			State *mState;
			std::unique_ptr<Scene::Base> mScene;
		};
	}
}