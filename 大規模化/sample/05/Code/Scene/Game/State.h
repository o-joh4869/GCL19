#pragma once

namespace Scene {
	class State;
namespace Game {

	class Player;
	namespace Enemy {
		class Manager;
	}

	class State {
	public:
		State(const Scene::State *bstate);
		State(const State&) = delete;
		State &operator= (const State&) = delete;
		~State();
		const Scene::State *bState; //ã‚ÌŠK‘w‚ÌState

		Player *player;
		Enemy::Manager *enemyManager;

		int stageID;
	};
}}