#pragma once
#include<memory>
#include<array>
namespace Scene {
	class Base;
	class State;

	class Manager {
	public:
		Manager();
		Manager(const Manager&) = delete;
		Manager &operator= (const Manager&) = delete;
		~Manager();
		void update();
	private:
		State *mState;
		std::unique_ptr<Base> mScene;
	};
}

extern Scene::Manager gSceneManager;
