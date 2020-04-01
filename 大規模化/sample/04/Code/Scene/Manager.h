#pragma once
#include<memory>
#include<array>
namespace Scene {
	class Base;

	class Manager {
	public:
		Manager();
		void update();
	private:
		std::unique_ptr<Base> mScene;
	};
}

extern Scene::Manager gSceneManager;
