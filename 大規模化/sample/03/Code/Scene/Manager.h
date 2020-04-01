#pragma once
#include<memory>
#include<array>
namespace Scene {
	class Base;

	class Manager {
	public:
		Manager();
		enum GameMode {
			GAMEMODE_TITLE,
			GAMEMODE_GAME,

			GAMEMODE_SIZE
		};
		void changeScene(const GameMode &next);
		void update();
	private:
		std::array<std::unique_ptr<Base>, static_cast<size_t>(GAMEMODE_SIZE)> mScene;
		GameMode mGameMode;
	};
}

extern Scene::Manager gSceneManager;
