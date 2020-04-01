#pragma once
#include"../Base.h"

namespace Scene { namespace Game {
	class State;
namespace Play {
	class Manager : public Scene::Game::Base {
	public:
		Manager(Scene::Game::State *state);
		Scene::Base *update() override;

	private:
		State *mState;
	};
}}}